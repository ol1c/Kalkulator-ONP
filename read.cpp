#include <iostream>
#include "list.h"
#include "read.h"

using namespace std;

int charToInt(const char& c)
{
	//it transfers a number from char to int
	//char digits start from 48('0') and go to 57('9')
	//so char - 48 equals int value of this number
	return (int)c - 48;
}


void handleToken(token_t& token, const char buff[])
//0 - . or ,
//1 - number
//2 - +
//3 - -
//4 - *
//5 - /
//6 - (
//7 - )
//8 - MAX
//9 - MIN
//10 - IF
//11 - N
{
	if (buff[0] >= '0' && buff[0] <= '9')
	{
		token.id = NUMBER;
		int i = 0;
		token.value = 0;
		while (buff[i] != '\0')
		{
			token.value *= 10;
			token.value += charToInt(buff[i]);
			i++;
		}
	}
	//if it's not a number it has to be an operator
	else if (buff[0] == 'I')
	{
	token.id = IF;
	}
	//N like operator N
	else if (buff[0] == 'N')
	{
		token.id = N;
	}
	//M like operator MIN and MAX
	else if (buff[0] == 'M')
	{
		//I like MIN
		if (buff[1] == 'I')
		{
			token.id = MIN;
		}
		//if it's not MIN that means it's MAX
		else
		{
			token.id = MAX;
		}
	}
	else if (buff[0] == '+')
	{
		token.id = PLUS;
	}
	else if (buff[0] == '-')
	{
		token.id = MINUS;
	}
	else if (buff[0] == '*')
	{
		token.id = MULTIPLICATION;
	}
	else if (buff[0] == '/')
	{
		token.id = DIVISION;
	}
	else if (buff[0] == '(')
	{
		token.id = PARENTHESES_START;
	}
	else if (buff[0] == ')')
	{
		token.id = PARENTHESES_END;
	}
	else
	{
		token.id = COMMA;
	}
}

int getPriority(const token_t& token)
{
	if (token.id == PLUS || token.id == MINUS)
	{
		return OPERATOR_PLUS_MINUS;
	}
	else if (token.id == MULTIPLICATION || token.id == DIVISION)
	{
		return OPERATOR_MULTIPLICATION_DIVISION;
	}
	else if (token.id == PARENTHESES_START || token.id == PARENTHESES_END)
	{
		return OPERATOR_PARENTHESES;
	}
	else
	{
		return OPERATOR_IF_MIN_MAX_N;
	}
}

void handleParentheses(token_t& buff, List& queue, List& stack)
{
	token_t* token_pointer;

	if (buff.id == PARENTHESES_START)
	{
		stack.PushStack(buff.id, buff.value);
	}
	else
	{
		while (!stack.IsEmpty())
		{
			token_pointer = stack.GetItemPointer();
			if (token_pointer->id == PARENTHESES_START)
			{
				stack.Pop();
				break;
			}
			else
			{
				queue.PushQueue(token_pointer->id, token_pointer->value);
				stack.Pop();
			}
		}
	}

}

void handleComma(List& queue, List& stack)
{
	token_t* token_pointer;

	while (!stack.IsEmpty())
	{
		token_pointer = stack.GetItemPointer();
		if (token_pointer->id == PARENTHESES_START)
			break;
		queue.PushQueue(token_pointer->id, token_pointer->value);
		stack.Pop();
	}
}

void handleDot(List& queue, List& stack)
{
	token_t* token_pointer;
	while (!stack.IsEmpty())
	{
		token_pointer = stack.GetItemPointer();
		queue.PushQueue(token_pointer->id, token_pointer->value);
		stack.Pop();
	}
}

void handleBasicOperators(const token_t& buff, List& queue, List& stack)
{
	token_t* token_pointer;
	int priority;
	priority = getPriority(buff);
	while (!stack.IsEmpty())
	{
		token_pointer = stack.GetItemPointer();
		if (token_pointer->id == PARENTHESES_START || getPriority(*token_pointer) < priority)
			break;

		queue.PushQueue(token_pointer->id, token_pointer->value);
		stack.Pop();
	}
	stack.PushStack(buff.id, buff.value);
}

void handleN(const token_t& buff, List& queue, List& stack)
{
	token_t* token_pointer;
	int priority;
	priority = getPriority(buff);
	while (!stack.IsEmpty())
	{
		token_pointer = stack.GetItemPointer();
		if (token_pointer->id == PARENTHESES_START ||token_pointer->id == N || getPriority(*token_pointer) < priority)
			break;

		queue.PushQueue(token_pointer->id, token_pointer->value);
		stack.Pop();
	}
	stack.PushStack(buff.id, buff.value);
}

int handleMinMax(List& queue)
{
	const int MAX_SIZE = 11; //max int as a string 
	List stack;
	token_t token;
	char buff[MAX_SIZE];
	int how_many = 1;

	while (true)
	{
		cin >> buff;
		handleToken(token, buff);

		if (token.id == NUMBER)
		{
			queue.PushQueue(token.id, token.value);
		}
		else if (getPriority(token) == OPERATOR_PARENTHESES)
		{
			handleParentheses(token, queue, stack);
		}
		else if (token.id == COMMA)
		{
			handleComma(queue, stack);
			how_many++;
		}
		else if (token.id == MAX || token.id == MIN)
		{
			token.value = handleMinMax(queue);
			queue.PushQueue(token.id, token.value);
		}
		else if (token.id == N)
		{
			handleN(token, queue, stack);
		}
		else if (token.id == IF)
		{
			handleIf(queue);
			queue.PushQueue(token.id, token.value);
		}
		else
		{
			handleBasicOperators(token, queue, stack);
		}

		if (stack.IsEmpty())
		{
			return how_many;
		}
	}
}

void handleIf(List& queue)
{
	const int MAX_SIZE = 11; //max int as a string 
	List stack;
	token_t token;
	char buff[MAX_SIZE];

	while (true)
	{
		cin >> buff;
		handleToken(token, buff);

		if (token.id == NUMBER)
		{
			queue.PushQueue(token.id, token.value);
		}
		else if (getPriority(token) == OPERATOR_PARENTHESES)
		{
			handleParentheses(token, queue, stack);
		}
		else if (token.id == MAX || token.id == MIN)
		{
			token.value = handleMinMax(queue);
			queue.PushQueue(token.id, token.value);
		}
		else if (token.id == N)
		{
			handleN(token, queue, stack);
		}
		else if (token.id == IF)
		{
			handleIf(queue);
			queue.PushQueue(token.id, token.value);
		}
		else if (token.id == COMMA)
		{
			handleComma(queue, stack);
		}
		else
		{
			handleBasicOperators(token, queue, stack);
		}

		if (stack.IsEmpty())
		{
			break;
		}
	}
}
