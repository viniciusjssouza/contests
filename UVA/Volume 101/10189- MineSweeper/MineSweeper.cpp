/***********************************************************
 * 10189- MineSweeper - ACM Problems - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data: 15/01/2008
 ************************************************************/

#include <cstdio>
#include <iostream>

#define FLDMAX	110

using namespace std;
/*
char getOutput(char field[FLDMAX][FLDMAX], int i, int k, int lin, int col);
void initFld(char field[FLDMAX][FLDMAX]);


int main()
{
	long start = clock();
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	
	int fldNum = 0;
	while (true)
	{
		int lin = 0, col = 0;
		scanf(" %d %d ", &lin, &col);
		if (!lin && !col)break;
		if (fldNum) cout << "\n";
		fldNum ++;
		
		char field[FLDMAX][FLDMAX];
		initFld(field);
		for (int i =0; i < lin; i++)
		{
			char line[col+2];
			for (int x= 0; x < (col+2); x++)
				line[x] = '\0';
			//scanf("%s", line);
			gets(line);
			for (int k = 0; k < col; k++)
			{
				field[i][k] = line[k];
			}
		}
		if (lin && col)cout << "Field #" << fldNum << ":\n";
		for (int i = 0; i < lin; i++)
		{
			for (int k = 0; k < col; k++)
			{
				cout << getOutput(field, i, k, lin, col);
			}
			cout << "\n";
		}
	}
	long end = clock();
	cout << "Tempo:"<< end-start << endl;
	return 0;
}

char getOutput(char field[FLDMAX][FLDMAX], int i, int k, int lin, int col)
{
	if (field[i][k] == '*') return '*';
	int conta = 0;
	
	if ( (i-1) >= 0 && (k-1) >= 0 && field[i-1][k-1] == '*')
		conta++;
	if ( (i-1) >= 0 && field[i-1][k] == '*')
		conta++;
	if ( (i-1) >= 0 && (k+1) < col && field[i-1][k+1] == '*')
		conta++;
	if ( (k-1) >= 0 && field[i][k-1] == '*')
		conta++;
	if ( (k+1) < col && field[i][k+1] == '*')
		conta++;
	if ( (k-1) >= 0 && (i+1) < lin && field[i+1][k-1] == '*')
		conta++;
	if ( (i+1) < lin && field[i+1][k] == '*')
		conta++;
	if ( (k+1) < col && (i+1) < lin && field[i+1][k+1]== '*')
		conta++;
	return(conta + '0');
}

void initFld(char field[FLDMAX][FLDMAX])
{
	for (int i = 0; i < FLDMAX; i++)
	{
		for (int k = 0; k < FLDMAX; k++)
			field[i][k] = '.';
	}
}
*/