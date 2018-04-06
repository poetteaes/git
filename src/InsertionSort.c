# include <stdio.h>

/*直接插入排序 每一趟将一个待排序的数插入到已经排序的正确位置上*/
void InsertionSort(int Arr[], int N)
{
	int i,j;
	int temp;
	
	for(i=0; i<N-1; i++)
	{
		for(j=i+1; j>0; j--)
		{
			if(Arr[j]<Arr[j-1])
			{
				temp = Arr[j];
				Arr[j] = Arr[j-1];
				Arr[j-1] = temp;
			}
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
	InsertionSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}