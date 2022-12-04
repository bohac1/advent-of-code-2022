#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char get_common_char(char * line1, char * line2, char * line3) {
    char * common_char = NULL;
    while(common_char == NULL) {
        common_char = strpbrk(line1, line2);
        common_char = strpbrk(common_char, line3);
    }
    if (common_char[0] > 'Z') {
        return common_char[0] - 'a' + 1;
    }
    return common_char[0] - 'A' + 27;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-3.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    int sum = 0;
    char* group[2] = {NULL, NULL};

    if (fp == NULL) {
        printf("Input file not found\n");
    }
    int counter = 0;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        if (counter % 3 == 2) {
            sum += get_common_char(group[0], group[1], line);
            free(group[0]);
            free(group[1]);
        } else
            group[counter % 3] = strdup(line);
        ++counter;
    }

    fclose(fp);
    free(line);

    printf("%d\n", sum);
    return 0;
}
