#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct queue {
    int data;
    struct queue *next;
};

struct monke {
    int id;
    struct queue * items;
    char * operation;
    int test_val;
    int test_pass;
    int test_fail;
    int inspection_count;
};

int monke_cmp(const void * a,const void * b) {
    struct monke *m1 = (struct monke *) a;
    struct monke *m2 = (struct monke *) b;
    int diff = m1->inspection_count - m2->inspection_count;
    return diff;
}

struct queue *push(struct queue * queue, int data) {
    struct queue * new_queue = (struct queue *) malloc(sizeof(struct queue));
    if(queue == NULL) {
        new_queue->data = data;
        new_queue->next = NULL;
        return new_queue;
    }
    struct queue * starting_queue = queue;
    while(queue->next != NULL) {
        queue = queue->next;
    }
    new_queue->data = data;
    queue->next = new_queue;
    new_queue->next = NULL;
    return starting_queue;
}

struct queue *pop(struct queue * queue, int * data) {
    struct queue *temp;
    temp = queue;
    queue = queue->next;
    *data = temp->data;
    free(temp);
    return queue;
}

int inspect_item(int item, struct monke * monke) {
    // monke->operation pattern "<operator>{1} <operand>+"
    monke->inspection_count++;
    char operator = monke->operation[0];
    char * operand = monke->operation + sizeof(char) * 2;
    int operand_value;

    if(strncmp(operand, "old", 3) == 0) {
        operand_value = item;
    } else {
        operand_value = atoi(operand);
    }

    switch(operator) {
        case '+':
            item += operand_value;
            break;
        case '*':
            item *= operand_value;
            break;
    }
    return item;
}

void print_monke(struct monke * monke) {
    printf("monke %d: ", monke->id);
    struct queue *temp = monke->items;
    while(temp != NULL) {
        printf("%d, ", temp->data);
        temp = temp->next;
    }
    puts("");
}

int main(int argc, char const *argv[]) {
    FILE * fp = fopen("/Users/michalhome/Documents/advent-of-code-2022/input/day-11.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t chars_read;
    struct monke ** monkes = NULL;
    size_t monkes_len = 0;

    printf("%d\n",atoi("old"));
    if (fp == NULL) {
        puts("Input file not found\n");
    }
    int item = 1;
    // monkes = malloc(sizeof(struct monke *) * 8);
    while ((chars_read = getline(&line, &len, fp)) != -1) {
        // Monkey 0:
        //   Starting items: 79, 98
        //   Operation: new = old * 19
        //   Test: divisible by 23
        //     If true: throw to monkey 2
        //     If false: throw to monkey 3
        // read monke id
        monkes = realloc(monkes, sizeof(struct monke *) * (monkes_len + 1));
        monkes[monkes_len] = (struct monke*) malloc(sizeof(struct monke));
        monkes[monkes_len]->id = atoi(line + sizeof(char) * 7);
        monkes[monkes_len]->inspection_count = 0;
        // read items
        chars_read = getline(&line, &len, fp);
        monkes[monkes_len]->items = NULL;
        char * item_ptr = line + sizeof(char) * 18;
        while((item = atoi(item_ptr)) > 0) {
            monkes[monkes_len]->items = push(monkes[monkes_len]->items, item);
            item_ptr = strchr(item_ptr, ',');
            if(item_ptr == NULL) {
                break;
            } else {
                item_ptr += sizeof(char);
            }
        }
        // read operation
        chars_read = getline(&line, &len, fp);
        monkes[monkes_len]->operation = malloc(strlen(line) * sizeof(char) - sizeof(char) * 23);
        strcpy(monkes[monkes_len]->operation, line + sizeof(char) * 23);
        // monkes[monkes_len].operation = strdup(line + sizeof(char) * 23);
        // read test
        chars_read = getline(&line, &len, fp);
        monkes[monkes_len]->test_val = atoi(line + sizeof(char) * 21);
        // read test true
        chars_read = getline(&line, &len, fp);
        monkes[monkes_len]->test_pass = atoi(line + sizeof(char) * 29);
        // read test false
        chars_read = getline(&line, &len, fp);
        monkes[monkes_len]->test_fail = atoi(line + sizeof(char) * 30);
        // new line after monke specifications end
        chars_read = getline(&line, &len, fp);
        monkes_len++;
    }

    // 20 rounds of monke business
    int current_item;
    for(int i = 0; i < 20; i++) {
        for(size_t j = 0; j < monkes_len; j++) {
            while(monkes[j]->items != NULL) {
                monkes[j]->items = pop(monkes[j]->items, &current_item);
                current_item = inspect_item(current_item, monkes[j]);
                current_item /= 3;
                if(current_item % monkes[j]->test_val) {
                    // fail test
                    monkes[monkes[j]->test_fail]->items = push(monkes[monkes[j]->test_fail]->items, current_item);
                } else {
                    // pass test
                    monkes[monkes[j]->test_pass]->items = push(monkes[monkes[j]->test_pass]->items, current_item);
                }
            }
        }
        printf("After round %d\n", i+1);
        for(size_t j = 0; j < monkes_len; j++) {
            print_monke(monkes[j]);
        }
        printf("\n");
    }
    qsort(monkes, monkes_len, sizeof(struct monke*), monke_cmp);
    printf("result of monke business: %d\n", monkes[0]->inspection_count * monkes[1]->inspection_count);
    return 0;
}
