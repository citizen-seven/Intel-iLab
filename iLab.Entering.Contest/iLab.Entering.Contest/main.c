#include <stdio.h>
#include <string.h>
int main()
{
    int i,count=0;
    char brackets[100];
    scanf("%s",brackets);
    for (i=0; i<strlen(brackets); i++) {
        if (brackets[i]=='(') {
            count=count+1;
        }
        else {
            if (brackets[i]==')') {
                count=count-1;
            }
        }
        if (count<0) {
            break;
        }
    }
    if (count==0) {
        printf("DONE");
    }
    else {
        printf("MISTAKE!");
    }
}