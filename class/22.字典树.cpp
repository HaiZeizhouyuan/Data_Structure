/*************************************************************************
	> File Name: 22.字典树.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月21日 星期四 20时06分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 26

typedef struct Node {
    int flag;//当前节点是否独立成词
    struct Node *next[BASE];//26个英文字母
} Node;

Node *getNewNode(){
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(p->next));
    return p;
}

void insert(Node *p, const char *s) {
    for (int i = 0; s[i]; i++) {
        int ind = s[i] - 'a';
        if (p->next[ind] == NULL) p->next[ind] = getNewNode();
        p = p->next[ind];
    }
    p->flag = 1;
    return ;
}

void clear(Node *root){
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}
//k是层数
void output(Node *root, int k, char *s) {
    s[k] = 0;
    if (root->flag) {
        printf("%s\n", s);
    }
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        s[k] = 'a' + i;
        output(root->next[i], k + 1, s);
    }
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
    output(root, 0, str);
    clear(root);
    return 0;
}
