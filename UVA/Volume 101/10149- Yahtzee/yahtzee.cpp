/*****************************************************************
 * UVa 10149 - Yahtzee - Livro Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 09/07/2008 - 
 * Tecnicas: Hill Clambing Iterativo
 * Dificuldade (1-10): 8
 *****************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include<vector>
#define INF 0x3f3f3f3f

using namespace std;

int dices[13][6];
int currentNode[13];
int nextNode[13];
int solNode[13];
int sol = -INF;

inline int sumAll(int index) {
	int val = 0;
	for (int i = 0; i < 6; i++)
		val += ((i+1) * dices[index][i]); 
	return val;
}

inline bool hasXofAKind(int x, int index) {
	for (int i = 0; i < 6; i++) {
		if (dices[index][i] >= x) {
			return true;
		}
	}
	return false;
}

int eval(int node[13], bool print = false) {
	int sixSum = 0, total = 0, val, index;
	bool has;
	// 1 a 6
	for (int i = 0; i < 6; i++) {
		int index = node[i];
		val = dices[index][i]*(i+1);
		sixSum += val;
		total += val;
		if (print)
			printf("%d ", val);
	}
	// chance
	val = sumAll(node[6]);
	total+=val;
	if (print)
		printf("%d ", val);
	//three of a kind
	if (hasXofAKind(3, node[7])) {
		val = sumAll(node[7]);
		total+=val;
	} else val = 0;
	if (print)
		printf("%d ", val);

	//four of a kind
	if (hasXofAKind(4, node[8])) {
		val = sumAll(node[8]);
		total+=val;				
 	} else val = 0;
	if (print)
		printf("%d ", val);
	//five of a kind
	if (hasXofAKind(5, node[9])) {
		total+=50;
		val = 50;
	} else val = 0;
	if (print)
		printf("%d ", val);

	//short straight
	index = node[10];
	has = false;
	for (int i = 0; i < 3; i++) {
		if (dices[index][i] >= 1 && dices[index][i+1] >= 1 && dices[index][i+2] >= 1 &&
				dices[index][i+3] >= 1) {
			has =true;
			break;
		}		
	}
	if (has) {
		total+=25;
		val = 25;
	} else val = 0;
	if (print)
		printf("%d ",val);

	//long straight
	index = node[11];
	has = false;
	for (int i = 0; i < 2; i++) {
		if (dices[index][i] >= 1 && dices[index][i+1] >= 1 && dices[index][i+2] >= 1 &&
				dices[index][i+3] >= 1 && dices[index][i+4] >= 1) {
			has =true;
			break;
		}		
	}
	if (has) {
		total+=35;
		val = 35;
	} else val = 0;
	if (print)
		printf("%d ", val);

	// fullhouse
	bool has3 = false, has2 = false;
	index = node[12];	
	for (int i = 0; i < 6; i++) {
		if (dices[index][i] == 3)
			has3 = true;
		else if (dices[index][i] == 2)
			has2 = true;
		else if (dices[index][i] == 5) {
			has3 = has2 = true;
			break;
		}
			
	}
	if (has3 && has2) {
		total+=40;
		val = 40;
	} else val = 0;
	if (print)
		printf("%d ", val);

	// bonus
	if (sixSum >= 63) 
		total += 35;
	if (print){
		if (sixSum >= 63)
			printf("%d ", 35);
		else printf("0 ");
	}
	
	if (print)
		printf("%d\n", total);
	return total;	
}

int main() {
	int n;
	while (!feof(stdin)) {
		sol = -INF;
		for (int i = 0; i < 13; i++) {
			currentNode[i] = i;
			for (int k = 0; k < 6; k++)
				dices[i][k] = 0;
		}
		for (int i = 0; i < 13; i++) {
			for (int k = 0; k < 5; k++) {
				if (scanf("%d", &n) != 1) return 0;
				dices[i][n-1]++;			
			}
		}

		for (int ite = 0; ite < 50; ite++) {
			random_shuffle(currentNode, currentNode+13);
/*			
			cout <<"config initial\n";
			for (int i = 0; i < 13; i++)
				cout << currentNode[i] << endl;
*/
			int currentVal = eval(currentNode);
			while (true) {
				int nextEval = -INF;
				for (int i=0; i < 13; i++) {
					for (int k = i+1; k < 13; k++) {
						swap(currentNode[i], currentNode[k]);
						int val = eval(currentNode);
						if (val > nextEval) {
							nextEval = val;
							copy(currentNode, currentNode+13, nextNode);
						}
						swap(currentNode[i], currentNode[k]);
					}
				}
				if (nextEval <= currentVal){
					break;
				}
				copy(nextNode, nextNode+13, currentNode);	
				currentVal = nextEval;
			}
			if (currentVal > sol) {
				sol = currentVal;
				copy(currentNode, currentNode+13, solNode);
			}
		}
		eval(solNode, true);		
	}
	return 0;
}
