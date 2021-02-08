/*************************************************************************
	> File Name: data.h
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 12时49分24秒
 ************************************************************************/

#ifndef _DATA_H
#define _DATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./color.h"
#include <limits.h>
#define MAX_SIZE 256
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}
typedef struct {
	unsigned char uch;			// 以8bits为单元的无符号字符,考虑到文件中有汉字，所以定义成unsigned char
	unsigned long weight;		// 每类（以二进制编码区分）字符出现频度
} TmpNode;

// 哈夫曼树结点
/*typedef struct {
	unsigned char uch;				// 以8bits为单元的无符号字符
	unsigned long weight;			// 每类（以二进制编码区分）字符出现频度
	char *code;						// 字符对应的哈夫曼编码（动态分配存储空间）
	int parent, lchild, rchild;		// 定义双亲和左右孩子
} HufNode, *HufTree;
*/
typedef struct HufNode {
    unsigned char uch;
    unsigned long weight;
    char code[100];
    struct HufNode *lchild, *rchild;
}HufNode;

#ifdef _D
#define DBG(fmt, args...) printf(fmt, ##args); //将后面的参数加到后面，　如果没有参数则将'.'删除
#else 
#define DBG(fmt, args...)  //如果定义了，预编译时会删掉这个宏　
#endif

#endif
