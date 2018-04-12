/*
 *Single LinkedList Without head node Dmo
 *
 */

# include<stdio.h>
# include<stdlib.h>

typedef struct LINKEDLISTNODE
{
	int value;
	struct LINKEDLISTNODE *next;
} Node;

int InsertLinkedList(Node **plink, int newValue);  /*有序链表插入节点*/
int DeleteLinkedList(Node **plink, int newValue);  /*删除指定值的节点*/
void FreeLinkedList(Node **plink);                 /*删除所有节点释放内存*/
void ReverseLinkedList(Node **plink);              /*反转链表*/
void printLinkedList(Node **plink);                /*打印链表*/
 

/*新建一个空节点*/
Node *CreateNewNode(void)
{
	Node *pNode = NULL;
	
	pNode = (Node*)malloc(sizeof(Node));
	if(pNode == NULL)
	{
		printf("Malloc error\n");
		return NULL;
	}
	
	return pNode;
}

/*有序链表插入新节点 假设节点值从小到大排序*/
int InsertLinkedList(Node **plink, int newValue)
{
	Node *pCurrent = NULL;
	Node *pNewNode = NULL;
	
	if(plink == NULL)
	{
		printf("Failed to insert new Node! plink cannot be NULL\n");
		return -1;
	}
		
	/*search the linked list*/
	pCurrent = *plink;
	while(pCurrent != NULL && (pCurrent->value) < newValue)
	{
		plink = &(pCurrent->next);
		pCurrent = *plink;
	}
	
	/*create a new node*/
	pNewNode = CreateNewNode();
	if(pNewNode == NULL)
	{
		printf("Failed to malloc memory.\n");
		return -1;
	}
	
	/*insert the new node*/
	pNewNode->value = newValue;
	pNewNode->next = pCurrent;
	*plink = pNewNode;
	
	return 0;
	
}

/*删除指定值的节点*/
int DeleteLinkedList(Node **plink, int delValue)
{
	Node *pCurrent = NULL;
	Node *pPrevious = NULL;
	
	if(plink == NULL)
	{
		printf("Error! plink cannot be NULL\n");
		return -1;
	}
	
	/*search the linked list*/
	pCurrent = *plink;
	while(pCurrent != NULL && (pCurrent->value) != delValue)
	{
		pPrevious = pCurrent;
		pCurrent = pCurrent->next;
	}
	
	if(*plink == NULL)
	{
		/*empty linked list*/
		return -1;
	}
	if(*plink != NULL && pCurrent == NULL)
	{
		/*delValue not found*/
		return -1;
	}
	
	
	/*delValue found. delete it and free the memory*/
	if(pPrevious== NULL) /*DEL FIRST NODE*/
		*plink = pCurrent -> next;
    else
		pPrevious->next = pCurrent -> next;
	free(pCurrent);
	
	return 0;
}

/*删除所有节点释放内存*/
void FreeLinkedList(Node **plink)
{
	
	Node *pCurrent = NULL;
	Node *pTemp = NULL;
	
	if(plink == NULL)
		return;
	
	pCurrent = *plink;
	while(pCurrent != NULL)
	{
		pTemp = pCurrent;
		pCurrent = pCurrent->next;
		free(pTemp);
	}
	
	return;
}         

    
/*反转链表*/ 
void ReverseLinkedList(Node **plink)
{
	Node *pCurrent = NULL;
	Node *pPrevious = NULL;
	Node *pTemp = NULL;
	
	if(plink == NULL)
		return;
	
	pCurrent = *plink;
	while(pCurrent != NULL)
	{
		pTemp = pCurrent->next;
		pCurrent->next = pPrevious;
		
		pPrevious = pCurrent;
		pCurrent = pTemp;
	}
	
	*plink = pPrevious;
     return;
}                

/*打印链表*/
void printLinkedList(Node **plink)
{
	Node *pCurrent = NULL;
	
	if(plink == NULL)
		return;
	
	pCurrent = *plink;
	while(pCurrent != NULL)
	{
		printf("%d " ,pCurrent->value);
		pCurrent = pCurrent->next;
	}
	printf("\n");
	
	return;
}


int main(void)
{
	int N;
	int Arr[100];
	int i;
	int ret;
	Node *root = NULL;
	Node *temp = NULL;
	
	/*input*/
	printf("Please input an positive integer N which is between 1 and 100.\n");
	scanf("%d", &N);
	if(N <= 0 || N >100)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d integer numbers orderder by its value asc.\n", N);
	/*Init linked list with Arr*/
	for(i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
		ret = InsertLinkedList((Node**)&root,Arr[i]);
		if(ret == -1)
		{
			printf("InsertLinkedList() error\n");
			FreeLinkedList(&root);
			return -1;
		}
	}

	printf("Init linkedList:\n");
    printLinkedList(&root);
	
	printf("Reverse linkedList:\n");
	ReverseLinkedList(&root);
	printLinkedList(&root);
	
	printf("DeleteLinkedList Node:\n");
	if(DeleteLinkedList(&root, 3) == -1)
	{
		printf("DeleteLinkedList error:\n");
	}
	printLinkedList(&root);
	
	printf("Destroy LinkedList:\n");
	FreeLinkedList(&root);

	return 0;
}