/*************************************************************************
	> File Name: compress.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月31日 星期日 10时55分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include "./data.h"
//#include "./Haffman.h"

unsigned int char_kinds;//字符种类
FILE *infile, *outfile;//待解压的文件和解压后的文件
unsigned char char_temp;//暂存8bits字节
unsigned long file_len = 0;//文件大小
char code_buff[CHAR_NUM + 5] = "\0";//待存比编码缓存区
unsigned int code_len;//最后不足8 bit的字节的长度
unsigned int node_num = 0;
HafNode *haf_node;
//初始化节点数组
void initNode(TmpNode *tmp_nodes) {
    for (int i = 0; i < CHAR_NUM; i++) {
        tmp_nodes[i].weight = 0;
        tmp_nodes[i].uch = (unsigned char)i;//数组的下标与字符相对应
    }
    return ;
}

//获取中值
unsigned long middle(unsigned long  a, unsigned long b, unsigned long c) {
    if (a > b)  swap(a, b);
    if (a > c)  swap(a, c);
    if (b > c) swap(b, c);
    return b;
}

//快速排序
void quickSort(TmpNode *tmp_nodes, int l, int r) {
    while(l < r) {
        int x = l, y = r, z = (l + r) >> 1;
        unsigned long midNum = middle(tmp_nodes[x].weight, tmp_nodes[z].weight, tmp_nodes[y].weight);
        do {
            while(x <= y && tmp_nodes[x].weight > midNum) x++;
            while(x <= y && tmp_nodes[y].weight < midNum) y--;
            if (x <= y) {
                swap(tmp_nodes[x], tmp_nodes[y]);
                x++, y--;
            }
        }while(x <= y);
        quickSort(tmp_nodes, x, r);
        r = y;
    }
    return ;
}

//统计实际节点数量
int charKinds(TmpNode *tmp_nodes) {
    for (int i = 0; i < CHAR_NUM; i++) {
        if(tmp_nodes[i].weight == 0) return i;
    }
    return CHAR_NUM;
}

//单字符文件的压缩
int singleChar(TmpNode *tmp_nodes, char *ofname) {
    outfile = fopen(ofname, "wb");
    if (outfile == NULL) {
        perror("fopen outfile failes!");
        return -1;
    }
    printf("sing\n");
    printf("k : %d, c : %c, w : %ld\n", 1, tmp_nodes[0].uch, tmp_nodes[0].weight);
    fwrite((char *)&(char_kinds), sizeof(unsigned int), 1, outfile); //写入字符种类
    fwrite((char *)&tmp_nodes[0].uch, sizeof(unsigned char), 1, outfile);//写入唯一的字符
    fwrite((char *)&tmp_nodes[0].weight, sizeof(unsigned long), 1, outfile);//写入字符权重, 也就是文件长度
    free(tmp_nodes);
    fclose(outfile);
    return 1;

}
//写入字符和响应的权重, 供解压时重建哈弗曼树
void inputTreeToFile(HafNode *haf_node, char *ifname, char *ofname) {
    outfile = fopen(ofname, "wb");
    fwrite((char *)&char_kinds, sizeof(unsigned int), 1, outfile);//写入字符种类
    for (int i = 0; i < char_kinds; i++) {
        fwrite((char *)&haf_node[i].ch, sizeof(unsigned char), 1, outfile);//写入字符
        fwrite((char *)&haf_node[i].weight, sizeof(unsigned), 1, outfile);//写入权重
    }

    fwrite((char *)&(file_len), sizeof(unsigned long), 1, outfile);//写入文件长度
    infile = fopen(ifname, "rb");
    fread((char *)&char_temp, sizeof(unsigned char), 1, infile);
  
    while(!feof(infile)) {
        for (int i = 0; i < char_kinds; i++) {
            if (char_temp == haf_node[i].ch) {
                strcat(code_buff, haf_node[i].code);
                printf("ch :%c, code : %s\n", char_temp, haf_node[i].code);
                break;
            }
        }
        //以8个字节长度为处理单元
        while(strlen(code_buff) >= 8) {
            char_temp = '\0';
            for (int i = 0; i < 8; i++) {
                char_temp <<= 1;
                if (code_buff[i] == '1') char_temp |= 1;
            }
            fwrite((char *)&char_temp, sizeof(unsigned char), 1, outfile);
            strcpy(code_buff, code_buff +  8);
        }
        fread((char *)&char_temp, sizeof(unsigned char), 1, infile);
    }
    //处理最后不足8bits的编码
    code_len = strlen(code_buff);
    if (code_len > 0) {
        char_temp = '\0';
        for (int i = 0; i < code_len; i++) {
            char_temp <<= 1;
            if (code_buff[i] == '1') {
                char_temp |= 1;
            }
            char_temp <<= 8 - code_len;//将编码字段从尾部移到字节的高位
            fwrite((char *)&char_temp, sizeof(unsigned char), 1, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
    return ;

}

//压缩文件
int compress(char *ifname, char *ofname) {
    TmpNode *tmp_nodes = (TmpNode *)calloc(CHAR_NUM,  sizeof(TmpNode));
    initNode(tmp_nodes);//初始化节点数组
    if ((infile = fopen(ifname, "rb")) == NULL) {//打开待解压的文件
        perror("fopen infile failed!");
        return -1;
    }
    //遍历待解压的文件,统计每个字符的权重,以及计算文件大小
    fread((char *)&char_temp, sizeof(unsigned char), 1, infile);
    while(!feof(infile)) {
        ++tmp_nodes[char_temp].weight;
        ++file_len;
        fread((char *)&char_temp, sizeof(unsigned char), 1, infile);
    }
    fclose(infile);
    //按照权重的大小对节点从大到小排序
    quickSort(tmp_nodes, 0, CHAR_NUM - 1);
    //统计实际节点数量
    char_kinds = charKinds(tmp_nodes);
    if (char_kinds == 2) {//加上结尾的回车符
        int sig_res = singleChar(tmp_nodes, ofname);
        if (sig_res < 0) return -1;     
    }else {
        HafNode **arr = (HafNode **)calloc(sizeof(HafNode *), (2 * char_kinds - 1));
        for (int i = 0; i < char_kinds; i++) {
             getNewNode(arr, tmp_nodes[i].uch, tmp_nodes[i].weight);    
        }
        free(tmp_nodes);
        haf_node = (HafNode *)calloc(sizeof(HafNode),  (2 * char_kinds - 1)); 
        getHaffmanTree(arr, char_kinds);
        HufCode(haf_node, root, haf_node);
        inputTreeToFile(haf_node, ifname, ofname);
        clear(root);
        free(arr);
        free(haf_node);
    }

}

