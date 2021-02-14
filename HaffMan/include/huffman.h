/*************************************************************************
	> File Name: huffman.h
	> Author: 
	> Mail: 
	> Created Time: 2021年02月04日 星期四 13时15分32秒
 ************************************************************************/

#ifndef _HUFFMAN_H
#define _HUFFMAN_H
void selects(HufNode *huf_tree, unsigned int n, int *s1, int *s2);

//初始化哈弗曼树
void initHuff(HufNode *huf_tree, unsigned int char_kinds,TmpNode *tmp_nodes,unsigned int node_num);

// 建立哈夫曼树
void CreateTree(HufNode *huf_tree, unsigned int char_kinds, unsigned int node_num);

// 生成哈夫曼编码
void HufCode(HufNode *huf_tree, unsigned char_kinds);

//释放哈弗曼
void clear(unsigned char_kinds, HufNode *huf_tree);

#endif
