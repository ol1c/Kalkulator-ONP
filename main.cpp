#include <iostream>
#include "list.h"
#include "read.h"
#include "calc.h"

using namespace std;


int main()
{
	const int MAX_SIZE = 11; //max int as a string 
	int n; //number of calacutions 
	cin >> n;

	List stack; //stack
	List queue, onp; //queues
	token_t buff_token;
	token_t* token_pointer;
	bool err_flag; //error flags (true if ther is a error)
	char buff[MAX_SIZE]; //string buffor


	for (int i = 0; i < n; i++)
	{
		//reading
		while (true)
		{
			cin >> buff;
			if (buff[0] == '.')
			{
				handleDot(queue, stack);
				break;
			}
			handleToken(buff_token, buff);

			if (buff_token.id == NUMBER)
			{
				queue.PushQueue(buff_token.id, buff_token.value);
			}
			else if (getPriority(buff_token) == OPERATOR_PARENTHESES)
			{
				
				handleParentheses(buff_token, queue, stack);
			}
			else if (buff_token.id == MAX || buff_token.id == MIN)
			{
				buff_token.value = handleMinMax(queue);

				queue.PushQueue(buff_token.id, buff_token.value);
			}
			else if (buff_token.id == N)
			{
				handleN(buff_token, queue, stack);
			}
			else if (buff_token.id == IF)
			{
				handleIf(queue);
				queue.PushQueue(buff_token.id, buff_token.value);
			}
			else if (buff_token.id == COMMA);
			else
			{
				handleBasicOperators(buff_token, queue, stack);
			}
		}

		//printing and calculating
		while (!queue.IsEmpty())
		{
			token_pointer = queue.GetItemPointer();
			
			printToken(*token_pointer);

			onp.PushQueue(token_pointer->id, token_pointer->value);
			queue.Pop();
		}

		err_flag = false; //error, if everything works it will change the flag
		while (!onp.IsEmpty())
		{
			token_pointer = onp.GetItemPointer();
			stack.PushStack(token_pointer->id, token_pointer->value);
			if (token_pointer->id != NUMBER)
			{
				stack.Print();
				err_flag = calc(stack);
				if (err_flag)
					break;
			}
			onp.Pop();
		}

		if (err_flag)
			printf("\nERROR");
		else
			stack.Print();

		printf("\n\n");

		stack.Clear();
		onp.Clear();
		queue.Clear();
	}
}