/*************************************************************************
	> File Name: decompression.c
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 12时52分04秒
 ************************************************************************/
 #include "./include/head.h"

unsigned long file_len;
unsigned long writen_len = 0;		// 控制文件写入长度
FILE *infile, *outfile;
unsigned int char_kinds;		// 存储字符种类
unsigned int node_num;
HufNode *huf_tree;
unsigned char code_temp;		// 暂存8bits编码
unsigned int root;		// 保存根节点索引，供匹配编码使用


// 解压函数
int decompression(const char *inFileName, const char *outFileName)
{

    if ((infile = fopen(inFileName, "r")) == NULL) {		// 以二进制方式打开压缩文件
	    // 判断输入文件是否存在
    	perror("fopen inFileName failed");
        return 0;
    }
	// 读取压缩文件前端的字符及对应编码，用于重建哈夫曼树
	fread((char *)&char_kinds, sizeof(unsigned int), 1, infile);     // 读取字符种类数
    if (char_kinds == 0) {
		outfile = fopen(outFileName, "w");					// 打开压缩后将生成的文件
		fclose(infile);
		fclose(outfile);
    } else if (char_kinds == 1) {
		fread((char *)&code_temp, sizeof(unsigned char), 1, infile);     // 读取唯一的字符
		fread((char *)&file_len, sizeof(unsigned long), 1, infile);     // 读取文件长度
		outfile = fopen(outFileName, "w");					// 打开压缩后将生成的文件
		while (file_len--) fwrite((char *)&code_temp, sizeof(unsigned char), 1, outfile);	
		fclose(infile);
		fclose(outfile);
	} else {
        DBG(GREEN"more kinds\n"NONE);
		node_num = 2 * char_kinds - 1;		// 根据字符种类数，计算建立哈夫曼树所需结点数 
		huf_tree = (HufNode *)malloc(node_num * sizeof(HufNode));		// 动态分配哈夫曼树结点空间
		// 读取字符及对应权重，存入哈夫曼树节点
		for(int i = 0; i < char_kinds; ++i)     
		{
			fread((char *)&huf_tree[i].uch, sizeof(unsigned char), 1, infile);		// 读入字符
			fread((char *)&huf_tree[i].weight, sizeof(unsigned long), 1, infile);	// 读入字符对应权重
		    huf_tree[i].parent = 0;
		}
		//初始化后node_num-char_kins个结点的parent
		for(int i = char_kinds; i < node_num; ++i) 
			huf_tree[i].parent = 0;
        
		CreateTree(huf_tree, char_kinds, node_num);		// 重建哈夫曼树（与压缩时的一致）
		// 读完字符和权重信息，紧接着读取文件长度和编码，进行解码
		fread((char *)&file_len, sizeof(unsigned long), 1, infile);	// 读入文件长度
		outfile = fopen(outFileName, "w");		// 打开压缩后将生成的文件
		root = node_num - 1;
		while(1)
		{
			fread((char *)&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码
			// 处理读取的一个字符长度的编码（通常为8位）
			for(int i = 0; i < 8; ++i)
			{
				// 由根向下直至叶节点正向匹配编码对应字符
				if(code_temp & 128)
					root = huf_tree[root].rchild;
				else
					root = huf_tree[root].lchild;
			    if(root < char_kinds){
					fwrite((char *)&huf_tree[root].uch, sizeof(unsigned char), 1, outfile);
					++writen_len;
					if (writen_len == file_len) break;		// 控制文件长度，跳出内层循环
					root = node_num-1; // 复位为根索引，匹配下一个字符
				}
				code_temp <<= 1;		// 将编码缓存的下一位移到最高位，供匹配
			}
			if (writen_len == file_len) break;		// 控制文件长度，跳出外层循环
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		clear(char_kinds, huf_tree);
	}
    return 1;
}//extract()

