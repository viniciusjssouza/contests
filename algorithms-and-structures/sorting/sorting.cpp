/**************************************************************************
*				SORTING
*
*************************************************************************/

void selectionSort(int v[], int N) {
	for (int i = 1; i < N-1; i++) {
		int pos = i;
		for (int k = i+1; k < N; k++) {
			if (v[pos] > v[k])
				pos = k;
		}
		int tmp = v[i];
		v[i] = v[pos];
		v[pos] = tmp;
	}	
}

void insertSort(int v[], int N) {
	for (int i = 1; i < N; i++) {
		int key = v[i];
		int k = i-1;
		for (; k >= 0 && key < v[k]; k--) {
			v[k+1] = v[k];
		}
		v[k+1] = key;
	}	
}


void mergeSort(vector<int> &vet, int sup, int inf)
{
	if ( (sup - inf) <= 1)
		return;
	if ( (sup - inf) == 2)
	{
		if (vet[inf] > vet[sup-1])
		{
			int temp = vet[inf];
			vet[inf] = vet[sup-1];
			vet[sup-1] = temp;
			nTrocas++;
		}
		return;
	}
	
	int half = (sup+inf) / 2;
	mergeSort(vet, half, inf);
	mergeSort(vet, sup, half); 	

	vector<int> temp(sup-inf);
	int ptrInf = inf, ptrSup = half;
	int i = 0;
	for (; ptrInf < half && ptrSup < sup; i++)
	{
		if (vet[ptrSup] < vet[ptrInf])
		{
			temp[i] = vet[ptrSup];
			ptrSup++;
			nTrocas += (half - ptrInf);
		}
		else
		{
			temp[i] = vet[ptrInf];
			ptrInf++;
		}
	}
	if (ptrSup < sup)
		ptrInf = ptrSup;
	for (;i < temp.size(); i++, ptrInf++)
		temp[i] = vet[ptrInf];

	for (int k = inf, i = 0; k < sup; k++, i++)
		vet[k] = temp[i];
}

/*********************** Busca Binaria *****************************************/
private ITEM searchR(int l, int r, KEY v)    {  
    if (l > r) return null;  
    int m = (l+r)/2;  
    if (equals(v, st[m].key())) return st[m];  
    if (less(v, st[m].key()))  
         return searchR(l, m-1, v);  
    else return searchR(m+1, r, v);  
  }  
ITEM search(KEY v)  
  { return searchR(0, N-1, v); } 
