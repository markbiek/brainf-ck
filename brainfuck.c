#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define false 0
#define true 1

char *p;

void step(int ch) {
    switch(ch) {
        case '>':
            ++p;
            break;
        case '<':
            --p;
            break;
        case '+':
            ++*p;
            break;
        case '-':
            --*p;
            break;
        case '.':
            putchar(*p);
            break;
        case ',':
            *p = getchar();
            break;
        case '[':
            printf("ERROR: Nested loops are not allowed (yet).\n");
            exit(1);
            break;
        case ']':
            break;
        default:
            break;
    }
}

void parse(char *fname) {
    FILE *f;
    int ch;
    char a[30000];
    char scmd[30000];

    p = a;
    f = fopen(fname, "r");
    if(f == NULL) {
        fprintf(stderr, "Unable to open file.\n");
        exit(1);
    }

    while( (ch = getc(f)) != EOF) {
        if(ch == '[') {
            //Start our loop handler
            int subCh;
            bool bdone = false;
            scmd[0] = '\0';

            //printf("Starting loop!\n");
            while(!bdone) {
                subCh = getc(f);

                //Reached EOF before finding a closing ]
                if(feof(f)) {
                    printf("ERROR: Unexpected end of file.\n");
                    fclose(f);
                    exit(1);
                }else if(subCh == ']') {
                    bdone = true;
                }else {
                    char s2[2];
                    s2[0] = subCh;
                    s2[1] = '\0';
                    strcat(scmd, s2);
                }
            }

            if(strlen(scmd) > 0) {
                int loop = 0;
                //printf("Finished loop\n");
                //printf("%s\n", scmd);

                //Execute loop contents
                while(*p && ++loop < 30000) {
                    int i=0, j=strlen(scmd);
                    for(i=0; i < j; i++) {
                        step(scmd[i]);
                    }
                }
                //printf("loop=%d\n", loop);
            }else {
                printf("ERROR: No commands found in loop.\n");
                exit(1);
            }
        }else {
            //Process some other character
            step(ch);
        }
    }

    fclose(f);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Please specify a file to parse.\n");
    }else {
        parse(argv[1]);
    }

    exit(0);
}
