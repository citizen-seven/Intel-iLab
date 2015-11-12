#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "MyStack.h"


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
            realloc(a.head, 2*sizeof(a.head));
        }
    }
    if (a.count == 0) {
        dump(&a);
        printf("The sequence of brackets is correct\n");
        free(a.head);
        free(s);
        
    }
    else {
        dump(&a);
        printf("The sequence of brackets is incorrect\n");
    }
    return 1;
}
