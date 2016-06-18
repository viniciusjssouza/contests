/****************************************************************************
* UVA 10278 - Programming Challenges - Fire Stations
*
* Autor: Vinicius J. S. Souza
* Data: 16/05/2009
* Tecnicas utilizadas: grafos + algoritmo de Floyd-Warshall
****************************************************************************/

#include<iostream>
#include<deque>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

#define MAX 1000000000

using namespace std;

int nFS, nIS;

void floyd(vector< vector<int> > &grafo, vector<int> &dist, const vector<bool> &isFS)
{
	for (int k=1; k < grafo.size(); k++)
	{
		for (int i=1; i < grafo.size(); i++)
		{	
             		for (int j=1; j < grafo.size(); j++) 
			{
                   		int through_k = grafo[i][k]+grafo[k][j];
                   		if (through_k < grafo[i][j])
                           		grafo[i][j] = through_k;
				if (isFS[j] && !isFS[i] && grafo[i][j] < dist[i])
					dist[i] = grafo[i][j]; 
			}
             	}
	}
}

int findLocation(const vector< vector<int> > &grafo, const vector<int> &fs, const vector<bool> &isFS, const vector<int> &dist)
{
	int max = MAX;
	int index = 1;
	for (int i = 1; i < grafo.size(); i++)
	{
		if (isFS[i]) continue;
		int stepMax = -1;
		for (int k = 1; k < grafo.size(); k++)
		{
			int foo = min(grafo[i][k], dist[k]);
			if (!isFS[k] && foo > stepMax)
				stepMax = foo;	
		}
		if (stepMax < max)
		{
			index = i;	
			max = stepMax;
		}
	}
	return index;
}

int main()
{
	int nTest;
	cin >> nTest;
	bool isInicio = true;
	while (nTest--)
	{
		if (!isInicio)
			putchar('\n');
		else
			isInicio = false;			
		cin >> nFS >> nIS;
		nIS++;
		vector<int> fireStations(nFS);
		vector<bool> isFS(nIS, false);
		for (int i = 0; i < fireStations.size(); i++)
		{
			cin >> fireStations[i];		
			isFS[fireStations[i]] = true;
		}
		vector< vector<int> > grafo(nIS, vector<int>(nIS, MAX));
		for (int i = 1; i < grafo.size(); i++)
			grafo[i][i] = 0;
		getchar();
		string line;	
		while (getline(cin, line) && line != "")
		{
			stringstream buffer(line);
			int a, b, w;
			buffer >> a >> b >> w;
			grafo[a][b] = w;
			grafo[b][a] = w;
		}
		vector<int> dist(grafo.size(), MAX);
		floyd(grafo, dist, isFS);
/*
		for (int i =0; i < grafo.size(); i++)
		{
			for (int k = 0; k < grafo.size(); k++)
			{
				cout << grafo[i][k] << ' ';
			}
			cout << endl;
		}
*/
		cout << findLocation(grafo, fireStations, isFS, dist) << endl;		  		
	}
	return 0;
}
