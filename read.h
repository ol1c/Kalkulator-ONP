#pragma once
#include <iostream>
#include "list.h"

enum Priority {
	OPERATOR_PLUS_MINUS = 1,
	OPERATOR_MULTIPLICATION_DIVISION = 2,
	OPERATOR_IF_MIN_MAX_N = 3,
	OPERATOR_PARENTHESES = 4
};

//converts char from param and returns int value
int charToInt(char& c);

//handles tokens from buffor
void handleToken(token_t& token, const char buff[]);

//function returns priority of the operator
int getPriority(const token_t& token);

//reads parentheses
void handleParentheses(token_t& buff, List& queue, List& stack);

//reads comma
void handleComma(List& queue, List& stack);

//reads dot
void handleDot(List& queue, List& stack);

//reads basic math operators
void handleBasicOperators(const token_t& buff, List& queue, List& stack);

//reads negation
void handleN(const token_t& buff, List& queue, List& stack);

//reads min and max operators
int handleMinMax(List& queue);

//reads operator if
void handleIf(List& queue);