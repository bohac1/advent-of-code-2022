#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int is_visible(char ** trees, int y, int x, int scanned_y, int scanned_x) {
    int visible = 4;
    printf("%d %d\n", y, x);
    char tree_height = trees[y][x];
    // left
    for(int i = 0; i < x; i++) {
        if(trees[y][i] >= tree_height) {
            visible--;
            break;
        }
    }
    // right
    for(int i = scanned_x; i > x; i--) {
        if(trees[y][i] >= tree_height) {
            visible--;
            break;
        }
    }
    // above
    for(int i = 0; i < y; i++) {
        if(trees[i][x] >= tree_height) {
            visible--;
            break;
        }
    }
    // below
    for(int i = scanned_y; i > y; i--) {
        if(trees[i][x] >= tree_height) {
            visible--;
            break;
        }
    }
    if (visible) return 1;
    return 0;
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-8.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    char ** trees = NULL;
    int trees_size = 0;
    int number_of_visible = 0;

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

    for(int x = 0; x < scanned_x; x++) {
        for(int y  = 0; y < trees_size; y++) {
            printf("x:%d y:%d\n", x, y);
            printf("%s", trees[y]);
            number_of_visible += is_visible(trees, y, x, trees_size - 1, scanned_x);
        }
    }
    fclose(fp);
    free(line);

    for(int i = 0; i < trees_size; i++)
        free(trees[i]);
    free(trees);

    printf("Number of visible trees %d\n", number_of_visible);
    return 0;
}
