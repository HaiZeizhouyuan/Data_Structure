/*************************************************************************
	> File Name: 2.list.protice5.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月04日 星期一 20时05分30秒
 ************************************************************************/

#include<string.h>
#include <stdlib.h>
#include<stdio.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List{
    Node head;
    int length;
}List;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = val;
    p->next = NULL;
    return p;
}

List *getNewList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}


int insert(List *l, int loc, int val) {
    if (l == NULL) return 0;
    if (loc < 0 || loc > l->length) return 0;
    Node *p = &(l->head), *node = getNewNode(val), *q;
    while(loc--) p = p->next;
    q = p->next;
    node->next = q;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(List *l, int loc) {
    if (l == NULL) return 0;
    if (loc < 0 || loc >= l->length) return 0;
    Node *p = &(l->head), *q;
    while(loc--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 1;
}

void reserver(List *l) {
    Node *p = l->head.next, *q;
    l->head.next = NULL;
    while(p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return ;
}

void output(List *l) {
    Node *p = l->head.next;
    printf("head->");
    while(p) {
        printf("%d->", p->val);
        p = p->next;
    }
    printf("NULL\n");
    return ;
}

void clearNode (Node *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clearTree(List *l) {
    if (l == NULL) return ;
    Node *p = l->head.next;
    while(p){
        Node *q = p->next;
        clearNode(q);
        p = q;
    }
    free(l);
    return ;
}

int main() {
    #define max_n 20
    int op, loc, val;
    List *l = getNewList();
    for (int i = 0; i < max_n; i++) {
        scanf("%d", &op);
        switch(op) {
            case 1: {
                scanf("%d%d", &loc, &val);
                insert(l, loc, val);
            }break;
            case 2:{
                scanf("%d", &loc);
                erase(l, loc);
            }break;
            case 3: {
                reserver(l);
            } break;
        }
        output(l);
    }
    clearTree(l);
    #undef max_n
    return 0;
}
