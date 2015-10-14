#include <stdio.h>

void put(char bracket, char* stack) {
    *stack = bracket;
};

int main()
{
    typedef struct {
        char head[100];
    } stack;
    stack a;
    char c;
    char s[100];
    char* str = s;
    int i = 0;
    
    scanf("%s",s);
    c = *str;
    if (*str != '(' && *str != '{' && *str != '[') {
        printf("Wrong line of brackets\n");
    }
    while (*str != '\0') {
        if (*str == '(' || *str == '{' || *str == '[') {
            put(*str, &a.head[i]);
            i++;
            str++;
        }
        if (*str == ')') {
            str++;
            if (a.head[i-1] == '(') {
                put('\0', &a.head[i-1]);
                i--;
            }
            else {
                str--;
                put(*str, &a.head[i]);
                break;
            }
        }
        
        if (*str == '}') {
            str++;
            if (a.head[i-1] == '{') {
                put('\0', &a.head[i-1]);
                i--;
            }
            else {
                str--;
                put(*str, &a.head[i]);
                break;
            }
        }
        if (*str == ']') {
            str++;
            if (a.head[i-1] == '[') {
                put('\0', &a.head[i-1]);
                i--;
            }
            else {
                str--;
                put(*str, &a.head[i]);
                break;
            }
        }
    }
    if (a.head[0] == '\0') {
        printf("The sequence of brackets is correct\n");
    }
    else {
        printf("The sequence of brackets is incorrect\n");
    }
    return 0;
    
}