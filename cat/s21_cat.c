#include <string.h>
#include "../common/common_func.h"

#define SUCCEED 0b0
#define ERROR 0b1
#define B_FLAG 0b10
#define E_FLAG 0b100
#define N_FLAG 0b1000
#define S_FLAG 0b10000
#define T_FLAG 0b100000

int ParserFlagsCat(int argc, char* argv[]);
int MinusFlag(char* argv[]);
int MinusMinusFlag(char* argv[]);
void CheckFlagsBN(int flags, char* current_c, int* string_number);
void CheckFlagT(int flags, char* current_c, FILE* fp);
void CheckFlagS(int flags, char* current_c, FILE* fp);
void CheckFlagE(int flags, char* current_c);

int main(int argc, char* argv[]) {
    int flags = ParserFlagsCat(argc, argv);
    if (flags & ERROR) {
        printf("Wrong flags");
    } else {
        MainCircle(argc, argv, flags);
    }
}

int ParserFlagsCat(int argc, char* argv[]) {
    int flags = SUCCEED;
    for(int row = 0; (row < argc) && (flags & ERROR) == 0; row++) {
        int length = strlen(argv[row]);
        if(argv[row][0] == '-' && length > 1) {
            if(argv[row][1] == '-') {
                flags |= MinusMinusFlag(&argv[row]);
            } else {
                flags |= MinusFlag(&argv[row]);
            }
        }
    }
    return flags;
}

int MinusFlag(char* argv[]) {
    int flags = SUCCEED;
    for(int i = 1; (*argv)[i]; i++) {
        if((*argv)[i] == 'b') {
            flags |= B_FLAG;
        } else if((*argv)[i] == 'e' || (*argv)[i] == 'E') {
            flags |= E_FLAG;
        } else if((*argv)[i] == 'n') {
            flags |= N_FLAG;
        } else if((*argv)[i] == 's') {
            flags |= S_FLAG;
        } else if((*argv)[i] == 't' || (*argv)[i] == 'T') {
            flags |= T_FLAG;
        } else {
            flags |= ERROR;
        }
    }
    return flags;
}

int MinusMinusFlag(char* argv[]) {
    int flag = SUCCEED;
    char str_b[18] = "--number-nonblank";
    char str_n[9] = "--number";
    char str_s[16] = "--squeeze-blank";
    if(strcmp(str_b, *argv) == 0) {
        flag |= B_FLAG;
    } else if(strcmp(str_n, *argv) == 0) {
        flag |= N_FLAG;
    } else if(strcmp(str_s, *argv) == 0) {
        flag |= S_FLAG;
    } else {
        flag |= ERROR;
    }
    return flag;
}

void CheckFlagsBN(int flags, char* current_c, int* string_number) {
    if ((flags & B_FLAG) && *current_c != '\n' ) {
            (*string_number)++;
            printf("%6d  ", *string_number);
        } else if((flags & B_FLAG) == 0 && (flags & N_FLAG)) {
            (*string_number)++;
            printf("%6d  ", *string_number);
        }
}

void CheckFlagT(int flags, char* current_c, FILE* fp) {
    if((flags & T_FLAG) && *current_c == '\t') {
            putchar('^');
            putchar('I');
            *current_c = fgetc(fp);
        }
}

void CheckFlagS(int flags, char* current_c, FILE* fp) {
    if((flags & S_FLAG) && *current_c == '\n') {
            while(*current_c == '\n') {
                *current_c = fgetc(fp);
            }
            if(*current_c != EOF) {
                fseek(fp, -1, SEEK_CUR);
                *current_c = '\n';
            } else {
                putchar('\n');
            }
        }
}

void CheckFlagE(int flags, char* current_c) {
    if(flags & E_FLAG && *current_c == '\n') {
            putchar('$');
        }
}


void ReadAndWrite(FILE* fp, int flags, int* string_number) {
    char current_c = fgetc(fp);
    *string_number = 0;
    while(current_c != EOF) {
        // Проверка флагов и формирование начала строки
        CheckFlagsBN(flags, &current_c, string_number);
        CheckFlagT(flags, &current_c, fp);
        CheckFlagS(flags, &current_c, fp);
        // Считывание и запись строки из файла
        while(current_c != '\n' && current_c != EOF ) {
            putchar(current_c);
            current_c = fgetc(fp);
        }
        // Проверка флагов и формирование конца строки
        CheckFlagE(flags, &current_c);
        if(current_c == '\n') {
            putchar(current_c);
        }
        // Проверка на пустую строку
        current_c = (current_c != EOF) ? fgetc(fp) : EOF;
    }
}
