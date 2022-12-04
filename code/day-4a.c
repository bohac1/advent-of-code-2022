#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int one_subset_of_other(int * ranges) {
    // 0-1,2-3
    if(ranges[0] >= ranges[2] && ranges[1] <= ranges[3]) return 1;
    if(ranges[2] >= ranges[0] && ranges[3] <= ranges[1]) return 1;
    return 0;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-4.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    int sum = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }
    char * offset = NULL;
    int tmp_val[4];
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        offset = line;
        for(int i = 0; i < 4; ++i) {
            tmp_val[i] = atoi(offset);
            offset = strpbrk(offset, "-,");
            if (i != 3)
                offset += sizeof(char);
        }
        sum += one_subset_of_other(tmp_val);
    }

    fclose(fp);

    printf("%d\n", sum);
    return 0;
}
