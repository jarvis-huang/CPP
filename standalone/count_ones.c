#include "stdio.h"
#include "stdlib.h"

// Count number of bit 1's in a number's binary representation
// Showcase bit operations.
void main(void)
{
	int i, num, count;
	printf("Enter a number: ");
	while (scanf("%d", &num) == 1)
	{
		if (num==0)
			break;
		count = 0;
		for (i=0; i<32; i++)
		{
			if (((num << 31-i) & (1 << 31)) == (1 << 31))
				count ++;
		}
		printf("count=%d\n",count);
		printf("Enter a number: ");
	}
}
	
