#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>

using namespace std; 

typedef pair<int, string> par;

bool cmp(const par &a, const par &b) {
	if (a.first > b.first)
		return true;
	if (a.first < b.first)
		return false;
	return a.second < b.second;
}

int main() {
	int N, tcase = 1;
	char nome[20];
	while (1) {
		scanf("%d", &N);
		if (!N)
			break;
		vector<par> placar;
		for (int i = 0; i < N; i++) {
			scanf("%s", nome);
			int menor = 0x3fffffff, maior = -1, total = 0;
			for (int k = 0; k < 12; k++) {
				int x;
				scanf("%d", &x);
				if (x < menor)
					menor = x;
				if (x > maior)
					maior = x;
				total += x;
			}
			total -= (maior + menor);
			placar.push_back(par(total, nome));
		}
		stable_sort(placar.begin(), placar.end(), cmp);
		int pos = 1;
		printf("Teste %d\n%d %d %s\n", tcase++, pos, placar[0].first, placar[0].second.c_str());
		for (int i = 1; i < N; i++) {
			if (placar[i].first != placar[i-1].first)
				pos = i+1;
			printf("%d %d %s\n", pos, placar[i].first, placar[i].second.c_str());
		}	

		putchar('\n');
	}
	return 0;
}
