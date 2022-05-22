#include "../common/common_func.h"

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

char* StartBuffer(size_t size_buff) {
    // Начальное выделение памяти
    char* buff = NULL;
    if(!(buff = (char*)malloc(size_buff * sizeof(char)))) {
        printf("Can't allocate memory");
        exit(1);
    }
    return buff;
}
