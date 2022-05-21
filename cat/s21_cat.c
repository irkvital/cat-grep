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
char* ReadStr(FILE* fp, size_t* size_buff, char* buff);
void Write(FILE* fp, int flags, char* buff, int* string_number);

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

void ReadAndWrite(FILE* fp, int flags, int* string_number) {
    // Начальное выделение памяти
    size_t size_buff = 100;
    char* buff = NULL;
    if(!(buff = (char*)malloc(size_buff * sizeof(char)))) {
        printf("Can't allocate memory");
        exit(1);
    }
    *string_number = 0;
    while(!feof(fp)) {
        buff = ReadStr(fp, &size_buff, buff);
        Write(fp, flags, buff, string_number);
    }
    free(buff);
}

char* ReadStr(FILE* fp, size_t* size_buff, char* buff) {
    size_t i = - 1;
        do {
            if(i == *size_buff - 1) {
                *size_buff *= 2;
                if(!(buff = (char*)realloc(buff, *size_buff * sizeof(char)))) {
                    printf("Can't allocate memory");
                    exit(1);
                }
            }
            i++;
            buff[i] = getc(fp);
        } while(buff[i] != '\n' && buff[i] != EOF && buff[i] != '\0');
        buff[i] = '\0';
        return buff;
}

void Write(FILE* fp, int flags, char* buff, int* string_number) {
    //B & N флаги
    if ((flags & B_FLAG) && buff[0] != '\0' ) {
        printf("%6d  ", ++(*string_number));
    } else if((flags & B_FLAG) == 0 && (flags & N_FLAG)) {
        printf("%6d  ", ++(*string_number));
    }
    // S флаг
    if((flags & S_FLAG) && buff[0] == '\0') {
        if((flags & S_FLAG) && buff[0] == '\0') {
        buff[0] = '\n';
            while(buff[0] == '\n') {
                buff[0] = fgetc(fp);
            }
            if(buff[0] != EOF) {
                fseek(fp, -1, SEEK_CUR);
            }
            buff[0] = '\0';
        }
    }
    // Строка + T флаг
    for(int i = 0; buff[i]; i++) {
        if((flags & T_FLAG) && buff[i] == '\t') {
            putchar('^');
            putchar('I');
        } else {
            putchar(buff[i]);
        }
    }
    // E флаг
    if(flags & E_FLAG) {
        putchar('$');
    }
    if(!feof(fp)) {
        putchar('\n');
    }
}