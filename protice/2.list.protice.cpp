/*************************************************************************
	> File Name: 2.list.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat Jun 20 11:32:52 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;
typedef struct List {
    ListNode head;
    int length;
} List;

ListNode *getNewNode(int);
List *getLinkList();
int insert(List *, int, int);
int erase(List *, int);
void reserve(List *);
void output(List *);
void clear_ListNode(ListNode *);
void clear_List(List *);
void output1(List *, int);

int main () {
    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    int loc, op, val, flag;
    for (int i = 0; i < max_op; i++) {
        loc = rand() % (l->length + 3) -1;
        op = rand() % 4;
        val = rand() % 10000;
        switch(op) {
            case 0 :
            case 1 : {
                flag = insert(l, loc, val);
                printf("insert %d at %d of list is %d\n", val, loc, flag);
            } break;
            case 2 : {
                flag = erase(l, loc);
                printf("erase item at %d of list is %d\n", loc, flag);
            } break;
            case 3 : {
                flag = -1;
                printf("reserve the List! \n");
                reserve(l);
            } break;
        }
        output(l);
        output1(l, flag);
        printf("\n");
    }
    clear_List(l);
    #undef max_op

    return 0;
}

ListNode *getNewNode (int val) {
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

int insert(List *l, int loc, int val) {
    int ret = loc;
    if (l == NULL) return -1;
    if (loc < 0 || loc > l->length) return -1;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (loc--) p = p->next;//头指针在loc 前一个节点
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ret;
}

int erase(List *l, int loc) {
    int ret = loc;
    if (l == NULL) return -1;
    if (loc < 0 || loc >= l->length) return -1;
    ListNode *p = &(l->head), *q;
    while (loc--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return ret;
}

void output(List *l) {
    printf("head->");
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
    return ;
}

void output1(List *l, int loc) {
    char str[100];
    int offer = 3;
    ListNode *p = l->head.next;
    while (loc != -1 && p) {
        offer += sprintf(str, "%d->", p->data);
        loc -= 1;
        p = p->next;
    }

    for (int i = 0; i < offer; i++) printf(" ");
    printf("^\n");
    for (int i = 0; i < offer; i++) printf(" ");
    printf("|\n\n");
    return ;

}

void reserve (List *l) {
    ListNode *p = l->head.next, *q;
    while(p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return ;
}


void clear_ListNode(ListNode *node) {
    if (node == NULL) return;
    free(node);
    return ;
}

void clear_List(List *l) {
    if (l == NULL) return;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return ;
}
