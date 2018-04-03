# include <stdio.h>


/*冒泡排序*/
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


int main(void)
{
	int N;
	int Arr[100];
	int i;
	
	/*
	i=0;
	while(scanf("%d", &N)==1 && Arr[i] !='\n')
	{
		scanf("%d", &Arr[i]);
		i = i + 1;
	}
	*/
	
	/*input*/
    printf("Please input an integer number\n");
	scanf("%d", &N);
	if(N<=1 || N>100)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d integer numbers\n", N);
	for(i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
	}
	
	/*sort and output*/
	BubbleSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
    return 0;
}

