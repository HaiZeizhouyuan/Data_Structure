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
} ListNode;

typedef struct List {
    ListNode *head;
    int length;
} List;

int main(){
    srand(time(0));
    #define max_op 20
    List *l = getLinkList();
    int ind, op, val;
    for (int i = 0; i < max_op; i++) {

    }

    return 0;
}

ListNode *getNewNode(int val) {
    ListNode *p = (ListNode *)malloc (sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

List *getLinkList(){
    List *l =  (List)malloc(sizeof(List));
    l->head = NULL;
    l->length = l;
    return l;
}

void clear_node(List *node) {
    
}
