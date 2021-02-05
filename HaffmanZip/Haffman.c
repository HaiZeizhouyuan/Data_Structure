/*************************************************************************
	> File Name: Haffman.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月31日 星期日 13时39分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include "./data.h"
extern unsigned int node_num;

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

