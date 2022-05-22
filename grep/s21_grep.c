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