#include<iostream>
#include<cstdio>
#include<set>
#include<vector>
#include<queue>
#include<algorithm>

#define INF 0x3fffffff

using namespace std; 

int data[10010];  
int N, P; 
bool in[24];

int main() {
	int tcase =1;
	while(true) {
		scanf("%d %d", &N, &P);
		if (N==0 && P==0)
			break;
		vector<queue<int> > prox(24);		
		for (int i = 0; i < N; i++) {
			scanf("%d", &data[i]);
			prox[data[i]].push(i);
		}
		for (int i = 1; i <= 23; i++) {
			in[i] = 0;
			prox[i].push(INF);
		}	
		int trocas = 0;
		vector<int> palanque;
		for (int i = 0; i < N; i++) {
			if (!in[data[i]]) {
				if (palanque.size() >= P) {
					trocas++;
					int idx = 0;
					for (int p = 1; p < P; p++) {
						if (prox[palanque[p]].front() == INF) {
							idx = p;
							break;
						}
						else if (prox[palanque[p]].front() > prox[palanque[idx]].front())
							idx = p;
					}
					in[palanque[idx]] = false;					
					palanque[idx] = data[i];
				} else
					palanque.push_back(data[i]);
				in[data[i]] = true;
			}
			if (prox[data[i]].front() < INF)			
				prox[data[i]].pop();			
		}
		printf("Teste %d\n%d\n\n", tcase++, trocas);
	}
	return 0;
}
 
