DEF_CMD(end,0,{return 0;},none)
DEF_CMD(push,1,{Stack_push (This, This->cmd[++This->pc]);},num)
DEF_CMD(pop,2,{Stack_pop(This);},none)
DEF_CMD(add,3,{Stack_push(This, Stack_pop(This)+Stack_pop(This));},none)
DEF_CMD(sub,4,{Stack_push(This, -(Stack_pop(This)-Stack_pop(This)));},none)
DEF_CMD(mul,5,{Stack_push(This, Stack_pop(This)*Stack_pop(This));},none)
DEF_CMD(div,6, { temp = Stack_pop(This);
    if (temp != 0) {
        Stack_push(This, temp);
        Stack_push(This, 1/(Stack_pop(This)/Stack_pop(This)));
    } else {
    printf("Can't divide on zero!");
    exit(-1);
    }
}, none)
DEF_CMD(mov, 7, {cpu_mov(This, This->cmd[++This->pc], This->cmd[++This->pc]);}, regs)
DEF_CMD(cmp, 13, {cpu_cmp(This);}, none)
DEF_CMD(jmp, 8, {cpu_jmp(This);}, label)
DEF_CMD(jne, 9, {cpu_jne(This);}, label)
DEF_CMD(je, 10, {cpu_je(This);}, label)
DEF_CMD(call, 11, {This->pc++;}, label)
DEF_CMD(ret, 12, {}, none)