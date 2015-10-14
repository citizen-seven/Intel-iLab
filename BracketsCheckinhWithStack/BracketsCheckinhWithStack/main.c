#include <stdio.h>

/*
1) Replace strucrute definition from main
2) push (or put in this case) should accept stack structure as a parameter
3) look comment below for "wrong line" error
4) I do not understand your idea actually. Why do you put 'close bracket' chars into stack?
   If the previous char is not an 'open bracket' it is already a wrong sequence.
   Thus explain me why. Because it does not work properly on "))" (or similar) input
*/

void put(char bracket, char* stack) {
    *stack = bracket;
};

int main()
{
    // replace it
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
        // exit() is neccessary here, because the program will not work
        // if the first char is NOT a 'open bracket' char
        exit(-1);
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
                // why do you have str-- in else? what is the point of the action?
                str--;
                put(*str, &a.head[i]); // same here? why?
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
    //check ignoring only
    
}