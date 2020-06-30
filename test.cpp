/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Jun 27 11:42:19 2020
 ************************************************************************/

/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun  7 18:57:04 2020
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct ListNode{
    char data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode head;
    int length;
} List;

ListNode *getNewNode(char val) {
    ListNode *p = (ListNode *) malloc (sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

List *getLinkList(){
    List *l =  (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int ind, char val) {
    int ret = ind;
    if (l == NULL) return -1;
    if (ind < 0 || ind > l->length) return -1;
    ListNode *p =&(l->head), *node = getNewNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ret;
}


void output(List *l){
    printf("head->");
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%c->", p->data);
    }
    printf("NULL\n");
    return ;
}
void reverser(List *l) {
    ListNode *p = l->head.next, *q;
    l->head.next = NULL;
    while (p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
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
int main () {
    int n;
    char str;
    scanf("%d", &n);
    List *l = getLinkList();
    for (int i = 0; i < n; i++) {
        scanf("%c", &str);
        i - n + 1 && scanf(" ");
        insert(l, l->length, str);
    }
    //reverse(l);
    output(l);
    clear_List(l);
    return 0;
}
