/*
* UVA 10099 - Tourist Guide - Programming Challenges
* Tecnicas: Conectividade em grafos - variacao do algoritmo de Floyd-Warshall 
* Autor: Vinicius J. S. Souza
* Data: 28/02/2009
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

#define MAXINT 1000000

using namespace std;

int n, r;

void floyd(vector< vector<int> > &grafo)
{
	for (int k=0; k < n; k++)
	{	
		for (int i=0; i < n; i++)
		{
			for (int j=0; j < n; j++) 
	    		{
				int through_k = min(grafo[i][k], grafo[k][j]);
		        	if (through_k > grafo[i][j])
		                	grafo[i][j] = through_k;
		     	}
		}
	}
}

int main()
{
	int scenario = 0;
	while (1)
	{
		scenario++;
		cin >> n >> r;
		if (!n && !r) break;
		vector< vector<int> > grafo = vector< vector<int> >(n, vector<int>(n, -1));
		int c1, c2, p;
		for (int i = 0; i < r; i++)
		{
			cin >> c1 >> c2 >> p;
			grafo[c1-1][c2-1] = p;
			grafo[c2-1][c1-1] = p;
		}
		cin >> c1 >> c2 >> p;
		
		floyd(grafo);

		int min = grafo[c1-1][c2-1] - 1;
		//cout << "min: " << min << endl;
		int result = (int)ceil((double)p / (double)min);
		cout << "Scenario #" << scenario << endl;
		cout << "Minimum Number of Trips = " << result << "\n\n";						
	}
}

