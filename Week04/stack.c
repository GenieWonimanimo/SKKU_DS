#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STACK   100
typedef enum {false, true} bool;
typedef int Data;

typedef struct
{
    Data items[MAX_STACK];
    int top;
} Stack;

// Make stack empty
void InitStack(Stack *pstack);
// Check whether stack is full
bool IsFull(Stack *pstack);
// Check whether stack is empty
bool IsEmpty(Stack *pstack);

// Read the item at the top
Data Peek(Stack *pstack);
// Insert an item at the top
void Push(Stack *pstack, Data item);
// Remove the item at the top
Data Pop(Stack *pstack);


void ReversePrint(char* s, int len);

bool IsParanBalanced(char* exp, int len);

int GetPriority(char op);
bool IsParentheses(char op);
bool ComparePriority(char op1, char op2);
void ConvInfixToPostfix(char* exp, char* convExp, int len);

int main(void)
{
    char exp[] = "2*(3+4)";
    char convExp[100];
    ConvInfixToPostfix(exp, convExp, sizeof(exp)/sizeof(char));
    printf("%s", convExp);
    return 0;
}

void InitStack(Stack *pstack)
{
    pstack->top = -1;
}

bool IsFull(Stack *pstack)
{
    return pstack->top == MAX_STACK - 1;
}

bool IsEmpty(Stack *pstack)
{
    return pstack->top == -1;
}

Data Peek(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Data item)
{
    if (IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

Data Pop(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[(pstack->top)--];
}

void ReversePrint(char* s, int len)
{
    Stack stack;
    char ch;

    InitStack(&stack);
    for (int i = 0; i < len; i++)
        Push(&stack, s[i]);
    
    while (!IsEmpty(&stack))
    {
        ch = Peek(&stack);
        printf("%c", ch);
        Pop(&stack);
    }
}

bool IsParanBalanced(char* exp, int len)
{
    Stack stack;
    int i;
    InitStack(&stack);
    for (i = 0; i < len; i++)
        if (exp[i] == '(')
            Push(&stack, exp[i]);
        else if (exp[i] == ')')
        {
            if (IsEmpty(&stack))
                return false;
            else
                Pop(&stack);
        }
    
    if (IsEmpty(&stack))
        return true;
    else
        return false;
}

int GetPriority(char op)
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

bool IsParentheses(char op)
{
    return (op == '(' || op == ')');
}

bool ComparePriority(char op1, char op2)
{
    int op1_pr = GetPriority(op1);
    int op2_pr = GetPriority(op2);

    if (op1_pr >= op2_pr)
        return true;
    else
        return false;
}

int EvalPostfix(char* exp, int len)
{
    Stack stack;
    int op1, op2;
    int i;
    InitStack(&stack);
    for (i = 0; i < len; i++)
    {
        if (isdigit(exp[i]))
            Push(&stack, exp[i] - '0');
        else
        {
            op2 = Peek(&stack); Pop(&stack);
            op1 = Peek(&stack); Pop(&stack);
            if (exp[i] == '+')
                Push(&stack, op1 + op2);
            else if (exp[i] == '-')
                Push(&stack, op1 - op2);
            else if (exp[i] == '*')
                Push(&stack, op1 * op2);
            else if (exp[i] == '/')
                Push(&stack, op1 / op2);
        }
    }
    return Peek(&stack);
}

void ConvInfixToPostfix(char* exp, char* convExp, int len)
{
    Stack stack;
    int idx = 0;
    int i;
    InitStack(&stack);
    for (i = 0; i < len; i++)
    {
        if (isdigit(exp[i]))
            convExp[idx++] = exp[i];
        else if (IsParentheses(exp[i]))
            continue;
        else
        {
            while (!IsEmpty(&stack) && ComparePriority(Peek(&stack), exp[i]))
            {
                convExp[idx++] = Peek(&stack);
                Pop(&stack);
            }
            Push(&stack, exp[i]);
        }
    }
    while (!IsEmpty(&stack))
    {
        convExp[idx++] = Peek(&stack);
        Pop(&stack);
    }
}