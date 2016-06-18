/****************************************************************
* UVA 10199 - Tourist Guide - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data : 07/06/2009
* Tecnicas utilizadas: teoria de grafos conexos (pontes) + bfs
**************************************************************/

#include<iostream>
#include<deque>
#include<map>
#include<string>
#include<set>

using namespace std;

void bfs(map<string, deque<string> > &grafo, deque<string> &cities, map<string, bool> &antes, 
	map<string, bool> &depois, string &city)
{
	deque<string> filaAntes;
	deque<string> filaDepois;	
	if (!grafo[city].size())
		return;
	
	filaAntes.push_back(grafo[city][0]);
	filaDepois.push_back(grafo[city][0]);

	antes[grafo[city][0]] = true;
	depois[grafo[city][0]] = true;

	while (filaAntes.size() || filaDepois.size())
	{
		string vAntes, vDepois;
		if (filaAntes.size())
		{
			vAntes = filaAntes.front();
			filaAntes.pop_front();
		}
		if (filaDepois.size())
		{
			vDepois = filaDepois.front();
			filaDepois.pop_front();
		}
		for (int i = 0; i < grafo[vAntes].size(); i++)
		{
			string w = grafo[vAntes][i];
			if (!antes[w])
			{
				antes[w] = true;
				filaAntes.push_back(w);
			}
		}
		for (int i = 0; i < grafo[vDepois].size(); i++)
		{
			string w = grafo[vDepois][i];
			if (!depois[w] && w != city)
			{
				depois[w] = true;
				filaDepois.push_back(w);
			}
		}
	}
}
		

int main()
{
	int n;
	int testCase = 1;
	bool isInicio = true;
	while(true)
	{
		cin >> n;
		if (!n) break;
		if (isInicio)
			isInicio = false;
		else putchar('\n');
		map<string, deque<string> > grafo;
		deque<string> cities(n);
		
		for (int i = 0; i < cities.size(); i++)
			cin >> cities[i];
		int nLig;
		cin >> nLig;
		for (int i = 0; i < nLig; i++)
		{
			string x, y;
			cin >> x >> y;
			grafo[x].push_back(y);
			grafo[y].push_back(x);
		}
		set<string> locations;
		int nCam = 0;
		
		for (int i = 0; i < cities.size(); i++)
		{
			map<string, bool> processado1;
			map<string, bool> processado2;
			bfs(grafo, cities, processado1, processado2, cities[i]);  				
			bool isConnect = true;
			for (int k = 0; k < cities.size(); k++)
				if (i != k && processado1[cities[k]] != processado2[cities[k]])
				{
					isConnect = false;
					break;	
				}
			if (!isConnect)
			{
				nCam++;
				locations.insert(cities[i]);
			}
		}

		cout << "City map #" << testCase << ": " << nCam << " camera(s) found\n";
		for (set<string>::iterator i = locations.begin(); i != locations.end(); i++)
			cout << (*i) << endl;
		testCase++;		
	}
	return 0;
}
