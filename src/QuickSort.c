# include <stdio.h>

/*快速排序 找一个基准key 把小于基准的都放在key左边 大于key的都放在key右边，
key最终处于正确的位置上，再递归对key两边的子列进行相同的排序，直到每个子列只有一个数，即完成排序
*/

/*
（1）以左边的数为基准key
（2）从右到左扫描，直到找到一个小于key的值或者与左边的游标相遇停止
（3）从左到有扫描，直到找到一个大小key的值或者与左边的游标停止
（4）如果两边的游标没有相遇，则交换左右游标指向的值。然后重复(2)(3)（4）,直到游标相遇
（5）相遇位置的值即是key应该在的值，交换基准与此位置的值
（6）对相遇位置左右的子列进行递归调用
*/


/*
(1)注意是先选择基准，基准最后再放在正确位置
(2)以下实现，必须从右往左开始扫描，否则有误
*/

void QuickSortDriver(int Arr[], int left, int right)
{
	int i,j;
	int temp;
	
	i = left;
	j = right;
	
	if(left >= right)
		return;
	
	/*起始位置的值作为基准*/
	while(i<j)
	{
		while(i<j && Arr[j]>=Arr[left])  /*从右向左扫描 找到第一个小于基准的下标 ！！！必须先从右向左否则不对 */
			j--;
		
		while(i<j && Arr[i]<=Arr[left]) /*向右扫描 找到第一个大于基准的下标*/
			i++;
			
		if(i<j)
		{
			temp = Arr[i];
			Arr[i] = Arr[j];
			Arr[j] = temp;
		}
	}
	
	/*基准放到正确的位置上并对左右的子列进行递归调用*/
	if(j != left) /*此时i=j 由于j先移动必然有a[j]<key*/
	{
		temp = Arr[j];
	    Arr[j] = Arr[left];
	    Arr[left] = temp;
	}
	
	QuickSortDriver(Arr, left, j-1);
	QuickSortDriver(Arr, j+1, right);
	
}

void QuickSort(int Arr[], int N)
{
	QuickSortDriver(Arr, 0, N-1);
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
	QuickSort(Arr, N);
	for(i=0; i<N; i++)
	{
		printf("%d ",Arr[i]);
	}
	printf("\n");
	
	return 0;
}


