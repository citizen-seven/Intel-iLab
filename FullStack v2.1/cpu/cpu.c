//
//  main.c
//  cpu
//
//  Created by RI on 17.11.15.
//  Copyright © 2015 RI. All rights reserved.
//

#define STACK_SIZE 100
#define LABEL_SIZE 10
#define MULTIPLIER 2

#define REG_NUM 4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "MyStack.h"

typedef struct cpu {
    Stack_t stack;
    unsigned int R[REG_NUM];
    int cmp_flag;
    int* cmd;
    int pc;
    int cmd_num;
} CPU_t;


void CPU_ctor(CPU_t* This) {
    assert(This);
    Stack_ctor(&This->stack);
    printf("The %d memory has been callocated for stack\n",STACK_SIZE);
    This->cmd_num = 20;
    This->cmd = (int*) calloc(This->cmd_num, sizeof(int));
    printf("The %d memory has been callocated for commands\n",STACK_SIZE);
    for (int k = 0; k<=REG_NUM; k++) {
        This->R[k] = 0;
    };
    This->cmp_flag = 0;
    This->pc = 0;
}

int CPU_dump(CPU_t* This) {
    int i;
    printf("\nDUMP IS HERE\n");
    printf("Numbers stack:");
    for (i=0; i < This->stack.size; i++) {
        printf("%d ",This->stack.head[i]);
    }
    printf("\nStack pointer = %d ",This->stack.count);
    printf("\nCurrent numbers stack size = %d",This->stack.size);
    printf("\nCompare flag = %d ",This->cmp_flag);
    printf("\nCommand number is %d of %d allocated memory",This->pc, This->cmd_num);
    for (i = 1; i < REG_NUM; i++) {
        printf("\nR%d = %d", i, This->R[i]);
    }
    return 1;
}

void CPU_dtor(CPU_t* This) {
    assert(This && "Can't destruct a NULL pointer");
    Stack_dtor(&This->stack);
    free(This->cmd);
    printf("\nThe memory has been cleaned\n");
}

int cmd_download(CPU_t* This, FILE* in) {
    int buff = 0, i = 0, count = 0;
    while (!feof(in)) {
        fscanf(in, "%d", &buff);
        This->cmd[i] = buff;
        i++;
        count++;
        if (count >= This->cmd_num) {
            This->cmd_num*=2;
            This->cmd = (int*)realloc(This->cmd, This->cmd_num);
        }
    }
    fclose(in);
    return count;
}

int Stack_pop(CPU_t* This) {
    if (This->stack.count>=1) {
        This->stack.count--;
        return This->stack.head[This->stack.count]; // 
    } else {
        printf("Pop from an empty stack\n");
        CPU_dump(This);
        CPU_dtor(This);
        exit(0xBAD);
    }
}

void Stack_push(CPU_t* This, elem_t element) {
    This->stack.head[This->stack.count] = element; // why don't you use Stack_pop and Stack_push from 
    This->stack.count++; // stack overflow?
}

int cpu_mov(CPU_t* This, unsigned int dest, unsigned int source) {
    if (source) {
        This->R[dest] = This->R[source];
        return 2;
    } else {
        This->R[dest] = Stack_pop(This);
        return 1;
    }
}

void cpu_jmp(CPU_t* This) {
    unsigned int dest = This->cmd[++This->pc];
    This->pc = --dest; //interpreter will increment the value of pc
}

void cpu_cmp(CPU_t* This) {
    elem_t a = Stack_pop(This);
    elem_t b = Stack_pop(This);
    if (a > b) {
        This->cmp_flag = 1;
    } else if (a == b) {
        This->cmp_flag = 0;
    } else This->cmp_flag = -1;
    Stack_push(This, b);
    Stack_push(This, a);
}

void cpu_jne(CPU_t* This) {
    cpu_cmp(This);
    if (This->cmp_flag != 0) {
        cpu_jmp(This);
    }
}

void cpu_je(CPU_t* This) {
    elem_t a = Stack_pop(This);
    elem_t b = Stack_pop(This);
    if (a > b) {
        This->cmp_flag = 1;
    } else if (a == b) {
        This->cmp_flag = 0;
    } else This->cmp_flag = -1;
    if (This->cmp_flag == 0) {
        cpu_jmp(This);
    }
    This->pc++;
}

int stack_ok(CPU_t* This) { // not enough for a CPU checker!..
    if (This->stack.count < 0) {
        printf("counter is below zero");
        exit(-1);
    }
    if (This->stack.head == NULL) {
        printf("Stack overflow");
        exit(-1);
    }
    return 0;
}

int CPU_run(CPU_t* This) {
    int i = 0;
    int temp = 0;
    for (i=0; ; This->pc++) {
        switch (This->cmd[This->pc]) {
#define DEF_CMD(name,num,rule,argnum) \
        case num:\
                rule\
                break;
#include "cmdlist.h"
        }
    }
    return 0;
}

int main() {
    CPU_t* cpu;
    FILE* in = fopen("out.txt","r");
    CPU_ctor(cpu);
    if(!cmd_download(cpu, in)) {
        printf("Empty commands file!!\n");
        CPU_dtor(cpu);
        return 0;
    }
    CPU_run(cpu);
    CPU_dump(cpu);
    CPU_dtor(cpu);
    printf("LOL\n"); // LOL :)
    return 0;
}
