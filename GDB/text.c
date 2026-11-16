#include <stdio.h>
int main()
{
	int xb[5];
	int i;
	int sum = 0;
	for (i = 0; i < 5; i++)
		xb[i] = i * 2;
	for (i = 0; i < 5; i++)
	{
		sum = sum + xb[i];
	}
	printf("sum = %d\n", sum);
	return 0;
}
