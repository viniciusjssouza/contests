/***********************************************************************************
 * UVa - 10041 - Vito's Family - Programming Challenges	 
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 09/08/2008
 ************************************************************************************/
#include <iostream>
#include <list>
#include <algorithm>

#define debug false

using namespace std;

int calculaMedia(list<int> &ruas);
int calculaDistancia(list<int> &ruas, int &n);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int nCasos = 0;
	
	cin >> nCasos;
	while (nCasos--)
	{
		int nRelatives = 0;
		list<int> ruas;
		cin >> nRelatives;
		
		int x =0;
		for(int i = 0; i < nRelatives; i++)
		{
			cin >> x;
			ruas.push_back(x);
		}
		
		/*
		if (nRelatives == 1) 
		{
			cout << "1\n";
			continue;
		}
		*/
		ruas.sort();
		
		int media = calculaMedia(ruas);
		int minimal = calculaDistancia(ruas, media);
		cout << minimal << endl;
	}
	return 0;
}

int calculaMedia(list<int> &ruas)
{
	list<int>::iterator ite = ruas.begin();
	int media = ruas.size() / 2;
	for (int i = 0; i < media; i++)
		ite++;
	
	return *ite;
}

int calculaDistancia(list<int> &ruas, int &n)
{
	int soma = 0;
	for (list<int>::iterator i = ruas.begin(); i != ruas.end(); i++)
	{
		int dist = n - *i;
		if (dist < 0) dist = -dist;
		soma += dist;
	}	
	return soma;
}