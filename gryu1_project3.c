/*
 * Stack Project
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#define EXTRA 1

struct stack{
    int*stk;
    int top;
    int max_size;
};

unsigned int memory_used = 0;

struct stack * newStack(int size){
    struct stack * other_stack = malloc(sizeof(struct stack));
    memory_used = memory_used + (sizeof(struct stack));
    (*other_stack).stk = malloc(sizeof(size)*size);
    memory_used = memory_used + (sizeof(size)*size);
    (*other_stack).top = -1;
    (*other_stack).max_size = size;
    return other_stack;
}

int push(struct stack * s, int data){
    if((*s).top == (*s).max_size-1){
        return -1;
    }else{
        (*s).top++;
        (*s).stk[(*s).top] = data;
        return 0;
    }
}

void display(struct stack * s){
    int num;
    printf("The status of the stack is:\n\t");
    printf("top:%d\n\t", (*s).top);
    printf("max_size:%d\n\t", (*s).max_size);
    printf("============\n\t");
    for (num = (*s).top; num >= 0; --num){
        printf("[%d] :%d\n\t", num, (*s).stk[num]);
    }
    //printf("%d", (*s).stk);
}

int  pop(struct stack * s){
    int x, q;
    int (*stk_new) [(*s).max_size];
    if((*s).top == -1){
        return -1;
    }else{
        x = (*s).stk[(*s).top];
        stk_new = malloc(((*s).max_size)*sizeof(int));
        memory_used = memory_used + ((*s).max_size)*sizeof(int);
        for (q = 0; q < (*s).max_size; q++){
            (*stk_new)[q] = (*s).stk[q];
        }
    }
    free((*s).stk);
    memory_used = memory_used - ((*s).max_size)*sizeof(int);
    (*s).stk = stk_new;
    (*s).top--;
    return x;
}

void deleteStack(struct stack * s){
    free((*s).stk);
    memory_used = memory_used - ((*s).max_size)*sizeof(int);
    free(s);
    memory_used = memory_used - sizeof(struct stack);
}

void stringReverse (char string[], struct stack * ptr){
    int i;
    for (i = 0; i < strlen(string); i++)
        push(ptr, *(string+i));
    for (i = 0; i < strlen(string); i++)
        *(string+i) = pop(ptr);
}

void main (){
    printf("Heap Memory in use: %lu\n", memory_used);
    /******************** Test #1 **************************/
    printf("\n =========== Test # 1: Stack creation =========== \n");
    struct stack * s = newStack(10);
    assert(s->stk != 0);
    assert(s->top == -1);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 1 passed\n");
    /******************** Test #2 **************************/
    printf("\n =========== Test # 2: push 1 value onto the stack =========== \n");
    assert(push(s, 5) != -1);
    display(s);
    assert(s->stk[0] == 5);
    assert(s->top == 0);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 2 passed\n");

    /******************** Test #3 **************************/
    printf("\n =========== Test # 3: push 2nd value onto the stack =========== \n");
    assert(push(s, 7) != -1);
    display(s);
    assert(s->stk[0] == 5);
    assert(s->stk[1] == 7);
    assert(s->top == 1);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 3 passed\n");

    /******************** Test #4 **************************/
    printf("\n =========== Test # 4: fill the stack =========== \n");
    for(int i = 2; i < 10; i++){
        assert(push(s, i+10) != -1);
        display(s);
        assert(s->stk[i] == i+10);
        assert(s->top == i);
        assert(s->max_size == 10);
    }
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 4 passed\n");

    /******************** Test #5 **************************/
    printf("\n =========== Test # 5: insert into full stack =========== \n");
    assert(push(s, 10) == -1);
    assert(s->top == 9);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 5 passed\n");

    /******************** Test #6 **************************/
    printf("\n =========== Test # 6: pop 1 value off the stack =========== \n");
    assert(pop(s) == 19);
    display(s);
    assert(s->top == 8);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 6 passed\n");

    /******************** Test #7 **************************/
    printf("\n =========== Test # 7: pop 2nd value off the stack =========== \n");
    assert(pop(s) == 18);
    display(s);
    assert(s->stk[s->top] == 17);
    assert(s->top == 7);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 7 passed\n");

    /******************** Test #7 **************************/
    printf("\n =========== Test # 8: push value onto the stack =========== \n");
    assert(push(s, 20) != -1);
    assert(push(s, 21) != -1);
    display(s);
    assert(s->stk[s->top] == 21);
    assert(s->top == 9);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 8 passed\n");

    /******************** Test #9 **************************/
    printf("\n =========== Test # 9: remove remaining elements from the stack =========== \n");
    int array[] = {5, 7, 12, 13, 14, 15, 16, 17, 20, 21};
    for(int i = sizeof(array)/sizeof(int) - 1; i >= 0; i--){
        assert(pop(s) == array[i]);
        display(s);
        assert(s->top == i-1);
        assert(s->max_size == 10);
    }
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test #9 passed\n");

    /******************** Test #10 **************************/
    printf("\n =========== Test # 10: pop from an empty stack =========== \n");
    assert(pop(s) == -1);
    assert(s->top == -1);
    assert(s->max_size == 10);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test # 10 passed\n");

    /******************** Test #11 **************************/
    printf("\n =========== Test # 11: random elements into a random sized stack =========== \n");
    srand(time(NULL));
    int stack_size = (rand() % 500) + 5;
    struct stack * rand_stack = newStack(stack_size);
    int stest = -1;
    int direction = 2;
    for(int i = 0; i < stack_size * 10; i++){
        if(rand() % 10 <= direction){
            (pop(rand_stack) == -1) ? direction = 2 : stest--;
            assert(rand_stack->top == stest);
        }else{
            (push(rand_stack, rand() % 100) == -1) ? direction = 8 : stest++;
            assert(rand_stack->top == stest);
        }
        assert(rand_stack->max_size == stack_size);
    }
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test #11 passed\n");

    char str1[] = "Hello";
    struct stack * str_stack1 = newStack(sizeof(str1));
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("%s => ", str1);
    stringReverse(str1, str_stack1);
    printf("%s\n", str1);

    char str2[] = "";
    struct stack * str_stack2 = newStack(sizeof(str2));
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("%s => ", str2);
    stringReverse(str2, str_stack2);
    printf("%s\n", str2);

    char str3[] = "Computer Science";
    struct stack * str_stack3 = newStack(sizeof(str3));
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("%s => ", str3);
    stringReverse(str3, str_stack3);
    printf("%s\n", str3);

    deleteStack(str_stack1);
    deleteStack(str_stack2);
    deleteStack(str_stack3);
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Extra Credit passed\n");
    
    /******************** Test #12 **************************/
    printf("\n=========== Test # 12: Clean up memory ===========\n");
    deleteStack(s);
    s = NULL;
    deleteStack(rand_stack);
    rand_stack = NULL;
    printf("Heap Memory in use: %lu\n", memory_used);
    printf("\t...Test #12 passed\n");
}
