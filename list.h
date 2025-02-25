#pragma once
#include <iostream>


//token id 
enum ID {
	COMMA,
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	PARENTHESES_START,
	PARENTHESES_END,
	MAX,
	MIN,
	IF,
	N
};

//basic token struct
struct token_t{
	int value;
	enum ID id;
	token_t* prev;
	token_t* next;
};

//class for stacks and queues
class List {
	token_t* head;
	token_t* tail;

public:
	List();

	//checks if object is empty
	const bool IsEmpty();

	//delete first item from object
	void Pop();
	//clears whole object
	void Clear();
	//prints whole object
	void Print();
	//returns pionter to the first item
	token_t* GetItemPointer();
	void PushStack(const int& value_of_number);
	void PushStack(const enum ID& id, const int& value);
	void PushQueue(const int& value_of_number);
	void PushQueue(const enum ID& id, const int& value);
	~List();
protected:
	void PrintItem(const token_t& item);
};