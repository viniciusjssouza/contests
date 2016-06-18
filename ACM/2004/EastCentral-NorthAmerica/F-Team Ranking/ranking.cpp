/*******************************************************************
* F - Team Ranking - East Central - North America - 2004 
*
* Autor: Vinicius J. S. Souza
* Data: 08/09/2010
* Tecnicas: recursao para gerar permutacoes - O(n²)
* Dificuldade (1-10): 6
*********************************************************************/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>

using namespace std;

int N;
string teams = "ABCDE";
string votes[101];
vector<string> perm;
bool used[5];
int posA[5], posB[5];

void geraPerm(int nivel, string &s) {
	if (nivel == 5) {
		perm.push_back(s);
		return;
	}
	for (int i = 0; i < teams.size(); i++) {
		if (!used[i]) {
			used[i] = true;
			s[nivel] = teams[i];
			geraPerm(nivel+1, s);
			used[i] = false;
		}			
	}
}

int dist(string &a, string &b) {
	for (int i = 0; i < 5; i++) {
		posA[a[i]-'A'] = posB[b[i]-'A'] = i;
	}
	int d = 0;
	for (int i = 0; i < 5; i++) {
		for (int k = i+1; k < 5; k++) {
			if (i == k)
				continue;
			bool difA = posA[i] > posA[k];
			bool difB = posB[i] > posB[k];
			if (difA != difB)
				d++;
		}
	}
	return d;
}

int main() {
	string s = teams;
	memset(used, false, sizeof(used));
	geraPerm(0, s);
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			cin >> votes[i];	
		}
		int bestIdx = 0, bestVal = 0x3fffffff;
		for (int i = 0; i < perm.size(); i++) {
			int soma = 0;
			for (int k = 0; k < N; k++) {
				soma += dist(perm[i], votes[k]);
			}
			if (soma < bestVal) {
				bestVal= soma;
				bestIdx = i;
			}
		}					
		cout << perm[bestIdx] << " is the median ranking with value " << bestVal << ".\n";	
	}
	return 0;
}
