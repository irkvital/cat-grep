#include "../common/common_func.h"

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