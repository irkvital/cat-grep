#include "../cat/s21_cat.h"

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

void MainCircle(int argc, char* argv[], int flags) {
    int string_number = 0;
    for(int row = 1; row < argc; row++) {
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

void ReadAndWrite(FILE* fp, int flags, int* string_number) {
    size_t size_buff = START_SIZE_BUFF;
    char* buff = StartBuffer(size_buff);
    *string_number = 0;
    while(!feof(fp)) {
        buff = ReadStr(fp, &size_buff, buff);
        Write(fp, flags, buff, string_number);
    }
    free(buff);
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