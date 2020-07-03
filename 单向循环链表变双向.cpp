/*************************************************************************
	> File Name: 单向循环链表变双向.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun 29 20:51:53 2020
 ************************************************************************/
/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun  7 18:57:04 2020
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode *next;
    struct ListNode *prior;
} ListNode;

typedef struct List {
    ListNode head;
    int length;
} List;

ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *) malloc (sizeof(ListNode));
    p->data = val;
    p->next = p->prior =  NULL;
    return p;
}

List *getLinkList(){
    List *l =  (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p =&(l->head), *node = getNewNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

List *build(List *l) {
    ListNode *p = &(l->head), *q, *ret;
    if (l == NULL) return l;
    q = p->next;
    ret = q;
    do {
        q->prior = p;
        p = p->next;
        q = q->next;
    } while (q != ret);
    return l;
}
void output(List *l, int m){
    ListNode *p = l->head.next, *q;
    while(p->data !=  m) p = p->next;
    q = p;
    printf("%d", p->data);
    p = p->prior;
    while (p != q) {
        printf("%d", p->data);
        p = p->prior;
    }
    printf("\n");
    return ;
}

void clear_ListNode(ListNode *node) {
    if(node == NULL) return ;
    free(node);
    return ;
}

void clear_List(List *l) {
    if (l == NULL) return ;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return ;
}

int main() {
    int n, val, m;
    scanf("%d", &n);
    List *l = getLinkList();
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insert(l, i, val);
    }
    l = build(l);
    scanf("%d", &m);
    //output(l, m);
    clear_List(l);
    return 0;
}
