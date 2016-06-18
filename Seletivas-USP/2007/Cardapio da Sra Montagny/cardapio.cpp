/********************************************************************************************
* Seletiva IME-USP - Cardapio da Sra. Montagny
*
* Autor: Vinicius J. S. Souza
* Data: 02/01/2010
* Tecnicas: componentes fortemente conexas (em grafos direcionados) - 2 Sat - Algoritmo de
	    Tarjan
****************************************************************************************/
#include<iostream>
#include<map>
#include<deque>
#include<vector>
#include<algorithm>
#include<string>

#define MAX 2100

using namespace std; 

int N, INDEX;

struct Node
{
   int index;
   int lowlink;
   bool inStack;
   Node()
   {	
      index = -1;
      lowlink = 0x7FFFFFFF;
      inStack = false;
   }
};

vector<Node> info(MAX+1);
vector<deque<int> > grafo(MAX+1);

string inverse(string s)
{
   return (s[0] == '!' ? s.substr(1, s.size()-1) : "!" + s);
}

bool tarjan(int key, deque<int> &pilha)
{
   info[key].index = info[key].lowlink = INDEX++;
   pilha.push_front(key);
   info[key].inStack = true;
   for (int i = 0; i < grafo[key].size(); i++)
   {
      int nextKey = grafo[key][i];
      if (info[nextKey].index == -1)
      {
		 tarjan(nextKey, pilha);
		 info[key].lowlink = min(info[key].lowlink, info[nextKey].lowlink);
      }
      else if (info[nextKey].inStack)
	 info[key].lowlink = min(info[key].lowlink, info[nextKey].index);
   }
   if (info[key].lowlink == info[key].index)
   {
      map<int, bool> used;
      int n;
      do
      {
		 n = pilha.front();
		 pilha.pop_front();
		 info[n].inStack= false;
		 used[n] = true;
		 if (used[(MAX-n)])
			return false;
      }while (n != key);
      
   }
   return true;
}

int main()
{
   long start = clock();
   int instancia = 1;
   while (!feof(stdin) && scanf("%d", &N) == 1)
   {
      if (instancia > 1) putchar('\n');
      int conv = 1;
      map<string, int> str2int;
      for (int i = 0; i < N; i++)
      {
		 char aux1[25], aux2[25];
		 scanf("%s %s", aux1, aux2);
		 int pedido1, pedido2, inv1, inv2;
		 string s1(aux1), s2(aux2);
		 string inverse1 = inverse(s1), inverse2 = inverse(s2);
		 if (!str2int[s1])
		 {
			str2int[s1] = pedido1 = conv;
			str2int[inverse1] = inv1 = (MAX-conv);
			conv++;
			info[pedido1].index = info[inv1].index = -1;
			info[pedido1].inStack = info[pedido1].lowlink = info[inv1].inStack = info[inv1].lowlink = 0; 
			grafo[pedido1].clear();
			grafo[inv1].clear();
		 }
		 else
		 {
			pedido1 = str2int[s1];
			inv1 = (MAX-pedido1);
		 }
		 
		 if (!str2int[s2])
		 {
			str2int[s2] = pedido2 = conv;
			str2int[inverse2] = inv2 = (MAX-conv);
			conv++;
			info[pedido2].index = info[inv2].index = -1;
			info[pedido2].inStack = info[pedido2].lowlink = info[inv2].inStack = info[inv2].lowlink = 0; 
			grafo[pedido2].clear();
			grafo[inv2].clear();
		 }
		 else
		 {
			pedido2 = str2int[s2];
			inv2 = (MAX-pedido2);
		 }
		 grafo[inv1].push_back(pedido2);
		 grafo[inv2].push_back(pedido1);	    
		  }	 
		  bool isPossible = true;
		  INDEX = 0;
		  deque<int> pilha;
		  for (int i = 1; i < conv; i++)
		  {
		 if (info[i].index == -1)
		 {
			if (!tarjan(i, pilha))
			{
			   isPossible = false;
			   break;
			}
		 }
      }
      printf("Instancia %d\n", instancia);
      printf("%s\n", (isPossible == true ? "sim" : "nao"));
      instancia++;      
   }   
}
