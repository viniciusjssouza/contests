/*********************************************************************
*
*		Programacao Dinamica
*
************************************************************************/

/************************** 0-1 Knapsack *****************************/

Input: N items, each with various Vi (Value) and Wi (Weight) and max Knapsack size
MW.
Output: Maximum value of items that one can carry, if he can either take or not-take a
particular item.
Let C[i][w] be the maximum value if the available items are {X1,X2,...,Xi} and the
knapsack size is w.
      if i == 0 or w == 0 (if no item or knapsack full), we can't take anything C[i][w] = 0
      if Wi > w (this item too heavy for our knapsack),skip this item C[i][w] = C[i-1][w];
      if Wi <= w, take the maximum of "not-take" or "take" C[i][w] = max(C[i-1][w] ,
C[i-1][w-Wi]+Vi);
      The solution can be found in C[N][W];

for (i=0;i<=N ;i++) C[i][0] = 0;
for (w=0;w<=MW;w++) C[0][w] = 0;
for (i=1;i<=N;i++)
  for (w=1;w<=MW;w++) {
     if (Wi[i] > w)
        C[i][w] = C[i-1][w];
     else
        C[i][w] = max(C[i-1][w] , C[i-1][w-Wi[i]]+Vi[i]);
  }
output(C[N][MW]);

/**************************************************************************/

/**
	Verifica se existe um número t que seja a soma de outros números 
	contidos no vetor 'data'.
	O vetor 'used' deve ter o tamanho da maior soma possível 
*/
memset(used, 0, sizeof(used));
int max= 0;
used[0] = true;
for (int i = 0; i < N && !used[t]; i++) {
	for (int k = max; k >= 0; k--) {
		if (used[k]) {
			used[data[i] + k] = true;
		}
	}	
	max += data[i];
}
