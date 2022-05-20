#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define COLORRED "\x1B[1;31m"
#define COLORDEFAULT "\x1B[0m"

int main(int argc, char* argv[]) {
    regex_t regex;
    regmatch_t pmatch[3];
    const size_t nmatch = 3;
    int reti = 0, i = 0;
    char a[200] = "11aabcdgrepeaabcdefgaa";

    reti = regcomp(&regex, argv[1], REG_EXTENDED); // REG_EXTENDED   REG_ICASE -не различать регистр
    if(reti) {
        printf("Couldn't compile regex\n");
    } else {
        reti = regexec(&regex, a, nmatch, pmatch, 0);
        if(!reti) {
            printf("& %d %d %d %d &\n", pmatch[0].rm_so, pmatch[1].rm_so, pmatch[0].rm_eo, pmatch[1].rm_eo);
            //puts("Match\n");
            for(; i < pmatch[0].rm_eo; i++) {
                if(i >= pmatch[0].rm_so && i < pmatch[0].rm_eo) {
                    printf(COLORRED "%c", a[i]);
                } else {
                    printf(COLORDEFAULT "%c", a[i]);
                }
            }
        } else {
            //puts("Not match\n");
        }
        
        //_______________________________________________________________________
        reti = regexec(&regex, (a + pmatch->rm_eo), nmatch, pmatch, 0);
        if(!reti) {
            //puts("Match\n");
            for(; a[i] ; i++) {
                if(i - 4 >= pmatch->rm_so && i - 4 < pmatch->rm_eo) {
                    printf(COLORRED "%c", a[i]);
                } else {
                    printf(COLORDEFAULT "%c", a[i]);
                }
            }
            putchar('\n');
        } else {
            //puts("Not match\n");
        }
        printf("!%d!%d!%d!", pmatch->rm_so, pmatch->rm_so, i);
        regfree(&regex);
    }
    printf ("%s\n", a );
}
