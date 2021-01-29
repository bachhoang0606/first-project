#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef struct _NODE
{
	char name[30];
	char phone[10];
	char mail[30];
	struct _NODE* left;
	struct _NODE* right;
}NODE;

NODE* root = NULL;

void FreeTree(NODE** r)
{
	if (*r != NULL)
	{
		NODE* left = (*r)->left;
		NODE* right = (*r)->right;
		free(*r);
		*r = NULL;
		FreeTree(&left);
		FreeTree(&right);
	}
}

int CountRight(NODE* node)
{
	if (node == NULL)
		return 0;
	else{
		if (node->right == NULL)
			return CountRight(node->left);
		else
			return 1 + CountRight(node->left) + CountRight(node->right);
	}
}

int CountLeaf(NODE* node)
{
	if (node == NULL)
		return 0;
	else{
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
		{
			return CountLeaf(node->left) + CountLeaf(node->right);
		}
	}	
}

int Height(NODE* node)
{
	if (node == NULL)
		return 0;
	else
	{
		int leftHeigth = Height(node->left);
		int rightHeight = Height(node->right);
		return 1 + (leftHeigth < rightHeight ? rightHeight : leftHeigth);
	}
}

int CountNode(NODE* node)
{
	if (node == NULL)
		return 0;
	else{
		return 1 + CountNode(node->left) + CountNode(node->right);
	}
}


NODE* CreateNode(char* a,char* b,char* c)
{
	NODE* node = (NODE*)calloc(1, sizeof(NODE));
	strcpy(node->name, a);
	strcpy(node->phone, b);
	strcpy(node->mail, c);
	node->left = NULL;
	node->right = NULL;
	return node;
}

void AddNode(NODE** r,NODE* newNode)
{
	if (*r == NULL)
		*r = newNode;
	else{
		if (strcmp(newNode->name, (*r)->name) < 0)
		{
			AddNode(&((*r)->left),newNode);
		}else{
			AddNode(&((*r)->right),newNode);
		}
	}
}

void Print1Tree(NODE* r)
{
	if (r != NULL)
	{
		Print1Tree(r->left);
		printf("%s;%s;%s\n", r->name, r->phone, r->mail);
		Print1Tree(r->right);
	}
}
void Print2Tree(NODE* r)
{
	if (r != NULL)
	{
		Print2Tree(r->left);
		Print2Tree(r->right);
		printf("%s;%s;%s\n", r->name, r->phone, r->mail);
	}
}
void Print3Tree(NODE* r)
{
	if (r != NULL)
	{
		printf("%s;%s;%s\n", r->name, r->phone, r->mail);
		Print3Tree(r->left);
		Print3Tree(r->right);
	}
}

NODE** SearchNODE(NODE** r,char *seach)
{
	if(*r == NULL) return NULL;
	else if(strcmp((*r)->word,seach) == 0) return r;
	else if(strcmp((*r)->word,seach) < 0) 
	{
		if((*r)->right == NULL)	return NULL;
		else return SearchNODE(&((*r)->right),seach);
	}
	else if(strcmp((*r)->word,seach) > 0) 
	{
		if((*r)->left == NULL) return NULL;
		else return SearchNODE(&((*r)->left),seach);
	}
}

NODE** Minright(NODE** tmp) 
{
	if((*tmp)->left == NULL)
	{
		return tmp;
	}else return Minright(&((*tmp)->left));
}

NODE** Maxleft(NODE** tmp) 
{
	if((*tmp)->right == NULL)
	{
		return tmp;
	}else return Maxleft(&((*tmp)->right));
}

void DeNODE(NODE** delete)
{
	if((*delete)->right == NULL && (*delete)->left == NULL) 
	{
		free(*delete);
		*delete = NULL;
	}else if((*delete)->right == NULL)
	{
		NODE** maxleft = Maxleft(&((*delete)->left));
		strcpy((*delete)->word,(*maxleft)->word);
		DeNODE(maxleft);
	}else
	{
		NODE** minright = Minright(&((*delete)->right));
		strcpy((*delete)->word,(*minright)->word);
		DeNODE(minright);
	}
}

void main(int argc,char** argv)
{
	if(argc<2)
	{
		printf("khong du tham so\n");
	}
	else
	{
		char* desfile=argv[1];
		FILE* f=fopen(desfile,"rt");
		if(f==NULL)
		{
			printf("khong mo duoc file\n");
		}
		else
		{

			char* sl = (char*)calloc(30,sizeof(char));
			char* a = (char*)calloc(30,sizeof(char));
			char* b = (char*)calloc(10,sizeof(char));
			char* c = (char*)calloc(30,sizeof(char));
			NODE* new = NULL;
			fgets(sl,30,f);
			printf("so nguoi trong danh ba : %s\n",sl);
			while(!feof(f))
			{
				memset(a,0,30);
				memset(b,0,10);
				memset(c,0,30);
                fgets(a,30,f);
                if(strlen(a) == 0)
				{
					break;
				}
                else{
					a[strlen(a)-1] = '\0';
				    printf("%s\n",a);
				    fgets(b,10,f);
					b[strlen(b) - 1] = '\0';
				    printf("%s\n",b);
					fgets(c,30,f);
					c[strlen(c) - 1] = '\0';
				    printf("%s\n",c);
				    new = CreateNode(a,b,c);
				    AddNode(&root,new);      
                }
			}
			free(a);
			free(b);
			free(c);
			Print1Tree(root);
			printf("\n\n");
			Print2Tree(root);
			printf("\n\n");
			Print3Tree(root);
			printf("\n\n");
		}
		fclose(f);
	}
}
