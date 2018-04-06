# include <stdio.h>

# define MAXLEN 100

void HeapFixUp(int Arr[], int i);
int InsertHeap(int Arr[], int n, int new); /*插入一个数，返回插入后的节点数n+1*/

void HeapFixDown(int Arr[], int n, int i);
int DeleteHeapRoot(int Arr[], int n);  /*并不是真的删除 将其放在与最后一个节点交换，返回删除后的大小n-1即可*/

void BuildHeap(int Arr[], int n);   /*给定一个数组 建一个有序的最小二叉堆*/

int FindKmaxValue(int Arr[], int N, int K);

/*
最小堆以数组的形式实现  
下标从0开始  节点i的左儿子 2i+1 右儿子2i+2; i节点的父节点是(i-1)/2 不是i/2-1
*/

/*上浮调整，可用于插入数据时调整堆序性*/
void HeapFixUp(int Arr[], int i)
{
	int temp,j;
	
	if(i == 0)
	{
		/*插入的是根节点，无需调整 !!!!*/
		return;
	}
	
	/*寻找正确的位置，插入数据，上浮过程中无需跟同级节点比较，因为其已经小于父节点*/
	j = (i-1)/2; /*父节点*/
	while(j >=0  && Arr[j]>Arr[i])
	{
		/*交换当前节点与父节点的值，这样只是好理解。实际上也可以用temp备份插入的值，每次与temp比较，无需交换，
		只要更新Arr[j]的值即可，最终的i是插入位置*/
		temp = Arr[i];
		Arr[i] = Arr[j];
		Arr[j] = temp;
		
		i = j;
		j = (i-1)/2;
	}
}

/*在满足堆序性的最小堆中插入一个节点，在位置n处插入,n是当前实际长度*/
int InsertHeap(int Arr[], int n, int new)
{
	if(n >= MAXLEN)
	{
		printf("Error! Heap is full.\n");
		return -1;
	}
	
	Arr[n] = new;  /*插入到数组尾部 也就是在堆的最后增加一个叶节点*/
	HeapFixUp(Arr, n);  /*上移调整，使其满足堆序*/
	
	return n+1;
}

/*下沉调整堆序，可用于删除元素和建堆*/
void HeapFixDown(int Arr[], int n, int i)
{
	int temp,j;
	
	if(n <=0)
	{
		printf("The heap is empty.\n");
		return;
	}
	
	temp = Arr[i];
	j = 2*i +1 ; /*左儿子*/
	while(j<n) /*j不是最后一个节点*/
	{
		/*左右（如果有的话）儿子找到较小的，再与父节点比较*/
		if(j+1<n && Arr[j+1] < Arr[j] ) /*j+1<n表明有右儿子*/
			j = j + 1;
		
		if(Arr[j]>=temp)
			break;
		
		Arr[i] = Arr[j];
		i = j;
		j = 2*i +1 ;
	}
	
	Arr[i] = temp;
}

/*删除堆顶元素 实现时将其与最后一个节处的值交换，返回为删除后的实际节点n-1*/
int DeleteHeapRoot(int Arr[], int n)
{
	int temp;
	
	if(n <=0)
	{
		printf("Error! The heap is empty.\n");
		return -1;
	}
	
	/*交换堆顶元素与最后一个元素*/
	temp = Arr[0];
	Arr[0] = Arr[n-1];
	Arr[n-1] = temp;
	
	/*下浮调整堆序*/
	HeapFixDown(Arr, n-1, 0);
	
	return (n-1);
}

/*给定一个数组 建一个有序的最小二叉堆*/
void BuildHeap(int Arr[], int n)
{
	/*相当于堆一个无序堆 进行下沉调整; 
	每次调整可以看作是对一个根节点为i的单独二叉树进行调整，
	因此叶子节点不需要调整,第一个非叶子节点是最后一个节点(n-1)的父节点((n-1)-1)/2 = n/2-1
	*/
	
	int i;
	for(i=n/2-1; i>=0; i--)
		HeapFixDown(Arr, n , i);
		
}

int main(void)
{
	int N;  /*作为当前堆的实长度*/
	int Arr[MAXLEN];
	int i;
	int K = 3;
	
	/*input*/
	printf("Please input an positive integer N which is between 1 and 100.\n");
	scanf("%d", &N);
	if(N <= 0 || N >MAXLEN)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d integer numbers.\n", N);
	for(i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
	}
	
	
	/*BuildHeap*/
	printf("BuildHeap:\n");
	BuildHeap(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	/*InsertHeap*/
	printf("InsertHeap:\n");
	N = InsertHeap(Arr, N, (int)14);
    if(N != -1)
	{
		for(i=0; i<N; i++)
		{
			printf("%d ",Arr[i]);
		}
		printf("\n");
	}
	
	/*DeleteHeapRoot*/
	printf("DeleteHeapRoot:\n");
	N = DeleteHeapRoot(Arr, N);
    if(N != -1)
	{
		for(i=0; i<N; i++)
		{
			printf("%d ",Arr[i]);
		}
		printf("\n");
	}
	
	/*FindKmaxValue*/
	printf("FindKmaxValue:\n");
	if(FindKmaxValue(Arr, N, K) == -1)
	{
		printf("Not exists kth number:\n");
	}
	else
	{
		for(i=0; i<K; i++)
		{
			printf("%d ",Arr[i]);
		}
		printf("\n");
	}
	
	return 0;
}


/*利用最小堆可以求最大的k个数 或者第k大的数
思路是先用前k个数建立一个最小堆，然后每个数与堆顶元素对比
如果小于等于堆顶，那么肯定不是前K大的数，如果比堆顶的大那么应该取代堆顶元素，并进行下沉调整
这里重复的也算一个排序的序号
*/

int FindKmaxValue(int Arr[], int N, int K)
{
	int i;
	
	if(N<K)
	{
		return -1;
	}
	
	BuildHeap(Arr, K);
	
	for(i=K; i<N; i++)
	{
		if(Arr[i]>Arr[0])
		{
			Arr[0] = Arr[i];
			HeapFixDown(Arr, K, 0);
		}
	}
	
	return 0;
}