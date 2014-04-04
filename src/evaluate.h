#ifndef EVALUATE_H
#define EVALUATE_H

int evaluate(	char *expression, 
				Stack *operatorStack, 
				Stack *dataStack
			);
			
void tryEvaluateOperatorsOnStackThenPush(	
											Stack *dataStack,
											Stack *operatorStack, 
											OperatorToken *operator
										);
										
void evaluateAllOperatorsOnStack(	Stack *dataStack,
									Stack *operatorStack
								);

void evaluateOperator(	Stack *dataStack, 
						OperatorToken *operator
					);

#endif // EVALUATE_H