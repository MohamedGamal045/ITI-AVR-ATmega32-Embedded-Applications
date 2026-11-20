#include <stdio.h>

int main()
{
    int id;
	printf("Enter Your ID:\n");
	scanf("%d",&id);
	switch(id)
	{
		case 1234:printf("Mohamed");break;
		case 5678:printf("Gamal");break;
		case 9101:printf("Soliman");break;
		default:printf("Wrong id");break;
	}
	return 0;
}