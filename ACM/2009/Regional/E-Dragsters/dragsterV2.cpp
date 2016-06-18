/*************************************************************************
* E-Dragsters - Regional 2009 
*
* Autor: Vinicius J. S. Souza
* Data: 22/09/2009
* Tecnicas: teoria de probabilidades + backtracking
**************************************************************************/
#include<iostream>
#include<vector>

using namespace std;

int N;
float mProb[305][305];

typedef pair<int, double> pid;

class Partida
{
public:
	int c1;
	int c2;
	int prox;
	
	Partida()
	{ this->prox = -1; }
};

void backtrack(int p, vector<pid> &adv, vector<Partida> &camp)
{
	Partida* partida = &camp[p];
	if (partida->c1 == 1 || partida->c2 == 1)
		return;
	if (partida->c1 <= N && partida->c2 <= N)
	{
		adv.push_back( pid(partida->c1, mProb[partida->c1][partida->c2]) );
		adv.push_back( pid(partida->c2, mProb[partida->c2][partida->c1]) );
	}
	else if (partida->c1 <= N && partida->c2 > N)
	{
		backtrack(partida->c2, adv, camp);
		double subtotal = 0.0;
		for (int i = 0; i < adv.size(); i++)
		{
			subtotal += (adv[i].second * mProb[partida->c1][adv[i].first]);
			adv[i].second *= mProb[adv[i].first][partida->c1];
		}
		adv.push_back( pid(partida->c1, subtotal) );
	}
	else if (partida->c1 > N && partida->c2 <= N)
	{
		backtrack(partida->c1, adv, camp);
		double subtotal = 0.0;
		for (int i = 0; i < adv.size(); i++)
		{
			subtotal += (adv[i].second * mProb[partida->c2][adv[i].first]);
			adv[i].second *= mProb[adv[i].first][partida->c2];
		}
		adv.push_back( pid(partida->c2, subtotal) );
	}
	else
	{
		vector<pid> temp1, temp2;
		backtrack(partida->c1, temp1, camp);
		backtrack(partida->c2, temp2, camp);
		for (int i = 0; i < temp1.size(); i++)
		{
			double subtotal = 0.0;
			for (int k = 0; k < temp2.size(); k++)
				subtotal += (temp1[i].second * mProb[temp1[i].first][temp2[k].first]* temp2[k].second);
			adv.push_back( pid(temp1[i].first, subtotal) );
		}
		for (int i = 0; i < temp2.size(); i++)
		{
			double subtotal = 0.0;
			for (int k = 0; k < temp1.size(); k++)
				subtotal += (temp2[i].second * mProb[temp2[i].first][temp1[k].first]* temp1[k].second);
			adv.push_back( pid(temp2[i].first, subtotal) );
		}
	}
}

int main()
{
	while(true)
	{
		scanf("%d", &N);
		if (!N) break;
		vector<Partida> camp(2*N, Partida());
		for (int i = 1; i <= N; i++)
			for (int k = 1; k <= N; k++)
				scanf("%f", &mProb[i][k]);
		int inicio = -1;
		for (int i = 0; i < N-1; i++)
		{
			int pos = i+N+1;
			scanf("%d %d", &camp[pos].c1, &camp[pos].c2);
			if (camp[pos].c1 > N)
				camp[camp[pos].c1].prox = pos;
			if (camp[pos].c2 > N)
				camp[camp[pos].c2].prox = pos;	
					
			if (camp[pos].c1 == 1 || camp[pos].c2 == 1)
				inicio = pos;			
		}
		if (inicio < 0)
		{
			printf("0.000000\n");
			continue;
		}

		double total = 1.0;
		while (inicio >= 0)
		{
			int p;
			if (camp[inicio].c1 == 1) 
				p = camp[inicio].c2;
			else		
				p = camp[inicio].c1;
			if (p <= N)
			{
				total *= mProb[1][p];
			}
			else
			{
				vector<pid> adv;
				backtrack(p, adv, camp);

				double temp = 0.0;
				for (int i = 0; i < adv.size(); i++)
					temp += (adv[i].second * total * mProb[1][adv[i].first]);
				total = temp;
			}	
			if (camp[inicio].prox >= 0)
			{
				int next = camp[inicio].prox;
				if (camp[next].c1 == inicio)
					camp[next].c1 = 1;
				else camp[next].c2 = 1;
			}	
			inicio = camp[inicio].prox;
		}
		printf("%.6f\n", total);
	}
}
