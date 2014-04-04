#ifndef STACK_H
#define STACK_H

typedef struct{
			char dummy;
			}Stack;


Stack *stackNew(void);
void push(Stack *stack, void *data);
void *pop(Stack *stack);
			
#endif // STACK_H