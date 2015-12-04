//
//  main.c
//  cpu
//
//  Created by RI on 17.11.15.
//  Copyright © 2015 RI. All rights reserved.
//

#define STACK_SIZE 20
#define LABEL_SIZE 10
#define REG_NUM 4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int elem_t;

typedef struct stack {
    elem_t* head;
    int count;
} Stack_t;

typedef struct cpu {
    Stack_t stack;
    Stack_t label_stack;
    unsigned int Rx[REG_NUM];
    int flag1;
    int* cmd;
    int pc;
    int cmd_num;
} CPU_t;


void CPU_ctor(CPU_t* This) {
    assert(This);
    This->stack.head = (elem_t*) calloc(STACK_SIZE, sizeof(elem_t));
    This->label_stack.head = (elem_t*) calloc(LABEL_SIZE, sizeof(elem_t));
    This->cmd = (int*) calloc(50, sizeof(int));
    printf("The %d memory has been callocated for stack\n",STACK_SIZE);
    printf("The %d memory has been callocated for labels\n",LABEL_SIZE);
    printf("The %d memory has been callocated for commands\n",STACK_SIZE);
    This->stack.count = 0;
    for (int k = 0; k<=REG_NUM; k++) {
        This->Rx[k] = 0;
    };
    This->flag1 = 0;
    This->pc = 0;
    This->cmd_num = 0;
}

void CPU_dtor(CPU_t* This) {
    assert(This);
    free(This->stack.head);
    free(This->label_stack.head);
    printf("\nThe memory has been cleaned\n");
    exit(0);
}

int cmd_download(CPU_t* This, FILE* in) {
    int buff = 0, i = 0, count = 0;
    while (!feof(in)) {
        fscanf(in, "%d", &buff);
        This->cmd[i] = buff;
        i++;
        count++;
    }
    fclose(in);
    return count;
}

int Stack_pop(CPU_t* This) {
    elem_t buff;
    if (This->stack.count>=1) {
        This->stack.count--;
        buff=This->stack.head[This->stack.count];
        This->stack.head[This->stack.count]=0;
    } else {
        printf("Pop from empty stack\n");
        exit(-1);
    }
    return buff;
}

void Stack_push(CPU_t* This, elem_t element) {
    This->stack.head[This->stack.count] = element;
    This->stack.count++;
}

int Stack_mov(CPU_t* This, unsigned int dest, unsigned int source) {
    if (source) {
        This->Rx[dest] = This->Rx[source];
        return 2;
    } else {
        This->Rx[dest] = Stack_pop(This);
        return 1;
    }
}

void cpu_jmp(CPU_t* This) {
    unsigned int dest = This->cmd[++This->pc];
    This->pc = dest;
    This->pc--;
}

void cpu_cmp(CPU_t* This) {
    elem_t a = Stack_pop(This);
    elem_t b = Stack_pop(This);
    if (a > b) {
        This->flag1 = 1;
    } else if (a == b) {
        This->flag1 = 0;
    } else This->flag1 = -1;
    Stack_push(This, b);
    Stack_push(This, a);
}

void cpu_jne(CPU_t* This) {
    cpu_cmp(This);
    if (This->flag1 != 0) {
        cpu_jmp(This);
    }
    This->pc++;
}

void cpu_je(CPU_t* This) {
    cpu_cmp(This);
    if (This->flag1 == 0) {
        cpu_jmp(This);
    }
    This->pc++;
}

int ok(CPU_t* This) {
    if (This->stack.count < 0) {
        printf("counter is below zero");
        exit(-1);
    }
    return 0;
}

int CPU_dump(CPU_t* This) {
    int i;
    printf("\nDUMP IS HERE\n");
    for (i=0; i < STACK_SIZE; i++) {
        printf("%d ",This->stack.head[i]);
    }
    printf("\nstack pointer = %d ",This->stack.count);
    for (i = 1; i <= REG_NUM; i++) {
        printf("\nR%d = %d", i, This->Rx[i]);
    }
    return 1;
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
    printf("LOL\n");
    return 0;
}