/**********************************************************************************
* UVA 742 - Domino Game - Final Sul-America - 1999 - Problema 2
*
* Autor: Vinicius J. S. Souza
* Data:  18/04/2009
* Tecnicas utilizadas: backtracking
************************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

#define RED true
#define GREEN false
#define BOTH 2
#define NO	-1

using namespace std;

int n, result;
int red[2][15], green[2][15];

bool isAllUsed(vector<bool> &used)
{
	for (int i = 0; i < n; i++)
		if (!used[i]) return false;
	return true;
}

void backtrack(vector<bool> &usedR, vector<bool> &usedG, const int end1, const int end2, bool played, bool sameTurn = false)
{
	if (played == GREEN && isAllUsed(usedG))
	{
		if (result == RED)
			result = BOTH;
		else result = GREEN;
		return;
	}		
	else if (played == RED && isAllUsed(usedR))
	{
		if (result == GREEN)
			result = BOTH;
		else result = RED;
		return;
	}

	bool done = false;

	if (played == GREEN)
	{
		for (int i = 0; i < n; i++)
		{
			bool call = false;
			int next1 = end1, next2 =end2;
			if (!usedR[i])
			{				
				if (red[0][i] == end1)
				{
					next1 = red[1][i];
					call = true;			
				}
				else if (red[0][i] == end2)
				{
					next2 = red[1][i];
					call = true;
				}
				if (call)
				{
					vector<bool> nextUsed(n);
					copy(usedR.begin(), usedR.end(), nextUsed.begin());
					nextUsed[i] = true;
					backtrack(nextUsed, usedG, next1, next2, RED, false);
					if (result == BOTH) return;
					call = false;
					done = true;
				}
				next1 = end1, next2 = end2;
				if (red[1][i] == end1)
				{
					next1 = red[0][i];
					call = true;
				}
				else if (red[1][i] == end2)
				{
					next2 = red[0][i];
					call = true;
				}
				if (call)
				{
					vector<bool> nextUsed(n);
					copy(usedR.begin(), usedR.end(), nextUsed.begin());
					nextUsed[i] = true;
					backtrack(nextUsed, usedG, next1, next2, RED, false);
					if (result == BOTH) return;
					done = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			bool call = false;
			int next1 = end1, next2 =end2;
			if (!usedG[i])
			{
				if (green[0][i] == end1)
				{
					next1 = green[1][i];
					call = true;
				}
				else if (green[0][i] == end2)
				{
					next2 = green[1][i];
					call = true;
				}
				if (call)
				{
					vector<bool> nextUsed(n);
					copy(usedG.begin(), usedG.end(), nextUsed.begin());
					nextUsed[i] = true;
					backtrack(usedR, nextUsed, next1, next2, GREEN, false);					
					if (result == BOTH) return;
					call = false;
					done = true;
				}
				next1 = end1, next2 =end2;
				if (green[1][i] == end1)
				{
					next1 = green[0][i];
					call = true;
				}
				else if (green[1][i] == end2)
				{
					next2 = green[0][i];
					call = true;
				}
				if (call)
				{
					vector<bool> nextUsed(n);
					copy(usedG.begin(), usedG.end(), nextUsed.begin());
					nextUsed[i] = true;
					backtrack(usedR, nextUsed, next1, next2, GREEN, false);					
					if (result == BOTH) return;
					done = true;
				}
			}
		}
	}
	if (!done && !sameTurn) 
		backtrack(usedR, usedG, end1, end2, !played, true);
}

int main()
{
	bool isInicio = true;
	while (true)
	{	
		cin >> n;	
		if (!n) break;
		if (!isInicio) 
			putchar('\n');
		else
			isInicio = false;

		int max = -1, index = 0;
		bool first = RED;
		vector<bool> usedR(n, false), usedG(n, false);
		for (int i = 0; i < n; i++)
		{
			cin >> red[0][i];
			cin >> red[1][i];
			if (red[0][i] == red[1][i] && red[0][i] > max)
			{
				max = red[0][i];
				index = i;
				first = RED;
			}
		}
		for (int i = 0; i < n; i++)
		{
			cin >> green[0][i];
			cin >> green[1][i];
			if (green[0][i] == green[1][i] && green[0][i] > max)
			{
				max = green[0][i];
				index = i;
				first = GREEN;
			}
		}
		if (first == RED)
			usedR[index] = true;
		else usedG[index] = true;
		result = NO;
		backtrack(usedR, usedG, max, max, first);	
		if (result == RED)
			printf("Only player Red can win\n");
		else if (result == GREEN)
			printf("Only player Green can win\n");
		else if (result == BOTH)
			printf("Both players can win\n");
		else
			printf("No players can win\n");
	}
}
