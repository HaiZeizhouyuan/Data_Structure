/*************************************************************************
	> File Name: 5.binary_tree_protice2.c
	> Author: zhouyuan
	> Mail: 
	> Created Time: 2020年08月29日 星期六 11时16分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    int n;
    Node *root;
} Tree;

Node  *getNewNode (int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    return node;
}

Tree *getNewTree () {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->n = 0;
    tree->root = NULL;
    return tree;
}

void clear_node (Node *node) {
    if (node == NULL) return ;
    free(node->lchild);
    free(node->rchild);
    free(node);
    return ;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}

Node *insert_node(Node *root, int val, int *flag) {
    if (root == NULL) {
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root;
    if (root->data > val) root->lchild = insert_node(root->lchild, val, flag);
    else root->rchild = insert_node(root->rchild, val, flag);
    return root;
}
void insert(Tree *tree, int val) {
    int flag = 0;
    if (tree == NULL) return ;
    tree->root = insert_node (tree->root, val, &flag);
    tree->n += flag;
    return ;
}

void in_order_node (Node *node) {
    if (node == NULL) return ;
    in_order_node(node->lchild);
    printf("%d ", node->data);
    in_order_node(node->rchild);
    return ;
}

void in_order(Tree *tree) {
    if (tree == NULL ) return ;
    printf("in_order : ");
    in_order_node (tree->root);
    printf("\n");
    return ;
}

void pre_order_node (Node *node) {
    if (node == NULL) return ;
    printf("%d ", node->data);
    pre_order_node(node->lchild);
    pre_order_node(node->rchild);
    return ;
}

void pre_order(Tree *tree) {
    if (tree == NULL ) return ;
    printf("in_order : ");
    pre_order_node (tree->root);
    printf("\n");
    return ;
}

void post_order_node (Node *node) {
    if (node == NULL) return ;
    post_order_node(node->lchild);
    post_order_node(node->rchild);
    printf("%d ", node->data);
    return ;
}

void post_order(Tree *tree) {
    if (tree == NULL ) return ;
    printf("in_order : ");
    post_order_node (tree->root);
    printf("\n");
    return ;
}

void output_node(Node *node) {
    if (node == NULL) return ;
    printf("%d", node->data);
    if (node->lchild == NULL && node->rchild == NULL) return ;
    printf("(");
    output_node(node->lchild);
    printf(", ");
    output_node(node->rchild);
    printf(")");
    return ;
}

void output_tree(Tree *tree) {
    if (tree  == NULL) return ;
    printf("Tree(%d) : [", tree->n);
    output_node(tree->root);
    printf("]\n\n");
    return ;
}

int main() {
    srand(time(0));
    Tree *tree = getNewTree();
    #define max_op 20
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        insert(tree, val);
        output_tree(tree);
    }

    in_order(tree);
    pre_order(tree);
    post_order(tree);

    #undef max_op
    clear_tree(tree);
    return 0;
}
