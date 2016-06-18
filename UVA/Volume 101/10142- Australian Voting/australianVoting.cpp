/****************************************************************************************************
 * UVa problem 10142 - Australian Voting - Programming Challenges
 * Autor: Vinicius J. S. Souza
 * Data:13/02/2008
 * **************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

#define REL	-2 // recem-eliminados
#define	EL  -1 // eliminados
#define NEL  0 // nao eliminado

using namespace std;

struct Candidato
{
	string nome;
	int votos;
};

bool hasEleito(int max, int maxPos, int maxQnt, int min);
bool isEliminado(int pos);
void processaVotos(int votacao[][10000]);
void findValues(int &max, int &maxPos, int &maxQnt, int &min);

int numVotos = 0;
int totalCandidatos = 0;
Candidato cand[100];
int eliminados[100];

int main()
{
	freopen("input.txt", "r", stdin);
	bool isInicio = true;
	int n = 0;
	// realiza a entrada
	// numero de casos...
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		// recebe numero de candidatos
		totalCandidatos = 0;
		numVotos = 0;
		scanf("%d\n", &totalCandidatos);
		if (!isInicio)
			cout << endl;
		else
			isInicio = false;

		// inicia o conjunto de eliminados;
		int votacao[totalCandidatos][10000];
		
		// inicializa os candidatos
		for (int k = 0; k < totalCandidatos; k++)
		{
			cand[k].votos = 0;
			getline(cin, cand[k].nome);
			eliminados[k] = NEL;
		}		

		while(true)
		{
			//recebe os votos
			string buffer;
			if (feof(stdin))break;
			getline(cin, buffer);
			if (buffer == "")break;
			istringstream is(buffer);
			int buffer2;
			
			//processa os votos para cada candidato.
			int k = 0;
			while (is >> buffer2)
			{
				if (k > 1000) break;
				if (buffer2 > totalCandidatos)break;
				votacao[k][numVotos] = buffer2;
				if (!k) cand[buffer2-1].votos++;
				k++;				
			}
			numVotos++;
		}
		// mostra a entrada
		/*
		for (int k = 0; k < numCandidatos; k++)
		{
			cout << cand[k].nome << " " << cand[k].votos << endl;
		}
		*/
		// procura o vencedor - logica do negocio
		int max = 0, min = 0, maxPos = 0, maxQnt = 0;
		
		findValues(max, maxPos, maxQnt, min);
		while (! hasEleito(max, maxPos, maxQnt, min)) 
		{
			// elimina os candidatos
			for (int k = 0; k < totalCandidatos; k++)
			{
				if (eliminados[k] == NEL && cand[k].votos == min)
				{
					eliminados[k] = EL;
				}
			}
			//processa os votos dos candidatos recem-eliminados
			processaVotos(votacao);
			findValues(max, maxPos, maxQnt, min);
		}		
	}
	return 0;
}

bool hasEleito(int max, int maxPos, int maxQnt, int min)
{
	//cout << max << " " << min << endl;
	if (maxQnt == 1 && (1.0 * max / numVotos) > 0.5)
	{
		cout << cand[maxPos].nome << endl;
		return true;
	}
	
	else if (max == min)
	{
		for (int i = 0; i < totalCandidatos; i++)
		{
			if (eliminados[i] == NEL)
				cout << cand[i].nome << endl;
		}
		return true;
	}
	else 
	{
		return false;
	}
}

void processaVotos(int votacao[][10000])
{
	for (int k = 0; k < totalCandidatos; k++)
		cand[k].votos = 0;

	for (int i = 0; i < numVotos; i++)
	{
		for (int k = 0; k < totalCandidatos; k++)
		{
			if (eliminados[votacao[k][i]-1] == NEL)
			{
				cand[votacao[k][i]-1].votos++;
				break;
			}
		}
	}
}

void findValues(int &max, int &maxPos, int &maxQnt, int &min)
{
	max = 0;
	min = 1000;
	maxQnt = 0;
	
	for (int i = 0; i < totalCandidatos; i++)
	{
		if (eliminados[i] != EL)
		{
			if (cand[i].votos > max)
			{
				max = cand[i].votos;
				maxPos = i;
				maxQnt = 1;
			}
			else if (cand[i].votos == max)
			{
				maxQnt++;
			}
			if (cand[i].votos < min)
				min = cand[i].votos;
		}
	}
	//cout << max << "  "  << maxPos << endl;
}
