#include <stdio.h>
#include "Stack.h"
#include "Token.h"
#include "Error.h"
#include "evaluate.h"
#include "CException.h"

int evaluate(char *expression, Stack *operatorStack, Stack *dataStack){
	Tokenizer *tokenizer;
	Token *token;
	NumberToken *number;
	OperatorToken *operator;
	
	tokenizer = tokenizerNew(expression);
	
	while(1){
	number = (NumberToken *)nextToken(tokenizer);
	if(number == NULL){
		Throw(ERR_NO_EXPRESSION);
	}else if(number->type != NUMBER_TOKEN){
		Throw(ERR_NOT_DATA);
	}else{
		push(dataStack, number);
	}
	
	operator = (OperatorToken *)nextToken(tokenizer);
	if(operator == NULL){
		break;
	}else if(operator->type != OPERATOR_TOKEN){
		Throw(ERR_NOT_OPERATOR);
	}else{
		tryEvaluateOperatorsOnStackThenPush(dataStack, operatorStack, operator);
	}
	}
	evaluateAllOperatorsOnStack(dataStack, operatorStack);
}

void tryEvaluateOperatorsOnStackThenPush(Stack *dataStack, Stack *operatorStack, OperatorToken *operator){
	OperatorToken *tokenCheck = pop(operatorStack);
	
	if(tokenCheck == NULL){
		push(operatorStack, operator);
	}else{
		if(tokenCheck->precedence >= operator->precedence){
			evaluateOperator(dataStack, tokenCheck);
		}
		else{
			push(operatorStack, tokenCheck);
			push(operatorStack, operator);
		}
	}
}

void evaluateAllOperatorsOnStack(Stack *dataStack, Stack *operatorStack){
	OperatorToken *token;
	while((token = pop(operatorStack))!= NULL){	
		evaluateOperator(dataStack, token);
	}
	
}

void evaluateOperator(Stack *dataStack, OperatorToken *operator){
	NumberToken *result;
	NumberToken *right = pop(dataStack);
	NumberToken *left = pop(dataStack);
	
	if(strcmp("+", operator->name) == 0){
	result = createNumberToken(right->value + left->value);
	}else if(strcmp("-", operator->name) == 0){
	result = createNumberToken(right->value - left->value);
	}else if(strcmp("^", operator->name) == 0){
	result = createNumberToken(right->value ^ left->value);
	}else if(strcmp("&", operator->name) == 0){
	result = createNumberToken(right->value & left->value);
	}else if(strcmp("|", operator->name) == 0){
	result = createNumberToken(right->value | left->value);
	}else if(strcmp("*", operator->name) == 0){
	result = createNumberToken(right->value * left->value);
	}else if(strcmp("/", operator->name) == 0){
	result = createNumberToken(right->value / left->value);
	}else if(strcmp("%", operator->name) == 0){
	result = createNumberToken(right->value % left->value);
	}else
		Throw(ERR_NOT_OPERATOR);

	
	push(dataStack, result);
}