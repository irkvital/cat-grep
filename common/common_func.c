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

int MinusFlag(char* argv[]) {
    int flags = SUCCEED;
    printf("!common!");////////////////////////////////////////////////////////
    for(int i = 1; (*argv)[i]; i++) {
        if((*argv)[i] == 'e' || (*argv)[i] == 'E') {
            flags |= E_FLAG;
        } else if((*argv)[i] == 'n') {
            flags |= N_FLAG;
    #ifdef SRC_S21_CAT_H_
        } else if((*argv)[i] == 'b') {
            flags |= B_FLAG;
        } else if((*argv)[i] == 's') {
            flags |= S_FLAG;
        } else if((*argv)[i] == 't' || (*argv)[i] == 'T') {
            flags |= T_FLAG;
    #endif
    #ifdef SRC_S21_GREP_H_
    printf("!grep!");
        } else if((*argv)[i] == 'i') {
            flags |= I_FLAG;
        } else if((*argv)[i] == 'v') {
            flags |= V_FLAG;
        } else if((*argv)[i] == 'c') {
            flags |= C_FLAG;
        } else if((*argv)[i] == 'l') {
            flags |= L_FLAG;
    #endif
        } else {
            flags |= ERROR;
        }
    }
    return flags;
}
