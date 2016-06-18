/*****************************************************************************
* UVa - 299 - Train Swapping
*
* Autor: Vinícius J. S. Souza
* Data: 02/02/2011
*****************************************************************************/

#include<iostream>
#include<cstdio>

using namespace std;

#define INF 0x3fffffff

int N, vet[51];

int mergeSort(int inf, int sup) {
	if (inf >= sup-1)
		return 0;
	int half = (sup+inf) / 2;
	int szL = half - inf + 1;
	int szR = sup - half + 1;	
	int total = mergeSort(inf, half) + mergeSort(half, sup);
	int tmpL[szL], tmpR[szR];
	
	tmpL[szL-1] = tmpR[szR-1] = INF;
	
	int i = inf;
	for (int k = 0; i < half; k++, i++) {
		tmpL[k] = vet[i];
	}
	for (int k = 0; i < sup; k++, i++) {
		tmpR[k] = vet[i];
	}
	int iteL = 0, iteR = 0;
	for (int k = inf; k < sup; k++) {
		if (tmpR[iteR] < tmpL[iteL]) {
			total += (szL-iteL-1);
			vet[k] = tmpR[iteR++];
		} else {
			vet[k] = tmpL[iteL++];
		}
	}	
	return total;
}

int main() {
	int ntest = 0;
	scanf("%d", &ntest);
	for (int i = 0; i < ntest; i++) {
		scanf("%d", &N);
		for (int n = 0; n < N; n++) {
			scanf("%d", &vet[n]);
		}
		printf("Optimal train swapping takes %d swaps.\n", mergeSort(0, N));
		/*for (int i = 0; i < N; i++)
			printf("%d ", vet[i]);
		cout << endl;
		*/
	} 	
	return 0;
}