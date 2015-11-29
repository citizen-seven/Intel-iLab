#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

/*typedef struct cmdInfo {
 int num;
 const char* name;
 } cmdInfo; */

int main() {
    int com_count=0;
    int labels[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    char* buff;
    char* str=(char*) calloc(100, sizeof(int));
    FILE* out = fopen("out.txt","w");
    FILE* in = fopen("in.txt","r");
    enum argument_type {
        none = 0, 
        num = 1,
        label = 2,
        regs = 3
    };

    //creating enum
#define DEF_CMD(name,num,rule,argtype) cmd_##name=num, //##- склеивание
    enum Commands {
#include "cmdlist.h"
        cmd_Last
    };
#undef DEF_CMD
    while (!feof(in)) {
        fgets(str, MAX_LEN, in);
        printf ("%s\n", str);
        com_count++;
        buff = (strtok(str, " "));
        if (strcmp(buff, ":label") == 0) {
            buff = (strtok(NULL, "\n"));
            if (((int)*buff)-'0'<10) { //doesn't detect wrong size!!!!!!!!
                labels[(int)*buff-'0'] = ++com_count;
                com_count--;
            } else {
                printf("Label number is over 10\n");
                exit(-1);
            }
        }
    };
    
    rewind(in);
    while (!feof(in)) {
        fgets(str, MAX_LEN, in);
        printf ("%s\n", str);
        buff = (strtok(str, " "));
        if (strcmp(buff, ":label") != 0) {
#define DEF_CMD(name,num,rule,argtype) \
            if (strcmp(buff, #name) == 0) {\
                fprintf(out, "%d ", cmd_##name);\
                switch (argtype) {\
                    case 1:\
                        buff = (strtok(NULL, " \n"));\
                        if (buff != NULL) {\
                            fprintf(out, "%s ", buff);\
                        } else {\
                            printf("Function %d needs an argument\n", cmd_##name);\
                            exit(-1);\
                        }\
                        break;\
                    case 2:\
                        buff = (strtok(NULL, " \n"));\
                        if (labels[(int)*buff-'0'] == -1) {\
                            printf("No :label %d to jump\n", (int)*buff-'0');\
                            exit(-1);\
                        }\
                        break;\
                    case 3:\
                        buff = (strtok(((void*)0), ",\n"));\
                        if (buff != NULL) {\
                            if (strncmp(buff,"Rx",1) == 0) {\
                                fprintf(out, "%s ",++buff);\
                            }\
                            buff = (strtok(((void*)0), " \n"));\
                            if (buff != NULL) {\
                                fprintf(out, "%s ",++buff);\
                            } else {\
                                fprintf(out, "%d ",0);\
                            }\
                            break;\
                        } else {\
                            printf("Function %d needs an argument\n", cmd_##name);\
                            exit(-1);\
                        }\
                    default:\
                        buff = (strtok(NULL, " \n"));\
                        break;\
                }\
            }\
            else 
#include "cmdlist.h"
            {printf("NO SUCH COMMAND\n"); exit(-1);
            }
#undef DEF_CMD
        }
    }
    
    fclose(out);
    fclose(in);
}
