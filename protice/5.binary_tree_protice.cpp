/*************************************************************************
	> File Name: 5.binary_tree_protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jun 26 09:53:05 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

Node *getNewNode (int val){
    Node *p = (Node *) malloc (sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *getNewTree() {
    Tree *tree = (Tree *) malloc (sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

void clear_node (Node *root) {
    if (root == NULL) return ;
    clear_node(root->lchild);
    clear_node(root->rchild);
    free(root);
    return ;
}

void clear_tree (Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

Node *insert_node (Node *node, int val, int *flag) {
    if (node == NULL) {
        *flag = 1;
        return getNewNode(val);
    }
    if (node->data == val) return node;
    if (node->data > val) node->lchild = insert_node(node->lchild, val, flag);
    else node->rchild = insert_node(node->rchild, val, flag);
    return node;
}

void insert_tree (Tree *tree, int val) {
    int flag = 0;
    tree->root = insert_node(tree->root, val, &flag);
    tree->n += flag;
    return ;

}

void output_node(Node *node) {
    if (node == NULL) return ;
    printf("%d", node->data);
    if (node->lchild == NULL && node->rchild == NULL) return ;
    printf("(");
    output_node(node->lchild);
    printf(",");
    output_node(node->rchild);
    printf(")");
    return ;

}

void output_tree (Tree *tree) {
    if (tree == NULL) return ;
    printf("Tree(%d) : ", tree->n);
    output_node(tree->root);
    printf("\n");
    return ;
}

void preorder_node (Node *node) {
    if (node == NULL) return ;
    printf("%d ", node->data);
    preorder_node(node->lchild);
    preorder_node(node->rchild);
    return ;
}

void preorder_tree (Tree *tree) {
    if (tree == NULL) return ;
    printf("preorder :");
    preorder_node (tree->root);
    printf("\n");
    return ;

}

void inorder_node (Node *node) {
    if (node == NULL) return ;
    inorder_node(node->lchild);
    printf("%d ", node->data);
    inorder_node(node->rchild);
    return ;
}

void inorder_tree (Tree *tree) {
    if (tree == NULL) return ;
    printf("inorder :");
    inorder_node (tree->root);
    printf("\n");
    return ;

}

void postorder_node (Node *node) {
    if (node == NULL) return ;
    postorder_node(node->lchild);
    postorder_node(node->rchild);
    printf("%d ", node->data);
    return ;
}

void postorder_tree (Tree *tree) {
    if (tree == NULL) return ;
    printf("postorder :");
    postorder_node (tree->root);
    printf("\n");
    return ;

}


int main () {
    srand(time(0));
    #define max_op 10
    Tree *tree = getNewTree();
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        insert_tree(tree,val);
        output_tree(tree);
    }
    preorder_tree(tree);
    inorder_tree(tree);
    postorder_tree(tree);
    clear_tree(tree);
    #undef max_op

}
