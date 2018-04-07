# include <stdio.h>


/*
二分查找 对已经排序的序列进行查找，返回找到的值得下标，不存在返回-1
*/

/*递归*/
int BinarySearchRecur(int Arr[], int left, int right, int value)
{
	if(left>right)
		return -1;

	if(Arr[(left + right)/2] == value)
		return (left + right)/2;
	else if(Arr[(left + right)/2] > value)
		return BinarySearchRecur(Arr, left, (left + right)/2-1, value);
	else
		return BinarySearchRecur(Arr, (left + right)/2 + 1, right, value);
}

/*非递归*/
int BinarySearchNotRecur(int Arr[], int left, int right, int value)
{
	int mid;

	while(left<=right)
	{
		mid = (left + right)/2;
		if(Arr[mid] == value)
			return mid;
		else if(Arr[mid] > value)
			right = mid - 1;
		else
			left = mid + 1;
	}
	
	return -1;
}

int main(void)
{
	int N, M;
	int Arr[100];
	int i;
	int index;
	
	/*input*/
	printf("Please input an positive integer N which is between 1 and 100.\n");
	scanf("%d", &N);
	if(N <= 0 || N >100)
	{
		printf("Invalid input N[%d]\n", N);
		return -1;
	}
	
	printf("Please input %d integer numbers by ascend order.\n", N);
	for(i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
	}
	
	printf("Please input an  integer M.\n");
	scanf("%d", &M);
	
	
	/*sort and ouput*/
	index = BinarySearchRecur(Arr, 0, N-1, M);
	if(index == -1)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("Found. Arr[%d]=%d\n", index,M);
	}
	
	return 0;
}