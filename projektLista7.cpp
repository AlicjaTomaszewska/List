#include <iostream>
#define MAX_STRING_SIZE 20
#define HOW_MANY_ITERATORS 10

using namespace std;

const char I[] = { "I" };
const char addAfter[] = { "A." };
const char addBefore[] = { ".A" };
const char addIterator[] = { "i" };
const char Remove[] = { "R" };
const char show[] = { "P" };
const char all[] = { "ALL" };
const char End[] = { "END" };
const char Beg[] = { "BEG" };
const char Plus[] = { "+" };
const char Minus[] = { "-" };

typedef struct DoublyLinkedList {
	long long int key;
	struct DoublyLinkedList* next = nullptr;
	struct DoublyLinkedList* prev = nullptr;
} DoublyLinkedList_type;

bool comparison(const char A[], const char B[])
{
	int sizeA = 0;
	int sizeB = 0;
	while (A[sizeA] != '\0')
	{
		sizeA++;
	}
	while (A[sizeB] != '\0')
	{
		sizeB++;
	}
	if (sizeA != sizeB)
	{
		return false;
	}
	for (int i = 0; i < sizeA; i++)
	{
		if (A[i] != B[i])
		{
			return false;
		}
	}
	return true;
}

void add_front(DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* element, long long int number, bool init)
{
	DoublyLinkedList_type* newElement = new DoublyLinkedList_type;
	newElement->key = number;
	if (element != nullptr)
		newElement->prev = element->prev;
	else
		newElement->prev = nullptr;
	newElement->next = element;

	if (element == nullptr)
	{
		if (init)
		{
			head = newElement;
			tail = newElement;
		}
		return;
	}
	if (element->prev != nullptr)
	{
		element->prev->next = newElement;
	}
	else
	{
		head = newElement;
	}
	element->prev = newElement;
}

void add_back(DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* element, long long int number, bool init)
{
	DoublyLinkedList_type* newElement = new DoublyLinkedList_type;
	newElement->key = number;
	newElement->prev = element;
	if (element != nullptr)
		newElement->next = element->next;
	else
		newElement->next = nullptr;

	if (element == nullptr)
	{
		if (init)
		{
			head = newElement;
			tail = newElement;
		}
		return;
	}
	if (element->next != nullptr)
	{
		element->next->prev = newElement;
	}
	else
	{
		tail = newElement;
	}
	element->next = newElement;
}

void pop(DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* elementToRemove, DoublyLinkedList_type* iter[])
{
	int counter = 0;
	DoublyLinkedList_type* prevElement = elementToRemove->prev;
	DoublyLinkedList_type* nextElement = elementToRemove->next;

	if (prevElement != nullptr)
	{
		prevElement->next = elementToRemove->next;
	}
	else
	{
		head = head->next;
	}
	if (nextElement != nullptr)
	{
		nextElement->prev = elementToRemove->prev;
	}
	else
	{
		tail = tail->prev;
	}
	while (counter < HOW_MANY_ITERATORS)
	{
		if (elementToRemove == iter[counter])
		{
			if (iter[counter] == nullptr)
			{
				counter++;
				continue;
			}
			if (iter[counter]->next != nullptr)
			{
				if (iter[counter]->prev != nullptr)
					iter[counter]->prev->next = iter[counter]->next;
				iter[counter]->next->prev = iter[counter]->prev;
				iter[counter] = iter[counter]->next;

			}
			else
			{
				if (iter[counter]->prev != nullptr)
					iter[counter]->prev->next = nullptr;
				iter[counter] = iter[counter]->prev;
			}
		}
		counter++;
	}
	delete elementToRemove;
}

void print(DoublyLinkedList_type* head)
{
	if (head != nullptr)
	{
		DoublyLinkedList_type* current = head;
		while (current != nullptr)
		{
			cout << current->key << " ";
			current = current->next;
		}
		cout << endl;
	}
}

void printIterator(DoublyLinkedList_type* iter[], int iterator)
{
	if (iter[iterator] != nullptr)
	{
		cout << iter[iterator]->key << endl;
	}
	else
	{
		cout << endl;
	}
}

void moveIteratorForward(DoublyLinkedList_type* iter[], int iterator)
{
	if (iter[iterator] == nullptr)
	{
		return;
	}
	else if (iter[iterator]->next != nullptr)
	{
		iter[iterator] = iter[iterator]->next;
	}
}

void moveIteratoBackward(DoublyLinkedList_type* iter[], int iterator)
{
	if (iter[iterator] == nullptr)
	{
		return;
	}
	else if (iter[iterator]->prev != nullptr)
	{
		iter[iterator] = iter[iterator]->prev;
	}
}

void freeList(DoublyLinkedList*& head, DoublyLinkedList*& tail, DoublyLinkedList* iter[])
{
	while (head != nullptr)
	{
		pop(head, tail, head, iter);
	}
}

void addBeforeFunction(char advancedOption[], long long int &number, int& index, DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* iter[])
{
	cin >> advancedOption;
	cin >> number;
	if (comparison(advancedOption, Beg))
	{
		add_front(head, tail, head, number, true);
	}
	else if (comparison(advancedOption, End))
	{
		add_front(head, tail, tail, number, true);
	}
	else
	{
		index = int(*advancedOption) - 48;
		add_front(head, tail, iter[index], number, false);
	}
}

void addAfterFunction(char advancedOption[], long long int& number, int& index, DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* iter[])
{
	cin >> advancedOption;
	cin >> number;
	if (comparison(advancedOption, End))
	{
		add_back(head, tail, tail, number, true);
	}
	else if (comparison(advancedOption, Beg))
	{
		add_back(head, tail, head, number, true);
	}
	else
	{
		index = int(*advancedOption) - 48;
		add_back(head, tail, iter[index], number, false);
	}
}

void addIteratorFunction(char advancedOption[], int& index, int& iterator, DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* iter[])
{
	cin >> iterator >> advancedOption;
	if (comparison(advancedOption, Beg)) {
		iter[iterator] = head;
	}
	else if (comparison(advancedOption, End)) {
		iter[iterator] = tail;
	}
	else
	{
		index = int(*advancedOption) - 48;
		iter[iterator] = iter[index];
	}
}

void removeFunction(char advancedOption[], int& iterator, DoublyLinkedList_type*& head, DoublyLinkedList_type*& tail, DoublyLinkedList_type* iter[])
{
	cin >> advancedOption;
	if (comparison(advancedOption, Beg))
	{
		pop(head, tail, head, iter);
	}
	else if (comparison(advancedOption, End))
	{
		pop(head, tail, tail, iter);
	}
	else
	{
		iterator = int(*advancedOption) - 48;
		pop(head, tail, iter[iterator], iter);
	}
}

void showFunction(char advancedOption[], int& iterator, DoublyLinkedList_type*& head, DoublyLinkedList_type* iter[])
{
	cin >> advancedOption;
	if (comparison(advancedOption, all))
	{
		print(head);
	}
	else
	{
		iterator = int(*advancedOption) - 48;
		printIterator(iter, iterator);
	}
}

int main()
{
	char option[MAX_STRING_SIZE];
	char advancedOption[MAX_STRING_SIZE];
	int index = -1;
	int iterator = -1;
	long long int number = -1;
	DoublyLinkedList_type* head = nullptr;
	DoublyLinkedList_type* tail = nullptr;
	DoublyLinkedList_type* iter[HOW_MANY_ITERATORS];

	while (cin >> option)
	{
		if (comparison(option, I))
		{
			cin >> number;
		}
		else if (comparison(option, addBefore))
		{
			addBeforeFunction(advancedOption, number, index, head, tail, iter);
		}
		else if (comparison(option, addAfter))
		{
			addAfterFunction(advancedOption, number, index, head, tail, iter);
		}
		else if (comparison(option, addIterator))
		{
			addIteratorFunction(advancedOption, index, iterator, head, tail, iter);
		}
		else if (comparison(option, Remove))
		{
			removeFunction(advancedOption, iterator, head, tail, iter);
		}
		else if (comparison(option, show))
		{
			showFunction(advancedOption, iterator, head, iter);
		}
		else if (comparison(option, Plus))
		{
			cin >> iterator;
			moveIteratorForward(iter, iterator);
		}
		else if (comparison(option, Minus))
		{
			cin >> iterator;
			moveIteratoBackward(iter, iterator);
		}
	}
	freeList(head, tail, iter);
	return 0;
}
