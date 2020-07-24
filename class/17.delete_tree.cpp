/*************************************************************************
	> File Name: 17.delete_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul 21 19:13:35 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;


Node* getNewNode (int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = val;
    p->lchild = p->rchild = NULL;
    return p;
}


Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (root->key > val) root->lchild  = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp && temp->rchild) temp = temp->rchild;
    return temp;
}

Node *delete_node (Node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->lchild = delete_node(root->lchild, key);
    else if (key > root->key) root->rchild = delete_node(root->rchild, key);
    else {
        //度为0的叶子节点
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

Node *search(Node *root, int key){
    if (root == NULL || root->key == key) return root;
    if (root->key > key) return search(root->lchild, key);
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
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main () {
    Node *root = NULL;
    int op, val;
    while(~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: 
                root = insert(root, val); 
                printf("insert success the tree : ");
                in_order(root);
                break;
            case 1: 
                root = delete_node(root, val); 
                printf("delete success the tree : ");
                in_order(root);
                break;
            case 2:
            printf("search %d is %s", val, search(root, val) ? "success" : "failed");
        }
        printf("\n");
    }

    clear(root);
    return 0;
}
