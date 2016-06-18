#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char str[100005];
int N;
int grafo[255][255];
int conta[255];
bool used[255][255];

int main() {	
	while (true) {
		memset(grafo, 0, sizeof(grafo));
		memset(conta, 0, sizeof(conta));
		memset(used, 0, sizeof(used));
		
		scanf("%s", str);
		if (str[0] == '*')
			break;
		N = strlen(str);
		conta[str[0]]++;
		for (int i= 1; i < N; i++) {
			conta[str[i]]++;
			grafo[str[i-1]][str[i]]++;	
		}
		int res =0;
		for (int i = 0; i < 255; i++) {
			if (conta[i] >= 2) 
				res++;
		}
		for (int i= 1; i < N; i++) {			
			if (grafo[str[i-1]][str[i]] > 1) {
				res++;
				if (i > 1 && grafo[str[i-2]][str[i-1]] > 1)
					res += grafo[str[i-2]][str[i-1]];
			}	
		}
		printf("%d\n", res);
	}
	return 0;
}
