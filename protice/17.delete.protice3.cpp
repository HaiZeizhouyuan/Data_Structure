/*************************************************************************
	> File Name: 17.delete.protice3.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月24日 星期四 13时44分31秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

#define SIZE(n) (n ? n->size : 0)
#define L(n) (n ? n->lchild : NULL)
#define R(n) (n ? n->rchild : NULL)
#define KEY(n) (n ? n->key : 0)

typedef struct Node{
    int key, size;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->size = 1;
    p->lchild = p->rchild = NULL;
    return p;
}

void update_size(Node *root) {
    root->size = SIZE(root->lchild) + SIZE(root->rchild) + 1;
    return ;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    if (key < root->key) return search(root->lchild, key);
    return search(root->rchild, key);
}

int search_k(Node *root, int k) {
    if (root == NULL) return -1;
    if (SIZE(L(root)) == k - 1) return root->key;
    if (k <= SIZE(L(root))) return search_k(root->lchild, k);
    return search_k(root->rchild, k - SIZE(L(root)) - 1);
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    if (key > root->key) root->rchild = insert(root->rchild, key);
    update_size(root);
    return root;
}

Node *predecssor(Node *root) {
    Node *temp = root->lchild;
    while(temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->lchild = erase(root->lchild, key);
    else if (key > root->key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecssor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
            return temp;
        }
    }
    update_size(root);
    return root;
}


void print(Node *root) {
    printf("%d[%d], %d, %d\n", 
          KEY(root), SIZE(root), KEY(L(root)),
          KEY(R(root))
    );
    return ;
}


void output(Node *root){
    if (root == NULL) return ;
    output(root->lchild);
    print(root);
    output(root->rchild);
    return ;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output_k(Node *root, int k) {
    if (k == 0 || root == NULL) return ;
    if (k <= SIZE(root->lchild)) {
        output_k(root->lchild, k);
    } else {
        output(root->lchild);
        print(root);
        output_k(root->rchild, k - SIZE(root->lchild) - 1);
    }
    return ;
}
int main() {
    srand(time(0));
    int op, val;
    Node *root = NULL;
    while(~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: printf("search %d , result is %d\n", val, search(root, val)); break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: printf("search k = %d, result : %d\n", val, search_k(root, val)); break;
            case 4: {
                printf("output top-%d elements\n", val);
                output_k(root, val); 
                printf("---------\n");
            } break;
        }
        if (op == 1 || op == 2) {
            output(root);
            printf("--------\n");
        }
    }
    clear(root);
 
    return 0;
}
