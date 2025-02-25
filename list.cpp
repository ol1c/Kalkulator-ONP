#include <iostream>
#include "list.h"

using namespace std;

List::List()
{
	this->head = NULL;
	this->tail = NULL;
}

const bool List::IsEmpty()
{
	if (this->head == NULL && this->tail == NULL)
		return true;
	else
		return false;
}

void List::Pop()
{
	if (!IsEmpty())
	{
		token_t* element_to_pop = this->head;
		this->head = element_to_pop->next;
		if (this->head == NULL)
			this->tail = NULL;
		delete element_to_pop;
	}
}

token_t* List::GetItemPointer()
{
	return this->head;
}

void List::PushQueue(const enum ID& id, const int& value)
{
	token_t* element = new token_t;
	element->id = id;
	element->value = value;
	element->next = NULL;
	if (IsEmpty())
	{
		this->head = element;
		element->prev = NULL;
	}
	else
	{
		this->tail->next = element;
		element->prev = this->tail;
	}
	this->tail = element;
}

void List::PushQueue(const int& value_of_number)
{
	token_t* element = new token_t;
	element->id = NUMBER;
	element->value = value_of_number;
	element->next = NULL;
	if (IsEmpty())
	{
		this->head = element;
		element->prev = NULL;
	}
	else
	{
		this->tail->next = element;
		element->prev = this->tail;
	}
	this->tail = element;
}

void List::PushStack(const enum ID& id, const int& value)
{
	token_t* element = new token_t;
	element->id = id;
	element->value = value;
	element->prev = NULL;
	if (IsEmpty())
	{
		this->tail = element;
		element->next = NULL;
	}
	else
	{
		element->next = this->head;
	}
	this->head = element;
}

void List::PushStack(const int& value_of_number)
{
	token_t* element = new token_t;
	element->id = NUMBER;
	element->value = value_of_number;
	element->prev = NULL;
	if (IsEmpty())
	{
		this->tail = element;
		element->next = NULL;
	}
	else
	{
		element->next = this->head;
	}
	this->head = element;
}

void List::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

void List::PrintItem(const token_t& item)
{
	switch (item.id)
	{
	case NUMBER:
	{
		printf("%d  ", item.value);
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
		printf("MAX%d  ", item.value);
		break;
	}
	case MIN:
	{
		printf("MIN%d  ", item.value);
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

void List::Print()
{
	if (!IsEmpty())
	{
		printf("\n");
		token_t* item = GetItemPointer();
		PrintItem(*item);
		while (item->next != NULL)
		{
			item = item->next;
			PrintItem(*item);
		}
	}
}

List::~List()
{
	Clear();
}
