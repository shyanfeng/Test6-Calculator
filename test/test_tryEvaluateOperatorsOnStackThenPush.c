#include "unity.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "evaluate.h"
#include "Error.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_tryEvaluateOperatorsOnStackThenPush_should_pop_and_check_and_push_to_stack(){
	Stack dataStack, operatorStack, operator;
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	
	pop_ExpectAndReturn(&operatorStack, &plus);
	push_Expect(&operatorStack, &plus);
	push_Expect(&operatorStack, &multiply);	
	
	tryEvaluateOperatorsOnStackThenPush(&dataStack, &operatorStack, &multiply);
}

void test_tryEvaluateOperatorsOnStackThenPush_should_pop_and_check_when_higher_precedence_should_calculate_and_push(){
	Stack dataStack, operatorStack, operator;
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken answer1 = {.type = NUMBER_TOKEN, .value = 6};
	
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(6, &answer1);
	push_Expect(&dataStack, &answer1);
	
	tryEvaluateOperatorsOnStackThenPush(&dataStack, &operatorStack, &multiply);
}

