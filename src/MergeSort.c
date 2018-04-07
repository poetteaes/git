# include <stdio.h>
# include <stdlib.h>

/*
void Merge(int A[], int M, int B[], int N, int out[])
{ 
    int i=0;
	int j=0;
	int k=0;

	while(i<M && j<N)
	{
		if(A[i]>B[j])
			out[k++] = B[j++];
		else
			out[k++] = A[i++];
	}
	
	while(i<M)
		out[k++] = A[i++];
	
	while(j<N)
		out[k++] = B[j++];
		
}
*/

/*分治算法  分段处理再合并 用递归的方法*/

void Merge(int Arr[], int tmpArr[], int left,int mid, int right)
{
	int i, j,k;
	
	i = left;
	j = mid + 1;
	k = 0;
	
	while(i<=mid && j<=right)
	{
		if(Arr[i]>Arr[j])
			tmpArr[k++] = Arr[j++];
		else
			tmpArr[k++] = Arr[i++];
	}
	
	while(i<=mid)
		tmpArr[k++] = Arr[i++];
	
	while(j<=right)
		tmpArr[k++] = Arr[j++];
	
	for(i =0; i<right-left+1; i++ )
		Arr[i+left] = tmpArr[i];
}

void MergeDriver(int Arr[], int tmpArr[], int left, int right)
{
	int mid;
	
	if(left >= right)
		return;
	
	mid = (left + right)/2;
	MergeDriver(Arr, tmpArr, left, mid);
	MergeDriver(Arr, tmpArr, mid+1, right);
	Merge(Arr, tmpArr, left, mid, right);
}

int MergeSort(int Arr[], int N)
{
	int *tmpArr = NULL;
	
	tmpArr = (int*)malloc(sizeof(int)*N);
	if(tmpArr == NULL)
	{
		printf("Error! malloc error.\n");
		return -1;
	}
	
	MergeDriver(Arr, tmpArr, 0, N-1);
	free(tmpArr);
	
	return 0;
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
	MergeSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}