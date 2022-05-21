#ifndef SRC_COMMON_FUNC_H_
#define SRC_COMMON_FUNC_H_

#include <stdlib.h>
#include <stdio.h>

#define START_SIZE_BUFF 100

char* ReadStr(FILE* fp, size_t* size_buff, char* buff);
char* StartBuffer(size_t size_buff);

#endif  // SRC_COMMON_FUNC_H_
