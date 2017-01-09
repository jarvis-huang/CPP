#include "stdio.h"
#include "stdlib.h"

void DoCombination(char *instring, int *used, int len, int level)
{
	int i, empty = 1;
	if (level==len) {
		for (i=0; i<len; i++) {
			if (used[i]) {
				empty = 0;
				printf("%c",instring[i]);
			}
		}
		if (empty)
			printf("empty string");
		printf("\n");
		return;
	}
	
	used[level] = 0;
	DoCombination(instring, used, len, level+1);
	used[level] = 1;
	DoCombination(instring, used, len, level+1);
	used[level] = 0;
}	

void main (void)
{
	char *instring;
	int len, i;
	int *used;
	
	instring = "cato";
	len = 4;
	used = (int *)malloc(len*sizeof(int));
	for (i=0; i<len; i++) {
		used[i] = 0;
	}
	
	DoCombination(instring, used, 4, 0);
}