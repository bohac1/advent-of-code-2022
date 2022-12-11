#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

void clock_tick(int * clk_count, int reg_X) {
    if(*clk_count % 40 >= reg_X - 1 && *clk_count % 40 <= reg_X + 1) {
        printf("#");
    } else {
        printf(".");
    }
    *clk_count += 1;
    if((*clk_count) % 40 == 0) {
        puts("");
    }
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-10.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;

    int clk_count = 0;
    int reg_X = 1;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    while ((chars_read = getline(&line, &len, fp)) != -1) {
        // pattern addx 15
        if(line[0] == '\n') {
            break;
        }
        clock_tick(&clk_count, reg_X);
        if(strncmp(line, "addx", 4) == 0) {
            clock_tick(&clk_count, reg_X);
            reg_X += atoi(line + sizeof(char) * 4);
        }
    }

    fclose(fp);
    free(line);
    return 0;
}
