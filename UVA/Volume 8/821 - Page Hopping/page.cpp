/***************************************************************
* UVa 821 - Page Hopping - 
*
* Autor: Vinicius J. S. Souza
* Data: 18/02/2010
* Tecnicas: all-pairs shortest path - Floyd-Warshall
* Dificuldade(1-10): 5 
***************************************************************/
#include<iostream>
#include<cstdio>
#include<set>

#define INF	123456789

using namespace std;

set<int> pages;
int weight[110][110];
int ligs[10000][2];
int ptr = 0;
set<int>::iterator it1, it2, it3;
int _case = 1;

int main() {
	int a, b;
	while (true) {
		ptr = 0;
		scanf("%d %d", &ligs[ptr][0], &ligs[ptr][1]);
		if (!ligs[ptr][0] && !ligs[ptr][1])
			break;
		pages.insert(ligs[ptr][0]);
		pages.insert(ligs[ptr][1]);
		ptr++;
		while (true) {
			scanf("%d %d", &ligs[ptr][0], &ligs[ptr][1]);
			if (!ligs[ptr][0] && !ligs[ptr][1])
				break;
			pages.insert(ligs[ptr][0]);
			pages.insert(ligs[ptr][1]);
			ptr++;
		}
		for (it1 = pages.begin(); it1 != pages.end(); it1++) {
			for (it2 = it1; it2 != pages.end(); it2++) {
				weight[(*it1)][(*it2)] = weight[(*it2)][(*it1)] = INF;
			}	
		}
		for (int i = 0; i < ptr; i++)
			weight[ligs[i][0]][ligs[i][1]] = 1;	

		for (it1 = pages.begin(); it1 != pages.end(); it1++) {
			for (it2 = pages.begin(); it2 != pages.end(); it2++) {
				for (it3 = pages.begin(); it3 != pages.end(); it3++) {
					int x =  weight[(*it2)][(*it1)] + weight[(*it1)][(*it3)];
					if ( x < weight[(*it2)][(*it3)] ) {
						weight[(*it2)][(*it3)] = x;	
					}
				}
			}
		}
		long double total = 0.0;
		for (it1 = pages.begin(); it1 != pages.end(); it1++) {
			it2 = it1; 
			for (++it2; it2 != pages.end(); it2++) {
				total += (weight[(*it1)][(*it2)] + weight[(*it2)][(*it1)]);
			}	
		}
		long double nC = pages.size()*(pages.size()-1);
		printf("Case %d: average length between pages = %.3lf clicks\n", _case++, (double)(total / nC));
		pages.clear();
	}	
	return 0;
}
