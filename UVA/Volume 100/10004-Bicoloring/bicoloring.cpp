/*
* UVA 10004 - Bicoloring - Programming Challenges
* Tecnicas: Travessia de Grafos - BFS
* Autor: Vinicius J. S. Souza 
*/
#include<iostream>
#include<deque>
#include<vector>

#define RED 1
#define BLACK -1

using namespace std;

struct Aresta
{
   int lig;
   int peso;         
};
   
class Grafo
{
public:
    vector< deque<int> > arestas;
    int nVertices;    
    vector<int> parent;   
    vector<int> colored;    


    Grafo(int n)
    {
        nVertices = n;
        arestas = vector< deque<int> >(n);
	parent = vector<int>(n, -1);
	colored = vector<int>(n, false);
        for (register int i = 0; i < n; i++)
            arestas[i] = deque<int>();            
    }

    	/* Para descobrir se o grafo pode ser bicolorido,
	  utiliza-se a  busca em largura (BFS) para colorir.*/
    	bool isBicolorable(const int &v)
	{		
		deque<int> fila;
		colored[v] = RED;
		fila.push_back(v);
	
		while (fila.size())
		{
			register int vertice = fila[0];
			fila.erase(fila.begin());
			for (register int i = 0; i < arestas[vertice].size(); i++)
			{
				if (!colored[arestas[vertice][i]])
				{
					colored[arestas[vertice][i]] = -colored[vertice];
					parent[arestas[vertice][i]] = vertice;
					fila.push_back(arestas[vertice][i]);
				}
				else if (parent[vertice] != arestas[vertice][i] && 
					colored[arestas[vertice][i]] == colored[vertice])
					return false;				
			}
		}
		return true;		
	}			
};

int main()
{
	while (1)
	{
		register int nVertices, nArestas;
		cin >> nVertices;
		if (!nVertices) break;
		cin >> nArestas;
		Grafo grafo(nVertices);
		register int start = -1;
		for (register int i = 0; i < nArestas; i++)
		{
			register int v1, v2;
			cin >> v1 >> v2;
			if (start < 0) start = v1;
			grafo.arestas[v1].push_back(v2);
			grafo.arestas[v2].push_back(v1);					
		}
		if (!grafo.isBicolorable(start))
			cout << "NOT BICOLORABLE.\n";
		else 
			cout << "BICOLORABLE.\n";
	}
	return 0;
}
