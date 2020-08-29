/*************************************************************************
	> File Name: 4.stack.protice2.c
	> Author: zhouyuan
	> Mail: 
	> Created Time: 2020年08月27日 星期四 15时25分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

typedef struct Stack {
    char *str;
    int size, top;
} Stack;

Stack *getNewStack (int size);
int expend(Stack *s);
char top(Stack *s);
int empty(Stack *s);
int push(Stack *s, char str);
int pop(Stack *s);
void clear(Stack *s);
void output(Stack *s);

char word[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int main() {
    #define max_op 20
    srand(time(0));
    Stack *s = getNewStack(10);
    for (int i = 0; i < max_op; i++) {
        char str = word[rand() % 26];
        int op = rand() % 4;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                int flag = push(s, str);
                printf("push %c to stack is %s\n", str, flag ? "success" : "failed");
                } break;
            case 3: {
                char t = top(s);
                printf("pop %c from stack is %s\n", t, pop(s) ? "success" : "failed");
                } break ;
        }
        output(s);
    }
    clear(s);
    #undef max_op

    return 0;
}

Stack *getNewStack(int size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->str = (char *)malloc(sizeof(char) * size);
    s->top = -1;
    s->size = size;
    return s;
}

int expend(Stack *s) {
    int extr_size;
    char *p;
    while (extr_size) {
        p = (char *)realloc(s->str, sizeof(char) * (s->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p) return 0;
    s->size += extr_size;
    s->str = p;
    return 1;
}

int push(Stack *s, char str) {
    if (s == NULL) return 0;
    if (s->top == s->size - 1) {
        printf("expend Stack is %s, and it new size is %d\n\n", expend(s) ? "success" : "failed", s->size);
    }
    s->str[++(s->top)] = str;
    return 1;
}

char top(Stack *s) {
    return s->str[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if(s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->str);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("Stack(%d) : ", s->size);
    for (int i = 0; i <=s->top; i++) {
        i && printf(",");
        printf("%c", s->str[i]);
    }
    printf("\n\n");
}

