DEF_CMD(END,0,{return 0;},none)
DEF_CMD(PUSH,1,{Stack_push (This, This->cmd[++i]);},num)
DEF_CMD(POP,2,{Stack_pop(This);},none)
DEF_CMD(ADD,3,{Stack_push(This, Stack_pop(This)+Stack_pop(This));},none)
DEF_CMD(SUB,4,{Stack_push(This, -(Stack_pop(This)-Stack_pop(This)));},none)
DEF_CMD(MUL,5,{Stack_push(This, Stack_pop(This)*Stack_pop(This))},none)
DEF_CMD(DIV,6, { temp = Stack_pop(This);
    if (temp != 0) {
        Stack_push(This, temp);
        Stack_push(This, 1/(Stack_pop(This)/Stack_pop(This)));
    } else {
    printf("Can't divide on zero!");
    exit(-1);
    }
}, none)
DEF_CMD(MOV, 7, {}, regs)
DEF_CMD(JMP, 8, {}, label)
DEF_CMD(JNE, 9, {}, label)
DEF_CMD(JE, 10, {}, label)
DEF_CMD(CAL, 11, {}, label)
DEF_CMD(RET, 12, {}, label)