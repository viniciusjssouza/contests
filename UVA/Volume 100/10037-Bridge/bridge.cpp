/***************************************************
 * 10037-Bridge - Programming Challenges - UVa
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 10/03/2010
 * Tecnicas: sorting
 * Dificuldade(1-10): 7
 ****************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int nCases, N;
int m[1010];
int out[5000];

int main() {
	scanf("%d", &nCases);
	for (int k = 0; k < nCases; k++) {
		if (k)
			putchar('\n');
		scanf("%d", &N);
		
		for (int i = 0; i < N; i++) {
			scanf("%d", &m[i]);
		}
		if (!N) {
			printf("0\n");
			continue;
		} else if (N == 1) {
			printf("%d\n%d\n", m[0], m[0]);
			continue;
		}
		stable_sort(m, m+N);
		int total = 0;
		int outptr = 0;
		for (int ptr = N-1; ptr > 0; ptr -= 2) {
			if (ptr > 2) {
				int s1 = m[0] + 2*m[1] + m[ptr];
				int s2 = 2*m[0] + m[ptr-1] + m[ptr];
				if (s1 <= s2) {
					total += s1;
					out[outptr++] = m[0];
					out[outptr++] = m[1];
					out[outptr++] = m[0];
					out[outptr++] = m[ptr-1];
					out[outptr++] = m[ptr];
					out[outptr++] = m[1];		
				} else {
					total += s2;
					out[outptr++] = m[0];
					out[outptr++] = m[ptr];
					out[outptr++] = m[0];
					out[outptr++] = m[0];
					out[outptr++] = m[ptr-1];
					out[outptr++] = m[0];		
				}				
			} else if (ptr == 2) {				
				total += m[1] + m[0] + m[2];
				out[outptr++] = m[0];
				out[outptr++] = m[1];
				out[outptr++] = m[0];
				out[outptr++] = m[0];
				out[outptr++] = m[2];
			} else if (ptr == 1){
				total += m[1];
				out[outptr++] = m[0];
				out[outptr++] = m[1];				
			}				
		}	
		printf("%d\n", total);
		for (int i = 0, count = 0; i < outptr; count++) {
			if (count & 1)
				printf("%d\n", out[i++]);
			else{
				printf("%d %d\n", out[i], out[i+1]);
				i+=2;
			}
		}	
	}
}



