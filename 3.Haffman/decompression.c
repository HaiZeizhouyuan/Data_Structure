/*************************************************************************
	> File Name: decompression.c
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 12时52分04秒
 ************************************************************************/
 #include "data.h"
 #include "./huffman1.h"

unsigned long file_len;
unsigned long writen_len = 0;		// 控制文件写入长度
FILE *infile, *outfile;
unsigned int char_kinds;		// 存储字符种类
unsigned int node_num;
HufNode **huf_tree;
unsigned char code_temp;		// 暂存8bits编码
HufNode *root;
unsigned long long linefeed_nums = 0; //换行符的数目

// 解压函数
int decompression(char *inFileName, char *outFileName)
{

    if ((infile = fopen(inFileName, "rb")) == NULL) {		// 以二进制方式打开压缩文件
	    // 判断输入文件是否存在
    	perror("fopen inFileName failed");
        return 0;
    }
	// 读取压缩文件前端的字符及对应编码，用于重建哈夫曼树

	fread((char *)&linefeed_nums, sizeof(unsigned int), 1, infile);     // 读取字符种类数
	fread((char *)&char_kinds, sizeof(unsigned int), 1, infile);     // 读取字符种类数
    if((char_kinds == 1 && linefeed_nums == 1) || char_kinds == 0 && linefeed_nums == 0){ //空文件
        DBG(GREEN"BLACK\n"NONE);
		outfile = fopen(outFileName, "wb");					// 打开压缩后将生成的文件
		fclose(infile);
		fclose(outfile);
    } else if ((char_kinds == 2 && linefeed_nums == 1) || (char_kinds == 1 && linefeed_nums == 0)) { //单个字符
		fread((char *)&code_temp, sizeof(unsigned char), 1, infile);     // 读取唯一的字符
		fread((char *)&file_len, sizeof(unsigned long), 1, infile);     // 读取文件长度
        printf("kinds: %d, c : %c\n", char_kinds, code_temp);
		outfile = fopen(outFileName, "wb");					// 打开压缩后将生成的文件
		while (file_len--) fwrite((char *)&code_temp, sizeof(unsigned char), 1, outfile);	
		fclose(infile);
		fclose(outfile);
	} else {
        DBG(GREEN"start more kind uncom...\n"NONE);
		node_num = 2 * char_kinds - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
		huf_tree = (HufNode **)malloc(node_num * sizeof(HufNode *));		// 动态分配哈夫曼树结点空间
		TmpNode * tmp_nodes = (TmpNode *)malloc(node_num * sizeof(TmpNode));
        // 读取字符及对应权重，存入哈夫曼树节点
        DBG(GREEN"start init...\n"NONE);
		for(int i = 0; i < char_kinds; ++i) {
			fread((char*)&tmp_nodes[i].uch, sizeof(unsigned char), 1, infile);		// 读入字符对应权重
			fread((char *)&tmp_nodes[i].weight, sizeof(unsigned long), 1, infile);	// 读入字符对应权重
		}

		// 初始化后node_num-char_kins个结点的parent
        DBG(YELLOW"init tree start\n"NONE); 
        initHuff(huf_tree, char_kinds, tmp_nodes);
        DBG(GREEN"start create tree...\n"NONE);
        getHaffmanTree(&root, huf_tree, char_kinds);
        DBG(GREEN"create tree is success...\n"NONE);
		// 读完字符和权重信息，紧接着读取文件长度和编码，进行解码
		fread((char *)&file_len, sizeof(unsigned long), 1, infile);	// 读入文件长度
		outfile = fopen(outFileName, "wb");		// 打开压缩后将生成的文件
        HufNode *nodes = root;
		while(1)
		{
			fread((char *)&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码
			// 处理读取的一个字符长度的编码（通常为8位）
			for(int i = 0; i < 8; ++i)
			{
				// 由根向下直至叶节点正向匹配编码对应字符
				if(code_temp & 128)
                    nodes = nodes->rchild;
				else
                    nodes = nodes->lchild;
				if (nodes->lchild == NULL && nodes->rchild == NULL) {
                    fwrite((char *)&nodes->uch, sizeof(unsigned char), 1, outfile);
					++writen_len;
					if (writen_len == file_len) break;		// 控制文件长度，跳出内层循环
                    nodes = root;
				}
				code_temp <<= 1;		// 将编码缓存的下一位移到最高位，供匹配
			}
			if (writen_len == file_len) break;		// 控制文件长度，跳出外层循环
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
        clear(root);
        free(huf_tree);
	}
    return 1;
}//extract()

