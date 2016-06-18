#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

#define MAX_ALUNOS 1010

int main() 
{
	int i, indice_melhor, n;
	int turma=1;
	struct {
		int codigo, media;
	} alunos[MAX_ALUNOS];
	scanf("%d", &n);
	while (n> 0) {
		for (i = 0; i < n; i++)
			scanf("%d %d", &alunos[i].codigo, &alunos[i].media);
		indice_melhor = 0;
		vector<int> best;
		best.push_back(0);
		for (i = 1; i < n; i++) {
			if (alunos[i].media > alunos[indice_melhor].media) {
				best.clear();
				indice_melhor = i;
				best.push_back(i);
			} else if (alunos[i].media == alunos[indice_melhor].media) {
				best.push_back(i);
			}		
		}
		printf("Turma %d\n", turma++);
		for (int i = 0; i < best.size(); i++) {
			printf("%d ", alunos[best[i]].codigo);
		}
		printf("\n\n");
		scanf("%d", &n);
	}
	return 0;
}

