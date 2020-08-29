/*************************************************************************
	> File Name: 4.stack.protice1.c
	> Author: zhouyuan
	> Mail: 
	> Created Time: 2020年08月27日 星期四 11时18分39秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
 
typedef struct Stack {
    int *data;
    int top, size;
} Stack;

Stack *getNewStack(int size);
int expend_stack(Stack *s);
int top(Stack *s);
int empty(Stack *s);
int push(Stack *s, int val);
int pop(Stack *s);
void clear(Stack *s);
void output(Stack *s);

int main() {
    #define max_op 20
    srand(time(0));
    Stack *s = getNewStack(10);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Stack is %s\n", val, push(s, val) ? "sucess" : "faled");
            } break;
            case 3: {
                int t = top(s);
                printf("pop %d from stack is %s\n", t, pop(s) ? "success" : "failed");
            } break;
        }
        output(s);
    }
    clear(s);
    #undef max_op
    return 0;
}

Stack *getNewStack(int size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * size);
    s->top = -1;
    s->size = size;
    return s;
}

int expend_stack(Stack *s) {
    int extr_size = s->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(s->data, sizeof(int) * (s->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
    s->size += extr_size;
    s->data = p;
    return 1;
}

int top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int push(Stack *s, int val) {
    if (s == NULL) return 0;
    if (s->top == s->size - 1) {
        expend_stack(s);
        printf("\033[31mexpend stack is success, and new size is %d\n\n\033[0m", s->size);
    }
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("Stack(%d) : ", s->size);
    for (int i = 0; i <= s->top; i++) {
        i && printf(",");
        printf("%d", s->data[i]);
    }
    printf("\n\n");
}
