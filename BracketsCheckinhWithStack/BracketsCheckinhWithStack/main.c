#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    char* head;
    int count;
} stack;

void ctor(stack* This) {
    assert(This);
    This -> head = (char *) calloc(20, sizeof(char));
}

void dtor(stack* This) {
    assert(This);
    free(This->head);
    printf("The sequence of brackets is incorrect\n");
    exit(0);
}

void push(char bracket, stack* stack) {
    stack->head[stack->count] = bracket;
    stack->count++;
    
};
char pop(stack* stack) {
    stack->count--;
    return(stack->head[stack->count]);
};

int main()
{
    stack a;
    ctor(&a);
    a.count=0;
    int i;
    int brackets_number;
    printf("Write the number of brackets:");
    scanf("%d\n",&brackets_number);
    char* s = (char *) calloc(brackets_number, sizeof(char));
    char* str = s;
    for (i=0; i<brackets_number; i++) {
        scanf("%c",&s[i]);
    }
    if (*str != '(' && *str != '{' && *str != '[') {
        dtor(&a);
    }
    while (*str != '\0') {
        if (*str == '(' || *str == '{' || *str == '[') {
            push(*str, &a);
            str++;
        }
        if (*str == ')') {
            str++;
            if (pop(&a) != '(') {
                dtor(&a);
            }
        }
        if (*str == '}') {
            str++;
            if (pop(&a) != '{') {
                dtor(&a);
            }
        }
        if (*str == ']') {
            str++;
            if (pop(&a) != '[') {
                dtor(&a);
            }
        }
        if (20-strlen(a.head) < 2) {
            realloc(a.head, 20*sizeof(char));
        }
    }
    if (a.count == 0) {
        printf("The sequence of brackets is correct\n");
        free(a.head);
        free(s);
    }
    else {
        printf("The sequence of brackets is incorrect\n");
    }
    return 1;
}
