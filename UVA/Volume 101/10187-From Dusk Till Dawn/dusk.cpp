/**********************************************************************************
* UVA 10187 - From Dusk Till Dawn - Programming Challenges
*
* Autor: Vinicius J. S. Souza
* Data:  03/04/2009
* Tecnicas utilizadas: grafos + busca em largura(bfs)
**********************************************************************************/

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<deque>

#define MAX 1000000000

using namespace std;

struct Viagem
{
	string destino;
	int partida;
	int chegada;
};

class Aresta
{
public:
	string city;
	int bloodCount;
	int chegada;		
	
	Aresta(string c, int bc, int ch)
	{
		city = c;
		bloodCount = bc;
		chegada = ch;
	}
};

int bfs(map<string, vector<Viagem> > &g, const string &origem, const string &destino)
{
	deque<Aresta > fila;
	Aresta a(origem, 0, 0);
	fila.push_back(a);

	int min = MAX, last;
	register bool isInit= true;
	while (fila.size())
	{
		Aresta current = fila.front();
		fila.pop_front();
		if (current.bloodCount > min)
			continue;
		if (current.city == destino)
		{
			if (current.bloodCount < min)
				min = current.bloodCount;
			continue;
		}
		for (int i = 0; i < g[current.city].size(); i++)
		{			
			Viagem v = g[current.city][i];
			
			int bloodCount = current.bloodCount;	
			int last = current.chegada;
			
			if (!isInit && (v.partida <= 6 && last <= 6 && v.partida < last))
				bloodCount++;			
			else if (!isInit && (v.partida >= 18 && last >= 18 && v.partida < last))
				bloodCount++;
			else if (!isInit && (v.partida >= 18 && last <= 6))
				bloodCount++;
			Aresta next(v.destino, bloodCount, v.chegada);
			fila.push_back(next);	
		}
		isInit = false;
	}	 
	if (min >= MAX) return -1;
	return min;
}

int main()
{
	int nTest;
	scanf("%d", &nTest);
	for(int test = 0; test < nTest; test++)
	{
		int nRotas;
		scanf("%d", &nRotas);
		map<string, vector<Viagem> > grafo;
		string str;
		for (int i = 0; i < nRotas; i++)
		{
			Viagem v;
			int duracao;
			cin >> str >> v.destino;
			scanf("%d %d", &v.partida, &duracao);
			v.partida = (v.partida % 24);
			if (!v.partida) v.partida = 24;
			v.chegada = v.partida + duracao;
			v.chegada = (v.chegada % 24);
			if (!v.chegada) v.chegada = 24;
			
			if ( duracao > 12 ) continue;
			if (v.partida > 6 && v.partida < 18) continue;
			if (v.chegada > 6 && v.chegada < 18) continue;
			
			grafo[str].push_back(v);
		}
		string origem, destino;
		cin >> origem >> destino;
		int result = bfs(grafo, origem, destino);
		printf("Test Case %d.\n", test+1);
		if (result < 0)
			printf("There is no route Vladimir can take.\n");
		else
			printf("Vladimir needs %d litre(s) of blood.\n", result);
	}
	return 0;
}
