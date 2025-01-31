
#include "cipher.h"
#include <string.h>
#define  JUMP_NUM_2  2
#define  JUMP_NUM_3  3
#define  JUMP_NUM_28 28
#define  JUMP_NUM_5 5


int test_encode_1(){
    int num = JUMP_NUM_2;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz";
    char result[] = "cdefghijklmnopqrstuvwxyzab";
    encode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}

int test_encode_2(){
    int num = JUMP_NUM_2;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char result[] = "cdefghijklmnopqrstuvwxyzab"
                    "CDEFGHIJKLMNOPQRSTUVWXYZAB";
    encode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}


int test_encode_3(){
    int num = -JUMP_NUM_5;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ*";
    char result[] = "vwxyzabcdefghijklmnopqrstu"
                    "VWXYZABCDEFGHIJKLMNOPQRSTU*";
    encode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}


int test_encode_4(){
    {
        int num = JUMP_NUM_28;
        int comparing;
        char new[] = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ%$";
        char result[] = "cdefghijklmnopqrstuvwxyzab"
                        "CDEFGHIJKLMNOPQRSTUVWXYZAB%$";
        encode(new, num);
        comparing = strcmp(new,result);
        if (comparing != 0 ){
            return 0;
        } else{
            return 1;
        }
    }

}

int test_decode_1(){
    int num = JUMP_NUM_2;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz";
    char result[] = "yzabcdefghijklmnopqrstuvwx";
    decode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}


int test_decode_2(){
    int num = JUMP_NUM_3;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char result[] = "xyzabcdefghijklmnopqrstuvw"
                    "XYZABCDEFGHIJKLMNOPQRSTUVW";
    decode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}


int test_decode_3(){
    int num = -JUMP_NUM_5;
    int comparing;
    char new[] = "abcdefghijklmnopqrstuvwxyz"
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ*";
    char result[] = "fghijklmnopqrstuvwxyzabcde"
                    "FGHIJKLMNOPQRSTUVWXYZABCDE*";
    decode(new, num);
    comparing = strcmp(new,result);
    if (comparing != 0 ){
        return 0;
    } else{
        return 1;
    }
}



int test_decode_4(){
        int num = JUMP_NUM_28;
        int comparing;
        char new[] = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ$%";
        char result[] = "yzabcdefghijklmnopqrstuvwx"
                        "YZABCDEFGHIJKLMNOPQRSTUVWX$%";
        decode(new, num);
        comparing = strcmp(new,result);
        if (comparing != 0 ){
            return 0;
        } else{
            return 1;
        }
    }
