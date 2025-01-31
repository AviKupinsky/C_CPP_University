
#ifndef CIPHER
#define CIPHER
#include <string.h>
#include <stdio.h>
#define  INT_NUM 26

void encode(char * p,int k){
    int temp;
    if (k > INT_NUM){
        while (k > INT_NUM)
        k = (k - INT_NUM);
    } else if(k< - INT_NUM){
        while (k< - INT_NUM)
            k = (k + INT_NUM);
    }
    for (int i = 0; i < p[i]; ++i) {
        temp = p[i];
        if((temp >= 'a') && (temp <= 'z')) {
            temp = (temp + k);
            if (temp > 'z') {
                temp = (temp - 'z' + 'a' - 1);
            } else if (temp < 'a'){
                temp = (temp - 'a' + 'z' + 1);
            }
            p[i] = temp;
        } else if((temp >= 'A') && (temp<= 'Z')){
            temp = (temp +k);
            if (temp > 'Z'){
                temp = (temp -'Z' + 'A' -1);
            }else if (temp < 'A'){
                temp = (temp - 'A' + 'Z' + 1);
            }
            p[i] = temp;
        }
    }
}


void decode(char * p,int k){
    int temp;
    if (k > INT_NUM){
        while (k > INT_NUM)
            k = (k - INT_NUM);
    } else if(k< - INT_NUM){
        while (k< - INT_NUM)
            k = (k + INT_NUM);
    }
    for (int i = 0; i < p[i]; ++i) {
        temp = p[i];
        if((temp >= 'a') && (temp <= 'z')) {
            temp = (temp - k);
            if (temp < 'a') {
                temp = (temp - 'a' + 'z' + 1);
            } else if (temp > 'z') {
                temp = (temp - 'z' + 'a' - 1);
            }
            p[i] = temp;
        } else if((temp >= 'A') && (temp<= 'Z')){
            temp = (temp - k);
            if (temp < 'A'){
                temp = (temp -'A' + 'Z' + 1);
            } else if (temp > 'Z'){
                temp = (temp -'Z' + 'A' -1);
            }
            p[i] = temp;
        }
    }
}

#endif