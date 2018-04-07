# include <stdio.h>

# define MAXLEN 100
typedef struct BUCKET
{
	int size;
	int num[100];
}BucketNode;


void BubbleSort(int Arr[], int N)
{
	int i, j;
	int temp;
	
	for(i=0; i<N-1; i++)
	{
		for(j=0; j<N-1-i; j++)
		{
			if(Arr[j]>Arr[j+1])
			{
				temp = Arr[j];
				Arr[j] = Arr[j+1];
				Arr[j+1] = temp;
			}
		}
	}
}

/*桶排序 把数据分到不同的桶里 在各个桶里进行排序

例如0-99整数可以分为10个桶  在每个同理分别排序即可实现排序

如果对不重复的范围不大的整数排序效果很好
*/
void BucketSort1(int Arr[], int N)
{
	int i, j, k;
	/*例如0-99正整数可以分为10个桶  在每个同理分别排序即可实现排序*/
	BucketNode sNode[10];
	
	/*初始化*/
	for(i=0; i<10; i++)
	{
		sNode[i].size = 0;
	}
	
	/*放到不同的桶里*/
	for(i=0; i<N; i++)
	{
		j = Arr[i]/10;
		sNode[j].num[sNode[j].size] = Arr[i];
		sNode[j].size  = sNode[j].size + 1;
	}
	
	
	/*各个桶中进行排序并复制回原数组*/
	k = 0;
	for(i=0; i<10; i++)
	{
		BubbleSort(sNode[i].num , sNode[i].size);
		for(j=0; j<sNode[i].size; j++)
		{
			Arr[k++] = sNode[i].num[j];
		}
	}

}

/*对0-100的数字排序 用101个桶*/
void BucketSort(int Arr[], int N)
{
	int i, j;
	int KMAX = 101;
	int bucket[KMAX];
	
	/*初始化*/
	for(i=0; i<KMAX; i++)
	{
		bucket[i] = 0;
	}

	/*放到桶里*/
	for(i=0; i<N; i++)
	{
		bucket[Arr[i]] ++ ;
	}
	
	/*复制回数组*/
	j = 0;
	for(i=0; i<KMAX; i++)
	{
		while(bucket[i]>0)
		{
			Arr[j++] = i ;
			bucket[i]--;
		}
		
	}
}

int main(void)
{
	int N;
	int Arr[100];
	int i;
	
	/*input*/
	printf("Please input an positive integer N which is between 1 and 100.\n");
	scanf("%d", &N);
	if(N <= 0 || N >100)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d integer numbers.\n", N);
	for(i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
	}
	
	
	/*sort and ouput*/
	BucketSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}