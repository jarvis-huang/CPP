/*
 * Project: Fibonacci
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
{double a=0,b=1,n,i;
printf("This program lists the Fibonacci sequence.\n");
printf("To F(?) do you want? ");
n=GetReal();
if (n==0) printf("F(0)=0");
if (n==1) {printf("F(0)=0\n");
           printf("F(1)=1");}
if (n>1) {printf("F(0)=0\n");
          printf("F(1)=1\n");
          for (i=2;i<=n;i=i+1)
		  {b=a+b;a=b-a;printf("F(");printf("%g",i);printf(")=");printf("%g\n",b);}
}
}