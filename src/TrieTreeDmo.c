/*
 * Trie tree algorithm dmo
 */
 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

#define MAXSTRLEN 1024

typedef struct TRIETREENODE
{
	int cnt;                       /*统计各个单词出现的次数 初始化为0*/
	struct TRIETREENODE *next[26]; /*假设单词只有字母*/
}TrieTreeNode;

TrieTreeNode *createTrieTreeNode();                        /*新建并初始化一个节点*/
int InsertTrieTreeNode(TrieTreeNode *ptrRoot, char *str);  /*插入一个单词*/
int DeleteTrieTreeNode(TrieTreeNode *ptrRoot, char *str);  /*删除一个单词*/
int SearchTrieTree(TrieTreeNode *ptrRoot, char *str);      /*搜索Trie树*/
void TraverseTrieTree(TrieTreeNode *ptrRoot);              /*遍历Trie树*/
void DestroyTrieTree(TrieTreeNode *ptrRoot);               /*销毁Trie树*/

/*新建并初始化一个节点*/
TrieTreeNode *createTrieTreeNode()
{
	TrieTreeNode *treeNode = NULL;

	/*申请内存*/
    treeNode = (TrieTreeNode*)malloc(sizeof(TrieTreeNode));
	if(treeNode == NULL)
	{
		printf("Error! malloc error.\n");
		return NULL;
	}
	
	/*初始化*/
	memset(treeNode->next, 0x00, sizeof(treeNode->next));
	treeNode->cnt = 0;

	return treeNode;
}

/*插入一个单词*/
int InsertTrieTreeNode(TrieTreeNode *ptrRoot, char *str)
{
	int i, index;
	TrieTreeNode *tempNode = ptrRoot;
	
	if(ptrRoot==NULL || str == NULL || str[0]=='\0') /*Trie树带有一头结点*/
		return 0;
	
	for(i=0;i<strlen(str) ;i++)
	{
		if(str[i]<'a' && str[i]>'z')  /*只能含有a-z之间的字母*/
		{
			printf("Invalid lettre[%c]\n", str[i]);
			return -1;
		}

		index = str[i]-'a';
        if(tempNode->next[index] != NULL)
		{
			tempNode  = tempNode->next[index];
			continue;
		}

        tempNode->next[index] = createTrieTreeNode();
        if(tempNode->next[index] == NULL)
	    {
	    	printf("createTrieTreeNode error.\n");
	    	return -1;
	    }
        tempNode  = tempNode->next[index];		
	}
	
	tempNode->cnt = tempNode->cnt + 1;
	return 0;
	
}


/*
 * 搜索Trie树
 * exist return count of target
 * not exist return 0
 */
int SearchTrieTree(TrieTreeNode *ptrRoot, char *str)
{
	 int i, index; 
	 TrieTreeNode *tempNode = ptrRoot;
	 
	 if(ptrRoot==NULL || str == NULL) 
		return 0;
	
	for(i=0;i<strlen(str) ;i++)
	{
		index = str[i]-'a';
        if(tempNode->next[index] == NULL)
		{
			return 0;
		}
		tempNode  = tempNode->next[index];
	}
	
	return tempNode->cnt;
}  

/*
 * not exist return 0
 * exist return (node->cnt - 1)
 */
int DeleteTrieTreeNode(TrieTreeNode *ptrRoot, char *str)
{
	int i, index; 
	TrieTreeNode *tempNode = ptrRoot;
	 
	if(ptrRoot==NULL || str == NULL) 
		return 0;
	
	for(i=0;i<strlen(str) ;i++)
	{
		index = str[i]-'a';
        if(tempNode->next[index] == NULL)
		{
			return 0;
		}
		tempNode  = tempNode->next[index];
	}
	tempNode->cnt = tempNode->cnt-1;
	return tempNode->cnt;
}

/*遍历Trie树,使用静态变量，递归时可以记录之前一层上的字符*/
void TraverseTrieTree(TrieTreeNode *ptrRoot)
{
	int i;
	static char word[MAXSTRLEN + 1] ={0};
	static int j=0;
	
	if(ptrRoot==NULL) 
		return;

	for(i=0; i<26; i++)
	{
		if(ptrRoot->next[i] == NULL)
		{
			continue;
		}

		word[j++] = i + 'a';
		if(ptrRoot->next[i]->cnt > 0)
		{
			word[j+1] = '\0';
			printf("%-20s %-8d\n",word, ptrRoot->next[i]->cnt);
		}
		TraverseTrieTree(ptrRoot->next[i]);
	    j--;
			
	}
	
	return;
}

/*销毁Trie树*/
void DestroyTrieTree(TrieTreeNode *ptrRoot)
{
	int i;
	
	if(ptrRoot==NULL) 
		return;
	
	for(i=0; i<26; i++)
	{
		if(ptrRoot->next[i] != NULL)
		{
			DestroyTrieTree(ptrRoot->next[i]);
		}
	}
	
	free(ptrRoot); /*子节点全部删除后就才可以释放根节点*/
	ptrRoot = NULL;
	
	return ;
}            

int main()
{
	int N;
	int i;
	int ret;
	char str[100][1024+1] = {0};
	char word[1024+1] = {0};
	TrieTreeNode *ptrRoot = NULL;
	
	/*input*/
	printf("Please input an positive integer N which is between 1 and 100.\n");
	scanf("%d", &N);
	if(N <= 0 || N >100)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d words whic contain only letters.\n", N);
	for(i=0; i<N; i++)
	{
		scanf("%s", *(str+i));
	}
	
	/*create  head code*/
	ptrRoot =  createTrieTreeNode();
	if(ptrRoot == NULL)
	{
		printf("createTrieTreeNode error.\n");
		return -1;
	}
	
	/*build tree */
	for(i=0; i<N; i++)
	{
		printf("%s ", *(str+i));
		ret = InsertTrieTreeNode(ptrRoot,*(str+i));
		if(ret != 0)
		{
			printf("InsertTrieTreeNode error.\n");
		    return -1;
		}
	}
	printf("\n");
	
	printf("TraverseTrieTree:\n");
	TraverseTrieTree(ptrRoot);
	
	printf("Please input an word.\n", word);
	scanf("%s", word);
	
	printf("Search %s in the tree. cnt=[%d]\n", word,SearchTrieTree(ptrRoot,word));
	
	printf("Delete %s in the tree. cnt=[%d]\n", word,DeleteTrieTreeNode(ptrRoot,word));
	
	printf("TraverseTrieTree:\n");
	TraverseTrieTree(ptrRoot);
	
	printf("DestroyTrieTree\n");
	DestroyTrieTree(ptrRoot);
	ptrRoot = NULL;
	
	printf("TraverseTrieTree:\n");
	TraverseTrieTree(ptrRoot); 
	
	return 0;
}  