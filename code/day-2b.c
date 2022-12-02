#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    char p1 = 0;
    char p2 = 0;
    int result = 0;
    FILE * fp = fopen("input/day-2.txt", "r");

    if (fp == NULL) {
        perror("fopen input/day-2.txt");
        exit(1);
    }

    while((p1 = fgetc(fp) - 'A') >= 0) {
        fgetc(fp); // skip leading whitespace
        p2 = fgetc(fp) - 'X';
        fgetc(fp); // skip leading end of line
        result += (p2) * 3 + (p1 + p2 + 2) % 3 + 1;
    }

    fclose(fp);
    printf("%d\n", result);

    return 0;
}
