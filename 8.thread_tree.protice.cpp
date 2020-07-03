/*************************************************************************
	> File Name: 8.thread_tree.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jun 30 20:11:42 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define NOCLUE 0
#define CLUE 1

typedef struct Node {
    int data;
    int ltag, rtag;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode (int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->ltag = p->rtag = NOCLUE;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->data == val) return root;
    if (root->data > val) root->lchild =  insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

void in_order (Node *root) {
    if (root == NULL) return ;
    if (root->ltag == NOCLUE)  in_order(root->lchild);
    printf("%d ", root->data);
    if (root->rtag == NOCLUE)  in_order(root->rchild);
    return ;
}

void clear (Node *root) {
    if (root == NULL) return ;
    if (root->rtag == NOCLUE) clear(root->lchild);
    if (root->ltag == NOCLUE) clear(root->rchild);
    free(root);
    return ;
}

int main () {
    #define max_op 20
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    in_order(root), printf("\n");
    //output(root);
    clear(root);

}


