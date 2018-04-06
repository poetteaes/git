# include <stdio.h>

/*选择排序 每一趟排序找出一个最小数的下标 将该下标处的数放到正确的位置上*/
void SelecttionSort(int Arr[], int N)
{
	int i, j;
	int idx;
	int temp;
	
	for(i=0; i<N-1; i++)
	{
		/*find the index of the min number*/
		idx = i;
		for(j=i+1; j<N; j++)
		{
			if(Arr[idx]>Arr[j])
				idx = j;
		}
		
		/*put the min number in the right place*/
		if(idx != i)
		{
			temp = Arr[i];
			Arr[i] = Arr[idx];
			Arr[idx] = temp;
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
	SelecttionSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}
