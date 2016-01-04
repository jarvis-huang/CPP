/*
 * Project: FindMedian
 * Created by CS106 Assignment Wizard 0.8
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

double GetMedian(double a[],double b[],int head1,int tail1,int head2,int tail);
double GetFinalMedian(double a[],double b[],int head1,int tail1,int head2,int tail2);
double GetSeperateMedian(double a[],double b[],int head1,int tail1,int head2,int tail2);

void main (void)
{
	double a[]={3.5,4,5,5.5,9,10};
	double b[]={10,34};
	double median;

	median=GetMedian(a,b,0,5,0,1);
	printf("median=%g",median);

}

double GetMedian(double a[],double b[],int head1,int tail1,int head2,int tail2)
{
	int len1=tail1-head1+1,len2=tail2-head2+1;    //长度
	double median1,median2;                       //中位数

	if ( a[head1]>=b[tail2] || a[tail1]<=b[head2] )  //分离数组
	{
		return GetSeperateMedian(a,b,head1,tail1,head2,tail2);
	}
	if(len1<=2 || len2<=2)                       //递归结束
	{
		return GetFinalMedian(a,b,head1,tail1,head2,tail2);
	}
	
	if(len1%2==1) 
	{
		median1=a[head1+len1/2];                 
	}
	else
	{
		median1=(a[head1+len1/2]+a[head1+len1/2-1])/2.0;
	}
	if(len2%2==1) 
	{
		median2=b[head2+len2/2];
	}
	else
	{
		median2=(b[head2+len2/2]+b[head2+len2/2-1])/2.0;
	}
	//以上为求各自中位数

	if (median1==median2) {return median1;}  //相等就返回
	//以下为递归
	if(median1<median2)
	{
		if(len1<len2) 
		{
			if(len1%2==1) {return GetMedian(a,b,head1+len1/2,tail1,head2,tail2-len1/2);}
			else {return GetMedian(a,b,head1+len1/2-1,tail1,head2,tail2-len1/2+1);}
		}
		else 
		{
			if (len2%2==1) {return GetMedian(a,b,head1+len2/2,tail1,head2,tail2-len2/2);}
			else {return GetMedian(a,b,head1+len2/2-1,tail1,head2,tail2-len2/2+1);}
		}
	}
	else 
	{
		if(len1<len2) 
		{
			if(len1%2==1) {return GetMedian(a,b,head1,tail1-len1/2,head2+len1/2,tail2);}
			else {return GetMedian(a,b,head1,tail1-len1/2+1,head2+len1/2-1,tail2);}
		}
		else 
		{
			if(len2%2==1) {return GetMedian(a,b,head1,tail1-len2/2,head2+len2/2,tail2);}
			else {return GetMedian(a,b,head1,tail1-len2/2+1,head2+len2/2-1,tail2);}
		}
	}
}

double GetSeperateMedian(double a[],double b[],int head1,int tail1,int head2,int tail2)
{
	int len1=tail1-head1+1,len2=tail2-head2+1,len;
	int n,n1,n2;
	//分离数组，主要是求出合中位数的位置，有时在第一个数组里，有时在第二个，这要讨论
	if (a[head1]>=b[tail2])
	{
		len=len1+len2;
		if(len%2==1) 
		{
			n=(len1+len2)/2; 
			if(n>=len2) {return a[n-len2];}
			else {return b[n];}
		}
		else
		{
			n1=(len1+len2)/2-1;
			n2=n1+1;
			if(n2<=len2-1) {return (b[n1]+b[n2])/2.0;}
			else if(n1>=len2) {return (a[n1-len2]+a[n2-len2])/2.0;}
			else {return (b[n1]+a[n2-len2])/2.0;}
		}
	}
	else
	{
		len=len1+len2;
		if(len%2==1) 
		{
			n=(len1+len2)/2; 
			if(n>=len1) {return b[n-len1];}
			else {return a[n];}
		}
		else
		{
			n1=(len1+len2)/2-1;
			n2=n1+1;
			if(n2<=len1-1) {return (a[n1]+a[n2])/2.0;}
			else if(n1>=len1) {return (b[n1-len1]+b[n2-len1])/2.0;}
			else {return (a[n1]+b[n2-len1])/2.0;}
		}
	}
}

double GetFinalMedian(double a[],double b[],int head1,int tail1,int head2,int tail2)
{
	int len1=tail1-head1+1,len2=tail2-head2+1;
	double x,y,z,j,k,num,num1,num2;
	//根据两数组长度分类处理：

	if(len1==1 && len2==1) {return (a[head1]+b[head2])/2.0;}   //都=1
	else if(len1==1)										   //有一个=1
	{
		num=a[head1];
		if(len2%2==1)
		{
			x=b[head2+len2/2-1];
			y=b[head2+len2/2];
			z=b[head2+len2/2+1];
			if (num<=x) {return (x+y)/2.0;}
			else if (num>=z) {return (y+z)/2.0;}
			else {return (y+num)/2.0;}
		}
		else
		{
			x=b[head2+len2/2-1];
			z=b[head2+len2/2];
			if (num<=x) {return x;}
			else if (num>=z) {return z;}
			else {return num;}
		}
	}
	else if(len2==1)
	{
		num=b[head2];
		if(len1%2==1)
		{
			x=a[head1+len1/2-1];
			y=a[head1+len1/2];
			z=a[head1+len1/2+1];
			if (num<=x) {return (x+y)/2.0;}
			else if (num>=z) {return (y+z)/2.0;}
			else {return (y+num)/2.0;}
		}
		else
		{
			x=a[head1+len1/2-1];
			z=a[head1+len1/2];
			if (num<=x) {return x;}
			else if (num>=z) {return z;}
			else {return num;}
		}
	}

	if(len1==2 && len2==2)                          //都等于2
	{
		if(a[head1]<=b[head2]) {num1=b[head2];}
		else{num1=a[head1];}
		if(a[tail1]>=b[tail2]) {num2=b[tail2];}
		else{num2=a[tail1];}
		return (num1+num2)/2.0;
	}												//有一个等于2
	else if(len1==2)
	{
		num1=a[head1];
		num2=a[tail1];
		if(len2%2==1)
		{
			x=b[head2+len2/2-1];
			y=b[head2+len2/2];
			z=b[head2+len2/2+1];
			if(num2<=x) {return x;}
			else if(num2<=y) {return num2;}
			else if(num1>=z) {return z;}
			else if(num1>=y) {return num1;}
			else {return y;}
		}
		else 
		{
			j=b[head2+len2/2-2];
			x=b[head2+len2/2-1];
			z=b[head2+len2/2];
			k=b[head2+len2/2+1];
			if(num2<=j) {return (j+x)/2;}
			else if(num2<=x) {return (num2+x)/2.0;}
			else if(num2<=z && num1<=x) {return (num2+x)/2.0;}
			else if(num2<=z && num1>x) {return (num2+num1)/2.0;}
			else if(num1<=x) {return (x+z)/2.0;}
			else if(num1<=k) {return (num1+z)/2.0;}
			else {return (z+k)/2.0;}
		}
	}

	else //if(len2==2)
	{
		num1=b[head2];
		num2=b[tail2];
		if(len1%2==1)
		{
			x=a[head1+len1/2-1];
			y=a[head1+len1/2];
			z=a[head1+len1/2+1];
			if(num2<=x) {return x;}
			else if(num2<=y) {return num2;}
			else if(num1>=z) {return z;}
			else if(num1>=y) {return num1;}
			else {return y;}
		}
		else
		{
			j=a[head1+len1/2-2];
			x=a[head1+len1/2-1];
			z=a[head1+len1/2];
			k=a[head1+len1/2+1];
			if(num2<=j) {return (j+x)/2;}
			else if(num2<=x) {return (num2+x)/2.0;}
			else if(num2<=z && num1<=x) {return (num2+x)/2.0;}
			else if(num2<=z && num1>x) {return (num2+num1)/2.0;}
			else if(num1<=x) {return (x+z)/2.0;}
			else if(num1<=k) {return (num1+z)/2.0;}
			else {return (z+k)/2.0;}
		}
	}
}
	
	
	
	

	

	
	
	
	
	
	
	
	
	

		
	

		
		
			
	
	
	

	
		
		
	
