#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define STACK_SORTING 0
#define STACK_SORTED 1


struct Stack {
	int info;
	Stack* next;
};
using namespace std;
void Push(Stack*, int);
int Pop(Stack*);
void View(Stack*);
void MemoryCleaning(Stack*); 
void DeleteNegativeElements(Stack*);
void SortingInfoExchange(Stack*);

int main()
{
	Stack* head = new Stack;
	head->next = NULL;
	int choice, amountOfElements, element;
	int i;
	while (true)
	{
		printf("\n 1 - Create  2 - Add  3 - View  4 - Remove negative elements 5 - Clear memory 6 - Sorting info exchange  else - Exit\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1: case 2:
			if (choice == 1 && head->next != NULL)
			{
				printf("Please, clear your dirty ass\n");
				break;
			}
			printf("Enter amount of elements: ");
			while (!(cin >> amountOfElements))
			{
				printf("---error---");
				return 0;

			}
			//scanf_s("%d", &amountOfElements);
			for (i = 1; i <= amountOfElements; i++)
			{
				element = rand() % 100 - 50;
				Push(head, element);
			}
			if (choice == 1)
			{
				printf("Elements were created: %d", amountOfElements);
			}
			else printf("Elements were added: %d", amountOfElements);
			break;
		case 3:
			if (!head)
			{
				printf("Stack is empty!");
				break;
			}
			printf("-------------------------------------------- Stack --------------------------------------------\n");
			View(head);
			break;
		case 4:
			DeleteNegativeElements(head);
			printf("Negative numbers was deleted!");
			break;
		case 5:
			if (head != NULL)
				MemoryCleaning(head);
				printf("Memory cleared!");
			break;
		case 6:
			SortingInfoExchange(head);
			printf("Elements were sorted!");
			break;

		default: 
			printf("Error: incorrect input!!!");
			return 0;

		}
	}
	delete head;

	return 0;
}

void Push(Stack* head, int info)
{
	Stack* newElement = new Stack;
	newElement->info = info;
	if (head->next == NULL)
		newElement->next = NULL;
		
	else
		newElement->next = head->next;
	head->next = newElement;
}

int Pop(Stack* head)
{
	Stack* tempNode;
	int info;
	if (head->next == NULL)
	{
		printf("Stack is empty");
		return 0;
	}
	else
	{
		tempNode = head->next;
		info = tempNode->info;
		head->next = tempNode->next;
		delete tempNode;
		return info;
	}
}

void View(Stack* head)
{
	Stack* tempNode = head->next;
	while (tempNode != NULL)
	{
		printf("%d\n", tempNode->info);
		tempNode = tempNode->next;
	}
}

void MemoryCleaning(Stack* head) 
{
	while (head->next != NULL) 
		Pop(head);

}


void DeleteNegativeElements(Stack* head) 
{
	Stack* secondHead = new Stack;
	int num;
	secondHead->next = NULL;
	while (head->next != NULL)
	{
		num = Pop(head);
		if (num >= 0)
			Push(secondHead, num);
	}
	while (secondHead->next != NULL)
	{
		num = Pop(secondHead);
		Push(head, num);
	}
	delete secondHead;
}


void SortingInfoExchange(Stack* head)
{
	Stack* tempNode;
	int temp;
	int flag = STACK_SORTING;
	while (flag == STACK_SORTING)
	{
		flag = STACK_SORTED;
		tempNode = head->next;
		while (tempNode->next != NULL)
		{
			if (tempNode->info > tempNode->next->info)
			{
				temp = tempNode->info;
				tempNode->info = tempNode->next->info;
				tempNode->next->info = temp;
				flag = STACK_SORTING;
			}
			tempNode = tempNode->next;
		}
	}
}
