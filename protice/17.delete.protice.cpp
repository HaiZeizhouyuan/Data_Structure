/*************************************************************************
	> File Name: 17.delete.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu Jul 23 09:30:46 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (val < root->key) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while(temp && temp->rchild) temp = temp->rchild;
    return temp;
}

Node *delete_node (Node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->lchild = delete_node(root->lchild, key);
    else if (key > root->key) root->rchild = delete_node(root->rchild, key);
    else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = delete_node(root->lchild, temp->key);
        }
    }
    return root;
}

Node *search(Node *root, int key) {
    if (root == NULL || root->key == key) return root;
    if (key < root->key) return search(root->lchild, key);
    else return search(root->rchild, key);
}

void in_order(Node *root) {
    if (root == NULL) return ;
    in_order(root->lchild);
    printf("%d ", root->key);
    in_order(root->rchild);
    return ;
}

void clear(Node *root) {
    if (root == NULL) return ;
    free(root->lchild);
    free(root->rchild);
    return ;
}


int main () {
    Node *root = NULL;
    int op, val;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: root = insert(root, val); break;
            case 1: root = delete_node(root, val);break;
            case 2: printf("search %s!",search(root, val) ? "success" : "failed");
        }
        in_order(root);
        printf("\n");
    }
    clear(root);
    return 0;
}
