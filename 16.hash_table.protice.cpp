/*************************************************************************
	> File Name: 16.hash_table.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul  7 21:00:11 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_m 100
typedef struct Node {
    char str;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **data;
    int size;
} HashTable;

Node *init_node(char str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = str;
    p->next = head;
    return p;
}

HashTable *init_hashtable (int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(h->size, sizeof(Node *));
    return h;
}

int BKDRHASH (char str) {
    int seed = 31, hash = 0;
    hash = hash * seed + str;
    return hash & 0x7fffffff;
}


int insert(HashTable *h, char str){
    int hash = BKDRHASH(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
}

int search(HashTable *h, char str) {
    int hash = BKDRHASH(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    return p != NULL;
}

void clear_node(Node *node) {
    if(node == NULL) return ; 
    free(node);
    return ;
}

void clear_hashtable(HashTable *h) {
    if (h == NULL) return ;
    for (int i = 0; i < h->size; i++) clear_node(h->data[i]);
    free(h->data);
    free(h);
}

bool containsDuplicate(int* nums, int numsSize){
    HashTable *h  = init_hashtable(numsSize);
    char str[numsSize];
    for (int i = 0; i < numsSize; i++) {
        sprintf(str + i, "%d", nums[i] );
        if (search(h, str[i])) {
            return true;
        } else {
            insert(h, str[i]);
        }
    }
    return false;
}
int main () {
    int nums[15];
    int i;
    for (i = 0; i < 5; i++)  {
        scanf("%d", nums + i);
    }
    int numsSize = i;
    /*for (int j = 0; j < 5; j++) {
        printf("%d ", nums[j]);
    }*/
    printf("%s\n",containsDuplicate(nums, numsSize) == true ? "true" : "false");
    return 0;
}
