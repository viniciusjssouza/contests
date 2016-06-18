/*************************************************************************
* ACM - 2005 - Reducao de Pena - Regional da Maratona de Programacao
*
* Autor: Vinicius J. S. Souza
* Data: 27/01/2010
* Tecnicas: Programacao dinamica.
*****************************************************************************/
#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

#define SEG 0
#define TER 1
#define QUA 2
#define QUI 3
#define SEX 4

typedef pair<int, int> pii;

struct Task
{
	int pontos;
	int inicio;
	int fim;	
};

inline bool cmpTask(Task a, Task b)
{
	return (a.inicio <= b.inicio);
}
multiset<pii, greater<pii> > order;
vector<vector<Task> > semana(5, vector<Task>());
int subtotal[5];
int total;
int N;
char day[3];
int id, hor1, min1, hor2, min2;

inline int timeToMin(int hor, int min)
{
	return (60*hor + min);
}	

inline int dayToIndex()
{
	if (day[0] == 'S')
	{
		if (day[2] == 'g')
			return SEG;
		return SEX;
	}	
	else if (day[0] == 'Q')
	{
		if (day[2] == 'a')
			return QUA;
		return QUI;
	}
	else return TER;
}

int main()
{
	while (true)
	{
		scanf("%d", &N);
		if (!N)
			break;
		total = 0;
		for (int i = SEG; i <= SEX; i++)
			semana[i].clear();
		for (int i = 0; i < N; i++)
		{
			Task t;
			scanf("%d %d %s %d:%d %d:%d", &id, &t.pontos, day, &hor1, &min1, &hor2, &min2);
			t.inicio = timeToMin(hor1, min1);
			t.fim = timeToMin(hor2, min2);
 			semana[dayToIndex()].push_back(t); 
		}

		for (int i = SEG; i <= SEX; i++)
		{
			stable_sort(semana[i].begin(), semana[i].end(), cmpTask);
			int tam;
			subtotal[i] = 0;
			if (! (tam = semana[i].size()))
 				continue;
			order.clear();
			order.insert(pii(semana[i][0].pontos, semana[i][0].fim));
			for (int t = 1; t < tam; t++)
			{
				for (multiset<pii>::iterator ite = order.begin(); ite != order.end(); ite++)
				{
					if ((*ite).second <= semana[i][t].inicio)
					{
						order.insert(pii(semana[i][t].pontos + (*ite).first, 
							semana[i][t].fim));
						break;
					}
				}
				order.insert(pii(semana[i][t].pontos, semana[i][t].fim));				
			}
			subtotal[i] = (*order.begin()).first;						
			total += subtotal[i];
		}
		printf("Total de pontos: %d\n", total);
		printf("Seg: %d\nTer: %d\nQua: %d\nQui: %d\nSex: %d\n", subtotal[SEG], subtotal[TER],
					subtotal[QUA], subtotal[QUI], subtotal[SEX]);
	}	
	return 0;
}
