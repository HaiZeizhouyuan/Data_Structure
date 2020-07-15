/*************************************************************************
	> File Name: 递归删除.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul 13 14:29:02 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    int n;
    Node *root;
} Tree;

typedef struct Stack {
    Node **data;
    int size, top;
} Stack;

Stack *getNewstack(int n);
Node *getNewNode(char);
Tree *getNewTree();

Node *top_stack(Stack *);
int empty(Stack *);
int push(Stack *, Node *);
int pop(Stack *);
void put1(Node *);
Node *build (const char *, int *);
void output(Node *, char);
void clear_stack(Stack *s);
void clear_node(Node *);
void clear_tree(Tree *);


int main () {
    char str[35], ch;
    for (int i = 0;; i++) {
        scanf("%c", &ch);
        if (ch == '\n') break;
        str[i] = ch;
    }
    scanf("%c", &ch);
    int node_num;
    Tree *tree = getNewTree();
    tree->root = build(str, &node_num);
    tree->n = node_num;
    put1(tree->root);
    printf("\n");
    output(tree->root, ch);
    printf("\n");
    clear_tree(tree);
    return 0;
}

Stack *getNewstack (int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->size = n;
    s->top = -1;
    return s;
}

Node *getNewNode (char val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    return node;
}

Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

Node *top_stack(Stack *s) {
    return s->data[s->top];
}

int empty_stack(Stack *s) {
    return s->top == -1;
}

int push (Stack *s, Node *temp){
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++(s->top)] = temp;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty_stack(s)) return 0;
    s->top -= 1;
    return 1;
}

Node *build(const char *str, int *node_num) {
    Stack *s = getNewstack(strlen(str));
    Node *temp = NULL, *p = NULL;
    int flag = 0;
    while (str[0]) {
        switch (str[0]) {
            case '(': 
                push(s, temp);
                flag = 0;
                break;
            case ')':
                p = top_stack(s);
                pop(s);
                break;
            case ',':
                flag = 1;
                break;
            case ' ':
                break;
            default :
                temp = getNewNode(str[0]);
                if (!empty_stack(s) && flag == 0) {
                    top_stack(s)->lchild = temp;
                } else if (!empty_stack(s) && flag == 1) {
                    top_stack(s)->rchild = temp;
                }
                ++(*node_num);
                break;
        }
        ++str;
    }
    clear_stack(s);
    if (temp && !p) p = temp;
    return p;
}

void put1(Node *root) {
    if (root == NULL) return ;
    printf("%c", root->data);
    if(root->lchild == NULL && root->rchild == NULL) return ;
    printf("(");
    put1(root->lchild);
    printf(",");
    put1(root->rchild);
    printf(")");
    return ;
}


void output(Node *root, char ch) {
    if (root == NULL || root->data == ch) return ;
    printf("%c", root->data);
    if ((root->lchild == NULL || root->lchild->data == ch) && (root->rchild == NULL || root->rchild->data == ch)) return;
    printf("(");
    if (root->lchild && root->lchild->data != ch) output(root->lchild, ch);
    if (root->rchild && root->rchild->data != ch) {
        printf(",");
        output(root->rchild, ch);
    }
    printf(")");
    return ;
}

void clear_stack(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void clear_node(Node *node) {
    if (node == NULL) return ;
    clear_node(node->lchild);
    clear_node(node->rchild);
    free(node);
    return;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return ;
    clear_node(tree->root);
    free(tree);
    return ;
}
