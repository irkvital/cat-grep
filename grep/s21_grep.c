#include "../grep/s21_grep.h"

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

void MainCircle(int argc, char* argv[], int flags) {
    // Init Regex
    regex_t regex;
    if(regcomp(&regex, "aa", REG_EXTENDED | REG_NEWLINE)) { // REG_EXTENDED   REG_ICASE -не различать регистр   !! Добавить регулярные выражения
        printf("Couldn't compile regex\n");
        exit(1);
    }
    // Open files & work
    for(int row = 1; row < argc; row++) {
        if(argv[row][0] != '-') {
            FILE *fp;
            if((fp = fopen(argv[row], "r")) == NULL) {
                printf("Can't open file: %s\n", argv[row]);
            } else {
                ReadAndWrite(fp, flags, argv, &regex);
                fclose(fp);
            }
        }
    }
    regfree(&regex);
}

void ReadAndWrite(FILE* fp, int flags, char* argv[], regex_t* regex) {
    size_t size_buff = START_SIZE_BUFF;
    char* buff = StartBuffer(size_buff); // Init buffer
    int reti = 0;
    int string_number = 0;
    while(!feof(fp)) {
        string_number++;
        buff = ReadStr(fp, &size_buff, buff);
        reti = regexec(regex, buff, 0, NULL, 0);
        if(!reti) {
            printf("String number: %d\n", string_number);
        }
    }
    if(!string_number) {
        puts("Not match\n");
    }
    free(buff);
}
