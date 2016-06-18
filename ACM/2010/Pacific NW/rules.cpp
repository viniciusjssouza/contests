/**************************************************************
* ACM - USA - Pacific Northwest - Always Follow the Rules in Zombieland
*
* Autor: Vinicius J. S. Souza
* Data: 04/10/2011
* Tecnicas: nenhum em especial
****************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>

#define para(i,B,N) for (int i = B; i < N; i++)

using namespace std;

typedef unsigned long long int int64;
string rules[100];

int main() {
	int N, R, X;
	scanf("%d", &N);
	getchar();
	para(i,0,N) {
		getline(cin,rules[i]);		
	}
	scanf("%d", &R);
	para (i,0,R) {
		scanf("%d", &X);
		if (X <= 0 || X > N) {
			printf("Rule %d: No such rule\n", X);
		} else {
			cout << "Rule " << X << ": "  << rules[X-1] << endl;
		}
	} 
	return 0;
}
