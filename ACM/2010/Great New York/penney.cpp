#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i, N) for(int i = 0; i < N; i++)

using namespace std;

string toss[] = {"TTT", "TTH", "THT", "THH", "HTT", "HTH", "HHT", "HHH"};
int conta[8];


int main() {
	int P;
	scanf("%d", &P);
	for (int p = 0; p < P; p++) {
		int x;
		scanf("%d", &x);
		para(i, 8) {
			conta[i] = 0;
		}
		string seq;
		cin >> seq;	
		para (i, seq.size()-2) {
			string sub = seq.substr(i,3);
			para(k, 8) {
				if (sub == toss[k]) {
					conta[k]++;
				}
			} 
		}
		cout << x;
		para(i,8) {
			cout << " " << conta[i];
		}
		cout << endl;
	}
	return 0;
}
