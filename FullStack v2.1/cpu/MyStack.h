//
//  MyStack.h
//  Assembler
//
//  Created by RI on 09.12.15.
//  Copyright © 2015 RI. All rights reserved.
//

#ifndef MyStack_h
#define MyStack_h
typedef int elem_t;

typedef struct mystack {
    elem_t* head;
    int count;
    int size;
} Stack_t;

void Stack_ctor(Stack_t* stack) {
    stack->head = (elem_t*) calloc(STACK_SIZE, sizeof(elem_t));
    stack->count = 0;
    stack->size = STACK_SIZE;
}

void Stack_dtor(Stack_t* stack) {
    assert(stack);
    free(stack->head);
}

void Stack_resize(Stack_t* stack) {
    stack->size *= MULTIPLIER;
    stack->head = realloc(stack->head, stack->size);
}

#endif /* MyStack_h */
