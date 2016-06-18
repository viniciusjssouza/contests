/*******************************************************************
* UVA 10034 - Freckles - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data: 12/04/2009
* Tecnicas utilizadas: grafo + minimum spanning tree (algoritmo de prim)
********************************************************************/


#include<iostream>
#include<deque>
#include<cmath>

#define MAX 1000000.0

using namespace std;

int n;

struct Aresta
{
	float weight;
	int v;
};

float calculaDistancia(const pair<float, float> &p1, const pair<float, float> &p2)
{
	return sqrt( (p1.first - p2.first) * (p1.first - p2.first) +
		 (p1.second - p2.second) * (p1.second - p2.second));
}

float prim(deque<deque<Aresta> > &grafo, int start)
{
	deque<int> parent(n, -1);
	deque<bool> intree(n, false);
	deque<float> distance(n, MAX);
	int v;
	int w;
	float weight;
	float dist;
	
	distance[start] = 0.0;
	v = start;
	int end = start;
	float totalLength = 0.0;	
	while (intree[v] == false) 
	{
		intree[v] = true;
		end = v;
		bool updated = false;
    		for (int i=0; i < grafo[v].size(); i++) 
		{
			w = grafo[v][i].v;
         		weight = grafo[v][i].weight;
         		if ((distance[w] > weight) && (intree[w]==false)) 
			{
				distance[w] = weight;
                 		parent[w] = v;
         		}
    		}
	    	dist = MAX;
		v=0;
		for (int i=0; i < grafo.size(); i++)
		{
			if ((intree[i]==false) && (distance[i] < dist)) 
			{
				updated = true;
				dist = distance[i];
				v = i;
			}
		}	
		if (updated)
			totalLength += dist;

	}
	return totalLength;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	while (nTest--)
	{
		float x,y;
		scanf("%d", &n);
		deque< pair<float, float> > data;
		deque< deque<Aresta> > grafo(n);
		for (int i = 0; i < n; i++)
		{
			pair<float, float> par;
			scanf("%f %f", &par.first, &par.second);
			data.push_back(par);
			for (int k = data.size()-2; k >= 0; k--)
			{
				Aresta a,b;
				a.weight = b.weight = calculaDistancia(par, data[k]);
				a.v = k;
				b.v = i;
				grafo[i].push_back(a);			
				grafo[k].push_back(b);
			}
		}
		printf("%.2f\n", prim(grafo, 0));		
		if (nTest >= 1) putchar('\n');
	}	
	return 0;
}

