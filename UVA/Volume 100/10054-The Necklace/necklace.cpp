/******************************************************************
* UVA 10054 - The Necklace - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 03/05/2009 
* Tecnicas utilizadas: Grafos + algoritmo de ciclo euleriano
******************************************************************/
#include<iostream>
#include<list>
#include<map>
#include<vector>
#include<set>
#include<deque>

using namespace std;

int n;
set<int> cores; 

void dfs(map<int, list<int> > &grafo, map<int, bool> &discovered, int v)
{
	discovered[v] = true;
	for (list<int>::iterator i = grafo[v].begin(); i != grafo[v].end(); i++)
	{
		int y = *i;
		if (!discovered[y]) 
			dfs(grafo, discovered, y);
	}
}

bool isConnected(map<int, list<int> > &grafo)
{
	map<int, bool> descoberto;
	
	dfs(grafo, descoberto, (*cores.begin()));

	for (set<int>::iterator ite = cores.begin(); ite != cores.end(); ite++)
		if (!descoberto[*ite])
			return false;
	return true;
}

bool even(map<int, list<int> > &grafo, int begin)
{
	for (set<int>::iterator ite = cores.begin(); ite != cores.end(); ite++)
	{
		int degree = grafo[*ite].size();
		if (degree % 2)
			return false;
	}
	return true;
}

void getEulerianCycle(map<int, list<int> > &grafo, deque<int> &path, int v)
{
	if (!grafo[v].size())
		path.push_front(v);
	else
	{
		for (list<int>::iterator ite = grafo[v].begin(); ite != grafo[v].end(); ite++)
		{
			int color = *ite;
			list<int>::iterator aux = ite;
			ite--;
			grafo[v].erase(aux);			
			for (list<int>::iterator ite2 = grafo[color].begin(); ite2 != grafo[color].end(); ite2++)
			{
				if (*ite2 == v)
				{
					grafo[color].erase(ite2);
					break;
				}
			}			
			getEulerianCycle(grafo, path, color);
		}
		path.push_front(v);
	}
}

int main()
{
	int nTest;
	cin >> nTest;
	for (int caso = 1; caso <= nTest; caso++)
	{
		for (set<int>::iterator ite = cores.begin(); ite != cores.end(); ite++)
			cout <<"Cores: " << *ite << endl;
		cin >> n;
		map<int, list<int> > grafo;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			grafo[x].push_back(y);
			grafo[y].push_back(x);
			cores.insert(x);
			cores.insert(y);
		}

		int begin = *cores.begin();

		printf("Case #%d\n", caso);
		if (isConnected(grafo) && even(grafo, begin))
		{
			deque<int> path;
			getEulerianCycle(grafo, path, begin);
			for (int k = 1; k < path.size(); k++)
				printf("%d %d\n", path[k-1], path[k]);			
		}
		else cout << "some beads may be lost\n";
		putchar('\n');
		cores.clear();
	}
	return 0;
}
