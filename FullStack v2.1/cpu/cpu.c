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

typedef struct stack { // You have stack structure already!! or you should have
    elem_t* head;
    int count;
} Stack_t;

typedef struct cpu {
    Stack_t stack;
    Stack_t label_stack;
    unsigned int Rx[REG_NUM]; // just R[__NUM__] is ok. or gprs. in Rx - x means any number
    int flag1; // flag? flags? why flag1... or cmp_flag if you use it just for comparison
    int* cmd;
    int pc;
    int cmd_num;
} CPU_t;


void CPU_ctor(CPU_t* This) {
    assert(This);
    This->stack.head = (elem_t*) calloc(STACK_SIZE, sizeof(elem_t)); // STACK_CONSTRUCT
    This->label_stack.head = (elem_t*) calloc(LABEL_SIZE, sizeof(elem_t)); // STACK_CONSTRUCT
    This->cmd = (int*) calloc(50, sizeof(int)); // there is no free afterwards
    printf("The %d memory has been callocated for stack\n",STACK_SIZE); // debug prints below. it is better to place them 
    printf("The %d memory has been callocated for labels\n",LABEL_SIZE); // right after the allocation takes place.
    printf("The %d memory has been callocated for commands\n",STACK_SIZE); // not at some random place in the constructor
    This->stack.count = 0; // STACK_CONSTRUCT
    for (int k = 0; k<=REG_NUM; k++) {
        This->Rx[k] = 0;
    };
    This->flag1 = 0;
    This->pc = 0;
    This->cmd_num = 0;
}

void CPU_dtor(CPU_t* This) {
    assert(This); // maybe smth more informative like assert(This && "Can't destruct a NULL pointer")
    free(This->stack.head); // STACK_DESTRUCT
    free(This->label_stack.head); // STACK_DESTRUCT
    printf("\nThe memory has been cleaned\n"); // debug print
    exit(0); // hey wtf? you don't need to close the program after destruction. what if you have multiple cores??
    // you forgot about command memory
}

int cmd_download(CPU_t* This, FILE* in) {
    int buff = 0, i = 0, count = 0;
    while (!feof(in)) {
        fscanf(in, "%d", &buff);
        This->cmd[i] = buff;
        i++;  // do not forget about command memory size.
        count++;
    }
    fclose(in);
    return count;
}

int Stack_pop(CPU_t* This) { // Stack_pop from your previous task?
    elem_t buff;
    if (This->stack.count>=1) {
        This->stack.count--;
        buff=This->stack.head[This->stack.count]; // return This->stack.head[This->stack.count];
        This->stack.head[This->stack.count]=0; // that is not cruicial. you can remove it -- see above.
    } else {
        printf("Pop from an empty stack\n");
        exit(-1); // same here. you dont need to exit completely. OR it should be safe. The best is to call all destructors.
    }
    return buff;
}

void Stack_push(CPU_t* This, elem_t element) {
    This->stack.head[This->stack.count] = element; // why don't you use Stack_pop and Stack_push from 
    This->stack.count++; // stack overflow?
}

int Stack_mov(CPU_t* This, unsigned int dest, unsigned int source) { // this is a CPU command. not Stack
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
    This->pc--;  // what is this for?
}

void cpu_cmp(CPU_t* This) {
    elem_t a = Stack_pop(This);
    elem_t b = Stack_pop(This);
    if (a > b) {
        This->flag1 = 1;
    } else if (a == b) {
        This->flag1 = 0;
    } else This->flag1 = -1;
    Stack_push(This, b); // In my opinion you can think of a specification where you don't need them back
    Stack_push(This, a); // But if you want to keep those numbers, it is fine
}

void cpu_jne(CPU_t* This) {
    cpu_cmp(This); // this should be a separate instruction, not a function
    if (This->flag1 != 0) {
        cpu_jmp(This);
    }
    This->pc++; // what is this for?
}

void cpu_je(CPU_t* This) { // same as function above
    cpu_cmp(This);  
    if (This->flag1 == 0) {
        cpu_jmp(This);
    }
    This->pc++;
}

int ok(CPU_t* This) { // not enough for a CPU checker!..
    if (This->stack.count < 0) {
        printf("counter is below zero");
        exit(-1);
    }
    return 0;
}

int CPU_dump(CPU_t* This) { // Dump is not full
    int i;
    printf("\nDUMP IS HERE\n");
    for (i=0; i < STACK_SIZE; i++) { // print that it is stack and which one! you have two of them
        printf("%d ",This->stack.head[i]);
    }
    printf("\nstack pointer = %d ",This->stack.count);
    for (i = 1; i <= REG_NUM; i++) { // Why did you left R0 alone? and you definitely don't have R[_REG_NUM_]!!
        printf("\nR%d = %d", i, This->Rx[i]);
    }
    return 1;
}

int CPU_run(CPU_t* This) {
    int i = 0;
    int temp = 0;
    for (i=0; ; This->pc++) {
    switch (This->cmd[This->pc]) { // indentation
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
