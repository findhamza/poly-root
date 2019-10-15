/* Author: Hamza Syed */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>

#include "structs.h"				//contains polydat

#define CHUNK 499				//defines max input possible
#define EPSILON 0.00000000000001		//defines max accuracy for double precision

int inputMode;					//inputMode determines whetere or not the input is echoed back in case of file input
bool debugMode;					//debug mode prints the small debuf statements littered throughout this code

struct polydat GetPolyData();			//Constructs the polydat structure from user input
void reconstruct(struct polydat);		//reconstructs the polynomial from info in polydat
double function(struct polydat, double);	//returns the f(x)
double bisect(struct polydat, double, double);	//Uses the bisection method to find root
int** nDerivative(struct polydat,int);		//finds the nth derivative of a polynomial
void destroyArr2d(int**);			//mainly made to destroy nDerivative 2d arrays
void destroyArr(int*);				//mainly made to destroy arrays
int* normArr(struct polydat);			//takes the 2d array and makes a 1d array with exponents as index and coeffiecents as index values
int minExpo(struct polydat);			//finds the minimum exponent
int maxExpo(struct polydat);			//finds the maximum exponent
bool precision(struct polydat, double);		//used to determine how close to zero our value is
double newton(struct polydat);			//Uses the newtons method to find root
void horner(struct polydat, double);		//prints the f(X) and f'(X) value using horners method
void menu();					//Used for selection as to what the user would like to do

int main()
{

	//Determine input mode and debug mode//
	inputMode = 0;
	int debug = 0;
	printf("\n\nPlease select program input mode (file=1) (keyboard=2)\nInput Mode: ");
	scanf("%d", &inputMode);
	printf("\n\nDebug Mode? (Yes=1) (No=0)\nDebug Mode: ");
	scanf("%d", &debug);

	if(debug == 1)
		debugMode = true;

	//start the menu selection//
	menu();

	return 0;
}

void menu()
{
	struct polydat polyInfo = GetPolyData();
	int input = INT_MIN;

	while(input != 0)
	{
		printf("\n\nWhat would you like to do?\n (New Polynomial = 1) (Find Root = 2) (Horners = 3) (Exit = 0)\n\nSelection: ");
		scanf("%d", &input);
		if(inputMode == 1)
			printf("%d", input);
		if(input == 1)
			polyInfo = GetPolyData();
		else if(input == 2)
		{
			printf("\n\nBisected[%lf,%lf]: %lf\n", polyInfo.a, polyInfo.b, bisect(polyInfo, polyInfo.a, polyInfo.b));
			printf("\n\nNetwonsR[%lf,%lf]: %lf\n", polyInfo.a, polyInfo.b, newton(polyInfo));
		}
		else if(input == 3)
		{
			double xVal = 0;
			printf("\n\nPlease provide x value for Horners Method: ");
			scanf("%lf", &xVal);
			horner(polyInfo, xVal);
		}
		else if(input == 0)
			exit(1);
	}

}

struct polydat GetPolyData()
{
	char userin[CHUNK];
	char *delimit = " xX()^\n";
	int ceFlag=0; //0=coefficent :: 1=exponent
	int sFlag=1; //1=positive :: -1=negative

	struct polydat polyInfo;

	//flush all stdin to ensure input is correctly recieved//
	int flush;
	while((flush = getchar()) != '\n' && flush !=EOF);


	//take the raw polynomial input//
	printf("\n\nPlease enter your polynomial: ");
	fgets(userin, CHUNK, stdin);
	if(inputMode == 1)
		printf("%s\n",userin);


	//start tokenizing the input to extract exponent and coefficents//
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
		if(debugMode == true)
			printf("\n%d\ncoe:%d\texpo:%d\n",inAt , polyInfo.coexpo[inAt][0], polyInfo.coexpo[inAt][1]);

		inAt++;
		if(val==NULL)
			break;
		else
			userinToken = strtok(NULL,delimit);
	}

	polyInfo.termCount = inAt;


	//deteremine point a and b//
	char response[2]="";
	printf("\nPlease enter point a: ");
	scanf("%lf",&polyInfo.a);
	if(inputMode == 1)
		printf("%lf\n",polyInfo.a);
	printf("Please enter point b: ");
	scanf("%lf",&polyInfo.b);
	if(inputMode == 1)
		printf("%lf\n",polyInfo.b);
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

bool precision(struct polydat polyInfo, double x)
{

	//utitlizes the max possible precision of double//
	int value = function(polyInfo,x);
	if(function(polyInfo, x)==0 || (function(polyInfo, x) < EPSILON && function(polyInfo, x) > -EPSILON))
	{
		return true;
	}

	return false;
}

int** nDerivative(struct polydat polyInfo, int n)
{
	int **nDer = (int**) malloc(sizeof(int*)*polyInfo.termCount); 	//rowcount = termcount
	for(int i=0; i<polyInfo.termCount; i++)				//columncount = 2
	{
		nDer[i] = (int*) malloc(sizeof(int)*2);

		int coe = polyInfo.coexpo[i][0];
		int expo = polyInfo.coexpo[i][1];
		for(int j=0; j<n; j++)
		{
			coe = coe*expo;
			expo--;
		}

		nDer[i][0] = coe;
		nDer[i][1] = expo;
	}

	return nDer;
}

void destroyArr2d(int** arr)
{
	free(*arr);
	free(arr);
}

void destroyArr(int* arr)
{
	free(arr);
}

double bisect(struct polydat polyInfo, double a, double b)
{
	//recursively calls upon itself till it can hit max precision//

	double mid = (a+b)/2;

	if(debugMode == true)
		printf("\nf(%lf/%lf=%lf)=%.16lf", a, b, mid, function(polyInfo, mid));

	if(precision(polyInfo,mid))
		return mid;
	else if(function(polyInfo, mid)*function(polyInfo, b)<0)
		return bisect(polyInfo, mid, b);
	else
		return bisect(polyInfo, a, mid);

	return DBL_MAX;
}

double newton(struct polydat polyInfo)
{
	double xInit = (polyInfo.a+polyInfo.b)/2;
	if(xInit == 0)
		xInit = 0.666;
	double xNext = xInit;

	if(xInit==0)
		xInit = .1;

	struct polydat firstDer = polyInfo;

	int** der = nDerivative(firstDer,1);
	for(int i=0; i<firstDer.termCount; i++)
	{
		firstDer.coexpo[i][0] = der[i][0];
		firstDer.coexpo[i][1] = der[i][1];
	}


	while(!precision(polyInfo,xNext))
	{
		double firstDerVal = function(firstDer,xNext);
		if(precision(firstDer,xNext))
			firstDerVal+=EPSILON;
		if(debugMode == true)
			printf("\n%.16lf",function(polyInfo,xNext));
		xNext = xNext - (function(polyInfo,xNext)/firstDerVal);
		if(debugMode == true)
			printf("n=>%.16lf",function(polyInfo,xNext));
		if(isinf(xNext))
			break;
	}

	destroyArr2d(der);
	return xNext;
}

int* normArr(struct polydat polyInfo)
{
	reconstruct(polyInfo);

	int arrSize = maxExpo(polyInfo) - minExpo(polyInfo);
	int *coeArr = (int*) malloc(sizeof(int*)*arrSize); 	//rowcount = termcount
	for(int i=0; i<=polyInfo.termCount; i++)
	{
		coeArr[polyInfo.coexpo[i][1]] += polyInfo.coexpo[i][0];
		if(debugMode == true)
			printf("\ncoeArr[%d] == %d\n",polyInfo.coexpo[i][1], polyInfo.coexpo[i][0]);
	}

	return coeArr;
}

int minExpo(struct polydat polyInfo)
{
	int minExpo = INT_MAX;

	for(int i=0; i<=polyInfo.termCount; i++)
		if(minExpo>polyInfo.coexpo[i][1])
			minExpo = polyInfo.coexpo[i][1];

	return minExpo;
}

int maxExpo(struct polydat polyInfo)
{
	int maxExpo = 0;

	for(int i=0; i<=polyInfo.termCount; i++)
		if(maxExpo<polyInfo.coexpo[i][1])
			maxExpo = polyInfo.coexpo[i][1];

	return maxExpo;
}

void horner(struct polydat polyInfo, double x)
{
	int *coeArr = normArr(polyInfo);
	size_t coeArrSize = maxExpo(polyInfo) - minExpo(polyInfo);
	double funcVal = coeArr[coeArrSize];
	double derVal = 0;
	if(debugMode == true)
		printf("\n%d and funcVal=%lf\n",coeArr[0],funcVal);

	for(int i=coeArrSize-1; i>=0; i--)
	{
		derVal = funcVal + (x * derVal);
		funcVal = coeArr[i] + (x * funcVal);
	}

	printf("\nHorners Value at F(%lf)=%lf and F'(%lf)=%lf", x, funcVal, x, derVal);


	destroyArr(coeArr);
}
