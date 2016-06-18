#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int N;
int caso = 1;

int main(){
	while (true) {
		scanf("%d", &N);
		if (!N) break;
		int x;
		char op;
		scanf("%d", &x);
		long long result = x;
		for (int i = 0; i < N-1; i++) {
			if (scanf("%c%d", &op, &x) == 2) {
				if (op == '+')
					result+= x;
				else if (op == '-')
					result -= x;
			}
		}
		printf("Teste %d\n", caso++);	
		cout << result << endl;
	}
}

