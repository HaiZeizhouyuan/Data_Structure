/*************************************************************************
	> File Name: 单链表的就地转置.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun 29 17:29:44 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct List {
    int length;
    Node head;
} List;

Node *getNewNode (char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

List *getNewList () {
    List *l = (List *)malloc(sizeof(List));
    l->length = 0;
    l->head.next = NULL;
    return l;
}

int insert(List *l, int loc, char val) {
    if (l == NULL) return 0;
    if (loc < 0 || loc > l->length) return 0;
    Node *p = &(l->head), *node = getNewNode(val);
    while(loc--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
} 

void reverse(List *l) {
    Node *p = l->head.next, *q;
    l->head.next = NULL;
    while (p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return ;
}

void output (List *l) {
    for (Node *p = l->head.next; p; p = p->next) {
        p != l->head.next && printf(" ");
        printf("%c", p->data);
    }
    printf("\n");
    return ;
}

void clear_node(Node *p) {
    if (p == NULL) return ;
    free(p);
    return ;
}

void clear_list(List *l) {
    if (l == NULL) return ;
    Node *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_node(p);
        p = q; 
    }
    free(l);
    return ;
}

int main () {
    int n;
    char str;
    scanf("%d\n", &n);
    List *l = getNewList();
    for (int i = 0; i < n; i++) {
        scanf("%c", &str);
        i - n + 1 && scanf(" ");
        insert(l, l->length, str);
    }
    reverse(l);
    output(l);
    clear_list(l);
    return 0;
}
