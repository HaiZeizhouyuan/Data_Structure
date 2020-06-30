/*************************************************************************
	> File Name: 7.Hafuman_tree.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jun 30 10:15:20 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_n 1000

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b, b = __temp;\
}

typedef struct Node {
    char ch;
    double p;
    struct Node *child[2];
} Node;

typedef struct Data {
    char ch;
    double p;
} Data;

typedef struct Codes {
    char ch;
    char *str;
} Codes;

typedef struct Haffman_tree {
    Node *root;
    int n;
    Codes *codes;
} Haffman_tree;

Data data[max_n + 5];

Node *getNewNode (Data *obj) {
    Node *p = (Node *)malloc (sizeof(Node));
    p->ch = (obj ? obj->ch : 0); 
    p->p = obj ? obj->p : 0;
    p->child[0] = p->child[1] = NULL;
    return p;
}

Haffman_tree *getNewTree(int n) {
    Haffman_tree *tree = (Haffman_tree *)malloc(sizeof(Haffman_tree));
    tree->codes = (Codes *)malloc(sizeof(Codes) * n);
    tree->n = n;
    tree->root = NULL;
    return tree;
}

void inserttOnce(Node **data, int n) {
    for (int j = n; j >= 1; j--) {
        if(data[j]->p > data[j - 1]->p) {
            swap(data[j], data[j - 1]);
            continue;
        } 
        break;
    }
    return ;
}

int extract_Codes(Node *root, Codes *data, int k, int l, char *buff) {
    buff[l] = 0;
    if (root->child[0] == NULL && root->child[1] == NULL) {
        data[k].ch = root->ch;
        data[k].str = strdup(buff);
        return 1;
    }
    int deleta = 0;
    buff[l] = '0';
    deleta += extract_Codes(root->child[0], data, k + deleta, l + 1, buff);
    buff[l] = '1';
    deleta += extract_Codes(root->child[0], data, k + deleta, l + 1, buff);
    return deleta;
}

Haffman_tree *build (Data *data, int n) {
    Node **nodes = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = getNewNode(data + i);
    }
    for (int i = 1; i < n; i++) {
        inserttOnce(nodes, i);
    }
    for (int i = n -1; i >= 1; i--) {
        Node *p = getNewNode(NULL);
        p->p = nodes[i]->p + nodes[i - 1]->p;
        p->child[0] = nodes[i - 1];
        p->child[1] = nodes[i];
        nodes[i - 1] = p; 
        inserttOnce(nodes, i - 1);
    }
    char *buff = (char *)malloc(sizeof(char *) * n);
    Haffman_tree *tree = getNewTree(n);
    tree->root = nodes[0];
    extract_Codes(tree->root, tree->codes, 0, 0, buff);
    free(nodes);
    free(buff);
    return tree;
}

int main () {
    int n;
    char str[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s%lf", str, &data[i].p);//str是字符加空格, %s可读空格， %c不可读空格。
        data[i].ch = str[0];
    }
    Haffman_tree *tree = build(data, n);
    for (int i = 0; i < tree->n; i++) {
        printf("%c : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    return 0;
}

