#include "unity.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "evaluate.h"
#include "Error.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_evaluateAllOperatorsOnStack_should_plus_and_multiply(void){
	Stack dataStack, operatorStack;
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken number3 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken answer1 = {.type = NUMBER_TOKEN, .value = 12};
	NumberToken answer2 = {.type = NUMBER_TOKEN, .value = 14};
	
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &number3);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(12, &answer1);
	push_Expect(&dataStack, &answer1);
	
	evaluateAllOperatorsOnStack(&operatorStack, &dataStack);
	
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &answer1);
	pop_ExpectAndReturn(&dataStack, &number1);
	createNumberToken_ExpectAndReturn(14, &answer2);
	push_Expect(&dataStack, &answer2);	
	
	evaluateAllOperatorsOnStack(&operatorStack, &dataStack);
}