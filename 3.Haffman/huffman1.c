/*************************************************************************
	> File Name: huffman1.c
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 20时12分12秒
 ************************************************************************/

#include "./data.h"

HufNode *getNewNode(unsigned char ch, unsigned long weight) {
    HufNode *p = (HufNode *)malloc(sizeof(HufNode));
    p->uch = ch;
    p->weight = weight;
    p->lchild = p->rchild = NULL;
    return p;
}

void initHuff(HufNode **huf_tree, unsigned int char_kinds, TmpNode *tmp_nodes) {
    for (int i = 0; i < char_kinds; i++) {
        huf_tree[i] = getNewNode(tmp_nodes[i].uch, tmp_nodes[i].weight);
	}
    return ;
}

HufNode *CombinNode(HufNode *a, HufNode *b) {
    HufNode *p = getNewNode(0, a->weight + b->weight);
    p->lchild = a;
    p->rchild = b;
    return p;
}

void pick_min(HufNode **huf_tree, unsigned int n) {
    for (int j = n - 1; j >= 0; --j) {
        if (huf_tree[n]->weight > huf_tree[j]->weight) {
            swap(huf_tree[n], huf_tree[j]);
        }
    }
    return ;
}


void getHaffmanTree(HufNode **root, HufNode **huf_tree, unsigned int n) {
    for (int i = 1; i < n; i++) {
        pick_min(huf_tree, n - i);
        pick_min(huf_tree, n - i - 1);
        huf_tree[n - i - 1] = CombinNode(huf_tree[n - i], huf_tree[n - i - 1]);
    }
    *root = huf_tree[0];
    
    DBG(GREEN"create end\n"NONE);
    return ;
}


void __getHufCode(HufNode *root, unsigned char *str, int k) {
    str[k] = '0';
    if (root->lchild == NULL && root->rchild == NULL) {
        strcpy(root->code, str);
        return ;
    }
    str[k] = '0';
    __getHufCode(root->lchild, str, k + 1);
    str[k] = '1';
    __getHufCode(root->rchild, str, k + 1);
    return ;
}

void getHufCode(HufNode *root) {
    unsigned char str[100];
    memset(str, 0, sizeof(str));
    __getHufCode(root, str, 0);
    return ;
}

void clear(HufNode *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

