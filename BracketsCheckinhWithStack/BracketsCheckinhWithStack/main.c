#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char head[100];
    int count;
} stack;

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
    a.count=0;
    char c;
    char s[100];
    char* str = s; // "s" is a adress itself. You can use s++ same with *s. no need for extra pointer 

    scanf("%s",s);
    c = *str;
    if (*str != '(' && *str != '{' && *str != '[') {
        printf("The sequence is incorrect\n");
        exit(0);
    }
    while (*str != '\0') {
        if (*str == '(' || *str == '{' || *str == '[') {
            push(*str, &a);
            str++;
        }
        if (*str == ')') {
            str++;
            if (pop(&a) == '(') { // you can just make if (pop(&a) != '(')) {...}
                a.count++; // two useless lines. why do you increment counter
                pop(&a);   // and then decrement it in pop, without using the return value
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }
        }
        if (*str == '}') {
            str++;
            if (pop(&a) == '{') {
                a.count++; // same as above
                pop(&a);
                
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }
        }
        if (*str == ']') {
            str++;
            if (pop(&a) == '[') {
                a.count++;
                pop(&a);
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }

        }
    }
    if (a.count == 0) {
        printf("The sequence of brackets is correct\n");
    }
    else {
        printf("The sequence of brackets is incorrect\n");
    }
    return 1;
}
