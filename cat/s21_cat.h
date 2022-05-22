#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <string.h>
#include "../common/common_func.h"

#define E_FLAG 0b10
#define N_FLAG 0b100
#define B_FLAG 0b1000
#define S_FLAG 0b10000
#define T_FLAG 0b100000

int ParserFlagsCat(int argc, char* argv[]);
int MinusMinusFlag(char* argv[]);
void MainCircle(int argc, char* argv[], int flags);
void ReadAndWrite(FILE* fp, int flags, int* string_number);
void Write(FILE* fp, int flags, char* buff, int* string_number);

#endif  // SRC_S21_CAT_H_
