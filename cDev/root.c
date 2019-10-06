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

/*	int term=0;
	printf("\nSorted Polys\n");
	while(polyInfo.coexpo[term][0]!=0 && polyInfo.coexpo[term][1]!=0)
	{
		printf("\n%d\ncoe:%d\texpo:%d\n",term , polyInfo.coexpo[term][0], polyInfo.coexpo[term][1]);
		term++;
	}
*/
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

		polyInfo.coexpo[inAt][0] = atoi(userinToken) * sFlag;
		if((val = strtok(NULL,delimit))!=NULL)
			expoval = atoi(val);
		else
			expoval = 0;
			polyInfo.coexpo[inAt][1] = expoval;

		printf("\n%d\ncoe:%d\texpo:%d\texpoval\n",inAt , polyInfo.coexpo[inAt][0], polyInfo.coexpo[inAt][1]);

		inAt++;
		userinToken = strtok(NULL,delimit);
	}

	for(int i=0; i<10; i++)
		printf("%d %d\n",polyInfo.coexpo[i][0],polyInfo.coexpo[i][1]);


/*	int *swap;
	for(int i=0; i<CHUNK; i++)
	{
		for(int j=0; j<CHUNK-i; j++)
		{
			if(polyInfo.coexpo[j][1]>polyInfo.coexpo[j+1][1]
				&& polyInfo.coexpo[j+1][0] != 0
				&& polyInfo.coexpo[j+1][1] != 0)
			{
				for(int k=0; k<1; k++)
				{
					int temp;
					temp = polyInfo.coexpo[j][k];
					polyInfo.coexpo[j][k] = polyInfo.coexpo[j+1][k];
					polyInfo.coexpo[j+1][k] = temp;
				}
			}
		}
	}
*/
	printf("please enter the range:");
	scanf("%d %d",&polyInfo.a,&polyInfo.b);


	return polyInfo;
}
