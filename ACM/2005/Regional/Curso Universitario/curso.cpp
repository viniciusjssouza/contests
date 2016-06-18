/***********************************************************************
* ACM - Curso Universitario - Maratona Regional - 2005
*
* Autor: Vinicius J. S. Souza
* Data: 20/01/2010
* Tecnicas: grafos + topological sorting 
*************************************************************************/
#include<iostream>
#include<cstdio>
#include<list>
#include<deque>
#include<map>
#include<string>

using namespace std;

int N, M, K;
char word[10];
map<string, deque<string> > dependencias;
map<string, int> outDegree;
list<string> materias;
map<string, bool> inserted;
deque<string> toRemove;	
deque<list<string> > ordem(210, list<string>());


int main()
{
	while (true)
	{
		scanf("%d %d", &N, &M);
		if (!N && !M)
			break;
		for (int i = 0; i < N; i++)
		{
			scanf("%s %d", word, &K);
			string mat(word);
			if (!inserted[mat]) 
			{
				inserted[mat] = true;
				materias.push_back(mat);
			}
			for (int k = 0; k < K; k++)
			{
				scanf("%s", word);
				string d(word);
				dependencias[d].push_back(mat);
				outDegree[mat]++;
				if (!inserted[d]) 
				{
					inserted[d] = true;
					materias.push_back(d);
				}
			}
		}
		int nSemestres = 0;
		while (materias.size())
		{		
			int removidos = 0;		
			ordem[nSemestres].clear();
					
			for (list<string>::iterator ite = materias.begin(); ite != materias.end(); 
				ite++)
			{
				if (outDegree[*ite] <= 0)
				{
					toRemove.push_back(*ite);
					removidos++;
					if (removidos >= M)
						break;
				}
			}

			int tam = toRemove.size();
			for (int i = 0; i < tam; i++)
			{
				deque<string> *ptr = &dependencias[toRemove[i]]; 
				int tam2 = ptr->size();
				for (int k = 0; k < tam2; k++)
					outDegree[(*ptr)[k]]--;
				ordem[nSemestres].push_back(toRemove[i]);
				materias.remove(toRemove[i]);
			}
			ordem[nSemestres].sort();
			nSemestres++;
			toRemove.clear();
		
		}
		printf("Formatura em %d semestres\n", nSemestres);
		for (int i = 0; i < nSemestres; i++)
		{
			printf("Semestre %d :", i+1);
			for (list<string>::iterator ite = ordem[i].begin(); ite != ordem[i].end(); 
				ite++)
				printf(" %s", (*ite).c_str());
			putchar('\n');
		}
		dependencias.clear();
		outDegree.clear();
		materias.clear();
		inserted.clear();
	}	
	return 0;
}
