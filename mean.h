#include<stdio.h>
float mean1(float data[304],int n)
{
	int i;
    float mean,sum=0.0;
    for(i=0 ; i<n ; i++)
    {
        sum=sum+data[i];
    }
    mean=sum/n;
	return mean;	
}
