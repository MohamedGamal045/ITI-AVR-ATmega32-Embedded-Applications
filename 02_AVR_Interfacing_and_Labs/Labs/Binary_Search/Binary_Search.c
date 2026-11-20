#include <stdio.h>

int main()
{
   int arr[10]={0};
	int search=0;
	int flag =0;
	int middle,start,end;
	for(int i=0;i<10;i++)
	{
		printf("Enter the number at index %d\n",i);
		scanf("%d",&arr[i]);
	}
	printf("Enter the value to search:\n");
	scanf("%d",&search);
	while(start<=end)
	{
		middle=(start+end)/2;
		if(arr[middle]==search)
		{
			flag=1;
			break;
		}
		else if(arr[middle]>search)
		{
			end=middle-1;
		}
		else if(arr[middle]<search)
		{
			start=middle+1;
		}
	}
	if(flag==1)
	{
		printf("Exist");
	}
	else
	{
		printf("Not Exist");
	}
	return 0;
}