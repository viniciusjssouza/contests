/***********************************************************
 * 10189- MineSweeper - ACM Problems - Programming Challenges - Versao 2
 * Autor: Vinicius J. S. Souza
 * Data: 08/03/2008
 ************************************************************/

#include <cstdio>
#include <iostream>

#define FLDMAX	101

#define antLin  i-1
#define posLin  i+1
#define antCol  k-1
#define posCol  k+1

#define infLin  antLin >= 0
#define supLin  posLin < lin
#define infCol  antCol >= 0
#define supCol  posCol < col


using namespace std;

char getOutput(int i, int k);
inline void initFld();

char field[FLDMAX][FLDMAX];
int lin = 0, col = 0;

int main()
{
	long start = clock();
	
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	int fldNum = 0;
	
	while (scanf(" %d %d ", &lin, &col) == 2)
	{	
		if (!lin || !col) break;
		
		initFld();

		for (register int i =0; i < lin; i++)
			gets(field[i]);			

		if (fldNum) putchar('\n');
		fldNum ++;
		printf("Field #%d:\n", fldNum);
		for (register int i = 0; i < lin; i++)
		{
			for (register int k = 0; k < col; k++)
				putchar(getOutput(i, k));
			putchar('\n');
		}
	}
	
	long end = clock();
	cout << "Tempo:"<< end-start << endl;
	return 0;
}

char getOutput(int i, int k)
{
	if (field[i][k] == '*') return '*';
	register int conta = 0;
	
	if ( infLin && infCol && field[antLin][antCol] == '*')
		conta++;
	if ( infLin && field[antLin][k] == '*')
		conta++;
	if ( infLin && supCol && field[antLin][posCol] == '*')
		conta++;
	if ( infCol && field[i][antCol] == '*')
		conta++;
	if ( supCol  && field[i][posCol] == '*')
		conta++;
	if ( infCol && supLin && field[posLin][antCol] == '*')
		conta++;
	if ( supLin && field[posLin][k] == '*')
		conta++;
	if ( supCol && supLin && field[posLin][posCol]== '*')
		conta++;
	return(conta + '0');
}

inline void initFld()
{
	for (int i = 0; i < lin; i++)
	{
		for (int k = 0; k < col; k++)
			field[i][k] = '.';
	}
}
