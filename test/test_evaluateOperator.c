#include "unity.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "evaluate.h"
#include "Error.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_evaluateOperator_should_plus_1_and_2(void){
	Stack dataStack;
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 3};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(3, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &plus);
	
}

void test_evaluateOperator_should_minus_2_and_3(void){
	Stack dataStack;
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = -1};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(-1, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &minus);
	
}

void test_evaluateOperator_should_xor_5_and_6(void){
	Stack dataStack;
	OperatorToken xor = {.type = OPERATOR_TOKEN, .name = "^", .precedence = 50};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 3};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(3, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &xor);
	
}

void test_evaluateOperator_should_and_5_and_6(void){
	Stack dataStack;
	OperatorToken and = {.type = OPERATOR_TOKEN, .name = "&", .precedence = 20};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 5};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(4, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &and);
	
}

void test_evaluateOperator_should_multiply_4_and_3(void){
	Stack dataStack;
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 12};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(12, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &multiply);
	
}

void test_evaluateOperator_should_divide_5_and_6(void){
	Stack dataStack;
	OperatorToken divide = {.type = OPERATOR_TOKEN, .name = "/", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 30};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 5};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(5, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &divide);
	
}

void test_evaluateOperator_should_modulo_5_and_6(void){
	Stack dataStack;
	OperatorToken modulo = {.type = OPERATOR_TOKEN, .name = "%", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 30};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 2};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(2, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluateOperator(&dataStack, &modulo);
	
}

void test_evaluateOperator_should_throw_error_when_not_operator(void){
	int exception;
	Stack dataStack;
	OperatorToken modulo = {.type = OPERATOR_TOKEN, .name = ":", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 30};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 2};
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	
	Try{
		evaluateOperator(&dataStack, &modulo);
	}Catch(exception){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR, exception);
	}
}





