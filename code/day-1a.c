#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-1.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t written;

    int max = 0, cur = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    while ((written = getline(&line, &len, fp)) != -1) {
        cur = cur + atoi(line);
        if(strcmp(line, "\n") == 0) {
            max = max > cur ? max : cur;
            cur = 0;
        }
    }

    fclose(fp);
    free(line);

    printf("%d\n", max);
    return 0;
}
