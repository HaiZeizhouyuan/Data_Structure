/*************************************************************************
	> File Name: main.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月30日 星期六 23时29分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<stdbool.h>
#include "./compress.h"
#include "./deexpression.h"

#define FILE_SIZE 260
char inFileName[FILE_SIZE + 5], outFileName[FILE_SIZE + 5];

void com_status_determine(int comStatus, char *deterFile, int comOrDecom) {
    if (comStatus == 1) {
        comOrDecom && printf("decompression %s is success!\n", deterFile);
        !comOrDecom && printf("compress %s is success!\n", deterFile);
    } else if (comStatus == 0){
        printf("sorry, %s doesn't exist!\n", deterFile);
    } else {
        comOrDecom && printf("sorry, %s decompression failed!\n", deterFile);
        !comOrDecom && printf("sorry, %s compress failed!\n", deterFile);
    }
}

int main(int argc, char **argv) {
    int opt;
    char ope[10];
    int comStatus = true;
    while((opt = getopt(argc, argv, " z:i:o:")) != -1) {
        switch(opt) {
            case 'z': {
                strncpy(ope, optarg, strlen(optarg));
            } break;
            case 'i': {
                strncpy(inFileName, optarg, strlen(optarg));
            }
            break;
            case 'o': {
                strncpy(outFileName, optarg, strlen(optarg));
            } break;
            default:
                fprintf(stderr, "Usage : %s [-zio!]\n", argv[0]);
                exit(0);
        }
    }
    
    if (!strlen(inFileName) || !strlen(ope)) {
        fprintf(stderr, "Usage : %s [-zio!]\n", argv[0]);
        exit(0);
    } 
    if (strncmp(ope, "tar", strlen("tar")) == 0){
        if (!strlen(outFileName)){
            sprintf(outFileName, "%s.zip", inFileName);
        } 
       
        comStatus = compress(inFileName, outFileName);
        com_status_determine(comStatus, inFileName, 0);
    }else if (strncmp(ope, "untar", strlen("untar")) == 0) {
        if (!strlen(outFileName)) {
            strncpy(outFileName, inFileName, strlen(inFileName) - 4);
        }
        comStatus = deexpression(inFileName, outFileName);
        com_status_determine(comStatus, inFileName, 1);
    }
    printf("z : %s, in : %s, ou: %s \n", ope, inFileName, outFileName);

    return 0;
}
