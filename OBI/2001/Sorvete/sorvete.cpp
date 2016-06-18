#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<list>

using namespace std;

int P, S, caso = 1;
typedef pair<int,int> pii;
pii pontos[5010];
list<pii> l;
list<pii>::iterator ite, ite2;

int main() {
	while (true) {
		scanf("%d %d", &P, &S);
		if (!S && !P) break;
		l.clear();
		for (int i = 0; i < S; i++) {
			pii p;
			scanf("%d %d", &p.first, &p.second);
			l.push_back(p);
		}
		l.sort();
		ite = l.begin();
		ite2 = ite; ite2++;
		for (; ite != l.end(); ite++) {
			ite2 = ite; ite2++;
			for (; ite2 !=l.end();) {
				if ((*ite).second >= (*ite2).first) {
					if ((*ite).second >= (*ite2).second) {
						ite2 = l.erase(ite2);
					} else if ((*ite).second < (*ite2).second) {
						(*ite).second = (*ite2).second;
						ite2 = l.erase(ite2);
					}				
				} else ite2++;
	
			}
		}
		printf("Teste %d\n", caso++); 
		for (ite = l.begin(); ite != l.end(); ite++) {
			printf("%d %d\n", (*ite).first, (*ite).second);
		} 
		putchar('\n');

	}
	return 0;
}
