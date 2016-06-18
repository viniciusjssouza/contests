/**********************************************************************************
 * SPOJ - 1892 - Desempilhando Caixas
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 11/09/2009 
 * Tecnicas: ad-hoc
 **********************************************************************************/
#include<iostream>
#include<deque>
#include<algorithm>

#define MAX 987654321

using namespace std;

typedef pair<int,int> pii;

int main()
{
	int N, P;
	while(true)
	{
		scanf("%d %d", &N, &P);
		if (!N && !P) break;
		deque<deque<int> > caixas(P, deque<int>());
		pii invPos;
		for (int i = 0; i < P; i++)
		{
			int t;
			scanf("%d", &t);
			for (int k = 0; k < t; k++)
			{
				int x;
				scanf("%d", &x);
				if (x == 1)
					invPos = pii(i, k);		
				caixas[i].push_back(x);
			}	
		}
		int pilhaDir = 0, pilhaEsq = 0;
		//soma pilhas a esquerda
		for (int i = invPos.first-1; i >= 0; i--)
		{
			if ( (int)(caixas[i].size() - invPos.second) <= 0)
				break;
			pilhaEsq += (caixas[i].size() - invPos.second);
		}
		//soma pilhas a direita
		for (int i = invPos.first+1; i < P; i++)
		{
			if ((int)(caixas[i].size() - invPos.second) <= 0)
				break;
			pilhaDir += (caixas[i].size() - invPos.second);
		}
		int result = min(pilhaEsq, pilhaDir) + (caixas[invPos.first].size()- 1 - invPos.second);
		printf("%d\n", result);
	}
}
