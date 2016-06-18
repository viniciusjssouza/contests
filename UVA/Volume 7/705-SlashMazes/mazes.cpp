/*
* UVA 705 - Slash Mazes - Programming Challenges
* Tecnicas: Transformações em grids - travessia de grafos com DFS
* Autor: Vinicius J. S. Souza
* Data: 26/02/2009
* Dica: transforme o grid nxm de barras em um grid 2*n x 2*m. O grafo está implícito. 
*/

#include<iostream>
#include<string>
#include<vector>
#include<deque>

using namespace std;

struct Pos
{
	int lin;
	int col;
};

bool finish = false;
int w, h, length, conta;
vector< vector<Pos> > parent;
vector< vector<bool> > processado;

void printGrafo(vector< vector<bool> > &g)
{
	for (int i = 0; i < g.size(); i++)
	{
		for (int k = 0; k < g[i].size(); k++)
			cout << g[i][k] << " " ;
		cout << endl;
	}
}

int getLength(Pos &start, Pos &end)
{
	if ((start.lin == end.lin && start.col == end.col) || start.lin < 0)
		return 0;
	return getLength(parent[start.lin][start.col], end) + 1;
}

void dfs(const vector< vector<bool> > &g, const int &lin, const int &col)
{
	processado[lin][col] = true;
	int hDouble = 2*h;
	int wDouble = 2*w;
	for (int i = -1; i < 2 && i+lin < hDouble; i++)
	{
		for (int k = -1; k < 2 && k+col < wDouble; k++)
		{
			if (finish) return;
			Pos pos;
			pos.lin = lin;
			pos.col = col;
			if (lin+i < 0 || k+col < 0) continue;
			if ((!k && !i) || g[lin+i][col+k]) continue;
			bool pLin = (lin % 2);
			bool pCol = (col % 2);
			bool ok = false;
			if (!k || !i) 
				ok = true;			
			else if (!pLin && !pCol)
			{
				if (i == 1 && k == 1)
				{
					if (col+1 < w && !g[lin][col+1])
						ok = true;		
				}
				else if (i == -1 && k == -1);
				else 
					ok = true;					
			}
			else if (!pLin && pCol)
			{		
				if (i == 1 && k == -1)
				{
		
			if (col && !g[lin][col-1])
						ok = true;		
				}
				else if (i == -1 && k == 1);
				else
					ok = true;										
			}
			else if (pLin && !pCol)
			{
				if (i == -1 && k == 1)
				{
					if (lin && !g[lin-1][col])
						ok = true;		
				}
				else if (i == 1 && k == -1);
				else
					ok = true;					
			}
			else if (pLin && pCol)
			{
				if (i == -1 && k == -1)
				{
					if (col && !g[lin][col-1])
						ok = true;			
				}
				else if (i == 1 && k == 1);
				else 
					ok = true;					
			}
			if (ok)
			{
				if (!processado[lin+i][col+k])
				{
					parent[i+lin][k+col] = pos;	
					dfs(g, i+lin, k+col);
				}
				else if (lin+i != parent[lin][col].lin || col+k != parent[lin][col].col) 		
				{
					Pos p = parent[lin+i][col+k];
					if (p.lin < 0 || p.col < 0 || p.lin != lin || p.col != col)
					{
						conta++;
						int l = getLength(pos, p);					
						if (l > length) 
							length = l;
						finish = true;
						return;		
					}
				}
			}
		}
	}			
}

int main()
{
	int n = 0;
	while (true)
	{
		n++;
		cin >> w >> h;
		if (!w && !h) break;
		int hDouble = 2 * h;
		int wDouble = 2 * w;
		vector< vector<bool> > grafo = vector< vector<bool> >(hDouble);		
		processado = vector< vector<bool> >(hDouble);		
		parent = vector< vector<Pos> >(hDouble);
		Pos p;
		p.lin = -1;
		p.col = -1;	
		conta = 0;
		length = 0;
		for (int i = 0; i < hDouble; i++)
		{
			grafo[i] = vector<bool>(wDouble, false);
			processado[i] = vector<bool>(wDouble, false);	
			parent[i] = vector<Pos>(wDouble, p);
		}
		char in;
		for (int i = 0; i < h; i++)
		{
			for (int k = 0; k < w; k++)	
			{
				cin >> in;
				int lin = 2 * i;
				int col = 2 * k;
				if (in == '/')
				{
					grafo[lin+1][col] = true;
					grafo[lin][col+1] = true;				
				}
				else
				{
					grafo[lin][col] = true;
					grafo[lin+1][col+1] = true;
				}
			}
		}
	
		if (w <= 1 || h <= 1)	
		{
			cout << "Maze #" << n << ":\n";
			cout << "There are no cycles.\n";
			cout << "\n";
			continue;
		}

		for (int i = 0; i < grafo.size(); i++)
		{
			for (int k = 0; k < grafo[i].size(); k++)
			{
				if (!processado[i][k] && !grafo[i][k])
				{
					parent = vector< vector<Pos> >(hDouble);
					for (int m = 0; m < hDouble; m++)
						parent[m] = vector<Pos>(wDouble, p);
					finish = false;				
					dfs(grafo, i, k);
				}
			}
		}

		cout << "Maze #" << n << ":\n";
		if (conta)
			cout << conta << " Cycles; the longest has length " << length << ".\n";	
		else
			cout << "There are no cycles.\n";
		cout << "\n";
			
	}
	return 0;
}
