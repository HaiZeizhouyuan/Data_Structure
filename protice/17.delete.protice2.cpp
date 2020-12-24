/*************************************************************************
	> File Name: 17.delete.protice2.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月22日 星期二 16时37分47秒
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
#define KEY(n) (n ? n->key : 0)

typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;


Node *getNewNod(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    p->size = 1;
    return p;
}

int search(Node *root, int val) {
    if (root == NULL) return 0;
    if (root->key == val) return 1;
    if (val < root->key) return search(root->lchild, val);
    return search(root->rchild, val);
}

int search_k(Node *root, int k) {
    if (root == NULL) return -1;
    if(SIZE(L(root)) == k - 1) return root->key;
    if (k <= SIZE(L(root))) {
        return search_k(root->lchild, k);
    }
    return search_k(root->rchild, k - SIZE(L(root)) - 1);
}

Node *insert(Node *root, int key) {
    if (root == NULL ) return getNewNod(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;    
}

Node *predecessor(Node *root) {
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
            Node *temp = predecessor(root);
            root->key = temp->key;
            temp->lchild = erase(root->lchild, temp->key);
        }
    }
    return root;

}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("(%d[%d], %d, %d)\n",
        KEY(root), SIZE(root),
        KEY(root->lchild),
        KEY(root->rchild)
    );
    return ;
}

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    print(root);
    output(root->rchild);
    return ;
}

void output_k (Node *root, int k) {
    if (k == 0 || root == NULL) return ;
    if (k <= SIZE(L(root))) {
        output_k(root->lchild, k);
    } else {
        output(root->lchild);
        print(root);
        output_k(root->rchild, k - SIZE(L(root)) - 1);
    }
    return ;
}


int main() {
    int op, val;
    Node *root = NULL;
    while(~scanf("%d%d", &op, &val)) {
        switch(op) {
            case 0:printf("search %d, result : %d\n", val, search(root, val)); break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: {
                printf("search k = %d, result : %d\n", 
                      val, search_k(root, val));
            } break;
            case 4: {
                printf("output top-%d elements\n", val);
                output_k(root, val);
                printf("--------------\n");
            } break;
        }
        if (op == 1 || op == 2) {
            output(root);
            printf("----------\n");
        }
    }
 
    return 0;
}
