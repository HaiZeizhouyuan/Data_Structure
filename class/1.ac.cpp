/*************************************************************************
	> File Name: 1.ac.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月23日 星期六 15时06分20秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
 
#define BASE 26

typedef struct Node {
    int flag, tagp[BASE];//1:trie, 0:ac
    char *str;
    struct Node *next[BASE], *fail;//fail等价指针
} Node;

int node_cnt = 0;//一共有多少节点

Node *getNewNode() {
    node_cnt += 1;
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(p->next));
    p->fail = NULL;
    return p;
}


void insert(Node *root, const char *str) {
    for (int i = 0; str[i]; i++ ) {
        int ind = str[i] - 'a';
        if (root->next[ind] == NULL) root->next[ind] = getNewNode();
        root= root->next[ind];
    }
    root->flag = 1;
    root->str = strdup(str);
    return ;
        
}


void build_ac(Node *root) {
    Node **q = (Node **)malloc(sizeof(Node *) * (node_cnt + 5));
    int head = 0, tail = 0;
    root->fail = NULL;
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) {
            root->next[i] = root;
            continue;
        }
        root->next[i]->fail = root;
        q[tail++] = root->next[i];

    }
    while(head < tail) {
        Node *p = q[head++];
        for (int i = 0; i < BASE; i++) {
            Node *c = p->next[i], *k = p->fail;
            if (c == NULL) {
                p->next[i] = k->next[i];
                continue;
            }
            while(k && k->next[i] == NULL) k = k->fail;
            if (k == NULL) k = root;
            if (k->next[i]) k = k->next[i];
            c->fail = k;
            q[tail++] = c;
        }
    }
    free(q);
    return ;
}


void match(Node *root, const char *text) {
    Node *p = root, *q;
    for (int i = 0; text[i]; i++) {
        int ind = text[i] - 'a';
        p = p->next[i];
        q = p;
        while(q) {
            if (q->flag == 1) printf("find : %s\n", q->str);
            q = q->fail;
        }
    }
}
void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}


int main() {
    int n;
    char str[100];
    scanf("%d", &n);
    Node *root = getNewNode();
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(root, str);
    }
    build_ac(root);
    scanf("%s", str);
    match(root, str);
 
    return 0;
}
