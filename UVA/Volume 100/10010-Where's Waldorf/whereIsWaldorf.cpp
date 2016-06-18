/********************************************************************
 * Problema 10010 - Where is Waldorf? - Livro Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 10/07/2008
 ********************************************************************/
#include <iostream>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

#define  NORTE		0
#define	 NOROESTE	1
#define	 OESTE		2
#define  NORDESTE	3
#define	 LESTE		4
#define	 SUDOESTE	5
#define	 SUL		6
#define	 SUDESTE	7

void findWord(vector<string> grid, const string &word, int &x, int &y);
bool montaPalavra(vector<string> grid, const string &word, const int &dir, const int &i, const int &k);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int numCases = 0;
	cin >> numCases;
	bool isInicio = true;
	
	for (int n = 0; n < numCases; n++)
	{
		if (!isInicio)
			cout << endl;
		else
			isInicio = false;
		int lin, col;
		cin >> lin; cin >> col;
		getchar();
		string line;
		vector<string> grid;
		for (int i = 0; i < lin; i++)
		{
			getline(cin, line);
			for (int k = 0; k < line.size(); k++)
				line[k] = tolower(line[k]);
			//cout << line << endl;
			grid.push_back(line);
		}		
		int numWords = 0;
		cin >> numWords;
		getchar();
		//cout << numWords << endl;
		for (int i = 0; i < numWords; i++)
		{
			getline(cin, line);
			for (int k = 0; k < line.size(); k++)
				line[k] = tolower(line[k]);
			//cout << line << endl;
			int x, y;
			findWord(grid, line, x, y);
			cout << x+1 << " " << y+1 << endl;
		}
	}
	return 0;
}

void findWord(vector<string> grid, const string &word, int &x, int &y)
{
	int maxx = grid[0].size()-1;
	int maxy = grid.size()-1;
		
	for (int i = 0; i <= maxy; i++)
	{
		for (int k = 0; k <= maxx; k++)
		{
			for (int direcao = 0; direcao < 8; direcao++)
			{
				if (montaPalavra(grid, word, direcao, i, k))
				{
					x = i;
					y = k;
					return;
				}
			}
		}
	}
}

bool montaPalavra(vector<string> grid, const string &word, const int &dir, const int &i, const int &k)
{
	if (grid[i][k] != word[0]) return false;
	
	int maxx = grid[0].size()-1;
	int maxy = grid.size()-1;
	int size = word.size();
	
	if (dir == LESTE)
	{
		if (k + size - 1 > maxx) return false;
		for (int m = 1; m < size; m++)
		{
			if (grid[i][k+m] != word[m]) return false;
		}
		return true;
	}	
	else if (dir == NORDESTE)
	{
		if (k + size - 1 > maxx || i - (size-1) < 0) return false;
		for (int m = 1; m < size; m++)
			if (grid[i-m][k+m] != word[m]) return false;
		return true;
	}
	else if (dir == NORTE)
	{
		if (i - (size-1) < 0) 
			return false;
		for (int m = 1; m < size; m++)
		{
			if (grid[i-m][k] != word[m]) return false;
		}
		return true;
	}
	else if (dir == NOROESTE)
	{
		if (i - (size - 1) < 0 || k - (size-1) < 0) return false;
		for (int m = 1; m < size; m++)
			if (grid[i-m][k-m] != word[m]) return false;
		return true;
	}
	else if (dir == OESTE)
	{
		if (k - (size -1) < 0) return false;
		for (int m = 1; m < size; m++)
			if (grid[i][k-m] != word[m]) return false;
		return true;
	}
	else if (dir == SUDOESTE)
	{
		if (k - (size-1) < 0 || i + (size-1) > maxy) return false;
		for (int m = 1; m < size; m++)
			if (grid[i+m][k-m] != word[m]) return false;
		return true;
	}
	else if (dir == SUL)
	{
		if (i + (size - 1) > maxy) return false;
		for (int m = 1; m < size; m++)
			if (grid[i+m][k] != word[m]) return false;
		return true;				
	}
	else if (dir == SUDESTE)
	{
		if (i + (size-1) > maxy || k + (size-1) > maxx) return false;
		for (int m = 1; m < size; m++)
			if (grid[i+m][k+m] != word[m]) return false;
		return true;
	}
	return false;
}