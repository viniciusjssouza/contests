/**************************************************/
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



/***********************************************************************
	Algoritmos de Busca
************************************************************************/

---- Hill Climbing Algorithm ------
   currentNode = startNode;
   loop do
      L = NEIGHBORS(currentNode);
      nextEval = -INF;
      nextNode = NULL;
      for all x in L 
         if (EVAL(x) > nextEval)
              nextNode = x;
              nextEval = EVAL(x);
      if nextEval <= EVAL(currentNode)
         //Return current node since no better neighbors exist
         return currentNode;
      currentNode = nextNode;

/*
 * Implementacao do algoritmo Quick-Union com compressao
 */
public class UnionFind {
    int[] sz;
    int[] id;

    public UnionFind(int N) {
        sz = new int[N];
        id = new int[N];
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    public int root(int i) {
        int v = i;
        while(id[i] != i)
            i = id[i];
        // compressao
        while (id[v] != v){
           int temp = id[v];
           id[v] = i;
           v = temp;
        }
        return i;
    }

    public boolean find(int i, int k)
    {
        return root(i) == root(k);
    }

    public void union(int i, int k) {
        int ri = root(i);
        int rk = root(k);
        if (ri != rk) {
            if (sz[i] < sz[k]) {
                id[ri] = rk;
                sz[rk] += sz[i];
            }
            else {
                id[rk] = ri;
                sz[ri] += sz[rk];
            }
        }
    }
}

