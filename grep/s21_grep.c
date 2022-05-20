#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
void MainCircle(int argc, char* argv[], int flags);

int main(int argc, char* argv[]) {
    int flags = ParserFlagsCat(argc, argv);
    if (flags & ERROR) {
        printf("invalid option");
    } else {
        MainCircle(argc, argv, flags);
    }
}

int ParserFlagsCat(int argc, char* argv[]) {
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

void MainCircle(int argc, char* argv[], int flags) {
    for(int row = 1; row < argc; row++) {
        int string_number = 0;
        if(argv[row][0] != '-') {
            FILE *fp;
            if((fp = fopen(argv[row], "r")) == NULL) {
                printf("Can't open file: %s\n", argv[row]);
            } else {
                // Работа с файлом
                ReadAndWrite(fp, flags, &string_number);
                fclose(fp);
            }
        }
    }
}