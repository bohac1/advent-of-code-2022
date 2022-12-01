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
            printf("%d, %zu\n", numbers[numbers_length-1], numbers_length);
            cur = 0;
        }
    }
    // sort the numbers
    qsort(numbers, numbers_length, sizeof(int), cmpint);
    printf("%d\n", numbers[numbers_length-1]);
    printf("%d\n", numbers[numbers_length-2]);
    printf("%d\n", numbers[numbers_length-3]);
    int total = numbers[numbers_length-1] + numbers[numbers_length-2] + numbers[numbers_length-3];
    printf("total: %d\n", total);
    return 0;
}
