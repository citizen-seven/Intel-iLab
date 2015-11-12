//
//  Header.h
//  BracketsCheckinhWithStack
//
//  Created by RI on 11.11.15.
//  Copyright © 2015 RI. All rights reserved.
//

#ifndef Header_h
#define Header_h

typedef struct {
    char* head;
    int count;
} stack;

void ctor(stack* This) {
    assert(This);
    This -> head = (char *) calloc(20, sizeof(char));
}

void dtor(stack* This) {
    assert(This);
    free(This->head);
    printf("The sequence of brackets is incorrect\n");
    exit(0);
}

void push(char bracket, stack* This) {
    This->head[This->count] = bracket;
    This->count++;
};

char pop(stack* This) {
    This->count--;
    return(This->head[This->count]);
};

int ok(stack* This) {
    return 0;
};

int dump(stack* This) {
    int i;
    printf("DUMP IS HERE\n");
    printf("count=%d\n",This->count);
    for (i=0; i<This->count; i++) {
        printf("%c ",This->head[This->count]);
    }
    
    return 1;
}

#endif /* Header_h */
