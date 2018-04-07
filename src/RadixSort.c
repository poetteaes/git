# include <stdio.h>


/*
基数排序 
先按照个位数排序，再按照十位数排序， 依次类推……
对于自然数排序可以想象有10个桶，按照个位数放到不同的桶里，然后再按照十位数放到不同的桶里，最终都在一个桶里完成了排序

实际实现的时候，其实就是按照个位数对原数据排序（使用计数排序），再按照十位数排序（使用计数排序）， 依次类推……
*/

int getDigit(int number, int digit)
{
	return ((number/digit)%10);
}

void RadixSort(int Arr[], int N)
{
	int i, j, k;
	int count[10];
	int temp[N];
	int maxNum;
	int maxBitLen;
	int exp;
	
	/*获取最大数的位数*/
	maxNum = Arr[0];
	for(i=1; i<N; i++)
	{
		if(Arr[i]>maxNum)
			maxNum = Arr[i];
	}
	
	maxBitLen = 1;
	while((maxNum =maxNum/10)!=0)
		maxBitLen ++ ;
	
	/*对各位数进行计数排序*/
	exp = 1;
	for(j=0; j<maxBitLen; j++ )
	{

		/*初始化*/
	    for(i=0; i<=10; i++)
	    {
	    	count[i] = 0;
	    }
         
	    /*计数*/
	    for(i=0; i<N; i++)
	    {
			k = getDigit(Arr[i], exp);
	    	count[k] ++ ;
	    }
	    
	    /*累计计数 统计不大于某个数的个数*/
	    for(i=1; i<=10; i++)
	    {
	    	count[i] = count[i] + count[i-1];
	    }
	    
	    /*逆向复制回数组 count[Arr[i]]-1就是Arr[i]在输出中的下标，
	    然后count[Arr[i]]减1也确保了重复的数也能放到正确的位置*/
	    for(i=N-1;i>=0; i--)
	    {
			k = getDigit(Arr[i], exp);
	    	temp[count[k]-1] = Arr[i];
	    	count[k] = count[k]  - 1;
	    }
	    
	    for(i=0; i<N; i++)
	    {
	    	Arr[i]  = temp[i];
	    }
		
		exp = exp * 10;
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
	RadixSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}