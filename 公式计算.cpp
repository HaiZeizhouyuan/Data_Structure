/*************************************************************************
	> File Name: gongshiyunshuan.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jun 30 20:22:29 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define max_n 100

typedef struct Stack {
    double *data;
    int size, top;
} Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (double *)malloc(sizeof(double) * n);
    s->size = n;
    s->top = -1;
}

int push_num(Stack *s, double val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++(s->top)] = val;
    return 1;
}

double top_num(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

int precede (int a, int b){
    int class_a , class_b;
    if (a == '+'|| a == '-') class_a = 1;
    else class_a = 2;
    if (b == '+' || b == '-') class_b = 1;
    else class_b = 2;
    return class_a > class_b;
}

double operate(int sym, double a, double b) {
    switch (sym) {
        case '+' : 
            return a + b;
            break;
        case '-':
            return b - a;
            break;
        case '*':
            return a * b;
            break;
        case '/' :
            return b * 1.0 / a;
            break;
        default :
            return 0;
    }
}

void calc(Stack *num, Stack *sym) {
    double a = top_num(num);
    pop(num);
    double b = top_num(num);
    pop(num);
    push_num(num, operate(top_num(sym), a, b));
    pop(sym);
    return ;
}

int is_dight(int str) {
    if (str - '0' >= 0 && str - '0' <= 9) return 1;
    else return 0;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int merge (int *arr) {
    int sum = 0;
    for (int i = 1; i <= arr[0]; i++ ) {   
        sum += arr[i] * pow(10, (arr[0] - i));
    }
    return sum;
}

void numop(int i, char *str, int *arr, Stack *num){
    str[i] -= '0';
    arr[++arr[0]] += str[i]; 
    if (!is_dight(str[i + 1]))  {
        push_num(num, merge(arr));
        memset(arr, 0, 100);  
    }
    return ;
}

void blacket(Stack *sym, Stack *num, int i) {
    if (top_num(sym) != '(') {
        calc(num, sym);
    } else {
        pop(sym);
        i += 1;
    }
    return ;
}

int main () {
    int arr[max_n + 5] = {0};
    Stack *num = init(max_n);
    Stack *sym = init(max_n);
    char str[max_n + 5];
    scanf("%[^\n]s", str);
    int len = strlen(str), w = 0;
    int i = 0;
    while (i < len) {
        if (is_dight(str[i])) { 
            numop(i, str, arr, num);
            i += 1;
        } else if (str[i] == ' ') {
            i += 1;
        } else {
            if (str[i] == ')') {
                if (top_num(sym) != '(') calc(num, sym);
                else {
                    pop(sym);
                    i += 1;
                }
            } else if (empty(sym) || precede(str[i], top_num(sym)) || (str[i] == '(') || ( top_num(sym) == '(')) {
                push_num(sym, str[i]);
                i += 1;
            } else {
                calc(num, sym);
            }
        }
    }
    while(!empty(sym)) calc(num, sym);
    printf("%.2lf\n", top_num(num));
    clear(num);
    clear(sym);
    return 0;
}

