/*************************************************************************
	> File Name: 2.list.protice3.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月03日 星期日 19时35分09秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

typedef struct ListNode{
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode head;
    int length;
} List;

ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

List *getLinkList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return -1;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while(ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(List *l, int ind) {
    if (l == NULL) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while(ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return 1;
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
    printf("head->");
    ListNode *p = l->head.next;
    while(p) {
        p = p->next;
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

void clear_ListNode(ListNode *node){
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear_List(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while(p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return ;
}

int main() {
    
 
    return 0;
}
