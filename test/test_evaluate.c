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
	//push_Expect(&operatorStack, &dataStack, &number38);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number39);
	//push_Expect(&operatorStack, &dataStack, &number39);
	
	Try{
		evaluate("38 39", &operatorStack, &dataStack);
	}Catch(exception){
		TEST_ASSERT_EQUAL(ERR_NOT_OPERATOR, exception);
	}
}

void test_evaluate_1_plus_2(){
	int exception;
	Tokenizer tokenizer;
	Stack operatorStack, dataStack;
	
	OperatorToken plus= {.type = OPERATOR_TOKEN, .name = "+", .precedence = 100};
	NumberToken number1 = {.type = NUMBER_TOKEN, .value = 1};
	NumberToken number2 = {.type = NUMBER_TOKEN, .value = 2};
	NumberToken answer = {.type = NUMBER_TOKEN, .value = 3};
	
	tokenizerNew_ExpectAndReturn("1+2", &tokenizer);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number1);
	nextToken_ExpectAndReturn(&tokenizer, (Token *)&number2);
	
	pop_ExpectAndReturn(&dataStack, &number1);
	pop_ExpectAndReturn(&dataStack, &number2);
	createNumberToken_ExpectAndReturn(3, &answer);
	push_Expect(&dataStack, &answer);
	
	evaluate("1+2", &operatorStack, &dataStack);
}


