/*利用最大堆从小到大排序*/

# include <stdio.h>

# define MAXLEN 100

void HeapFixDown(int Arr[], int n, int i);
int DeleteHeapRoot(int Arr[], int n);  /*并不是真的删除 将其放在与最后一个节点交换，返回删除后的大小n-1即可*/
void BuildHeap(int Arr[], int n);   /*给定一个数组 建一个有序的最小二叉堆*/

void HeapSort(int Arr[], int N); /*堆排序*/


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
		/*左右（如果有的话）儿子找到较大的，再与父节点比较*/
		if(j+1<n && Arr[j+1] > Arr[j] ) /*j+1<n表明有右儿子*/
			j = j + 1;
		
		if(Arr[j]<=temp)
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


void HeapSort(int Arr[], int N)
{
	int i;
	
	BuildHeap(Arr, N);
	
	for(i=N; i>1; i--)
		DeleteHeapRoot(Arr, i);
}

int main(void)
{
	int N;  /*作为当前堆的实长度*/
	int Arr[MAXLEN];
	int i;
	
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
	
	
	/*HeapSort*/
	printf("HeapSort:\n");
	HeapSort(Arr, N);
    if(N != -1)
	{
		for(i=0; i<N; i++)
		{
			printf("%d ",Arr[i]);
		}
		printf("\n");
	}
	
	return 0;
}