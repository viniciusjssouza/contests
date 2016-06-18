#include<iostream>
#include<map>
#include<set>
#include<deque>
#include<string>
#include<queue>
#include<vector>
#include<sstream>
#include<cmath>
#include<algorithm>

// constante que define as dimensoes do tabuleiro
#define MAX 4
// coeficientes da formula heuristica: f(x) = M * Manhatan(x) + W * Accumulated;
#define M  1
#define W  3

using namespace std;

// estrutura que define um configuracao do tabuleiro
struct Config
{
	int grid[MAX][MAX];
	string id;	
	int posX;
	int posY;
	int distance;
	int accumulated;
	string steps;
};

//distancia manhataniana de uma configuracao
int getManhatanDistance(int grid[MAX][MAX])
{
	int distance = 0;
	int posX,posY;
	for (int i = 0; i < MAX; i++)
	{
		for (int k = 0; k < MAX; k++)
		{
			int row = 3;
			int col = 3; 
			if (grid[i][k])
			{
				row = (grid[i][k] - 1) / MAX;
				col = (grid[i][k] -1) % 4;
				distance += (abs(row - i) + abs(col - k));			
			}			
/*			else
			{
				posX = col;
				posY = row;
			}
*/

		}
	}
//	if (!distance) distance = (abs(MAX-1 - posX) + abs(MAX-1 - posY));  
	return distance;
}

// funcao que compara configuracoes para a ordenacao de um set
struct Compare
{
  bool operator()(Config s1, Config s2) 
  {
    return (s1.distance <= s2.distance);
  }
};

// transforma um tabuleiro em string para ser utilizado como chave no hash map
string arrayToString(int grid[MAX][MAX])
{
	stringstream buffer;
	for (int i  =0; i < MAX; i++)
		for (int k = 0; k < MAX; k++)
			buffer << grid[i][k];						
	return buffer.str();
}

// verifica se uma dada configuracao possui solucao
bool temSolucao(int grid[MAX][MAX])
{
	int soma = 0;
	int row = 0;
	int limit = MAX * MAX + 1;
	vector<bool> vet(limit, false);
	for (int i = 0; i < MAX; i++)
	{
		for (int k = 0; k < MAX; k++)
		{
			if (!grid[i][k])
				row = i+1;
			else if (grid[i][k] == 1) vet[1] = true;
			else
			{
				for (int m = 1;  m < grid[i][k]; m++)
					if (!vet[m])
						soma++;
				vet[grid[i][k]] = true;
				//cout << "Soma:" << soma << endl;		
			}			
		}
	}
	if (!((soma + row) & 1)) return true;
	return false;
}

void copyArray(int a[MAX][MAX], int b[MAX][MAX])
{
	for (int i = 0; i < MAX; i++)
		for (int k = 0; k < MAX; k++)
			b[i][k] = a[i][k];
}

void printGrid(int a[MAX][MAX])
{
	for (int i = 0; i < MAX; i++)
	{
		for (int k = 0; k < MAX; k++)
		{
			cout << a[i][k] << ' ';
		}
		cout << endl;
	}
}

int main()
{
	long s = clock();
	int a[MAX][MAX];
	int n;
	cin >> n;
	while (n--)
	{
		int x0, y0;
		// realiza a entrada dos dados e obtem a posicao vazia (0)
		for (int i= 0; i < MAX; i++)
		{
			for (int k = 0; k < MAX; k++)
			{
				cin >> a[i][k];
				if (!a[i][k]) 
				{
					x0 = k;
					y0 = i;
				}
			}
		}
		string resposta="";
		
		set<Config, Compare> sorter; 
		map<string, bool> closedSet;
		map<string, int> openSet;
		
		if (!temSolucao(a))
		{
			cout << "This puzzle is not solvable.\n";
			continue;
		}
		
		Config conf;
		conf.accumulated = getManhatanDistance(a);	
		copyArray(a, conf.grid);
		conf.distance = M * conf.accumulated + W * conf.accumulated;
		conf.steps = "";
		conf.posX = x0;
		conf.posY = y0;
		conf.id = arrayToString(conf.grid);
		openSet[conf.id] = true;		
		sorter.insert(conf);		

		int conta = 0;			
		while (sorter.size())
		{			
			Config right, up, left, down;
			Config config = *sorter.begin();
/*			
			cout << config.steps << endl; 
			cout << config.distance << endl;
			printGrid(config.grid);
			cout << endl;
*/			
			if (closedSet[config.id] || config.steps.size() > 49) 
			{
				sorter.erase(sorter.begin());
				continue;
			}
			x0 = config.posX;
			y0 = config.posY;
			closedSet[config.id] = true;
			openSet[config.id] = 0;
			
			if (x0+1 < MAX) 
			{
				copyArray(config.grid, right.grid);
				swap(right.grid[y0][x0], right.grid[y0][x0+1]);
				int mDist = getManhatanDistance(right.grid);
				right.id = arrayToString(right.grid);
				if (!mDist) 
				{
					resposta = config.steps + "R";
					break;
				}
				else if (!closedSet[right.id] && temSolucao(right.grid))
				{
					right.accumulated = config.accumulated + mDist;
					right.distance = M * mDist + W * right.accumulated;
					right.posX = x0+1;
					right.posY = y0;				
					right.steps = config.steps + "R";

					if (openSet[right.id])
					{
						if (right.distance < openSet[right.id])
						{
							openSet[right.id] = right.distance;
							sorter.insert(right);				
						}
					}
					else 
					{
						openSet[right.id] = right.distance;
						sorter.insert(right);
					}
//					cout << "Inserindo R   "  << arrayToString(right.grid) << endl;
				}
			}

			if (y0-1 >= 0) 
			{
				copyArray(config.grid, up.grid);
				swap(up.grid[y0][x0], up.grid[y0-1][x0]);
				int mDist = getManhatanDistance(up.grid);
				up.id = arrayToString(up.grid);
				if (!mDist) 
				{
					resposta = config.steps + "U";
					break;
				}
				else if (!closedSet[up.id] && temSolucao(up.grid))
				{
					up.accumulated = config.accumulated + mDist;
					up.distance = M * mDist + W * up.accumulated;
					up.posX = x0;
					up.posY = y0-1;				
					up.steps = config.steps + "U";

					if (openSet[up.id])
					{
						if (up.distance < openSet[up.id])
						{
							openSet[up.id] = up.distance;
							sorter.insert(up);				
						}
					}
					else 
					{
						openSet[up.id] = up.distance;
						sorter.insert(up);
					}
//					cout << "Inserindo U  "  << arrayToString(up.grid) << endl;
				}
			}
		
			if (x0-1 >= 0) 
			{
				copyArray(config.grid, left.grid);
				swap(left.grid[y0][x0], left.grid[y0][x0-1]);
				int mDist = getManhatanDistance(left.grid);
				left.id = arrayToString(left.grid);
				if (!mDist) 
				{
					resposta = config.steps + "L";
					break;
				}
				else if (!closedSet[left.id] && temSolucao(left.grid))
				{
					left.accumulated = config.accumulated + mDist;
					left.distance = M * mDist + W * left.accumulated;
					left.posX = x0-1;
					left.posY = y0;				
					left.steps = config.steps + "L";

					if (openSet[left.id])
					{
						if (left.distance < openSet[left.id])
						{
							openSet[left.id] = left.distance;
							sorter.insert(left);				
						}
					}
					else 
					{
						openSet[left.id] = left.distance;
						sorter.insert(left);
					}
//					cout << "Inserindo L   "  << arrayToString(left.grid) << endl;
				}
			}

			if (y0+1 < MAX) 
			{
				copyArray(config.grid, down.grid);
				swap(down.grid[y0][x0], down.grid[y0+1][x0]);
				int mDist = getManhatanDistance(down.grid);
				down.id = arrayToString(down.grid);
				if (!mDist) 
				{
					resposta = config.steps + "D";
					break;
				}
				else if (!closedSet[down.id] && temSolucao(down.grid))
				{
					down.accumulated = config.accumulated + mDist;
					down.distance = M * mDist + W * down.accumulated;
					down.posX = x0;
					down.posY = y0+1;				
					down.steps = config.steps + "D";

					if (openSet[down.id])
					{
						if (down.distance < openSet[down.id])
						{
							openSet[down.id] = down.distance;
							sorter.insert(down);				
						}
					}
					else 
					{
						openSet[down.id] = down.distance;
						sorter.insert(down);
					}
//					cout << "Inserindo D   "  << arrayToString(down.grid) << endl;
				}
			}
//			conta++;
			sorter.erase(sorter.begin());	
		}
		if (!sorter.size())
			cout << "This puzzle is not solvable.\n";
		else
			cout << resposta << endl;
	}
	cout << (double)(clock()-s) / (double)CLOCKS_PER_SEC << endl;
	return 0;
}
