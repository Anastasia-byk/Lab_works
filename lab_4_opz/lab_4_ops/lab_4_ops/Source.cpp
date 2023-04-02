#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<iomanip>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

struct Stack 
{
	char info;
	Stack* next;
};

void Push(Stack*, char);
char Pop(Stack*);
int my_strlen(char*);
int precedence(char);
int isSign(char);
int isParenthesis(char);
char top(Stack*);
int evaluateToPostfix(Stack*, char*);
void infixToPostfix(Stack*, char*, char*);
void MemoryCleaning(Stack*);



int main()
{
	Stack* head = new Stack;
	head->next = NULL;
	char infix[30];
	char postfix[30];
	Stack* signStack = new Stack;
	int choice, len, postf_len = 0;
	int result;
	int isDigit;
	

	while (true) 
	{
		printf_s("\n 1 - Enter an expression (alphabetic or integer)  2 - Convert to reverse polish notation  3 - Examination  else - Exit\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			postf_len = 0;
			//MemoryCleaning(signStack);
			memset(postfix, '\0', 30);
			printf_s("Enter an expression: ");
			//gets_s(infix);
			//getchar();
			scanf("%s", infix);
			isDigit = 1;
			len = my_strlen(infix);
			break;

		case 2:
			signStack->next = NULL;
			int i, j;
			for (i = 0, j = 0; infix[i] != '\0'; i++)
			{
				if (isdigit(infix[i])) 
				{
					postfix[j] = infix[i];
					postf_len++;
					j++;
				}
				else if (isSign(infix[i])) 
				{
					while ((precedence(infix[i])) <= precedence(top(signStack)) && top(signStack) != ')') 
					{
						postfix[j] = Pop(signStack);
						postf_len++;
						j++;
					}
					Push(signStack, infix[i]);
				}
				else if (isParenthesis(infix[i])) 
				{
					if (infix[i] == '(') 
					{
						Push(signStack, infix[i]);
					}
					else
					{
						while (top(signStack) != '(')
						{
							postfix[postf_len] = Pop(signStack);
							postf_len++;
							j++;
						}
						//postfix[j] = '\0';
						Pop(signStack);

					}
				}
				else 
				{
					postfix[postf_len] = infix[i];
					isDigit = 0;
					postf_len++;
				}
			}
			while (signStack->next != NULL)
			{
				postfix[postf_len] = Pop(signStack);
				postf_len++;
			}
			postfix[postf_len] = '\0';
			printf_s("%s\n", postfix);
			break;

		case 3:
			if (isDigit) 
			{
				result = evaluateToPostfix(head, postfix);
				printf_s("Result is: %d\n", result);
				break;

			}
			for (i = 0; postfix[i] != '\0'; i++) 
			{
				if (isSign(postfix[i]) || isdigit(postfix[i]))
					continue;
				printf_s("Enter value (%c): ", postfix[i]);
				getchar();
				scanf("%c", &postfix[i]);

			}
			result = evaluateToPostfix(head, postfix);
			printf_s("Result is: %d\n", result);
			break;

		default:
			printf_s("Error: incorrect input!!!");
			return 0;
		}
	}
	delete head;
	return 0;
}

void Push(Stack* head, char info) 
{
	Stack* newElement = new Stack;
	newElement->info = info;
	if (head->next == NULL)
		newElement->next = NULL;
	else
		newElement->next = head->next;
	head->next = newElement;
}

char Pop(Stack* head)
{
	Stack* tempNode;
	char info;
	if (head->next == NULL)
	{
		printf_s("Stack is empty");
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

int my_strlen(char* infix) 
{
	int i;
	for (i = 0; infix[i] != '\0'; i++);
	return i;
}

int precedence(char sign) 
{
	switch (sign) 
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case'^':
			return 3;
		default:
			return 0;

	}
}

int isSign(char sign) 
{
	return sign == '+' || sign == '-' || sign == '*' || sign == '^';
}

int isParenthesis(char sign) 
{
	return sign == '(' || sign == ')';
}

char top(Stack* head) 
{
	if (head->next == NULL) 
	{
		return '\0';
	}
	else 
	{
		Stack* tempNode = head->next;
		return tempNode->info;
	}

}

int evaluateToPostfix(Stack* head, char postfix[]) {
	Stack* signStack = new Stack;
	int i;
	for (i = 0; postfix[i] != '\0'; i++) 
	{
		if (isdigit(postfix[i])) 
		{
			Push(signStack, postfix[i] - '0');
		}
		else if (isSign(postfix[i])) 
		{
			int sign1 = Pop(signStack);
			int sign2 = Pop(signStack);
			switch (postfix[i]) 
			{
				case'+': 
					Push(signStack, sign2 + sign1);
					break;
				case'-':
					Push(signStack, sign2 - sign2);
					break;
				case'*':
					Push(signStack, sign2 * sign1);
					break;
				case'/':
					Push(signStack, sign2 / sign1);
					break;
				case'^':
					Push(signStack, pow(sign2, sign1));
					break;
			}

		}

	}
	return Pop(signStack);
}

void MemoryCleaning(Stack* head)
{
	while (head->next != NULL)
		Pop(head);

}




