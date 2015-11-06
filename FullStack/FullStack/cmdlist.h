DEF_CMD(WHY,0,{printf("hello");},0)
DEF_CMD(PUSH,1,{StackPush (&stk, v);},1) //название команды и ее номер
DEF_CMD(POP,2,{StackPop(&stk);},0)
DEF_CMD(ADD,3,{StackPush(&stk, StackPop(&stk)+StackPop(&stk));},0)
DEF_CMD(SUB,4,{StackPush(&stk, -(StackPop(&stk)-StackPop(&stk)));},0)
