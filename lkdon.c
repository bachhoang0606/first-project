#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

typedef struct _Stack
{
	char stackname[30];
	struct _Stack* next;
}Stack;

Stack* root = NULL;
Stack* cur = NULL;

void Sort()
{
	Stack* tmp = root;
	Stack* prev = NULL;
	while (tmp != NULL)
	{
		Stack* next = tmp->next;
		while (next != NULL)
		{
			if (strcmp(tmp->stackname, next->stackname) > 0)
			{
				if (root == tmp)
				{
					root = next;
				}
				tmp->next = next->next;
				next->next = tmp;
				if (prev != NULL)
				{
					prev->next = next;
				}
				tmp = next;
			}
			next = next->next;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void Free()
{
	if (root != NULL)
	{
		Stack* tmp = root;
		while (tmp != NULL)
		{
			root = tmp->next;
			free(tmp);
			tmp = root;
		}
	}
}
void Remove(char* name)
{
	if (root != NULL)
	{
		Stack* tmp = root;
		Stack* prev = NULL;
		while (tmp != NULL)
		{
			if (strcmp(tmp->stackname, name) == 0)
			{
				if (prev != NULL)
				{
					prev->next = tmp->next; 
				}else
				{
					root = tmp->next; 
				}
				free(tmp);
				break;
			}else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
}

void Travers()
{
	if (root != NULL)
	{
		Stack* tmp = root;
		while (tmp != NULL)
		{
			printf("%s\n", tmp->stackname);
			tmp = tmp->next;
		}
	}
}

void Insert(char* name)
{
	if (cur != NULL)
	{
		Stack* newItem = 
		(Stack*)calloc(1, sizeof(Stack));
		strcpy(newItem->stackname, name);
		newItem->next = NULL;
		cur->next = newItem;
		cur = newItem;
	}else{
		Stack* newItem = 
		(Stack*)calloc(1, sizeof(Stack));
		strcpy(newItem->stackname, name);
		newItem->next = NULL;
		root = newItem;
		cur = newItem;
	}
}


void Reverse() //dao nguoc
{
	Stack* tmp = root;
	Stack* next = tmp->next;
	while (next != NULL)
	{
		if (tmp == root)
		{
			tmp->next = NULL;
		}
		Stack* tmp1 = next->next;
		next->next = tmp;
		tmp = next;
		next = tmp1;
	}
	root = tmp;
}

void main()
{
	char name[30];
	
	while (0==0)
	{
		printf("Name: ");
		__fpurge(stdin);
		fgets(name,30,stdin);
		name[strlen(name) - 1] = '\0';
		if (strlen(name) > 0)
		{
			Insert(name);
		}else
			break;
	}	
	//Reverse();
	Travers(); 
	printf("\n\n\n");
	//printf("Name to remove: ");
	// __fpurge(stdin);
	// gets(name);
	// Remove(name);
	Sort(); 
	Travers(); 
	Free(); 
}
