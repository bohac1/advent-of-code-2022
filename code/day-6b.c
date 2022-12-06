#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int str_unique(const char * str, int len) {
    for(int i = 0; i < len; i++)
        for(int j = i + 1; j < len; j++)
            if(str[i] == str[j])
                return 0;
    return 1;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-6.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    int uniq_chars = 14;
    int position = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }
    char * offset = NULL;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        for(; position < chars_read - uniq_chars; position++) {
            offset = line + position * sizeof(char);
            if(str_unique(offset, uniq_chars))
                break;
        }
    }
    fclose(fp);
    free(line);
    printf("%d\n", position + uniq_chars);
    return 0;
}
