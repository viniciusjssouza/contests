#include<iostream>

using namespace std;

#define	QUEEN 1
#define PAWN 2
#define	FREE 0		

int N, K, gridSize;
int grid[20][20];
unsigned long long total = 0;

bool checkKnight(int i, int k)
{
   if ((i-2) >= 0 && (k-1 >=0) && grid[i-2][k-1] == QUEEN)
      return true;
   if ((i-1) >= 0 && (k-2) >=0 && grid[i-1][k-2] == QUEEN)
      return true;
   if ((i-2) >= 0 && (k+1) < gridSize && grid[i-2][k+1] == QUEEN)
      return true;
   if ((i-1) >= 0 && (k+2) < gridSize && grid[i-1][k+2] == QUEEN)
      return true;   
   return false;
}

bool checkBishop(int i, int k)
{
   for (int y = i-1, x = k+1; (y >= 0) && (x < gridSize); y--, x++)
   {
      if (grid[y][x] == PAWN)
	 return false;
      if (grid[y][x] == QUEEN)
	 return true;
   }
   for (int y = i-1, x = k-1; (y >= 0) && (x >= 0); y--, x--)
   {
      if (grid[y][x] == PAWN)
	 return false;
      if (grid[y][x] == QUEEN)
	 return true;
   }
   return false;
}

bool checkRook(int i, int k)
{
   for (int y = i-1; y >= 0; y--)
   {
      if (grid[y][k] == PAWN) 
	 return false;
      if (grid[y][k] == QUEEN)
	 return true;
   }
   for (int x = k-1; x >= 0; x--)
   {
      if (grid[i][x] == PAWN) 
	 return false;
      if (grid[i][x] == QUEEN)
	 return true;
   }
   return false;
}

void backtrack(int i, int k, int nPawn, int nQueen, int v)
{
   if (v == QUEEN) cout << "Rainha ";
   else if (v==PAWN) cout << "Peao ";
   else cout << "Free ";
   cout << "at " << i << ", " << k << endl;
 
   if (i >= gridSize || k >= gridSize)
      return;
   if (v == QUEEN && (checkKnight(i, k) || checkBishop(i, k) || checkRook(i,k))) 
   {
      cout << "Solution not possible\n";
      return;
   }
   if (!nPawn && !nQueen)
   {
      total++;
      cout << "Solution Found\n";
      return;
   }
   grid[i][k] = v;
   int nextI = (k+1) < gridSize ? i : i+1;
   int nextK = (k+1) < gridSize ? k+1 : 0;
   if (nPawn)
      backtrack(nextI, nextK, nPawn-1, nQueen, PAWN);
   if (nQueen)
      backtrack(i+1, 0, nPawn, nQueen-1, QUEEN);
   backtrack(nextI, nextK, nPawn, nQueen, FREE);
   grid[i][k] = FREE;
}

int main()
{
   while (!feof(stdin) && scanf("%d %d", &N, &K) == 2)
   {
      total = 0;
      gridSize = N-K;
      for (int i = 0; i < gridSize; i++)
	 for (int k = 0; k < gridSize; k++)
	    grid[i][k] = FREE;
      backtrack(0, 0, K-1, N, PAWN);
      backtrack(0, 0, K, N-1, QUEEN);
      backtrack(0, 0, K, N, FREE);
      cout << total << endl;
   }
   return 0;
}


 
