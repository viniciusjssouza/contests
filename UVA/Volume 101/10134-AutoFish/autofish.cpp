/*************************************************************************
* UVa 10134 - Autofish
*
* Autor: Vinicius J. S. Souza
* Data: 22/02/2010
* Tecnicas: simulacao ad-hoc
* Dificuldade (1-10): 2
*************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>

char cmd[15];

int main() {
	int N;
	scanf("%d", &N);
	getchar();
	getchar();
	for (int i = 0; i < N; i++) {
		if (i > 0)
			putchar('\n');
		int lastCaught = 0, lastCompleted = 0, nfish = 0;
		int bu = 0;
		for (;true && !feof(stdin); lastCaught++) {			
			gets(cmd);
			if (strlen(cmd) < 2)
				break;
			if (cmd[0] == 'b') {
				if (bu < 6)
					bu++;
			} else if (cmd[0] == 'f') {
				if (bu >= 2) {						
					lastCompleted++;							
					if (nfish == 0 || (lastCaught >= 7 && lastCompleted >= 3)) {
						nfish++;
						bu -= 2;
						lastCompleted = 0;
						lastCaught = 0;							
					} 
				}

			}				
		}
		printf("%d\n", nfish);
	}
}
