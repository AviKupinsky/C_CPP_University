#ifndef BONUS
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cipher.h"
#include "tests.c"
#define ENCODE "encode"
#define DECODE "decode"
#define FIRST_ERROR \
"Usage: cipher <encode|decode> <k> <source path file> <output path file>\n"
#define SECOND_ERROR "The given shifts value is invalid\n"
#define THIRD_ERROR  "The given command is invalid\n"
#define FOURTH_ERROR  "The given file is invalid\n"
#define  THE_COMMAND 1
#define  THE_NUMBER  2
#define  INPUT_FILE  3
#define  OUTPUT_FILE 4
#define  NUM_ARG 5
#define  LENGTH_NUM  10
#define  NAME_FILE  20
#define  BUFFERE_NUM 128

/**
 *
 * @param x: number int
 * @param y :number int
 * @return 0 or 1 bast if the count eq to y
 * the function checks if the length of x is the same as y.
 */
int checking_second_problem(long x,int y){
    int count = 0;
    while (x != 0){
        x = x/LENGTH_NUM;
        count++;
    }
    if(count != y){
        return 0;
    }
    else{
        return 1;
    }
}

/**
 *
 * @param x int number
 * @param y int number
 * @return 0 or 1
 * the function checks if x or y are not 0.
 */
int checking_third_problem(int x, int y){
    if ((x != 0) && (y != 0)) {
        return 0;
    }
    else{
        return 1;
    }
}

/**
 *
 * @param y x int number
 * @param z x int number
 * @param w x int number
 * @return 0 or 1
 * this function checks if ant if the ints are 0,
 * and if there are it prints an error comment
 */
int checking_the_check(int y, int z, int w){
    if (y == 0){
        fprintf(stderr, "%s", SECOND_ERROR);
        return 0;
    }
    if (z == 0){
        fprintf(stderr, "%s", THIRD_ERROR);
        return 0;
    }
    if (w == 0){
        fprintf(stderr, "%s", FOURTH_ERROR );
        return 0;
    }else{
        return 1;
    }
}

/**
 *
 * @param memory : is symbols the buffer where we keep the memory
 * @param first_file : the input_file
 * @param second_file :the output_file
 * @param result : this is checking witch
 * command we should use, decode are encode
 * @param num : an int that tells as how much we should go.
 */
void reading_file(char *memory,FILE * first_file,
                  FILE *second_file, int result,int num){
    while (fgets(memory,sizeof(memory) ,first_file) != NULL)
        if (result == 0){
            encode(memory,num);
            fprintf(second_file,"%s", memory);
        } else{
            decode(memory,num);
            fprintf(second_file,"%s", memory);
        }
}

int main(int argc, const char *argv[]) {
    int end, second_check, third_check,
    fourth_check, first_result, second_result;
    char buffer[BUFFERE_NUM] = {0};
    char str1[NAME_FILE] = {0};
    char str2[NAME_FILE] = {0};

    //    first_check = checking_first_problem(argc);
    if (argc != NUM_ARG){
        fprintf(stderr, "%s", FIRST_ERROR);
        return EXIT_FAILURE;
    }

    // we are checking the second error
    int check_if_zero = strcmp(argv[THE_NUMBER], "0");
    int length = strlen(argv[THE_NUMBER]);
    long num_k = strtol(argv[THE_NUMBER], NULL, LENGTH_NUM);
    if(num_k < 0){
        length = length -1;
    }
    if (check_if_zero == 0){
        second_check = 1;
    } else{
        second_check = checking_second_problem(num_k, length);
    }

    // we are checking the third error
    first_result = strcmp(argv[THE_COMMAND], ENCODE);
    second_result = strcmp(argv[THE_COMMAND], DECODE);
    third_check = checking_third_problem(first_result, second_result);

    // we are checking the fourth error
    strcat(str1, argv[INPUT_FILE]);
    strcat(str2, argv[OUTPUT_FILE]);
    FILE *fd = fopen(str1, "r");
    if (fd == NULL) {
        fourth_check = 0;
    } else {
        fourth_check = 1;
    }

    // we are checking if any of the error
    // happened, and we need to print a statement
    end = checking_the_check(second_check,
                             third_check, fourth_check);

    //if there was an error we need to close the file and end this run
    if (end == 0) {
        if (fd != NULL) {
            fclose(fd);
        }
        return EXIT_FAILURE;
    }

    FILE *file = fopen(str2, "w");
    reading_file(buffer, fd, file, first_result, num_k);
    fclose(fd);
    fclose(file);
    return EXIT_SUCCESS;
}
#endif
