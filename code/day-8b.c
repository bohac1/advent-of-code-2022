#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int calculate_scenic_score(char ** trees, int y, int x, int scanned_y, int scanned_x) {
    int scenic_score = 1;
    char tree_height = trees[y][x];
    // left
    int tmp = 0;
    for(int i = x-1; i >= 0; i--) {
        tmp++;
        if(trees[y][i] >= tree_height) {
            break;
        }
    }
    scenic_score *= tmp;
    // right
    tmp = 0;
    for(int i = x+1; i < scanned_x; i++) {
        tmp++;
        if(trees[y][i] >= tree_height) {
            break;
        }
    }
    scenic_score *= tmp;
    // above
    tmp = 0;
    for(int i = y-1; i >= 0; i--) {
        tmp++;
        if(trees[i][x] >= tree_height) {
            break;
        }
    }
    scenic_score *= tmp;
    // below
    tmp = 0;
    for(int i = y+1; i <= scanned_y; i++) {
        tmp++;
        if(trees[i][x] >= tree_height) {
            break;
        }
    }
    scenic_score *= tmp;
    return scenic_score;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-8.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    char ** trees = NULL;
    int trees_size = 0;

    if (fp == NULL) {
        printf("Input file not found\n");
    }
    int scanned_x;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        trees = (char **) realloc(trees, sizeof(char *) * (trees_size + 1));
        trees[trees_size] = strdup(line);
        trees_size++;
        scanned_x = chars_read - 1;
    }

    int max_scenic_score = 0, current_scenic_score = 0;
    for(int x = 0; x < scanned_x; x++) {
        for(int y  = 0; y < trees_size; y++) {
            current_scenic_score = calculate_scenic_score(trees, y, x, trees_size - 1, scanned_x);
            if(max_scenic_score < current_scenic_score)
                max_scenic_score = current_scenic_score;
        }
    }
    fclose(fp);
    free(line);

    for(int i = 0; i < trees_size; i++)
        free(trees[i]);
    free(trees);

    printf("Max scenic score is: %d\n", max_scenic_score);
    return 0;
}
