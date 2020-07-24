/*************************************************************************
	> File Name: 2.list.protice1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul 21 11:16:11 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node head;
    int length;
} List;

Node *getNewNode (int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

List *getNewList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(List *l, int loc, int val) {
    int ret = loc;
    if (l == NULL) return -1;
    if (loc < 0 || loc > l->length) return -1;
    Node *p = &(l->head), *node = getNewNode(val);
    while (loc--) p = p->next; 
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ret;
}

int delete_node (List *l, int loc) {
    int ret = loc;
    if (l == NULL) return -1;
    if (loc < 0 || loc >= l->length) return -1;
    Node *p = &(l->head), *q;
    while(loc--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return ret;
}

void reverse (List *l) {
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

void output(List *l){
    printf("head->");
    for (Node *p = l->head.next; p; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

void priflag (List *l, int loc) {
    char str[100];
    Node *p = l->head.next;
    int offset = 3;
    while(loc != -1 && p) {
        offset += sprintf(str, "%d->", p->data);
        loc -= 1;
        p = p->next;
    }

    for (int i = 0; i < offset; i++) printf(" ");
    printf("^\n");
    for (int i = 0; i < offset; i++) printf(" ");
    printf("|\n\n");
    return ;
}

void clear_node (Node *node) {
    if (node == NULL) return ;
    free(node);
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
    int ret;
    srand(time(0));
    #define max_op 20
    List *l = getNewList();
    for (int i = 0; i < 30; i++) {
        int op = rand() % 5;
        int val = rand() % 100;
        int loc = rand() % (l->length + 3) - 1;
        switch (op) {
            case 0:
            case 1:
            case 2:
                ret = insert(l, loc, val);
                printf("insert %d in %d is %s\n", val, loc, ret != -1 ? "success" : "failed");
                break;
            case 3:
                ret = delete_node(l, loc);
                printf("delete item in %d from list is %s\n", loc, ret != -1 ? "success" : "failed");
                break;
            case 4:
                ret = -1;
                printf("reverse list :\n");
                reverse(l);
                break;
        }
        output(l);
        priflag(l, ret);
    }
    clear_list(l);
    #undef max_op
    return 0;
}

