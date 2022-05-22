#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#include <string.h>
#include <regex.h>
#include "../common/common_func.h"

#define COLORRED "\x1B[1;31m"
#define COLORDEFAULT "\x1B[0m"

#define I_FLAG 0b1000
#define V_FLAG 0b10000
#define C_FLAG 0b100000
#define L_FLAG 0b1000000
// Бонусная часть
//#define H_FLAG 0b10000000
//#define S_FLAG 0b100000000
//#define F_FLAG 0b1000000000
//#define O_FLAG 0b10000000000

int ParserFlagsGrep(int argc, char* argv[]);
void MainCircle(int argc, char* argv[], int flags);
void ReadAndWrite(FILE* fp, int flags, int* string_number);

#endif  // SRC_S21_GREP_H_