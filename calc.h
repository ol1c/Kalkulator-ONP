#pragma once
#include <iostream>
#include "list.h"

//prints token
void printToken(const token_t& token);

//handles logic of calculations
bool calc(List& stack);

//handles addition
bool addition(List& stack);

//handles subtraction
bool subtraction(List& stack);

//handles multiplication
bool multiplication(List& stack);

//handles division
bool division(List& stack);

//handles minimum
bool minimum(List& stack);

//handles maximum
bool maximum(List& stack);

//handles if
bool operatorIf(List& stack);

//handles negation
bool negation(List& stack);