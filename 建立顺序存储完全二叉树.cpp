/*************************************************************************
	> File Name: 建立顺序存储完全二叉树.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul 13 20:35:11 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

Node *init_node(char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *init_tree() {
    Tree *tree = (Tree *)malloc (sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

void insert (Tree *tree, Node **node_arr, int loc) {
    if (loc == 1) return ;
    if (loc % 2) node_arr[loc / 2]->lchild = node_arr[loc];
    else node_arr[loc / 2]->rchild = node_arr[loc];
    return ;
}

void output_node(Node *root) {
    if (root == NULL) return ;
    if (root->rchild == NULL && root->lchild == NULL) return ;
    printf("(");
    output_node(root->lchild);
    printf(",");
    output_node(root->rchild);
    printf(")");
    return ;

}

void output (Tree *tree) {
    if (tree == NULL) return ;
    output_node(tree->root);
    printf("\n");
    return ;
}


void clear_node (Node *node) {
    if (node == NULL) return ;
    clear_node(node->lchild);
    clear_node(node->rchild);
    free(node);
    return ;
}

void clear_tree(Tree *tree) {
    if (tree = NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

int main () {
    int size = 3, len = 0;
    char *str = (char *)malloc(size);
    char temp;
    str[0] = 0;
    for (int i = 0; ; i++) {
        scanf("%c", &temp);
        if (temp == '$') break;
        if (temp == ' ') continue;
        if (len == size) {
            size *= 2;
            str = (char *)realloc(str, size);
        }
        str[++len] = temp;
    }

    /*for (int i = 0; i < size; i++) {
        printf("%c", str[i]);
    }*/
    Tree *tree = init_tree();
    Node **node_arr = (Node **)malloc(sizeof(Node*) * (strlen(str) + 1));
    for (int i = 1; i <= strlen(str); i++) {
        node_arr[i] = init_node(str[i]);
        insert(tree, node_arr, i);
    }

    output(tree);
    clear_tree(tree);
    return 0;
}
