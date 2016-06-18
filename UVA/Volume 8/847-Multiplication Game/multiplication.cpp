/*******************************************************************
* UVa 847 - A Multiplication Game 
*
* Autor: Vinicius J. S. Souza
* Data: 11/03/2010
* Tecnicas: ???... Matematica
* 
********************************************************************/
#include<iostream>
#include<cstdio>

using namespace std;

unsigned long long N;

unsigned long long tbl[] = {1, 9, 18, 162, 324, 2916, 5832, 52488, 104976,
			944784, 1889568, 17006112, 34012224, 306110016, 612220032,
			5509980288llu};

int main(){
	int size = sizeof(tbl);		
	while (!feof(stdin) && scanf("%llu", &N)==1) {
		for (int i = 1; i < size; i++) {
			if (N > tbl[i-1] && N <= tbl[i]) {
				if (i & 1)				
					printf("Stan wins.\n");
				else
					printf("Ollie wins.\n");
				break;
			}
		} 				
	}
}
