/* Author: Hamza Syed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"

#define CHUNK 499

struct polydat GetPolyData();

int main()
{
	struct polydat polyInfo = GetPolyData();

	int term=0;
	printf("\n\nPoly\n");
	while(term!=polyInfo.termCount)
	{
		printf("(%dx^%d)", polyInfo.coexpo[term][0], polyInfo.coexpo[term][1]);
		if(term<polyInfo.termCount-1)
			printf("+");
		term++;
	}

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

/*	int termCount=0;
	while(polyInfo.coexpo[termCount][0]!=0 && polyInfo.coexpo[termCount][1]!=0)
		termCount++;
	printf("termcount: %d",termCount);
*/	polyInfo.termCount = inAt;

	char response[2]="";
	printf("\nPlease enter point a: ");
	scanf("%d",&polyInfo.a); printf("%d\n",polyInfo.a);
	printf("Please enter point b: ");
	scanf("%d",&polyInfo.b); printf("%d\n",polyInfo.b);
	while(polyInfo.a>polyInfo.b)
	{
		printf("\nLooks like a is larger than b\nRetry? (y,n) => ");
		scanf("%s",response);
		if(strcmp(response,"y")==0)
		{
			printf("Please enter point a: ");
			scanf("%d",&polyInfo.a);
			printf("Please enter point b: ");
			scanf("%d",&polyInfo.b);
		}
		else
			exit(1);
	}


	return polyInfo;
}
