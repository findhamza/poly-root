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

	char *userinToken = strtok(userin,delimit);
	int inAt=0;
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
		polyInfo.coexpo[inAt][1] = atoi(strtok(NULL,delimit));

		printf("\n%d\ncoe:%d\texpo:%d\n",inAt , polyInfo.coexpo[inAt][0], polyInfo.coexpo[inAt][1]);

		inAt++;
		userinToken = strtok(NULL,delimit);
	}

	printf("please enter the range:");
	scanf("%d %d",&polyInfo.a,&polyInfo.b);


	return polyInfo;
}
