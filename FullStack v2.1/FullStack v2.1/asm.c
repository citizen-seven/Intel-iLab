#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100

int convert(char* number) {
    int sum = 0;
    unsigned long len = strlen(number);
    for (long i = len - 1; i >= 0; i--) {
        sum += (number[i] - '0') * pow(10, len - i - 1);
    }
    return sum;
}

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
        buff = (strtok(str, " \n"));
#define DEF_CMD(name,num,rule,argtype) \
        if (strcmp(buff, #name) == 0) {\
            switch (argtype) {\
            case 0:\
                com_count+=1;\
                break;\
            case 1:\
            case 2:\
                com_count+=2;\
                break;\
            case 3:\
                com_count+=3;\
                break;\
            }\
        }
#include "cmdlist.h"
        if (strcmp(buff, ":label") == 0) {
            buff = (strtok(NULL, "\n"));
            if (convert(buff) < 10) {
                labels[(int) *buff - '0'] = com_count;
                com_count--;
            } else {
                printf("Label number is over 10\n");
                exit(-1);
            }
        }
    };
#undef DEF_CMD
    
    rewind(in);
    while (!feof(in)) {
        fgets(str, MAX_LEN, in);
        printf ("%s\n", str);
        buff = (strtok(str, " \n"));
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
                            printf("Function %s needs an argument\n", #name);\
                            exit(-1);\
                        }\
                        break;\
                    case 2:\
                        buff = (strtok(NULL, " \n"));\
                        if (buff != NULL) {\
                            if (labels[(int)*buff-'0'] == -1) {\
                                printf("No :label %d to jump\n", (int)*buff-'0');\
                                exit(-1);\
                            } else fprintf(out,"%d ",labels[(int)*buff-'0']);\
                        } else {\
                            printf("Function %s needs an argument\n", #name);\
                            exit(-1);\
                        }\
                        break;\
                    case 3:\
                        buff = (strtok(((void*)0), ",\n"));\
                        if (buff != NULL) {\
                            if (strncmp(buff,"Rx",1) == 0) {\
                                fprintf(out, "%s ", ++buff);\
                            }\
                            buff = (strtok(((void*)0), " \n"));\
                            if (buff != NULL) {\
                                fprintf(out, "%s ", ++buff);\
                            } else {\
                                fprintf(out, "%d ", 0);\
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
