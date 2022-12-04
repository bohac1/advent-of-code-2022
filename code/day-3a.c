#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int get_value (char * line, int offset) {
    for (size_t i = 0; i < offset; i++) {
        for (size_t j = 0; j < offset; j++) {
            if (line[i] == line[j+offset]) {
                if (line[i] > 'Z') {
                    return line[i] - 'a' + 1;
                }
                return line[i] - 'A' + 27;
            }
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-3.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    int sum = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }
    int offset;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        offset = chars_read/2;
        sum += get_value(line, offset);
    }

    fclose(fp);
    free(line);

    printf("%d\n", sum);
    return 0;
}
