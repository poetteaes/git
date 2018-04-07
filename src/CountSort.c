# include <stdio.h>

# define KMAX 100

/*计数排序 小于某个数的值的个数 从而得出该数的位置
如果不累计，直接展开或许更好吧

下面对0-100的数
*/
void CountSort(int Arr[], int N)
{
	int i, j;
	int count[KMAX+1];
	int temp[N];
	
	/*初始化*/
	for(i=0; i<=KMAX; i++)
	{
		count[i] = 0;
	}

	/*计数*/
	for(i=0; i<N; i++)
	{
		count[Arr[i]] ++ ;
	}
	
	/*累计计数 统计不大于某个数的个数*/
	for(i=1; i<=KMAX; i++)
	{
		count[i] = count[i] + count[i-1];
	}
	
	/*逆向复制回数组 count[Arr[i]]-1就是Arr[i]在输出中的下标，
	然后count[Arr[i]]减1也确保了重复的数也能放到正确的位置*/
	for(i=N-1;i>=0; i--)
	{
		temp[count[Arr[i]]-1] = Arr[i];
		count[Arr[i]] = count[Arr[i]]  - 1;
	}
	
	for(i=0; i<N; i++)
	{
		Arr[i]  = temp[i];
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
	CountSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}