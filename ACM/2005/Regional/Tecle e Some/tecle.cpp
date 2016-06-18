/************************************************************************
* Tecle e Some - Maratona - Regional de 2005
*
* Autor: Vinicius J. S. Souza
* Data: 11/02/2010
* Tecnicas: backtracking
* Dificuldade (0-10): 7
*************************************************************************/

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<deque>
#include<vector>
#include<cmath>
#include<string>
#include<cstdlib>

using namespace std;

typedef unsigned long long int64;
//					0 1 2 3 4 5 6 7 8 9
bool lig[10][10] = {0,0,0,0,0,0,0,1,1,1, 
					0,0,1,0,1,1,0,0,0,0,
					0,1,0,1,1,1,1,0,0,0,
					0,0,1,0,0,1,1,0,0,0,
					0,1,1,0,0,1,0,1,1,0,
					0,1,1,1,1,0,1,1,1,1,
					0,0,1,1,0,1,0,0,1,1,
					1,0,0,0,1,1,0,0,1,0,
					1,0,0,0,1,1,1,1,0,1,
					1,0,0,0,0,1,1,0,1,0	};

int64 S;
int D;
bool used[10];
int seq[20];
vector<string> sols;
bool hasSol = false;
int64 pot[11] = {1, 10l, 100l, 1000l, 10000l, 100000l, 1000000l, 10000000l, 100000000l, 
					1000000000l, 10000000000llu};

inline int64 calculaTotal(int pos) {
	int64 total= 0;
	int size = pos+1;
	int begin = 0, end = D-1;
	while (true) 
	{
		if (end < size) {		
			while (begin <= end)
				total += (pot[end-begin]*seq[begin++]);
			
		}else {
			end = size-1; 
			while (begin <= end)
				total += (pot[end-begin]*seq[begin++]);
        	break;
		}		
		end += D;
	} 
	return total;
}

bool backtrack(int digit, int pos) {
	used[digit] = true;
	seq[pos] = digit;
	
	bool end = false;
	int64 total = calculaTotal(pos);
	if (total > S)
		end = true;
	else if (total == S) {	
		hasSol = true;	
		int size = pos+1;
		string sol;
		sol.resize(size);
		for (int i = 0; i < size; i++) {
			sol[i] = (seq[i] + '0');
		}
		sols.push_back(sol);
	}
	if (!end)
	{
		int size = 10;
		for (int i = 0; i < size; i++) {
			if (!used[i] && lig[digit][i]) {
				if (backtrack(i, pos+1)) {
					break;
				}		
			}		
		}
	}
	used[digit] = false;	
	return end;
}

int main() {
	long s = clock();
	int instancia = 1;
	while (true) {
		scanf("%llu %d", &S, &D);
		if (S == -1 && D == -1)
			break;
		for (int i= 0; i < 10; i++)
			used[i] = 0;
		sols.clear();
		hasSol = false;
		for (int i = 0; i < 10; i++)
			backtrack(i, 0);
		if (hasSol)	{
			printf("#%d\n", instancia++);
			sort(sols.begin(), sols.end());

			int size = sols.size();
			for (int i = 0; i < size; i++) {
				string s = sols[i];
				int size2 = s.size();
				for (int k =0; k < size2; k++) {
					if (k && !(k%D))
						putchar(' ');
					putchar(s[k]);
				}
				putchar('\n');
			}	

		}
		else
			printf("#%d\nimpossivel\n", instancia++);
	}
	return 0;
}
