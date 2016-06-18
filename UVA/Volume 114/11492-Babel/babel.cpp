/**********************************************************************************
* UVA 10492 - Babel - Maratona de Programacao 2008 - Regional
*
* Autor: Vinicius J. S. Souza
* Data: 05/08/2009
* Tecnicas utilizadas: algoritmo de dijkstra
**********************************************************************************/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<deque>

#define MAX 9999999

using namespace std;

set<string> idiomas;

struct Edge
{
	int peso;
	int distancia;
	char fchar;
	string lig;
};

struct EdgeCompare
{
	bool operator()(const Edge &e1, const Edge &e2)
	{
		if (e1.distancia < e2.distancia)
			return true;
		else
			return false;
	}
};

int dijkistra(map<string, vector<Edge> > &grafo, string &origem, string &destino)
{
	multiset<Edge,EdgeCompare> fila;
	map<string, int> dist;
	map<string, bool> intree;
	int minimo = MAX;
	for (set<string>::iterator ite = idiomas.begin(); ite != idiomas.end(); ite++)
		dist[*ite]= MAX;	
	dist[origem] = 0;

	Edge init;
	init.peso = init.distancia = 0;	
	init.fchar = '!';
	init.lig = origem;
	fila.insert(init);
	intree[origem] = true;
	while (!fila.empty())
	{
		Edge edge = *fila.begin();
		fila.erase(fila.begin());		
		string v = edge.lig;
		//cout << "Vertice: " << v << endl;
		for (int i = 0; i < grafo[v].size(); i++)
		{
			Edge newEdge;
			string v2 = newEdge.lig = grafo[v][i].lig;
			newEdge.distancia = edge.distancia + grafo[v][i].peso;
			newEdge.peso = grafo[v][i].peso;
			newEdge.fchar = grafo[v][i].fchar;
			int contaChar = 0, contaIntree = 0;
			
			//cout << "Aresta: " << v2 << endl;			

			for (int k = 0; k < grafo[v2].size(); k++)
			{
				if (grafo[grafo[v2][k].lig].size() == 1 && grafo[v2][k].fchar == newEdge.fchar &&
						grafo[v2][k].lig != v)	
					contaChar++;
				if (!intree[grafo[v2][k].lig])
					contaIntree++;
				if (contaChar > 1 || contaIntree > 1)
					break;				
			}

			if (contaChar == 1 && contaIntree == 1)
				continue;
			if (newEdge.distancia < minimo && edge.fchar != newEdge.fchar
				&& dist[newEdge.lig] > dist[v]+newEdge.peso)
			{
				if (newEdge.lig == destino)
				{
					if (newEdge.distancia < minimo)
						minimo = newEdge.distancia;
					continue;
				}
				dist[newEdge.lig] = dist[v]+newEdge.peso;
				fila.insert(newEdge);
				intree[v2] = true;
			}			
		}
	}
	return minimo;
}

void printGrafo(map<string, vector<Edge> > &grafo)
{
	for (set<string>::iterator ite = idiomas.begin(); ite != idiomas.end(); ite++)
	{
		printf("Vertice %s\n", (*ite).c_str()); 
		for (int i = 0; i < grafo[*ite].size(); i++)
		{
			printf("%s - %d - %c\n", grafo[*ite][i].lig.c_str(), grafo[*ite][i].peso, 
				grafo[*ite][i].fchar); 
		}
		putchar('\n');
	}
}

int main()
{
	int n;
	long start = clock();
	while (true)
	{
		scanf("%d", &n);
		if (!n) 
			break;
		string origem, destino;
		cin >> origem >> destino;
		idiomas.insert(origem);
		idiomas.insert(destino);
		map<string, vector<Edge> > grafo;

		for (int i = 0; i < n; i++)
		{
			Edge e1, e2;
			string a,b, pal;
			cin >> a >> b >> pal;
			idiomas.insert(a);
			idiomas.insert(b);
			e1.fchar = e2.fchar = pal[0];
			e1.peso = e2.peso = pal.size();
			e1.lig = b;
			e2.lig = a;
			grafo[a].push_back(e1);
			grafo[b].push_back(e2);	
		}
		
		//printGrafo(grafo);
		int result =  dijkistra(grafo, origem, destino);
		if (result != MAX)
			printf("%d\n", result);
		else
			printf("impossivel\n");
		idiomas.clear();
	}
	//cout << ((float)(clock()-start)/(float)800000) << endl;
	return 0;
}
