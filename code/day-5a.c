#include "stdio.h"
#include "stdlib.h"
#include "string.h"
const int STACK_NUM = 9;

struct pile {
    char * values;
    int len;
};

void pile_push(char value, struct pile * stack) {
    if(value < 'A' || value > 'Z')
        return;
    stack->len += 1;
    stack->values = realloc(stack->values, (stack->len) * sizeof(char));
    stack->values[stack->len - 1] = value;
}

char * reverse_string(char * str, int len) {
    int i, j;
    char tmp;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
    return str;
}

char pile_pop(struct pile * stack) {
    if(stack->len <= 0)
        return 'f';
    char value = stack->values[stack->len - 1];
    stack->len--;
    return value;
}

void pile_print(struct pile * stack) {
    for (int i = 0; i < stack->len; i++) {
        printf("%c", stack->values[i]);
    }
    printf("\n");
}

void pile_move(int move, struct pile * from, struct pile * to) {
    for(int i = 0; i < move; i++) {
        pile_push(pile_pop(from), to);
    }
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-5.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    struct pile stacks[STACK_NUM];

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    for(int i = 0; i < STACK_NUM; i++) {
        stacks[i].values = NULL;
        stacks[i].len = 0;
    }
    // read stacks
    int tmp_stack_len = 4; // input for each stack is 4 chars long
    int stack_offset;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        for(int i = 0; i < STACK_NUM; i++) {
            stack_offset = i * tmp_stack_len;
            // EXAMPLE: [Z] [M] [P]
            if(line[stack_offset] == '\0')
                break;
            pile_push(line[stack_offset + 1], &stacks[i]);
        }
        if(line[1] == '1')
            break;
    }

    for(int i = 0; i < STACK_NUM; i++) {
        reverse_string(stacks[i].values, stacks[i].len);
        pile_print(&stacks[i]);
    }
    puts("================================================================");

    // read moves
    char * offset = NULL;
    int move, from, to;
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        // EXAMPLE: move 1 from 3 to 9
        if(line[0] == '\n')
            continue;
        offset = strchr(line, ' ');
        move = atoi(offset);
        offset = strchr(strchr(offset, 'f'), ' '); // find where the f in `from` is in the string and return the pointer to the number
        from = atoi(offset) - 1;
        offset = strchr(strchr(offset, 't'), ' '); // find where the t in `to` is in the string and return the pointer to the number
        to = atoi(offset) - 1;
        pile_move(move, &stacks[from], &stacks[to]);
    }

    for(int i = 0; i < STACK_NUM; i++) {
        pile_print(&stacks[i]);
    }
    puts("================================================================");

    fclose(fp);
    free(line);
    for( int i = 0; i < STACK_NUM; i++) {
        printf("%c", pile_pop(&stacks[i]));
        free(stacks[i].values);
    }
    puts("");

    return 0;
}
