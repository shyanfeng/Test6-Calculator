#ifndef EVALUATE_H
#define EVALUATE_H

int evaluate(char *expression);
void tryEvaluateOperatorsOnStackThenPush(	Stack *operatorStack, 
											Stack *dataStack, 
											OperatorToken *operator
										);
void evaluateAllOperatorsOnStack(	Stack *operatorStack, 
									Stack *dataStack
								);

void evaluateOperator(	Stack *dataStack, 
						OperatorToken *operator
					);

#endif // EVALUATE_H