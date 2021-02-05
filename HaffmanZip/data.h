/*************************************************************************
	> File Name: data.h
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月31日 星期日 10时57分08秒
 ************************************************************************/

#ifndef _DATA_H
#define _DATA_H
#define CHAR_NUM 260
#define swap(a, b){\
    __typeof(a) __tmp = (a);\
    (a) = (b), (b) = __tmp;\
}

typedef struct TmpNode{
    unsigned char uch;
    unsigned long weight;
} TmpNode;

//哈弗曼树的节点
typedef struct HafNode{
    unsigned char ch; //以8bits为单位的无符号字符
    unsigned long weight; //每类(以二进制区分)字符出现的频度
    char code[400];//字符对应的哈弗曼编码
    struct HafNode *lchild, *rchild;
} HafNode;



#endif
