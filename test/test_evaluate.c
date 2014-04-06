#include "unity.h"
#include "mock_Token.h"
#include "mock_Stack.h"
#include "evaluate.h"
#include "Error.h"
#include "CException.h"

void setUp(void){}

void tearDown(void){}

void test_evaluate_should_throw_error_when_not_data(){
	int exception;
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	
	tokenizerNew_ExpectAndReturn("+", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	
	Try{
		evaluate("+", &operatorStack, &dataStack);
	}Catch(exception){
		TEST_ASSERT_EQUAL(ERR_NOT_DATA, exception);
	}
}

void test_evaluate_should_throw_error_when_not_operator(){
	int exception;
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	NumberToken number38 = {.type = NUMBER_TOKEN, .value = 38};
	NumberToken number39 = {.type = NUMBER_TOKEN, .value = 39};
	
	tokenizerNew_ExpectAndReturn("38 39", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number38);
	push_Expect(&dataStack, &number38);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number39);
	
	Try{
		evaluate("38 39", &operatorStack, &dataStack);
	}Catch(exception){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR, exception);
	}
}

void test_evaluate_1_plus_2(){
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 3};
	
	tokenizerNew_ExpectAndReturn("1+2", &tokenizer);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number1);
	push_Expect(&dataStack, &number1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number2);
	push_Expect(&dataStack, &number2);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(3, &answer);
	push_Expect(&dataStack, &answer);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	evaluate("1+2", &operatorStack, &dataStack);
}

void test_evaluate_4_multiply_3(){
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	OperatorToken multiply = {.type = OPERATOR_TOKEN, .name = "*", .precedence = 100};
	NumberToken number4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken number3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 12};
	
	tokenizerNew_ExpectAndReturn("4*3", &tokenizer);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number4);
	push_Expect(&dataStack, &number4);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&multiply);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &multiply);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number3);
	push_Expect(&dataStack, &number3);
	
	nextToken_ExpectAndReturn(&tokenizer, NULL);
	pop_ExpectAndReturn(&operatorStack, &multiply);
	pop_ExpectAndReturn(&dataStack, &number4);
	pop_ExpectAndReturn(&dataStack, &number3);
	createNumberToken_ExpectAndReturn(12, &answer);
	push_Expect(&dataStack, &answer);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	evaluate("4*3", &operatorStack, &dataStack);
	
}

void test_evaluate_3_plus_4_plus_5_minus_6(){
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	OperatorToken plus = {.type = OPERATOR_TOKEN, .name = "+", .precedence = 70};
	OperatorToken minus = {.type = OPERATOR_TOKEN, .name = "-", .precedence = 70};
	NumberToken number3 = {.type = NUMBER_TOKEN, .value = 3};
	NumberToken number4 = {.type = NUMBER_TOKEN, .value = 4};
	NumberToken number5 = {.type = NUMBER_TOKEN, .value = 5};
	NumberToken number6 = {.type = NUMBER_TOKEN, .value = 6};
	NumberToken answer1 = {.type = NUMBER_TOKEN, .value = 7};
	NumberToken answer2 = {.type = NUMBER_TOKEN, .value = 12};
	NumberToken answer3 = {.type = NUMBER_TOKEN, .value = 6};
	
	tokenizerNew_ExpectAndReturn("3+4+5-6", &tokenizer);
	
	//3+4
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number3);
	push_Expect(&dataStack, &number3);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number4);
	push_Expect(&dataStack, &number4);
	
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&plus);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &number4);
	pop_ExpectAndReturn(&dataStack, &number3);
	createNumberToken_ExpectAndReturn(7, &answer1);
	push_Expect(&dataStack, &answer1);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &plus);
	
	//3+4+5
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number5);
	push_Expect(&dataStack, &number5);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&minus);
	pop_ExpectAndReturn(&operatorStack, &plus);
	pop_ExpectAndReturn(&dataStack, &number5);
	pop_ExpectAndReturn(&dataStack, &answer1);
	createNumberToken_ExpectAndReturn(12, &answer2);
	push_Expect(&dataStack, &answer2);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	push_Expect(&operatorStack, &minus);
	
	//3+4+5-6
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number6);
	push_Expect(&dataStack, &number6);
	nextToken_ExpectAndReturn(&tokenizer, NULL);	
	pop_ExpectAndReturn(&operatorStack, &minus);
	pop_ExpectAndReturn(&dataStack, &number6);
	pop_ExpectAndReturn(&dataStack, &answer2);
	createNumberToken_ExpectAndReturn(6, &answer3);
	push_Expect(&dataStack, &answer3);
	
	pop_ExpectAndReturn(&operatorStack, NULL);
	
	evaluate("3+4+5-6", &operatorStack, &dataStack);
	
	
}



