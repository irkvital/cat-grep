#ifndef SRC_COMMON_FUNC_H_
#define SRC_COMMON_FUNC_H_

#include <stdlib.h>
#include <stdio.h>

#define START_SIZE_BUFF 100

#define SUCCEED 0b0
#define ERROR 0b1

int MinusFlag(char* argv[]);
char* ReadStr(FILE* fp, size_t* size_buff, char* buff);
char* StartBuffer(size_t size_buff);

#endif  // SRC_COMMON_FUNC_H_
