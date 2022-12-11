#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int inspect_cycle(int cycle, int reg_X) {
    if((cycle + 20)%40 == 0) {
        printf("%d\n", cycle * reg_X);
        return cycle * reg_X;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-10.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;

    int clk_count = 0;
    int reg_X = 1;
    int sum = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    while ((chars_read = getline(&line, &len, fp)) != -1) {
        // pattern addx 15
        if(line[0] == '\n') {
            break;
        }
        clk_count++;
        sum += inspect_cycle(clk_count, reg_X);
        if(strncmp(line, "addx", 4) == 0) {
            printf("x: %d\n", reg_X);
            clk_count++;
            sum += inspect_cycle(clk_count, reg_X);
            reg_X += atoi(line + sizeof(char) * 4);
        }
    }

    fclose(fp);
    free(line);
    printf("%d\n", sum);
    return 0;
}
