/*************************************************************************
	> File Name: huffman1.h
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 20时16分07秒
 ************************************************************************/

#ifndef _HUFFMAN1_H
#define _HUFFMAN1_H

HufNode *getNewNode(unsigned char ch, unsigned long per);
void initHuff(HufNode **huf_tree, unsigned long char_kinds, TmpNode *tmp_nodes);

void CombinNode(HufNode **huf_tree, HufNode *a, HufNode *b);
void pick_min(HufNode **huf_tree, unsigned int n);

void getHaffmanTree(HufNode **root, HufNode **huf_tree, unsigned int n); 
void __getHufCode(HufNode *root, unsigned char *str, int k);
void getHufCode(HufNode *root);
void clear(HufNode *root); 
#endif
