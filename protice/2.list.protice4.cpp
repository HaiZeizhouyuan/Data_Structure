/*************************************************************************
	> File Name: 2.list.protice4.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月03日 星期日 20时22分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

typedef struct List{
    ListNode head;
    int length;
}List;

ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
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
    ListNode *p = &(l->head), *node = getNewNode(val);
    while(loc--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(List *l, int loc) {
    if (l == NULL) return 0;
    if (loc < 0 || loc >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while(loc--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 0;
}

void reverser(List *l) {
    ListNode *p = l->head.next, *q;
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
    ListNode *p = l->head.next;
    printf("head->");
    while(p) {
        printf("%d->", p->val);
        p = p->next;
    }
    printf("NULL");
    return ;
}

void clearNode(ListNode *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clearList(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while(p) {
        q = p->next;
        clearNode(p);
        p = q;
    }
    free(l);
    return ;
}

int main() {
 
 
    return 0;
}
