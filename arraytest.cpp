#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include"median.h"
#include"mean.h"
#define BSIZE 304
#define B1SIZE 14 
#define Train 242
#define Test 61
int u=0,w=0,c=Train;
//Distance Calculation
void distance(float gl2[Test][B1SIZE],float gl1[Train][B1SIZE],int x,int t,int c)
{	
	int k = 9,temp,di[Train],count=0,count1=0;
	int i,j=0,m,a[Test],a2[Test];
	float val=0;
	float dis[Train],z;
	float res[Train],res1[Test];
	for(i=1; i<Train ;i++)
	{
		for(j=0;j<13;j++)
		{
			val += pow((gl2[c][j]-gl1[i][j]),2);
		}
		dis[i] = sqrt(val);
		res[i] = gl1[i][13];
		di[i]=i;
	}
	for(i=Train;i<BSIZE;i++)
	{
		res1[i]=gl2[i][13];
		a2[i]=res1[i];
	}
	//Sorting the Distance and Corresponding Class Value
	for(i=1;i<Train;i++)
	{
		for(m=1;m<Train-i;m++)
		{
			if(dis[m]>dis[m+1])
			{
				temp=dis[m];
				dis[m]=dis[m+1];
				dis[m+1]=temp;
			
				temp=res[m];
				res[m]=res[m+1];
				res[m+1]=temp;
	
				temp=di[m];
				di[m]=di[m+1];
				di[m+1]=temp;
			}	
		}  
	}
	//Printing value of K-nearest Distance
	printf("\n------------------------\n");
	printf("\nTarget values of 5 nearest neighbors are:\n");
	printf("\n------------------------\n");
	
	for(i=1;i<=k;i++)
	{
		printf("%f\t %0.0f\n",dis[i],res[i]);	
	}

	for(i=1;i<=k;i++)
	{
		if(res[i]==0)
		{
			count++;	
		}
		else
		{
			count1++;
		}	
	}
	if(count>count1)
	{
		a[x]=0;
	}
	else
	{
		a[x]=1;
	}
	printf("Calculated Value: %d\n",a[x]);
	printf("Observed Value:%d\n",a2[t]);
	if(a[x] == a2[t])
	{
		u++;
	}
	else
	{
		w++;
	}
	//Checking for Correct Value
	if(x==60)
	{
		printf("\n------------------------\n");
		printf("Correct Value: %d\n",u);
		printf("InCorrect Value: %d\n",w);
		z=((float)u/(float)(Test-1))*100;
		//Printing Accuracy and Error
		printf("\n------------------------\n");
		printf("Accuracy: %f\n",z);
		printf("Error: %f\n",100-z);
	}
}
//Calculating Standard Deviation
float calculateSD(float data[],int n,float mean)
{
    float standardDeviation = 0.0;
    int i;
    for(i=0;i<n;i++)
        standardDeviation += pow((data[i] - mean), 2);
    return sqrt(standardDeviation/n);
}
//Main Function 
int main()
{
	int n = 13;
	// specify filename
	float median=0,*ch,sum=0.0,mean,mean2,mean3,sd,sd1,sd2;
	char filename[] = "heart.csv";
	char buffer[BSIZE];
	FILE *f;
	
	// we need to specify the column names
	char *field;
	float age[BSIZE],sex[BSIZE],cp[BSIZE],trestbps[BSIZE], chol[BSIZE],fbs[BSIZE],restecg[BSIZE],thalach[BSIZE],exang[BSIZE],oldpeak[BSIZE],slope[BSIZE],ca[BSIZE],thal[BSIZE],target[BSIZE];
	char gl[BSIZE][B1SIZE];
	int i=0,j=0,x=1,t=Train;
	float glu[BSIZE][B1SIZE],gl1[Train][B1SIZE],gl2[Test][B1SIZE];
	
	/* open the CSV file */
	f = fopen(filename,"r");
	if( f == NULL)
	{
		printf("Unable to open file '%s'\n",filename);
		exit(1);
	}
	while(fgets(buffer,BSIZE,f))
	{
		/* get age */
		field=strtok(buffer,",");// strtok() is used for splitting a string by some delimiter.
		age[i]=atof(field);//atof is a function that converts a string into an float representation.
		
		/* get sex */
		field=strtok(NULL,",");
		sex[i]=atof(field);
		
		/* chest pain type */
		field=strtok(NULL,",");
		cp[i]=atof(field);
		
		/* resting blood pressure (in mm Hg on admission to the hospital) */
		field=strtok(NULL,",");
		trestbps[i]=atof(field);
		
		/* serum cholestoral in mg/dl */
		field=strtok(NULL,",");
		chol[i]=atof(field);
		
		/* (fasting blood sugar > 120 mg/dl) (1 = true; 0 = false) */
		field=strtok(NULL,",");
		fbs[i]=atof(field);
		
		/* restecgresting electrocardiographic results */
		field=strtok(NULL,",");
		restecg[i]=atof(field);
		
		/* maximum heart rate achieved */
		field=strtok(NULL,",");
		thalach[i]=atof(field);
		
		/* exercise induced angina (1 = yes; 0 = no) */
		field=strtok(NULL,",");
		exang[i]=atof(field);
				
		/* ST depression induced by exercise relative to rest */
		field=strtok(NULL,",");
		oldpeak[i]=atof(field);
		
		/* the slope of the peak exercise ST segment */
		field=strtok(NULL,",");
		slope[i]=atof(field);
		
		/* number of major vessels (0-3) colored by flourosopy */
		field=strtok(NULL,",");
		ca[i]=atof(field);
		
		/* 3 = normal; 6 = fixed defect; 7 = reversable defect */
		field=strtok(NULL,",");
		thal[i]=atof(field);
		
		/* 1 or 0 */
		field=strtok(NULL,",");
		target[i]=atof(field);
		
		i++;		 
	}    
    //storing value row-wise
	for(i=1;i<BSIZE;i++)
	{
			glu[i][j]=age[i];
			glu[i][j+1]=sex[i];
			glu[i][j+2]=cp[i];
			glu[i][j+3]=trestbps[i];
			glu[i][j+4]=chol[i];
			glu[i][j+5]=fbs[i];
			glu[i][j+6]=restecg[i];
			glu[i][j+7]=thalach[i];
			glu[i][j+8]=exang[i];
			glu[i][j+9]=oldpeak[i];
			glu[i][j+10]=slope[i];
			glu[i][j+11]=ca[i];
			glu[i][j+12]=thal[i];
			glu[i][j+13]=target[i];
			j=0;					
    }
    j=0;
    //Data Preprocessing
    //finding NULL value in the data set
    for(i=1;i<BSIZE;i++)
	{
		if(glu[i][j]==0.0)
		{
			age[i]=Find_median(age , BSIZE);// if NULL value the put median in place of NULL value
			glu[i][j]=age[i];
			
		}
	}
	j=0;
	//feature scaling using Standardization
	mean = mean1(chol,BSIZE);//finding mean
	mean2 = mean1(trestbps,BSIZE);//finding mean
	mean3 = mean1(thalach,BSIZE);//finding mean
	sd=calculateSD(chol,BSIZE,mean);//calculating Standard deviation from calculateSD function 
	sd1=calculateSD(trestbps,BSIZE,mean2);
	sd2=calculateSD(thalach,BSIZE,mean3);
	for(i=1;i<BSIZE;i++)
	{
		chol[i]=((chol[i]-mean)/sd);//using Standardization formula xnew=((x[i] -xmean)/standard deviation)
		trestbps[i]=((trestbps[i]-mean2)/sd1);
		thalach[i]=((thalach[i]-mean3)/sd2);
		glu[i][j+3]=trestbps[i];
		glu[i][j+4]=chol[i];
		glu[i][j+7]=thalach[i];
	}
	//printing the data set
	printf("age \t sex \t cp \t trestbps \t chol \t fbs \t restecg \t thalach \t exang \t oldpeak \t slope \t ca \t thal \t target\n\n");
	for(i=1;i<BSIZE;i++)
	{
    	for(j=0;j<B1SIZE;j++)
    	{
    		printf("%0.2f\t",glu[i][j]);
		}
		printf("\n");
	}
	j=0;
	//Training Dataset
	for(i=1;i<=Train;i++)
	{
			gl1[i][j]=glu[i][j];
			gl1[i][j+1]=glu[i][j+1];
			gl1[i][j+2]=glu[i][j+2];
			gl1[i][j+3]=glu[i][j+3];
			gl1[i][j+4]=glu[i][j+4];
			gl1[i][j+5]=glu[i][j+5];
			gl1[i][j+6]=glu[i][j+6];
			gl1[i][j+7]=glu[i][j+7];
			gl1[i][j+8]=glu[i][j+8];
			gl1[i][j+9]=glu[i][j+9];
			gl1[i][j+10]=glu[i][j+10];
			gl1[i][j+11]=glu[i][j+11];
			gl1[i][j+12]=glu[i][j+12];
			gl1[i][j+13]=glu[i][j+13];
			j=0;
	}
	//Printing Training Data
	printf("age \t sex \t cp \t trestbps \t chol \t fbs \t restecg \t thalach \t exang \t oldpeak \t slope \t ca \t thal \t target\n\n");
	for(i=1;i<Train;i++)
	{
		for(j=0;j<B1SIZE;j++)
		{
			printf("%0.2f\t",gl1[i][j]);
		}
		printf("\n");
	}
	j=0;
	//Testing Dataset
	for(i=Train;i<BSIZE;i++)
	{
			gl2[i][j]=glu[i][j];
			gl2[i][j+1]=glu[i][j+1];
			gl2[i][j+2]=glu[i][j+2];
			gl2[i][j+3]=glu[i][j+3];
			gl2[i][j+4]=glu[i][j+4];
			gl2[i][j+5]=glu[i][j+5];
			gl2[i][j+6]=glu[i][j+6];
			gl2[i][j+7]=glu[i][j+7];
			gl2[i][j+8]=glu[i][j+8];
			gl2[i][j+9]=glu[i][j+9];
			gl2[i][j+10]=glu[i][j+10];
			gl2[i][j+11]=glu[i][j+11];
			gl2[i][j+12]=glu[i][j+12];
			gl2[i][j+13]=glu[i][j+13];
			j=0;
	}
	//Printing Test Data
	printf("age \t sex \t cp \t trestbps \t chol \t fbs \t restecg \t thalach \t exang \t oldpeak \t slope \t ca \t thal \t target\n\n");
	for(i=Train;i<BSIZE;i++)
	{
		for(j=0;j<B1SIZE;j++)
		{
			printf("%0.2f\t",gl2[i][j]);
		}
		printf("\n");
	}
	j=0;
	printf("\n----Applying KNN----\n");
//	printf("\nDistances calculated");
//	printf("\nDistances sorted");
	for(i=1;i<Test;i++)
	{
		distance(gl2,gl1,x,t,c);
		x++;
		t++;
		c++;
	}
	fclose(f);//closing the file
	return(0);
}
