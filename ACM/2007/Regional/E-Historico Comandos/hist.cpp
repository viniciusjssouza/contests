/***********************************************************************************
* E - Historio de Comandos - Maratona - Regional 2007 
*
* Autor: Vinicius J. S. Souza
* Data: 11/09/2009
* Tecnicas: estrutura de dados - pilha
********************************************************************************/
#include<iostream>
#include<map>
#include<deque>

using namespace std;

int main()
{
	int N;
	while (true)
	{
		scanf("%d", &N);
		if (!N) 
			break;
		deque<int> pilha;	
		map<int, bool> used;
		int total = 0;
		for (int i =0 ; i < N; i++)		
		{
			int num;
			scanf("%d", &num);
			if (!used[num])
			{
				used[num] = true;
				total += num + pilha.size();
			}
			else
			{
				for(int k = 0; k < pilha.size(); k++)
					if (pilha[k] == num)
					{
						total += k+1;		
						break;
					}
			}
			pilha.push_front(num);	
		}
		printf("%d\n", total);
	}
 	return 0;
}
