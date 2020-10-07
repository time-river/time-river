#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
}NODE, *LINKNODE;

typedef struct Stack {
    LINKNODE top;
    LINKNODE bottom;
}STACK, *LINKSTACK;

//ADT stack
LINKSTACK InitStack(void); //Initialization stack, and return the point of the stack
void      Push(LINKSTACK stack, char x); //Insert the element in the top of stack, return True if successing
char      Pop(LINKSTACK stack); //Delete the top element of stack, and return its data
void      DesStack(LINKSTACK stack); //Destory stack
void      CleStack(LINKSTACK stack); //Clear stack
int       IsEmptyStack(LINKSTACK stack); //Return zero if stack is empty
//Handle
void Handle(char *string); //Handle and output language
void A(void);
void B(void);
void C(char *string, int len);
void Translation(char str); //Translation language
int main(void){
    char string[30];
    scanf("%s", string);
    Handle(string);
    return 0;
}
//handle
void Handle(char *string) {
    int len = strlen(string);
    int i, j;
    char x;
    char tmp[30] = {'0'};
    LINKSTACK stack = InitStack();

    for(i = len-1; i >= 0; --i)
        Push(stack, string[i]);

    while(!IsEmptyStack(stack)) {
        x = Pop(stack);
        switch(x) {
            case 'A':
                A();
                break;
            case 'B':
                B();
                break;
            case '(':
                for(i = 0, x=Pop(stack); x != ')'; x=Pop(stack))
                    tmp[j++] = x;
                tmp[j] = '\0';
                C(tmp, strlen(tmp));
                break;
            default:
                putchar(x);
                break;
        }
    }
}

void A(void) {
    Translation('s');
    Translation('a');
    Translation('e');
    return;
}
void B(void) {
    Translation('t');
    A();
    Translation('d');
    A();
    return;
}
void C(char *string, int len) {
    int i;
    char str = string[0];
    LINKSTACK stack = InitStack();

    for(i = 1; i < len; ++i)
        Push(stack, string[i]);
    while(!IsEmptyStack(stack)) {
        Translation(str);
        Translation(Pop(stack));
    }
    Translation(str);

    return;
}

void Translation(char x) {
    switch(x){
        case 't':
            printf("天");
            break;
        case 'd':
            printf("地");
            break;
        case 's':
            printf("上");
            break;
        case 'a':
            printf("一只");
            break;
        case 'e':
            printf("鹅");
            break;
        case 'z':
            printf("追");
            break;
        case 'g':
            printf("赶");
            break;
        case 'x':
            printf("下");
            break;
        case 'n':
            printf("蛋");
            break;
        case 'h':
            printf("恨");
            break;
    }
}
//Stack
LINKSTACK InitStack(void) {
    LINKSTACK stack = (LINKSTACK)malloc(sizeof(STACK));

    if (NULL == stack)
        exit(-1);
    stack->top = stack->bottom = NULL;

    return stack;
}

void Push(LINKSTACK stack, char x) {
    LINKNODE node = (LINKNODE)malloc(sizeof(NODE));

    if (NULL == node)
        exit(-1);
    node->data = x;
    node->next = stack->top;
    stack->top = node;

    return;
}

char Pop(LINKSTACK stack) {
    if (IsEmptyStack(stack))
        return '\0';
    else {
        char x;
        LINKNODE tmp;
        tmp = stack->top;
        x = tmp->data;
        stack->top = tmp->next;
        free(tmp);
        return x;
    }
}

void DesStack(LINKSTACK stack) {
    if (!IsEmptyStack(stack)) {
        CleStack(stack);
    }
    free(stack);

    return;
}

void CleStack(LINKSTACK stack) {
    LINKNODE tmp;
    while (!IsEmptyStack(stack)) {
        tmp = stack->top;
        stack->top = tmp->next;
        free(tmp);
    }
    return;
}
int IsEmptyStack(LINKSTACK stack) {
    if (stack->bottom == stack->top)
        return 1;
    else
        return 0;
}
