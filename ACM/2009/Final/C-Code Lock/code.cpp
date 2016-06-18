#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>

using namespace std;

string word;
int dist[1010];
int N;

int calcDist(char c) {
	int opt1 = (c - 'a');
	int opt2 = ('z'-c + 1);
	// problema com a distancia 13! Pode ser negativa ou positiva
	if (opt1 < opt2)
		return opt1;
	return (-opt2);
}

int main() {
	while (true) {
		cin >> word;
		if (word[0] == '*')
			break;
		N = word.size();
		for (int i = 0; i < N; i++) {
			dist[i] = calcDist(word[i]);
		}
/*
		for (int i = 0; i < N; i++) {
			cout << dist[i] << endl;
		}
		printf("-------------------\n");
*/
		for (int i = 0; i < N; i++) {
			while (dist[i] != 0) {
					
			}
		}
	}
	return 0;
}
