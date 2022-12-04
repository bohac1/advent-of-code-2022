#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int cmpint(const void * lhs, const void * rhs) {
    return *(int *)lhs - *(int *)rhs;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-1.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t written;
    int * numbers;
    size_t numbers_length = 0;

    int cur = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    while ((written = getline(&line, &len, fp)) != -1) {
        cur = cur + atoi(line);
        if(strcmp(line, "\n") == 0) {
            numbers = realloc(numbers, (numbers_length++) * sizeof(int));
            numbers[numbers_length-1] = cur;
            cur = 0;
        }
    }

    fclose(fp);
    free(line);

    // sort the numbers
    qsort(numbers, numbers_length, sizeof(int), cmpint);
    printf("first: %d\n", numbers[numbers_length-1]);
    printf("second: %d\n", numbers[numbers_length-2]);
    printf("third: %d\n", numbers[numbers_length-3]);
    puts("===============");
    int total = numbers[numbers_length-1] + numbers[numbers_length-2] + numbers[numbers_length-3];

    free(numbers);

    printf("total: %d\n", total);
    return 0;
}
