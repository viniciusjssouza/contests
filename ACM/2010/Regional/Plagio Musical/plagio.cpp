/***********************************************************************
* Plagio Musical - ACM - Regional 2010
*
* Autor: Vinicius J. S. Souza
* Data: 13/09/2010
* Tecnicas: algoritmo KMP
**********************************************************************/

#include<iostream>
#include<map>
#include<cstring>
#include<string>

using namespace std;

map<string, int> mapa;
int musica[100010], trecho[10010], t[100010];
	
int M, T;

int dist(int a, int b) {
	int dif = 0;
	for (; a != b; dif++, a = ((a+1) % 12));
	return dif;
}

/** KMP - Busca uma string menor dentro de uma maior ou igual ***
* vetor t: usado internamento. Deve possuir o tamanho da str maior.
* T -> tamanho da str menor 
* M -> tamanho da str maior
* retorno -> quantas ocorrencias foram encontradas
*/
void preKmp(int strMenor[]) {
	t[0] = -1; // vetor usado pelo kmp. Deve possuir tamanho da string maior
	int i = 0;
	for (int j = 1; j < T; j++) {
		if (strMenor[j] == strMenor[i]) {
			t[j] = t[i];
		} else {
			t[j] = i;
			do {
				i = t[i];
			} while (i>=0 && strMenor[j] != strMenor[i]);
		}
		i++;
	}
	t[T] = i;
}


int KMP(int strMaior[], int strMenor[]) {
    /* Preprocessing */
	int found = 0;
    preKmp(strMenor);
	int i = 0;
	for (int j = 0; j < M; j++) {
		while (i >= 0 && strMaior[j] != strMenor[i]) 
			i = t[i];
		i++;
		if (i == T) {
			i = t[T];
			found++;
		}
	}  
	return found;
}


int main() {
	mapa["C"] = mapa["B#"] = 0;
	mapa["C#"] = mapa["Db"] = 1;
	mapa["D"] = 2;
	mapa["Eb"] = mapa["D#"] = 3;
	mapa["E"] = mapa["Fb"] = 4;
	mapa["F"] = mapa["E#"] = 5;
	mapa["Gb"] = mapa["F#"] = 6;
	mapa["G"] = 7;
	mapa["Ab"] = mapa["G#"] = 8;
	mapa["A"] = 9;
	mapa["A#"] = mapa["Bb"] = 10;
	mapa["B"] = mapa["Cb"] = 11;
	
	while (true) {
		scanf("%d %d", &M, &T);
		if (!M && !T) break;
		string nota;
		int ant = -1;
		for (int i = 0; i < M; i++) {
			cin >> nota;
			if (i) {
				int tmp = mapa[nota];
				musica[i-1] = dist(ant,tmp);
				ant = tmp;				
			} else
				ant = mapa[nota];
		}
		for (int i = 0; i < T; i++) {
			cin >> nota;
			if (i) {
				int tmp = mapa[nota];
				trecho[i-1] = dist(ant,tmp);
				ant = tmp;				
			} else
				ant = mapa[nota];
		}
		M--; T--;
		int ret = KMP(musica, trecho);		
		printf("%c\n", (ret > 0 ? 'S':'N'));
	}
	return 0;
} 
