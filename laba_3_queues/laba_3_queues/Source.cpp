#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>

#define _CRT_SECURE_NO_WARNINGS 
#define FROM_START 0
#define FROM_END 1
using namespace std;

struct List 
{
	int info;
	List *prev, *next;
};


List* AddToList(List*, List*, int, int);
void ViewList(List*, List*, int);
void DellElement(List*, List*);
void MemoryCleaning(List*, List*);
void RemoveNegativeElements(List*, List*);



int main() 
{
	int choice, amountOfElements, element;
	List* head = new List;
	head->prev = head->next = NULL;
	List* tail = head;


	while (1) {
		printf("\n 1 - Create  2 - Add to start 3 - Add to the end 4 - View from the beginning 5 - View from the end 6 - Remove negative elements 7 - Clear memory  0 - Exit DICK\n");
		scanf_s("%d", &choice);
		switch (choice) 
		{
		case 1: if (head->next != NULL) {
					printf("Clear memory!");
					break;
				}
			  printf("List was created!");
			  break;
		case 2: case 3: printf("Enter amount of elements: ");
						while (!(cin >> amountOfElements))
						{
							printf("---error---");
							return 0;

						}
						for (int i = 1; i <= amountOfElements; i++)
						{
							element = rand() % 100 - 50;
							if (choice == 2)
								head = AddToList(head, tail, element, FROM_START);
							else
								tail = AddToList(head, tail, element, FROM_END);

						}
						printf("Elements were added!");
						break;
		case 4:
			ViewList(head, tail, FROM_START);
			break;
		case 5:
			ViewList(head, tail, FROM_END);
			break;
		case 6:
			break;
		case 7:
			MemoryCleaning(head, tail);
			printf("Memory cleared!");
			break;

	
		}
	}


}

List* AddToList(List* head, List* tail, int info, int mode)
{
	List* temp = new List;
	temp->info = info;
	if (head->next == NULL)
	{
		temp->prev = head;
		temp->next = NULL;
		head->next = temp;
		tail = temp;
		if (mode == FROM_START)

		return tail;
	}	
	
	if (mode == FROM_START)
	{
		temp->prev = head;
		temp->next = head->next;
		head->next->prev = temp;
		head->next = temp;
		return head;
	}
	else
	{
		temp->next = NULL;
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
		return tail;
	}
}

void DellElement(List* head, List* tail) 
{
	List* temp = head->next;
	if (head->next == NULL) 
	{
		printf("Stack is empty\n");
		return;
	}
	else if (head->next->next == NULL)
		head->next = NULL;
	else
	{
		head->next = head->next->next;
		head->next->prev = head;
	}
	delete temp;
}

void ViewList(List* head, List* tail, int mode)
{
	List* temp;
	if (mode == FROM_START)
	{
		temp = head->next;
		while (temp != NULL)
		{
			printf("%d\n", temp->info);
			temp = temp->next;
		}
	}
	else
	{
		temp = tail;
		while (temp != head)
		{
			printf("%d\n", temp->info);
			temp = temp->prev;
		}
	}
}

void MemoryCleaning(List* head, List* tail)
{
	while (head->next != NULL)
		DellElement(head, tail);
}

void RemoveNegativeElements(List* head, List* tail) 
{

}
