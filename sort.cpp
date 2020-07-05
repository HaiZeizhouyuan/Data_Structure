/*************************************************************************
	> File Name: sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul  5 10:13:42 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}
//合并排序
void merge_sort(int *data, int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    merge_sort(data, l, mid);
    merge_sort(data, mid + 1, r);
    int temp[r - l + 1], x = l, y = mid + 1, loc = 0;
    while (x <= mid || y <= r) {
        if (x <= mid && (y > r || data[x] <= data[y])) {
            temp[loc] = data[x];
            x++;
        } else {
            temp[loc] = data[y];
            y++;
        }
        loc += 1;
    }
    for (int i = l; i <= r; i++) data[i] = temp[i  - l]; 

}
// 插入排序
void insert_sort(int *data, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
            }
            else break;
        }
    }
}
//冒泡排序
void bubble_sort (int *data, int length) {
    for (int i = 0; i < length - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < length - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}

void output(int *data, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", data[i]);
    }
    printf("]");
    printf("\n");
}

//选择排序
void select_sort(int *data, int n) {
    for (int i = 0; i < n - 1; i++ ) {
        int temp = i;
        for (int j = i + 1; j < n; j++){
            if (data[temp] > data[j]) temp = j;
        }
        if (temp - i) swap(data[temp], data[i]); 
    }
}

void quick_sort(int *data, int left, int right) {
	if (left > right) return ;
    int pivot = data[left], low = left, high = right;
    while(low < high) {
        while(low < high && data[high] >= pivot  ) high--;    
        data[low] = data[high];
        while(low < high &&  data[low] <= pivot) low++;
        data[high] = data[low];
    }
  	data[low] = pivot;
    quick_sort(data, left, low - 1);
    quick_sort(data,low + 1, right);
}

int main() {
    srand(time(0));
    #define max_op 20
    int data[max_op  + 5];
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        data[i] = val;
    }
    merge_sort(data, 0, max_op - 1);
    printf("merge_sort : ");
    output(data, max_op);
    insert_sort(data, max_op - 1);
    printf("insert_sort : ");
    output(data, max_op);
    bubble_sort(data, max_op - 1);
    printf("bubble_sort : ");
    output(data, max_op);
    select_sort(data, max_op);
    printf("select_sort : ");
    output(data, max_op);
    quick_sort(data,0, max_op - 1 );
    printf("quick_sort : ");
    output(data, max_op);
    return 0;
}
