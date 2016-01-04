/*
 * Project: Triangle
 * Created by CS106 Assignment Wizard 0.8
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <stdio.h>
#include "genlib.h"
#include "simpio.h"

void main (void)
{int i,n,k,m;
printf("This program generates a triangle.\n");
printf("What's the number of the rows? ");
n=GetInteger();
for (i=1;i<=2*n-1;i=i+2)
{for (k=1;k<=n-(i-1)/2;k=k+1) printf(" ");
for (m=1;m<=i;m=m+1) printf("*");
printf("\n");
}
}
