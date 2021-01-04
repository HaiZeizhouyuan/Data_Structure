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
int erase(List *,int);
void reverser(List *);
void output(List *);
void clear_ListNode(ListNode *);
void clear_List(List *);
void outout1(List *, int );
int main(){
    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    int ind, op, val, flag;

    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 1000;
        switch(op) {
            case 0:
            case 1: {
                flag = insert(l, ind, val);
                printf("insert %d at  %d to List = %d\n", val, ind, flag);
            }break;
            case 2: {
                flag = erase(l, ind);
                printf("erase item at %d is from List = %d\n", ind, flag);
            }break;
            case 3: {
                printf("reverse the List !\n");
                reverser(l);
                flag = -1;
            }break;
        }
        output(l);
        outout1(l, flag);
        printf("\n");
    }
    clear_List(l);
    #undef max_op
    return 0;
}

ListNode *getNewNode(int val) {
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

int insert(List *l, int ind, int val) {
    int ret = ind;
    if (l == NULL) return -1;
    if (ind < 0 || ind > l->length) return -1;
    ListNode *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return ret;
}

int erase(List *l, int ind) {
    int ret = ind;
    if (l == NULL) return -1;
    if (ind < 0 || ind >= l->length) return -1;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    l->length -= 1;
    return ret;
}

void output(List *l){
    printf("head->");
    ListNode *p = l->head.next;
    while(p) {
        printf("%d->", p->data);
        p = p->next;
    }
    /*for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d->", p->data);
    }*/
    printf("NULL\n");
    return ;
}
void outout1(List *l, int ind) {
    char str[100];
    int offset = 3;
    ListNode *p = l->head.next;
    while (ind != -1 && p) {
        offset += sprintf(str, "%d->", p->data);
        ind -= 1;
        p = p->next;
    }
    for (int i = 0; i < offset; i++) printf(" ");
    printf("^\n");
    for (int i = 0; i < offset; i++) printf(" ");
    printf("|\n\n");
    return ;

}
//翻转
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
