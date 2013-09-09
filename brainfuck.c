#include <stdio.h>
#include <stdlib.h>

void parse(char *fname) {
    FILE *f;
    int ch;
    char a[30000];
    char *p = a;

    f = fopen(fname, "r");
    if(f == NULL) {
        fprintf(stderr, "Unable to open file.\n");
        exit(1);
    }

    while( (ch = getc(f)) != EOF) {
        //printf("%c\n", ch);
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
                break;
            case ']':
                break;
            default:
                break;
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
