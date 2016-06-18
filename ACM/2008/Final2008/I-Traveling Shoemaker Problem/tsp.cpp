/*********************************************************************
* Traveling Shoemaker Problem - Final sul-americana 2008
*
* Autor: Vinicius J. S. Souza
* Data: 27/08/2009
* Tecnicas: grafos... caminho euleriano, bfs.
************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include<deque>
#include<set>

using namespace std;

typedef pair<int, int> pii;
typedef  vector< list<pii> > Grafo;

int n, m;
vector<bool> discovered;
int result;

void getEulerianPath(Grafo &grafo, deque<int> &path, int v)
{
	if (!grafo[v].size())
		path.push_front(v);
	else
	{
		for (list<pii>::iterator ite = grafo[v].begin(); ite != grafo[v].end(); ite++)
		{
			int v2 = (*ite).second;
			list<pii>::iterator aux = ite;
			ite--;
			grafo[v].erase(aux);			
			for (list<pii>::iterator ite2 = grafo[v2].begin(); ite2 != grafo[v2].end(); ite2++)
			{
				if ((*ite2).second == v)
				{
					grafo[v2].erase(ite2);
					break;
				}
			}
			getEulerianPath(grafo, path, v2);
		}
		path.push_front(v);
	}
}

bool isConnected(Grafo &g, int start, int e)
{
	discovered = vector<bool>(m, false);
	deque<int> fila;
	fila.push_back(start);
	int missing = m-1;
	discovered[start] = true;
	while (!fila.empty())
	{
		int v = fila.front();
		fila.pop_front();
		for (list<pii>::iterator i = g[v].begin(); i != g[v].end(); i++)
			if (!discovered[(*i).second] && (*i).second != e)
			{
				discovered[(*i).second] = true;
				missing--;
				if (!missing)
					return true;
				fila.push_back((*i).second);				
			}
	}
	if (!missing)
		return true;
	return false;
}

bool hasEulerianPath(Grafo &g, int &sv1, int &sv2)
{
	int start = 0;
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i].size())
		{
			start = i;
			break;
		}
	}
	isConnected(g, start, -1);
	int count= 0;
	for (int i = 0; i < m; i++)
	{
		if (!discovered[i] && g[i].size())
			return false;
		else if (!discovered[i] && !g[i].size())
			continue;
		else if (g[i].size() % 2)
		{
			if (!count)
				sv1 = i;
			else if (count == 1)
				sv2 = i;
			count++;
			if (count > 2)								
				return false;
		}
	}
	if (!count)
	{
		sv2 = sv1 = -1;
		return true;
	}
	return (count == 2);			
}

int main()
{
	while(true)
	{
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		Grafo g(m, list<pii>());
		vector<pii> conf(n, pii(-1,-1));
		for (int i = 0; i < m; i++)
		{
			int p;
			scanf("%d", &p);
			for (int k = 0; k < p; k++)
			{
				int x;
				scanf("%d", &x);
				if (conf[x].first < 0)
					conf[x].first = conf[x].second = i;
				else
					conf[x].second = i;
			}			
		}
		for (int i = 0; i < n; i++)
		{
			pii par = conf[i];
			g[par.first].push_back(pii(i, par.second));
			g[par.second].push_back(pii(i, par.first));
		}
		if (n == 1)
		{
			printf("0\n");
			continue;
		}
		for (int i = 0; i < m; i++)
			g[i].sort();
		int sv1, sv2;
		if (! hasEulerianPath(g, sv1, sv2) )
			printf("-1\n");
		else 
		{
			if (sv1 == sv2 && sv1 < 0)
				printf("0\n");
			else
			{
				deque<int> path;
				getEulerianPath(g, path, sv1);
				set<pii> vp;
				vp.insert( pii(path[path.size()-1], path[path.size()-2]));
				vp.insert( pii(path[path.size()-2], path[path.size()-1]));
				vp.insert( pii(path[0], path[1]));
				vp.insert( pii(path[1], path[0]));
				for (int i = 1; i < path.size()-1; i++)
				{
					if (path[i] == sv1) 
					{
						vp.insert(pii(path[i], path[i-1]));	
						vp.insert(pii(path[i-1], path[i]));	
					}
					else if (path[i] == sv2) 
					{
						vp.insert(pii(path[i], path[i+1]));	
						vp.insert(pii(path[i+1], path[i]));	
					}
				}
				for (int i = 0; i < conf.size(); i++)
				{
					bool end= false;
					for (set<pii>::iterator ite = vp.begin(); ite != vp.end(); ite++)
					{
						if ((*ite) == conf[i])
						{
							printf("%d\n", i);
							end = true;
							break;		
						}
					}
					if (end)
						break;
				}
			}
		}
	}
}
