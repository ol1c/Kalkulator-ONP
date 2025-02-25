#include <iostream>
#include "list.h"
#include "calc.h"

void printToken(const token_t& token)
{
	switch (token.id)
	{
	case NUMBER:
	{
		printf("%d  ", token.value);
		break;
	}
	case PLUS:
	{
		printf("+  ");
		break;
	}
	case MINUS:
	{
		printf("-  ");
		break;
	}
	case MULTIPLICATION:
	{
		printf("*  ");
		break;
	}
	case DIVISION:
	{
		printf("/  ");
		break;
	}
	case PARENTHESES_START:
	{
		printf("(  ");
		break;
	}
	case PARENTHESES_END:
	{
		printf(")  ");
		break;
	}
	case MAX:
	{
		printf("MAX%d  ", token.value);
		break;
	}
	case MIN:
	{
		printf("MIN%d  ", token.value);
		break;
	}
	case IF:
	{
		printf("IF  ");
		break;
	}
	case N:
	{
		printf("N  ");
		break;
	}
	}
}

bool addition(List& stack)
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error
	token_t* token = stack.GetItemPointer();

	if (token->id != NUMBER)
		return true; //error

	int sum;
	
	sum = token->value;
	stack.Pop(); //pop first addend
	if (stack.IsEmpty())
		return true; //error

	token = stack.GetItemPointer();
	if (token->id != NUMBER)
		return true; //error
	else
		sum += token->value;
	stack.Pop(); //pop second addend
	stack.PushStack(sum);
	return false; //no error
}

bool subtraction(List& stack)
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error

	token_t* token = stack.GetItemPointer(); //get minuend
	if (token->id != NUMBER)
		return true; //error
	int subtrahend = token->value;
	stack.Pop(); //pop subtrahend

	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer(); //get minuend
	if (token->id != NUMBER)
		return true; //error
	int difference = token->value;
	stack.Pop(); //pop minuend

	difference -= subtrahend;
	stack.PushStack(difference);
	return false; //no error
}

bool multiplication(List& stack)
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error
	token_t* token = stack.GetItemPointer();
	if (token->id != NUMBER)
		return true; //error

	int product;
	product = token->value;
	stack.Pop(); //pop multiplicand
	if (stack.IsEmpty())
		return true; //error

	token = stack.GetItemPointer();
	if (token->id != NUMBER)
		return true; //error
	else
		product *= token->value;
	stack.Pop(); //pop multiplier
	stack.PushStack(product);
	return false; //no error
}

bool division(List& stack)
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error
	token_t* token = stack.GetItemPointer(); //get divisor
	if (token->id != NUMBER)
		return true; //error
	if (token->value == 0)
		return true; //error
	int divisor = token->value;
	stack.Pop(); //pop divisor

	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer(); //get dividend
	if (token->id != NUMBER)
		return true; //error
	int quotient = token->value;
	stack.Pop(); //pop divident

	quotient /= divisor;
	stack.PushStack(quotient);
	return false; //no error
}

bool minimum(List& stack)
{
	token_t* token = stack.GetItemPointer();
	int size = token->value;
	stack.Pop();
	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer();
	int min;
	min = token->value;
	for (int i = 1; i <= size; i++)
	{
		if (stack.IsEmpty())
			return true; //error
		token = stack.GetItemPointer();
		if (token->id != NUMBER)
			return true; //error
		if (min > token->value)
			min = token->value;
		stack.Pop();
	}
	stack.PushStack(min);
	return false; //no error
}

bool maximum(List& stack)
{
	token_t* token = stack.GetItemPointer();
	int size = token->value;
	stack.Pop();
	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer();
	int max;
	max = token->value;
	for (int i = 1; i <= size; i++)
	{
		if (stack.IsEmpty())
			return true; //error
		token = stack.GetItemPointer();
		if(token->id != NUMBER)
			return true; //error
		if(max < token->value)
			max = token->value;
		stack.Pop();
	}
	stack.PushStack(max);
	return false; //no error
}

// if(a,b,c) if a>0 push b to stack else push c to stack
bool operatorIf(List& stack) 
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error
	token_t* token = stack.GetItemPointer(); //get c
	if (token->id != NUMBER)
		return true; //error
	int c, b;
	c = token->value; //copy value of c

	stack.Pop(); //pop c
	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer();//get b
	if (token->id != NUMBER)
		return true; //error
	b = token->value; //copy value of b

	stack.Pop(); //pop b
	if (stack.IsEmpty())
		return true; //error
	token = stack.GetItemPointer(); //get a
	if (token->id != NUMBER)
		return true; //error

	if (token->value > 0)
	{
		stack.Pop(); //pop a
		stack.PushStack(b); //push b
	}
	else
	{
		stack.Pop(); //pop a
		stack.PushStack(c); //push c
	}
	return false; //no error
}

bool negation(List& stack)
{
	stack.Pop(); //pop operator
	if (stack.IsEmpty())
		return true; //error
	token_t* token = stack.GetItemPointer();
	if (token->id != NUMBER)
		return true; //error
	else
	{
		token->value *= (-1);
		return false; //no error
	}
}

bool calc(List& stack)
{
	bool err_flag = true; //error, if everything works it will change the flag
	token_t* token = stack.GetItemPointer();
	switch (token->id)
	{
	case PLUS:
	{
		err_flag = addition(stack);
		break;
	}
	case MINUS:
	{
		err_flag = subtraction(stack);
		break;
	}
	case MULTIPLICATION:
	{
		err_flag = multiplication(stack);
		break;
	}
	case DIVISION:
	{
		err_flag = division(stack);
		break;
	}
	case MIN:
	{
		err_flag = minimum(stack);
		break;
	}
	case MAX:
	{
		err_flag = maximum(stack);
		break;
	}
	case IF:
	{
		err_flag = operatorIf(stack);
		break;
	}
	case N:
	{
		err_flag = negation(stack);
		break;
	}
	}
	return err_flag;
}