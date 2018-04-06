# include <stdio.h>

/*希尔排序（最小增量排序）  改进的插入排序 增量选取N/2 增量为1时全部数据插入排序 */
void ShellSort(int Arr[], int N)
{
	int i,j,l;
	int temp;
	int increment;
	
	increment = N/2;
	while(increment>0)
	{
		for(l=0; l<increment; l++) /*using insertion sort within each group */
		{
			for(i=l; i<N-increment; i=i+increment) /*N-increment*/
			{
				for(j=i+increment; j>l; j=j-increment)
				{
					if(Arr[j] < Arr[j-increment])
					{
						temp = Arr[j];
						Arr[j] = Arr[j-increment];
						Arr[j-increment] = temp;
					}
				}
			}
		}
		increment = increment / 2;
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
	ShellSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}