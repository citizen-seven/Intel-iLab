#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char head[100];
    int count;
} stack;

void put(char bracket, stack* stack) {
    stack->head[stack->count] = bracket;
};

int main()
{
    stack a;
    a.count=0;
    char c;
    char s[100];
    char* str = s;

    scanf("%s",s);
    c = *str;
    if (*str != '(' && *str != '{' && *str != '[') {
        printf("The sequence of brackets is incorrect\n");
        exit(0);
    }
    while (*str != '\0') {
        if (*str == '(' || *str == '{' || *str == '[') {
            put(*str, &a);
            a.count++;
            str++;
        }
        if (*str == ')') {
            str++;
            if (a.head[a.count-1] == '(') {
                a.count--;
                put('\0', &a);
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }
        }
        if (*str == '}') {
            str++;
            if (a.head[a.count-1] == '{') {
                a.count--;
                put('\0', &a);
                
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }
        }
        if (*str == ']') {
            str++;
            if (a.head[a.count-1] == '[') {
                a.count--;
                put('\0', &a);
            }
            else {
                printf("The sequence of brackets is incorrect\n");
                exit(1);
            }

        }
    }
    if (a.head[0] == '\0') {
        printf("The sequence of brackets is correct\n");
    }
    else {
        printf("The sequence of brackets is incorrect\n");
    }
    return 1;
}