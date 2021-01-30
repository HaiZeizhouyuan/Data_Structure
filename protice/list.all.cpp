/*************************************************************************
	> File Name: list.all.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月21日 星期四 12时01分41秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

//往链表末尾添加元素
    
ListNode *AddToTail(ListNode *pHead, int value) {
    ListNode *pNew = new ListNode();
    pNew->val = value;
    pNew->next = nullptr;
    if (pHead == nullptr) {
        return pNew;
    } else {
        ListNode *p = pHead;
        while(p->next) {
            p = p->next;
        }
        p->next = pNew;
    }
    return pHead;
}

// 打印链表



//删除某个节点


int main() {
 
 
    return 0;
}
