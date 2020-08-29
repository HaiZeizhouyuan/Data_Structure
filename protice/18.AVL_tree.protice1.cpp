/*************************************************************************
	> File Name: 18.AVL_tree.protice1.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri Jul 24 14:50:06 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define AVL(root) (root->data)

#define LH(root) (root->lchild->h)
#define RH(root) (root->rchild->h)
#define max(a, b) ({\
    __typeof(a) __a = (a);\
    __typeof(b) __b = (b);\
    __a > __b ? __a : __b;\
})

typedef struct Node {
    int data, h;
    struct Node *lchild, *rchild;
} Node;

Node _NIL;
#define NIL (&_NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->data = NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}
Node *getNewNode (int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NIL;
    p->h = 1;
    return p;
}

void updata_height(Node *root) {
    root->h = max(LH(root), RH(root)) + 1;
    return ;
}

Node *left_romate(Node *root) {
    printf("\033[34mleft_romate:\n\033[0m");
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    updata_height(root);
    updata_height(temp);
    return temp;
}

Node *right_romate(Node *root) {
    printf("\033[35mright_romate : \n\033[0m");
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updata_height(root);
    updata_height(temp);
    return temp;
}

Node *maintain(Node *root) {
    updata_height(root);
    if(abs(LH(root) - RH(root)) <= 1) return root;
    if (LH(root) > RH(root)) {
        if (LH(root->lchild) < RH(root->lchild)) {
            root->lchild = left_romate(root->lchild);
        }
        root = right_romate(root);
    } else {
        if (LH(root->rchild) > RH(root->rchild)) {
            root->rchild = right_romate(root->rchild);
        }
        root = left_romate(root);
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
    while (temp != NIL && temp->rchild != NIL) temp = temp->rchild;
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


void in_order(Node *root) {
    if (root == NIL) return ;
    in_order(root->lchild);
    printf("(%d, %d, %d)\n", AVL(root), AVL(root->lchild), AVL(root->rchild));
    in_order(root->rchild);
    return ;
}

void output(Node *root) {
    printf("AVL tree : ===============\n");
    in_order(root);
    printf("--------------------------\n");
    return ;
}



void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main () {
    srand(time(0));
    int val;
    Node *root = NIL;
    #define max_op 20
    for (int i = 0; i < max_op; i++) {
        val = rand() % 100;
        root = insert(root, val);
        printf("insert %d to tree : \n", val);
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
