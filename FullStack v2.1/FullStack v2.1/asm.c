#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*typedef struct cmdInfo {
 int num;
 const char* name;
 } cmdInfo; */

int main() {
    int i=0;
    char* buff;
    char* str=(char*) calloc(100, sizeof(int));
    FILE * out;
    out = fopen("out.txt","w");
    FILE * in;
    in = fopen("in.txt","r");
    //creating enum
#define DEF_CMD(name,num,rule,argnum) cmd_##name=num, //##- склеивание
    enum Commands {
#include "cmdlist.h"
        cmd_Last
    };
#undef DEF_CMD
    
    /*creating struct
     #define DEF_CMD(name,num,rule,argnum) \
     {cmd_##name, #name},
     const cmdInfo Info[] =
     {
     #include "cmdlist.h"
     {}
     };
     #undef DEF_CMD
     */
    while (1) {
        fgets(str, 50, in);
        printf ("%s\n", str);
        i++;
        buff = (strtok(str, " "));
#define DEF_CMD(name,num,rule,argnum) \
if (strcmp(buff, #name) == 0){ \
fprintf(out, "%d ", cmd_##name);\
if (argnum>0) { \
buff = (strtok(NULL, "\n"));\
fprintf(out, "%s ", buff);}}\
else
#include "cmdlist.h"
        printf("Error..\n"); //это испрaвит ошибку с последним else
#undef DEF_CMD
    }
    
    fclose(out);
    fclose(in);
}