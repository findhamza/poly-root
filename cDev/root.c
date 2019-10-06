/* Author: Hamza Syed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "structs.h"

#define CHUNK 499
#define EPSILON 0.00000000000001

struct polydat GetPolyData();
void reconstruct(struct polydat);
double function(struct polydat, double);
double bisect(struct polydat, double, double);

int main()
{
	struct polydat polyInfo = GetPolyData();
	reconstruct(polyInfo);

	printf("\n\nBisected[%lf,%lf]: %lf", polyInfo.a, polyInfo.b, bisect(polyInfo, polyInfo.a, polyInfo.b));

	return 0;
}

struct polydat GetPolyData()
{
	char userin[CHUNK];
	char *delimit = " xX()^\n";
	int ceFlag=0; //0=coefficent :: 1=exponent
	int sFlag=1; //1=positive :: -1=negative

	struct polydat polyInfo;

	printf("Please enter your polynomial: ");
	fgets(userin, CHUNK, stdin);
	printf("%s\n",userin);

	char *userinToken = strtok(userin,delimit);
	int inAt=0;
	char *val;
	int expoval=0;
	while(userinToken)
	{

		if(strcmp(userinToken,"+")==0 || strcmp(userinToken,"-")==0)
		{
			if(strcmp(userinToken,"-"))
				sFlag=1;
			if(strcmp(userinToken,"+"))
				sFlag=-1;
			userinToken = strtok(NULL,delimit);
		}

		if(atoi(userinToken)>0)
			polyInfo.coexpo[inAt][0] = atoi(userinToken) * sFlag;
		else
			polyInfo.coexpo[inAt][0] = atoi(userinToken);

		if((val = strtok(NULL,delimit))!=NULL)
			expoval = atoi(val);
		else
			expoval = 0;
		polyInfo.coexpo[inAt][1] = expoval;

		printf("\n%d\ncoe:%d\texpo:%d\n",inAt , polyInfo.coexpo[inAt][0], polyInfo.coexpo[inAt][1]);

		inAt++;
		if(val==NULL)
			break;
		else
			userinToken = strtok(NULL,delimit);
	}

	polyInfo.termCount = inAt;

	char response[2]="";
	printf("\nPlease enter point a: ");
	scanf("%lf",&polyInfo.a); printf("%lf\n",polyInfo.a);
	printf("Please enter point b: ");
	scanf("%lf",&polyInfo.b); printf("%lf\n",polyInfo.b);
	while(polyInfo.a>polyInfo.b)
	{
		printf("\nLooks like a is larger than b\nRetry? (y,n) => ");
		scanf("%s",response);
		if(strcmp(response,"y")==0)
		{
			printf("Please enter point a: ");
			scanf("%lf",&polyInfo.a);
			printf("Please enter point b: ");
			scanf("%lf",&polyInfo.b);
		}
		else
			exit(1);
	}


	return polyInfo;
}

void reconstruct(struct polydat polyInfo)
{
	int term=0;
	printf("\n\nReconstructed Poly\n");
	while(term!=polyInfo.termCount)
	{
		printf("(%dx^%d)", polyInfo.coexpo[term][0], polyInfo.coexpo[term][1]);
		if(term<polyInfo.termCount-1)
			printf("+");
		term++;
	}
	printf("\n\n");
}

double function(struct polydat polyInfo, double x)
{
	double funcVal=0;
	for(int i=0; i<=polyInfo.termCount; i++)
	{
		funcVal += polyInfo.coexpo[i][0] * pow(x,polyInfo.coexpo[i][1]);

	}
	return funcVal;
}

double bisect(struct polydat polyInfo, double a, double b)
{
	double mid = (a+b)/2;

	printf("\nf(%lf/%lf=%lf)=%.16lf", a, b, mid, function(polyInfo, mid));

	if(function(polyInfo, mid)==0 || (function(polyInfo, mid) < EPSILON && function(polyInfo, mid) > -EPSILON))
		return mid;
	else if(function(polyInfo, mid)*function(polyInfo, b)<0)
		return bisect(polyInfo, mid, b);
	else
		return bisect(polyInfo, a, mid);

	return DBL_MAX;
}
