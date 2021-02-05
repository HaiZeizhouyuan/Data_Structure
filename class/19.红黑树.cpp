/*************************************************************************
	> File Name: 19.红黑树.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2020年12月20日 星期日 14时09分45秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define RED 0
#define BLACK 1
#define DBLACK 2

typedef struct Node {
    int key;
    int color; // 0 red, 1 black, 2 double black
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->color = BLACK;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = RED;
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_child(Node *root) {
    return root->lchild->color == RED || root->rchild->color == RED;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root;
    int flag = 0;
    if (root->lchild->color == RED && has_red_child(root->lchild)) flag = 1;
    if (root->rchild->color == RED && has_red_child(root->rchild)) flag = 2;
    if (flag == 0) return root;    
    if (root->lchild->color == RED && root->rchild->color == RED) {
        goto insert_end;
    }
    if (flag == 1) {
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
insert_end:
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) {
        root->lchild = __insert(root->lchild, key);
    } else {
        root->rchild = __insert(root->rchild, key);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {
    if (root->lchild->color != DBLACK 
        && root->rchild->color != DBLACK) return root;
    if (has_red_child(root)) {
        int flag = 0;
        root->color = RED;
        if (root->lchild->color == RED) {//右双黑,左红色
            root = right_rotate(root); 
            flag = 1;
        } else {//左双黑,右红色
            root = left_rotate(root);
            flag = 2;
        }
        root->color = BLACK;
        if (flag == 1) root->rchild = erase_maintain(root->rchild);
        else root->lchild = erase_maintain(root->lchild);
        return root;
    }

    //x是双黑色，　兄弟节点也是黑色

    //情况一：它的兄弟的两个孩子都是黑的
    if ((root->lchild->color == DBLACK && !has_red_child(root->rchild)) ||
        (root->rchild->color == DBLACK && !has_red_child(root->lchild))) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
  
    if (root->lchild->color == DBLACK) {//根节点的左孩子是双黑的
        root->lchild->color = 1;
        if (root->rchild->rchild->color != RED) {//情况二：兄弟节点的右孩子是黑的，左孩子是红的
            root->rchild->color = RED;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
        }
        //情况三：兄弟节点的左孩子是黑的, 右孩子是红的
        root = left_rotate(root);
        root->color = root->lchild->color;
    } else {//根节点的右孩子是双黑的
        root->rchild->color = 1;
        if (root->lchild->lchild->color != RED) {//兄弟节点的右孩子是红的, 左孩子是黑的
            root->lchild->color = RED;
            root->lchild = left_rotate(root->lchild);
            root->lchild->color = BLACK;
        }
        root = right_rotate(root);
        root->color = root->rchild->color;
    }
    root->lchild->color = root->rchild->color = BLACK;// 两个子孩子变成黑色，变成情况一,干掉双黑
    return root;
}
Node *__erase(Node *root, int key) {
    if (root == NIL) return NIL;
    if (key < root->key) {
        root->lchild = __erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild != NIL ? root->lchild : root->rchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}
void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print(Node *root) {
    printf("%d %d %d %d\n", 
        root->key, 
        root->color,
        root->lchild->key,
        root->rchild->key
    );
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    output(root->lchild);
    print(root);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: output(root); break;
        }
    }
    return 0;
}

