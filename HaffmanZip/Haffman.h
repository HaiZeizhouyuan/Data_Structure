/*************************************************************************
	> File Name: Haffman.h
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月31日 星期日 14时07分37秒
 ************************************************************************/

#ifndef _HAFFMAN_H
#define _HAFFMAN_H
HafNode *getNewNode(unsigned char ch, unsigned long weigth);
HafNode *getHaffmanTree(HafNode **arr, int n);
void HufCode(HafNode *root, HafNode *haf_node);
void clear(HafNode *root);
#endif

