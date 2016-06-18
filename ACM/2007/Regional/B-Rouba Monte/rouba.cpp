/************************************************************************************
 * SBC - ACM ICPC - 2007 - Problema B - Rouba Monte
 *
 * Autor: Vinicius J. S. Souza
 * Data : 08/08/2008
 **********************************************************************************/
#include <iostream>
#include <vector>
#include <list>

#define debug false

using namespace std;

int simula(list<int> &compras, vector<int> &vencedores, const int &nJogadores);

int main()
{
	//freopen("input.txt", "r", stdin);
	
	int nCartas = -1, nJogadores = -1;
	while (true)
	{
		cin >> nCartas;
		cin >> nJogadores;
		if (!nCartas && !nJogadores) break;
		
		list<int> compras;
		for (int i = 0; i < nCartas; i++)
		{
			int aux = 0;
			cin >> aux;
			compras.push_back(aux);
		}
		vector<int> vencedores;
		int result = simula(compras, vencedores, nJogadores);
		cout << result << " ";
		for (int i = 0; i < vencedores.size(); i++)
		{
			cout << vencedores[i];
			if ((i+1) < vencedores.size()) cout << " ";
		}		
		cout << endl;
	}
	return 0;
}

bool findERemove(list<int> &lst, int &x)
{
	list<int>::iterator ite = lst.begin();
	while (ite != lst.end())
	{
		if (*ite == x) 
		{
			lst.erase(ite);
			return true;
		}
		ite++;
	}
	return false;
}

int simula(list<int> &compras, vector<int> &vencedores, const int &nJogadores)
{
	vector< list<int> > jogadores(nJogadores);
	list<int> descarte;

	for (int i = 0; compras.size() > 0; i++, compras.pop_front())
	{
		int carta = *compras.begin();
		if (debug) cout << "Carta:" << carta << endl;
		
		if (i >= nJogadores) i = 0;
		if (debug) cout << "Jogador:" << i+1 << endl;
		if (findERemove(descarte, carta))
		{
			jogadores[i].push_front(carta);
			jogadores[i].push_front(carta);						
			i--;
			if (debug) cout << "+ Duas cartas do descarte\n";
			continue;
		}
		
		bool continua = false;
		for(int k = 0; k < jogadores.size(); k++)
		{
			if (i == k) continue;
			if (jogadores[k].size() > 0 && jogadores[k].front() == carta)
			{
				jogadores[i].merge(jogadores[k]);
				jogadores[i].push_front(carta);
				continua = true;
				i--;
				if (debug) cout << "+ Cartas tomadas de outro jogador\n";
				break;
			}
		}
		if (continua) continue;
		
		if (jogadores[i].size() > 0 && jogadores[i].front() == carta)
		{
			jogadores[i].push_front(carta);
			i--;
			if (debug) cout << "+ cartas = a do topo do monte...+1\n";
			continue;
		}
		if (debug) cout << "Nenhuma das opcoes\n";
		descarte.push_front(carta);
	}
	
	int max = 0;
	for (int i = 0; i < jogadores.size(); i++)
	{
		if (jogadores[i].size() == max) 
			vencedores.push_back(i+1);
		
		if (jogadores[i].size() > max)
		{
			vencedores.clear();
			vencedores.push_back(i+1);
			max = jogadores[i].size();
		}
	}
	return max;
}