/*************************************************************************
	> File Name: 18.AVL_tree.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jul 24 09:36:36 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LH(root) (root->lchild->h)
#define RH(root) (root->rchild->h)
#define max(a, b) ({\
    __typeof(a) __a = (a);\
    __typeof(b) __b = (b);\
    __a > __b ? (a) : (b);\
})

#define AVL(root) (root->data)

typedef struct Node {
    int data, h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->data = NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NIL;
    p->h = 1;
    return p;
}

void updata(Node *root) {
    root->h = max(LH(root), RH(root)) + 1;
    return ;
}

Node *left_ramte(Node *root) {
    printf("left_ramte :\n");
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    updata(root);
    updata(temp);
    return temp;
}

Node *right_ramte(Node *root) {
    printf("right_ramte : \n");
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updata(root);
    updata(temp);
    return temp;
}

Node *maintain(Node *root) {
    updata(root);
    if (abs(LH(root) - RH(root)) <= 1) return root;
    if (LH(root) > RH(root)) {
        if (LH(root->lchild) < RH(root->lchild)) {
            root->lchild = left_ramte(root->lchild);
        }
        root = right_ramte(root);
    } else {
        if (LH(root->rchild) > RH(root->rchild)) {
            root->rchild = right_ramte(root->rchild);
        }
        root = left_ramte(root);
    }
    return root;
}

Node *insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (root->data == val) return root;
    if (root->data > val) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return maintain(root);
}

Node *predessor(Node *root) {
    Node *temp = root->lchild;
    while(temp != NIL && temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int val) {
    if (root == NIL) return root;
    if (root->data > val) root->lchild = erase(root->lchild, val);
    else if (root->data < val) root->rchild = erase(root->rchild, val);
    else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predessor(root);
            root->data = temp->data;
            root->lchild = erase(root->lchild, temp->data);
        }
    }
    return maintain(root);
}

void __output(Node *root){
    if (root == NIL) return ;
    __output(root->lchild);
    printf("(%d, %d, %d)\n", AVL(root), AVL(root->lchild), AVL(root->rchild));
    __output(root->rchild);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("AVL tree : =========\n");
    __output(root);
    printf("____________________\n");
    return ;
}



void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main() {
    srand(time(0));
    Node *root = NIL;
    int val;
    #define max_op 20
    for (int i = 0; i < max_op; i++) {
        val = rand() % 100;
        root = insert(root, val);
        printf("insert %d to tree\n", val);
        output(root);
    }
    while (~scanf("%d", &val)) {
        root = erase(root, val);
        printf("erase %d from tree\n", val);
        output(root);
    }
    #undef max_op
    clear(root);
    return 0;
}
