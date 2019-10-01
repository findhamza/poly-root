/* Author: Hamza Syed */
#include <stdio.h>
#include <string.h>

#include "structs.h"

struct polydat GetPolyData();

int main()
{
	struct polydat polyInfo = GetPolyData();
	return 0;
}

struct polydat GetPolyData()
{
	struct polydat polyInfo;

	printf("Please Enter Terms Count: ");
	scanf("%d",&polyInfo.termCount);
	

	printf("Please Enter Coefficient And Exponents");

	for(int i=0; i<=polyInfo.termCount; i++)
	{
		printf("Coefficient %d: ",i+1);
		scanf("%lf", polyInfo

	return polyInfo;
}
