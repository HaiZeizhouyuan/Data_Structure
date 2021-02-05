/*************************************************************************
	> File Name: deexpression.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月31日 星期日 20时38分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include "./data.h"
//#include "./Haffman.h"

FILE *infile, *outfile;
unsigned int char_kinds;
unsigned long file_len;
unsigned char code_temp;
unsigned int node_num;
HafNode **haf_tree;
unsigned long writen_len = 0;

HafNode *getNewNode(unsigned char ch, unsigned long weight) {
    HafNode *p = (HafNode *)malloc(sizeof(HafNode));
    p->ch = ch;
    p->weight = weight;
    p->lchild = p->rchild = NULL;
    return p;
}

HafNode *CombinNode(HafNode *a, HafNode *b) {
    HafNode *p = getNewNode(0, a->weight + b->weight);
    p->lchild = a;
    p->rchild = b;
    return p;
}

void pick_min(HafNode **arr, int n) {
    for (int j = n - 1; j >= 0; --j) {
        if (arr[n]->weight > arr[j]->weight) {
            swap(arr[n], arr[j]);
        }
    }
    return ;
}

HafNode *getHaffmanTree(HafNode **arr, unsigned int n) {
    for (int i = 1; i < n; i++) {
        pick_min(arr, n - i);
        pick_min(arr, n - i - 1);
        arr[n - i - 1] = CombinNode(arr[n - i], arr[n - i - 1]);
    }
    return arr[0];
}


void __HafCode(HafNode *root, char *str, int k, HafNode *haf_node) {
    str[k] = 0;
    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(root->code, str);
        haf_node[node_num++] = *root;
        return ;
    }
    str[k] = '0';
    __HafCode(root->lchild, str, k + 1, haf_node);
    str[k] = '1';
    __HafCode(root->rchild, str, k + 1, haf_node);
    return ;
}


void HufCode(HafNode *root, HafNode *haf_node) {
    char str[100];
    __HafCode(root, str, 0, haf_node);
    return ;
}

void clear(HafNode *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


int deexpression(char *ifname, char *ofname) {
    infile = fopen(ifname, "rb");
    if (infile == NULL) return -1;
    fread((char *)&char_kinds, sizeof(unsigned int), 1, infile);
    if (char_kinds == 2) {
        fread((char *)&code_temp, sizeof(unsigned char), 1, infile);
        fread((char *)&file_len, sizeof(unsigned long), 1, infile);
        outfile = fopen(ofname, "wb");// 打开压缩后将生成的文件
        while (file_len--) {
            fwrite((char *)&code_temp, sizeof(unsigned char), 1, outfile);
        }
        fclose(infile);
        fclose(outfile);
    } else {
        node_num = 2 * char_kinds - 1;
        
        haf_tree = (HafNode **)calloc(node_num, sizeof(HafNode *));
        unsigned char ch;
        unsigned char weight;
        for (int i = 0; i  < char_kinds; i++) {
            fread((char *)&ch, sizeof(unsigned char), 1, infile);
            fread((char *)&weight, sizeof(unsigned long), 1, infile);
            haf_tree[i] = getNewNode(ch, weight);
        }
        getHaffmanTree(haf_tree, char_kinds);
        fread((char *)&file_len, sizeof(unsigned long), 1, infile);
        outfile = fopen(ofname, "wb");
       	HafNode *root = haf_tree[0];
       	while(1)
		{
			fread((char *)&code_temp, sizeof(unsigned char), 1, infile);		// 读取一个字符长度的编码

			// 处理读取的一个字符长度的编码（通常为8位）
			for(int i = 0; i < 8; ++i)
			{
				// 由根向下直至叶节点正向匹配编码对应字符
				if(code_temp & 128)
					root = root->rchild;
				else
					root = root->lchild;

				if(root == NULL)
				{
					fwrite((char *)&root->ch, sizeof(unsigned char), 1, outfile);
					++writen_len;
					if (writen_len == file_len) break;		// 控制文件长度，跳出内层循环
					//root = node_num-1;        // 复位为根索引，匹配下一个字符
				}
				code_temp <<= 1;		// 将编码缓存的下一位移到最高位，供匹配
			}
			if (writen_len == file_len) break;		// 控制文件长度，跳出外层循环
		}

		// 关闭文件
		fclose(infile);
		fclose(outfile);

		// 释放内存
		free(haf_tree);
    }
}
