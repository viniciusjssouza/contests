/*****************************************************************
* Digits Count - ACM 2010 - Final Sul-americana 
*
* Autor: Vinicius J. S. Souza
* Data:24/10/2010
* Tecnicas: teoria dos numeros
* Dificuldade(1-10): 6
*************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>

#define para(i,N) for(int i = 0; i < N; i++)

using namespace std;

int A, B;
int countA[10], countB[10];
int tbl[] = { 0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000, 900000000};
int zerodif[] = {0, 1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111};

void conta(int n, int count[]) {
	char nstr[10];
	sprintf(nstr, "%d", n);
	int digit;
	int i = 0, pot = strlen(nstr)-1;		
	for (; pot > 0; pot--, i++) {
		int digit = (nstr[i]-'0');
		int base = pow(10.0,(float)pot);
		para(k,10) {
			count[k] += (digit * tbl[pot]);									
		} 
		para(k, digit) { 
			if (k == 0 && i == 0) {
				count[0] -= zerodif[pot];
			} else {
				count[k] += base;
			}
		}
		count[digit] += ((n % base)+1);
	}
	digit = (nstr[i]-'0');
	para(k, digit+1) { 
		if (k == 0 && i == 0) {
			count[0] -= zerodif[pot];
		} else {
			count[k]++;
		}
	}
}

int main() {
	while(true) {
		scanf("%d %d", &A, &B);
		if (!A && !B)
			break;
		para(i, 10) 
			countA[i] = countB[i] = 0;
		conta(A-1, countA);
		conta(B, countB);
		int i;
		para(i, 10) {
			if (i)
				putchar(' ');
			printf("%d", countB[i] - countA[i]);
		}
		printf("\n");
	}
	return 0;
}
