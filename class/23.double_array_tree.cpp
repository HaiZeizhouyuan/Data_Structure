/*************************************************************************
	> File Name: 23.double_array_tree.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月24日 星期日 08时47分07秒
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
    int flag;
    struct Node *next[BASE];
} Node;

typedef struct DAnode {
    int base, check;
} DANode;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(p->next));
    return p;
}

inline int code(char c) {
    return c - 'a';
}

int insert(Node *root, const char *str) {
    int cnt;
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int ind = code(str[i]);
        if (p->next[ind] == NULL) {
            cnt += 1;
            p->next[ind] = getNewNode();
        }
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear_trie(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear_trie(root->next[i]);
    }
    free(root);
    return ;
}

//根节点的base都是2
int get_base_value(Node *root, DAnode *tree, int ind) {
    int base = 1, flag;
    do {
        base += 1;
        flag = 1;
        for (int i = 0; i < BASE && flag; i++) {
            if (root->next[i] == NULL) continue;
            if (tree[base + i].check) {
                flag = 0;
            }
        }
    } while(flag == 0);
    return base;
}
int transform_doule_array_trie(Node *root, DAnode *tree, int ind) {
    if (root == NULL) return 0;
    if (root->flag) tree[ind].check = -tree[ind].check;
    int base = get_base_value(root, tree, ind);
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        tree[base + i].check = ind;
    }
    int max_ind = ind;
    for (int i = 0; i < BASE; i++) {
        int a = transform_doule_array_trie(root->next[i], tree, base + i);
        if (a > max_ind) max_ind = a;
    }
    return max_ind;
}


int main() {
    int n, cnt = 1;
    char str[100];
    scanf("%d", &n);
    Node *root = getNewNode();
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        cnt += insert(root, str);
    }
    size_t tree_size = sizeof(DAnode) * (cnt * BASE);
    DAnode *tree = (DAnode *)malloc(tree_size);
    memset(tree, 0, tree_size);
    int max_ind = transform_doule_array_trie(root, tree, 1);
    for (int i = 0; i <= max_ind; i++) {
        printf("(%d | %d, %d)\t", i, tree[i].base, tree[i].check);
        if ((i + 1) % 4 == 0) printf("\n");
    }
 //   build_ac_base_double_arry_trie(tree, max_ind);
    printf("\n");
    free(tree);
    clear_trie(root);
    return 0;
}
