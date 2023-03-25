
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


List* createList(int info);
void AddToList(List**, int, int);
void deleteAtBeginning(List**);
void ViewList(List*, List*, int);
void MemoryCleaning(List*);
void RemoveNegativeElements(List**);



int main() 
{
	int choice, amountOfElements, element, addChoice, beginOrEndChoice;
	List* head = new List;
	head->prev = head->next = NULL;
	List* tail = head;
	int info;
	int isCreatingList = 0;


	while (1) {
		printf("\n 1 - Create  2 - Add element 3 - View list 4 - Remove negative elements 5 - Clear memory Else - Exit\n");
		scanf_s("%d", &choice);
		switch (choice) 
		{
		case 1: if (head->next != NULL) {					
					printf("Clear memory!");
					break;
				}
			  isCreatingList = 1;
			  printf("List was created!");
			  break;
		case 2:												
			if (isCreatingList == 0)
			{
				printf("List is not created");
				break;
			}
			printf("Enter amount of elements: ");			
			while (!(cin >> amountOfElements))
			{
				printf("---error---");
				return 0;

			}
			printf("How to complete the list: 1 - random, 2 - from the keyboard\n ");
			while (!(cin >> addChoice)) 
			{
				printf("---error---");
				return 0;
			}
			if (addChoice == 1) 
			{
				printf("Where to add elements: 1 - Beginning 2 - End\n");
				while (!(cin >> beginOrEndChoice)) 
				{
					printf("---error---");
					return 0;
				}
				for (int i = 1; i <= amountOfElements; i++)
				{
					info = rand() % 100 - 50;
					if (isCreatingList)
					{
						head = createList(info);
						isCreatingList = 0;
						continue;
					}
					if (beginOrEndChoice == 1) 
					{
						AddToList(&head, info, FROM_START);
					}
					else if (beginOrEndChoice == 2)
					{
						AddToList(&head, info, FROM_END);
					}
					else
						return 0;
				}
				printf("Elements were added!");
			}
			else if (addChoice == 2) 
			{
				printf("Where to add elements: 1 - Beginning 2 - End\n");
				while (!(cin >> beginOrEndChoice))
				{
					printf("---error---");
					return 0;
				}
				for (int i = 0; i < amountOfElements; i++) 
				{
					printf("Enter element %d: ", i + 1);
					while (!(cin >> info)) 
					{
						printf("---error---");
						return 0;
					}
					if (isCreatingList)
					{
						head = createList(info);
						isCreatingList = 0;
						continue;
					}
					if (beginOrEndChoice == 1)
					{
						AddToList(&head, info, FROM_START);
					}
					else if (beginOrEndChoice == 2)
					{
						AddToList(&head, info, FROM_END);
					}
					else
						return 0;
				}
			}
						break;
		case 3:
			printf("How to view the list: 1 - From beginning 2 - From end\n");
			while (!(cin >> beginOrEndChoice))
			{
				printf("---error---");
				return 0;
			}
			if (beginOrEndChoice == 1)
			{
				ViewList(head, tail, FROM_START);
			}
			else if (beginOrEndChoice == 2)
			{
				tail = head;                                                         
				while (tail->next != NULL)
					tail = tail->next;
				ViewList(head, tail, FROM_END);
			}
			else
				return 0;
			break;
		case 4:
			RemoveNegativeElements(&head);
			printf("Negative elements were deleted!");
			break;
		case 5:
			MemoryCleaning(head);			
			head = new List;
			head->prev = head->next = NULL;
			isCreatingList = 0;
			printf("Memory cleares successfully:)\n");
			break;
		default:                                              
			MemoryCleaning(head);
			printf("Program is over!");
			return 0;
		}
	}


}

List* createList(int info) 
{
	List* temp = new List;
	temp->info = info;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}


void AddToList(List** head, int info, int mode) 
{
	List* newList = createList(info);
	if (*head == NULL)
	{
		*head = newList;
	}
	else if (mode == FROM_START) 
	{
		newList->next = *head;
		(*head)->prev = newList;
		*head = newList;
	}
	else if (mode == FROM_END)
	{
		List* temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newList;
		newList->prev = temp;

	}
}


void deleteAtBeginning(List** head) 
{
	if (*head == NULL) 
	{
		printf("Steck is empty!\n");
		return;
	}
	List* temp = *head;
	*head = (*head)->next;
	if (*head != NULL) 
	{
		(*head)->prev = NULL;
	}
	delete temp;
}

void ViewList(List* head, List* tail, int mode) 
{
	//head = head->next;
	if (mode == FROM_START) 
	{
		while (head != NULL) 
		{
			printf("%d\n", head->info);
			head = head->next;
		}
	}
	else if (mode == FROM_END) 
	{
		while (tail != NULL)
		{
			printf("%d\n", tail->info);
			tail = tail->prev;
		}
	}
}


void MemoryCleaning(List* head)       
{
	List* temp = head;
	while (temp != NULL) 
	{
		List* next = temp->next;
		delete temp;
		temp = next;
	}
}

void RemoveNegativeElements(List** head)
{
	struct List* temp = *head;
	struct List* next;
	while (temp != NULL) 
	{
		next = temp->next;
		if (temp->info < 0) 
		{
			if (temp == *head) 
			{
				*head = temp->next;
			}
			if (temp->next != NULL) 
			{
				temp->next->prev = temp->prev;
			}
			if (temp->prev != NULL) 
			{
				temp->prev->next = temp->next;
			}
			delete temp;
		}
		temp = next;
	}

}
