/*************************************************************************
	> File Name: 8.thread_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jun 30 19:19:29 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL 0
#define THREAD 1

typedef struct Node {
    int key;
    int ltag, rtag;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode (int val) {
    Node *p = (Node *)malloc(sizeof (Node));
    p->key  = val;
    p->lchild = p->rchild = NULL;
    p->rtag = p->rtag = NORMAL;
    return p;
}

Node *insert(Node *root,int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (root->key > val) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

void build_thread(Node *root) {
    if (root == NULL) return ;
    static Node *pre = NULL; //函数调用完会释放，下一次调用会形成新的变量， static会使变量始终不变。
    build_thread(root->lchild);
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = THREAD;
    }
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build_thread(root->rchild);
    return ;
}

Node *most_left(Node *p) {
    while (p && p->ltag == NORMAL) p = p->lchild;
    return p;
}


void output(Node *root) {
    Node *p= most_left(root);
    while (p) {
        printf("%d ", p->key);
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild);
        }
    }
    return ;
}

void in_order(Node *root) {
    if (root == NULL) return ;
    if (root->ltag == NORMAL) in_order(root->lchild);
    printf("%d ", root->key);
    if(root->rtag == NORMAL) in_order(root->rchild);
    return ;
}

void clear (Node *root) {
    if (root == NULL) return ;
    Node *p = most_left(root), *q;
    while (p) {
        q = p;
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild);
        }
        free(q);
    }
    //if (root->ltag == NORMAL) clear(root->lchild);
    //if (root->rtag == NORMAL) clear(root->rchild);
    free(root);
    return ;
}

int main () {
    srand(time(0));
    Node *root = NULL;
    #define max_op 20
    for (int i = 0; i < 30; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    build_thread(root);
    in_order(root), printf("\n");
    output(root); printf("\n");
    clear(root);
    return 0;
}
