/************************************************************
 * Problema 10044- Erdos Numbers - Livro Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data:  05/07/2008
 * Comentario: Esse eh muuuuuito dificil!!! :\
 ************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <queue>
#include <cstdio>

#define INITGRAU -1

using namespace std;

const string ERDOS("Erdos, P.");

void process(string line, map<string, set<string> > &grafo, map<string, int> &levels);
void getNomes(string line, vector<string> &nomes);
void printGrafo(map<string, set<string> > grafo, vector<string> nomes);
void doBFS(map<string, set<string> > grafo, map<string, int> &levels, string start);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int scenario = 0;
	cin >> scenario;
	//getchar();
	for (int i = 0; i < scenario; i++)
	{
		int numLinhas, numNomes;
		string line;
		map<string, set<string> > grafo;
		map<string, int> levels;
		vector<string> nomes;
		
		cin >> numLinhas; //getchar();
		cin >> numNomes; 
		getchar();
		for (int k = 0; k < numLinhas; k++)
		{
			getline(cin, line);
			process(line, grafo, levels);
		}	
		
		doBFS(grafo, levels, ERDOS);
		
		cout << "Scenario " << i+1 << endl;
		for (int k = 0; k < numNomes; k++)
		{
			getline(cin, line);
			if (levels.find(line) == levels.end() || levels[line] == -1)
				cout << line << " infinity" << endl;
			else
				cout << line << " " << levels[line] << endl;
		}		
	}
	return 0;
}

void process(string line, map<string, set<string> > &grafo, map<string, int> &levels)
{
	vector<string> nomes;
	vector<string>::iterator i, k;
	
	getNomes(line, nomes);
	
	for (i = nomes.begin(); i < nomes.end(); i++)
	{
		levels[*i] = INITGRAU;
		for (k = nomes.begin(); k < nomes.end(); k++)
		{
			if (i != k)
			{
				grafo[*i].insert(*k);
				grafo[*k].insert(*i);
			}
		}
	}
}

void getNomes(string line, vector<string> &nomes)
{
	string nome = "";
	int conta = 0;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ':') 
		{
			nomes.push_back(nome);
			break;
		}
		else if (line[i] == ',')
		{
			conta++;
			if (conta == 2)
			{
				nomes.push_back(nome);
				conta = 0;
				nome = "";	
				i++;
			}
			else nome += line[i];
		}
		else nome += line[i];	
	}
}

void printGrafo(map<string, set<string> > grafo, vector<string> nomes)
{
	vector<string>::iterator i;
	for (i = nomes.begin(); i < nomes.end(); i++)
	{
		cout << *i << " " << "Ligacoes:" << endl;
		set<string> lig = grafo[*i];
		set<string>::iterator k;
		for (k = lig.begin(); k != lig.end(); k++)
		{
			cout << *k << " ";
		}			
		cout << "\n\n";
	}
}

void doBFS(map<string, set<string> > grafo, map<string, int> &levels, string start)
{
	queue<string> fila;
	map<string, int> visited;
	string nome;
	int level = 0;
	visited[start] = 0;
	fila.push(start);
	levels[nome] = level;
	while (!fila.empty())
	{
		nome = fila.front();
		fila.pop();
		set<string>::const_iterator si = grafo[nome].begin(), fim = grafo[nome].end();
		level = visited[nome] + 1;
		for (; si != fim; si++)
		{
			if (visited.find(*si) == visited.end()) // nao foi visitado ainda
			{
				levels[*si] = level;
				visited[*si] = level;
				fila.push(*si);
			}
		}
	}
}
