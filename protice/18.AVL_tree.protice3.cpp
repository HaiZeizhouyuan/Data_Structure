/*************************************************************************
	> File Name: 18.AVL_tree.protice3.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月24日 星期四 15时29分13秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

#define H(n) (n->h)
#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define KEY(n) (n->key)

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}


void updata_height(Node *root) {
    root->h = (H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root)))+ 1;
    return ;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    updata_height(root);
    updata_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updata_height(root);
    updata_height(temp);
    return temp;
}

Node *maintain(Node *root){
    if (abs(H(L(root)) - H(R(root))) <= 1) return root;
    if (H(L(root)) > H(R(root))) {
        if (H(L(root->lchild)) < H(R(root->lchild))) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (H(L(root->rchild)) > H(R(root->rchild))) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    updata_height(root);
    return maintain(root);
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while(temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) root->lchild = erase(root->lchild, key);
    else if(root->key < key) root->rchild = erase(root->rchild, key);
    else {
        if(root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }

    }
    updata_height(root);
    return maintain(root);
}


void print(Node *root) {
    printf("[%d(%d), %d, %d]\n",
         KEY(root), H(root),
         KEY(L(root)), KEY(R(root))
    );
    return ;
}

void output(Node *root) {
    if(root == NIL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->rchild);
    clear(root->lchild);
    free(root);
    return ;
}
int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0: root = erase(root, val); break;
            case 1: root = insert(root, val); break;
        }
        output(root);
        printf("--------------\n");
    }
    clear(root);
 
    return 0;
}
