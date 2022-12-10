#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct knot {
    int x;
    int y;
    int is_tail;
};

struct knot_move {
    int x;
    int y;
};

struct knot_moves {
    struct knot_move ** moves;
    ssize_t len;
};

void record_move(struct knot * knot, struct knot_moves * moves) {
    // check if move already exists
    int exists = 0;
    for (ssize_t i = 0; i < moves->len; i++) {
        if (moves->moves[i]->x == knot->x && moves->moves[i]->y == knot->y) {
            exists++;
            break;
        }
    }
    if (exists == 1) {
        return;
    }
    // add new move
    moves->moves = realloc(moves->moves, sizeof(struct knot_move *) * moves->len + 1);
    moves->moves[moves->len] = malloc(sizeof(struct knot_move));
    moves->moves[moves->len]->x = knot->x;
    moves->moves[moves->len]->y = knot->y;
    moves->len++;
}

void move(struct knot * current, struct knot * previous, struct knot_moves * moves) {
    // do nothing if the knots are close to each other
    if(abs(current->x - previous->x) <= 1 && abs(current->y - previous->y) <= 1)
        return;

    // horizontal movement
    if(abs(current->x - previous->x) > 1 && current->y == previous->y) {
        if((current->x - previous->x) > 0) {
            current->x -= 1;
        } else {
            current->x += 1;
        }
    } else if(abs(current->y - previous->y) > 1 && current->x == previous->x) {
        // vertical movement
        if((current->y - previous->y) > 0) {
            current->y -= 1;
        } else {
            current->y += 1;
        }
    } else {
        // diagonal movement
        if((current->x - previous->x) > 0) {
            current->x -= 1;
        } else {
            current->x += 1;
        }
        if((current->y - previous->y) > 0) {
            current->y -= 1;
        } else {
            current->y += 1;
        }
    }

    if(current->is_tail) {
        record_move(current, moves);
    }
}

void move_head(struct knot * head, char direction) {
    switch (direction) {
        case 'L':
            head->x--;
            break;
        case 'R':
            head->x++;
            break;
        case 'U':
            head->y++;
            break;
        case 'D':
            head->y--;
            break;
    }
}
int main(int argc, char const *argv[]) {
    FILE * fp = fopen("input/day-9.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;

    size_t knots_len = 2;
    struct knot * knots = malloc(sizeof(struct knot) * knots_len);

    for(size_t i = 0; i < knots_len; i++) {
        knots[i].x = 0;
        knots[i].y = 0;
        knots[i].is_tail = 0;
    }
    knots[knots_len-1].is_tail = 1;

    struct knot_moves moves;
    moves.len = 0;
    record_move(&knots[0], &moves);

    char direction;
    char move_count;

    if (fp == NULL) {
        printf("Input file not found\n");
    }

    while ((chars_read = getline(&line, &len, fp)) != -1) {
        // pattern R 4
        if(line[0] == '\n') {
            break;
        }
        direction = line[0];
        move_count = atoi(line + sizeof(char) * 2);
        for(int i = 0; i < move_count; i++) {
            move_head(&knots[0], direction);
            // printf("H[%d;%d]\n", knots[0].x, knots[0].y);
            for(size_t j = 1; j < knots_len; j++) {
                move(&knots[j], &knots[j-1], &moves);
                // printf("T[%d;%d]\n", knots[j].x, knots[j].y);
            }

        }
    }
    fclose(fp);
    free(line);
    printf("total: %zd\n", moves.len);
    for(size_t i = 0; i < moves.len; i++) {
        free(moves.moves[i]);
    }
    free(moves.moves);
    free(knots);
    return 0;
}
