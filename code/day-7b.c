#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct dir_structure{
    char *name;
    struct dir_structure *parent;
    struct dir_structure **children;
    int num_children;
    int size;
    int is_directory;
};

struct dir_structure * create_dir_structure_if_not_exists(struct dir_structure * parent, char * name, int size, int is_directory) {
    // create child structure
    struct dir_structure * current = malloc(sizeof(struct dir_structure));
    current->name = strdup(name);
    current->parent = parent;
    current->children = NULL;
    current->num_children = 0;
    current->size = size;
    current->is_directory = is_directory;
    // attach child to parent structure
    parent->children = realloc(parent->children, sizeof(struct dir_structure *) * (parent->num_children + 1));
    parent->children[parent->num_children] = current;
    parent->num_children++;
    return current;
}

int calculate_sizes(struct dir_structure * current) {
    int sum = 0;
    if(current->is_directory) {
        for(int i = 0; i < current->num_children; i++) {
            sum += calculate_sizes(current->children[i]);
        }
        current->size = sum;
    } else {
        sum += current->size;
    }
    return sum;
}

void calculate_sum_of_sizes(struct dir_structure * current, int treshold, int * smallest) {
    for(int i = 0; i < current->num_children; i++) {
        calculate_sum_of_sizes(current->children[i], treshold, smallest);
    }
    if(current->is_directory && current->size > treshold) {
        if (*smallest > current->size || *smallest < 0)
            *smallest = current->size;
    }
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-7.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    struct dir_structure * root = malloc(sizeof(struct dir_structure));
    root->name = "/";
    root->parent = NULL;
    root->children = NULL;
    root->num_children = 0;
    struct dir_structure * working_dir;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    int file_size = 0;
    char * file_name = NULL;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        printf("%s\n", line);
        if(strncmp(line, "$ ", 2) == 0) {
            // line is a command
            if(strncmp(line, "$ cd ", 5) == 0) {
                if(strncmp(line, "$ cd ..", 7) == 0) {
                    // cd to parrent directory
                    if(working_dir->parent != NULL)
                        working_dir = working_dir->parent;
                } else if (strncmp(line, "$ cd /", 6) == 0) {
                    // cd to root directory
                    working_dir = root;
                } else {
                    // cd to child directory
                    working_dir = create_dir_structure_if_not_exists(
                        working_dir,
                        line + 5 * sizeof(char),
                        0,
                        1
                    );
                }
            }
            if(strncmp(line, "$ ls", 4) == 0) {
                // no op
            }
        } else {
            // line is a directory listing
            if(strncmp(line, "dir ", 4) == 0) {
                // is a directory
                create_dir_structure_if_not_exists(
                    working_dir,
                    line + 4 * sizeof(char),
                    0,
                    1
                );
            } else {
                // is a file
                file_size = atoi(line);
                file_name = strchr(line, ' ') + 1 * sizeof(char);
                create_dir_structure_if_not_exists(
                    working_dir,
                    file_name,
                    file_size,
                    0
                );
            }
        }
    }
    calculate_sizes(root);
    int sum = -1;
    int space_required = -1*((70000000 - 30000000) - root->size);
    printf("space_required %d\n", space_required);
    calculate_sum_of_sizes(root, space_required, &sum);
    printf("sum of sizes %d\n", sum);
    fclose(fp);
    free(line);

    // not doing the memory freeing for the this assignment sorry... :(

    return 0;
}
