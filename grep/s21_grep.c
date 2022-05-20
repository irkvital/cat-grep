#include "../common/common_func.h"
#include <string.h>
#include <regex.h>

#define COLORRED "\x1B[1;31m"
#define COLORDEFAULT "\x1B[0m"

#define SUCCEED 0b0
#define ERROR 0b1
#define E_FLAG 0b10
#define I_FLAG 0b100
#define V_FLAG 0b1000
#define C_FLAG 0b10000
#define L_FLAG 0b100000
#define N_FLAG 0b1000000
// Бонусная часть
//#define H_FLAG 0b10000000
//#define S_FLAG 0b100000000
//#define F_FLAG 0b1000000000
//#define O_FLAG 0b10000000000

int ParserFlagsGrep(int argc, char* argv[]);
int MinusFlag(char* argv[]);

int main(int argc, char* argv[]) {
    int flags = ParserFlagsGrep(argc, argv);
    if (flags & ERROR) {
        printf("invalid option");
    } else {
        MainCircle(argc, argv, flags);
    }
}

int ParserFlagsGrep(int argc, char* argv[]) {
    int flags = SUCCEED;
    for(int row = 0; (row < argc) && (flags & ERROR) == 0; row++) {
        int length = strlen(argv[row]);
        if(argv[row][0] == '-' && length > 1) {
            flags |= MinusFlag(&argv[row]);
        } else if(length == 1) {
            // Реализовать вывод в консоль для флага -
        }
    }
    return flags;
}

int MinusFlag(char* argv[]) {
    int flags = SUCCEED;
    for(int i = 1; (*argv)[i]; i++) {
        if((*argv)[i] == 'E') { // E или e уточнить!!! Добавить бонусные флаги.
            flags |= E_FLAG;
        } else if((*argv)[i] == 'i') {
            flags |= I_FLAG;
        } else if((*argv)[i] == 'v') {
            flags |= V_FLAG;
        } else if((*argv)[i] == 'c') {
            flags |= C_FLAG;
        } else if((*argv)[i] == 'l') {
            flags |= L_FLAG;
        } else if((*argv)[i] == 'n') {
            flags |= N_FLAG;
        } else {
            flags |= ERROR;
        }
    }
    return flags;
}

void ReadAndWrite(FILE* fp, int flags, int* string_number) {
    //int length = strlen(fp);
    regex_t regex;
    regmatch_t pmatch[3];
    const size_t nmatch = 3; 
    int reti = 0, i = 0;
    reti = regcomp(&regex, "a", REG_EXTENDED | REG_NEWLINE); // REG_EXTENDED   REG_ICASE -не различать регистр
    if(reti) {
        printf("Couldn't compile regex\n");
    } else {
        reti = regexec(&regex, fp, nmatch, pmatch, 0);
        if(!reti) {
            //printf("& %lld %lld %lld %lld &\n", pmatch[0].rm_so, pmatch[1].rm_so, pmatch[0].rm_eo, pmatch[1].rm_eo);
            puts("Match\n");
            // for(; i < pmatch[0].rm_eo; i++) {
            //     if(i >= pmatch[0].rm_so && i < pmatch[0].rm_eo) {
            //         printf(COLORRED "%c", fp[i]);
            //     } else {
            //         printf(COLORDEFAULT "%c", fp[i]);
            //     }
            // }
        } else {
            puts("Not match\n");
        }
    }
}