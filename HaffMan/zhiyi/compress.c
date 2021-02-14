/*************************************************************************
	> File Name: compress.c
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 12时50分15秒
 ************************************************************************/

#include "./include/head.h"

TmpNode *tmp_nodes;
unsigned int i, j;
unsigned int char_kinds;		// 字符种类
unsigned char char_temp;		// 暂存8bits字符
unsigned long file_len = 0;
FILE *infile, *outfile;
TmpNode node_temp;
unsigned int node_num;
HufNode *huf_tree;
char code_buf[MAX_SIZE] = "\0";		// 待存编码缓冲区
unsigned int code_len;
unsigned long long linefeed_num = 0; //换行符的数目

void initNode() {
    /*
	** 动态分配MAX_SIZE个结点，暂存字符频度，
	** 统计并拷贝到树结点后立即释放
	*/
    tmp_nodes = (TmpNode *)malloc(MAX_SIZE * sizeof(TmpNode));		

	// 初始化暂存结点
    for (int i = 0; i < MAX_SIZE; i++) {
        tmp_nodes[i].weight = 0;
        tmp_nodes[i].uch = (unsigned char)i;//数组的下标与字符相对应
    }
    return ;
}

//获取文本信息
int get_file_info(const char *inFileName) {
    // 遍历文件，获取字符频度
    if((infile = fopen(inFileName, "r")) == NULL) {
        perror("fopen failed");
        return -1;
    }
	// 判断输入文件是否存在
	fread((char *)&char_temp, sizeof(unsigned char), 1, infile);		// 读入一个字符

	while(!feof(infile)) {//判断文件是否结束,结束返回非0值, 没结束返回0
		++tmp_nodes[char_temp].weight;		// 统计下标对应字符的权重，利用数组的随机访问快速统计字符频度
		++file_len;
        if (char_temp == '\n') linefeed_num += 1;
		fread((char *)&char_temp, sizeof(unsigned char), 1, infile);		// 读入一个字符
	}
	fclose(infile);
    return 1;
}
//统计文本有多少种字符
int get_char_kinds() {
    for(int i = 0; i < MAX_SIZE; ++i) {
		if(tmp_nodes[i].weight == 0) return i;
    }
    return MAX_SIZE;
}

int black_file(const char *outFileName) {
    if ((outfile = fopen(outFileName, "w")) == NULL) {
        perror("fopen outfile failed");
        return -1;
    }					// 打开压缩后将生成的文件
    DBG(BLUE"<open outfile>"NONE" : open outfile success...\n");
	fwrite((char *)&char_kinds, sizeof(unsigned int), 0, outfile);		// 写入字符种类
	free(tmp_nodes);
	fclose(outfile);
    DBG(RED"<BLACK FILE>"NONE" : black file input success...\n");
    return 1;
}

int single_char(const char *outFileName) {
    printf("only a info\n");
    if ((outfile = fopen(outFileName, "w")) == NULL) {
        perror("fopen outfile failed");
        return -1;
    }					// 打开压缩后将生成的文件
	fwrite((char *)&char_kinds, sizeof(unsigned int), 1, outfile);		// 写入字符种类
	fwrite((char *)&tmp_nodes[0].uch, sizeof(unsigned char), 1, outfile);		// 写入唯一的字符
	fwrite((char *)&tmp_nodes[0].weight, sizeof(unsigned long), 1, outfile);		// 写入字符频度，也就是文件长度
	free(tmp_nodes);
	fclose(outfile);
    return 1;
}

void out_file_info(const char *outFileName) {
    // 写入字符和相应权重，供解压时重建哈夫曼树
	outfile = fopen(outFileName, "w");					// 打开压缩后将生成的文件
	fwrite((char *)&char_kinds, sizeof(unsigned int), 1, outfile);		// 写入字符种类
	for(i = 0; i < char_kinds; ++i) {
		fwrite((char *)&huf_tree[i].uch, sizeof(unsigned char), 1, outfile);			// 写入字符（已排序，读出后顺序不变）
		fwrite((char *)&huf_tree[i].weight, sizeof(unsigned long), 1, outfile);		// 写入字符对应权重
	}

	// 紧接着字符和权重信息后面写入文件长度和字符编码
	fwrite((char *)&file_len, sizeof(unsigned long), 1, outfile);		// 写入文件长度
    return ;
}

//获取中值
unsigned long middle(unsigned long  a, unsigned long b, unsigned long c) {
    if (a > b)  swap(a, b);
    if (a > c)  swap(a, c);
    if (b > c) swap(b, c);
    return b;
}

//快速排序
void quickSort(TmpNode *tmp_nodes, int l, int r) {
    while(l < r) {
        int x = l, y = r, z = (l + r) >> 1;
        unsigned long midNum = middle(tmp_nodes[x].weight, tmp_nodes[z].weight, tmp_nodes[y].weight);
        do {
            while(x <= y && tmp_nodes[x].weight > midNum) x++;
            while(x <= y && tmp_nodes[y].weight < midNum) y--;
            if (x <= y) {
                swap(tmp_nodes[x], tmp_nodes[y]);
                x++, y--;
            }
        }while(x <= y);
        quickSort(tmp_nodes, x, r);
        r = y;
    }
    return ;
}

void out_code(const char *inFileName) {
    infile = fopen(inFileName, "r");		// 以二进制形式打开待压缩的文件
	fread((char *)&char_temp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
	while(!feof(infile)) {
		// 匹配字符对应编码
		for(i = 0; i < char_kinds; ++i) {
			if(char_temp == huf_tree[i].uch) {
				strcat(code_buf, huf_tree[i].code);
            }
        }
		// 以8位（一个字节长度）为处理单元
		while(strlen(code_buf) >= 8) {
			char_temp = '\0';		// 清空字符暂存空间，改为暂存字符对应编码
			for(i = 0; i < 8; ++i) {
				char_temp <<= 1;		// 左移一位，为下一个bit腾出位置
				if(code_buf[i] == '1')
					char_temp |= 1;		// 当编码为"1"，通过或操作符将其添加到字节的最低位
			}
			fwrite((char *)&char_temp, sizeof(unsigned char), 1, outfile);		// 将字节对应编码存入文件
			strcpy(code_buf, code_buf+8);		// 编码缓存去除已处理的前八位
		}
		fread((char *)&char_temp, sizeof(unsigned char), 1, infile);     // 每次读取8bits
    }
	// 处理最后不足8bits编码
	code_len = strlen(code_buf);
	if(code_len > 0) {
		char_temp = '\0';		
		for(i = 0; i < code_len; ++i) {
			char_temp <<= 1;		
			if(code_buf[i] == '1')
				char_temp |= 1;
		}
		char_temp <<= 8 - code_len;       // 将编码字段从尾部移到字节的高位
		fwrite((char *)&char_temp, sizeof(unsigned char), 1, outfile);       // 存入最后一个字节
	}
    return ;
}


int compress(const char *inFileName, const char *outFileName) {
    //初始化暂存节点
    initNode();
    
    //获取文本信息
    if (get_file_info(inFileName) == -1) return -1;
    DBG(BLUE"<get_info>"NONE" : get info is success...\n");
    
    // 排序，将频度为零的放最后，剔除
	quickSort(tmp_nodes, 0, MAX_SIZE - 1);
    DBG(GREEN"<quickSort>"NONE" : quickSort is success...\n");
    
    // 统计实际的字符种类（出现次数不为0）
    char_kinds = get_char_kinds();
    DBG(YELLOW"<char kinds>"NONE" : get char kinds is success, kinds is %d...\n", char_kinds);
    
    if (char_kinds <= 1) { //空文件
        if (black_file(outFileName) == -1) return -1;
    } else if (char_kinds == 2 && linefeed_num == 1) { //单个字符
        if (single_char(outFileName) == -1) return -1;
        DBG(GREEN"<single_char>"NONE " : single_char success...\n");
    }
    else { //多种字符
        node_num = 2 * char_kinds - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
	       
        huf_tree = (HufNode *)malloc(node_num * sizeof(HufNode));		// 动态建立哈夫曼树所需结点
        //初始化哈弗曼树
        initHuff(huf_tree, char_kinds, tmp_nodes, node_num);
        DBG(GREEN"init success...\n"NONE);
	    CreateTree(huf_tree, char_kinds, node_num);		// 创建哈夫曼树
        DBG(BLUE"create tree is success...\n"NONE);
	    HufCode(huf_tree, char_kinds);		// 生成哈夫曼编码
        DBG(YELLOW"get code is success...\n"NONE);
        
        out_file_info(outFileName);//将字符种类，字符权重，　文本长度输入到压缩后的文件中
       DBG(RED"info out success...\n"NONE);
        out_code(inFileName);
        DBG(GREEN"out code\n"NONE);
		// 关闭文件
		fclose(infile);
		fclose(outfile);
        DBG(GREEN"close is success...\n"NONE);
        DBG(BLUE"start clear"NONE);
        clear(char_kinds, huf_tree);
        DBG(GREEN"<more char>"NONE" : more kinds success...\n");
	}
    return 1;
}//compress

