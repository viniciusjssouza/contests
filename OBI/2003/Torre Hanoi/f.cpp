#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int  N;

int main() {
	while (true) {
		scanf("%d", &N);
		if (!N) break;
		long result = (long)pow(2.0, (double)N)-1; 
		cout << result << endl;
	}
}


