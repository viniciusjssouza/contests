/****************************************************************
* ACM 2010 - East Central USA - H - We've got chemistry babe
*
* Autor: Vinicius J. S. Souza
* Data: 13/11/2011
* Tecnicas: Solucao de sistemas lineares NxM usando Eliminacao Gaussiana
***************************************************************/
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<string>
#include<map>
#include<deque>
#include<cmath>

using namespace std;

#define debug false
#define trace(x...) 	if(debug)printf(x);
#define MAXN 50
#define OFFSET MAXN / 2
#define para(i,B,N) for(int i = B; i < N; i++)

int L,R;
int rows, cols;
int lsystem[MAXN][MAXN];
map<string, int> idx;

typedef pair<int,int> pii;

void printSystem() {
	if (debug) {
		para(i,0,rows) {
			para(k,0,cols) {
				trace("%d ", lsystem[i][k]);
			}
			trace("\n");
		}			
		trace("------------\n");
	}	
}

/******************************************************************
* Linear system functions using Gaussian Elimination to solve
* systems of the form rows X cols
******************************************************************/
int gcd(int p, int q) {
	if (q > p) return(gcd(q,p));
    if (q == 0)
      return(p);
    int g = gcd(q, p%q);
	
    return(g);
}

void swap_rows(int lsystem[][MAXN], int a, int b) {
	para(k,0,cols) {
		swap(lsystem[a][k], lsystem[b][k]);
	}
}

/**
	Calcs the solutions of a linear system in the triangular form.
	The solutions are put in the cols columns of the system matrix.
	Returns false in case of an insolvable system.
*/
bool solve(int lsystem[][MAXN], int rows, int cols) {
	printSystem();
	para(c,1,100001) {
		bool ok = true;
		for(int r = rows-1; r>= 0; r--) {
			trace("Trying row %d e c=%d\n", r, c);
			if (r >= cols-2) {
				int num = lsystem[r][cols-1]*c;
				int den = lsystem[r][cols-2];
				if (!num && !den)
					continue;
				if (!den) {
					trace("ERROR: denominador 0 na solucao do sistema\n");
					return false;
				}
				if (num % den) {
					ok = false;
					break;
				}
				int sol = num/den;
				trace("Valores diferentes para solucao: %d = %d\n", lsystem[cols-2][cols], sol);
				if (lsystem[cols-2][cols] != 0 && lsystem[cols-2][cols] != sol) {
					//trace("Valores diferentes para solucao: %d = %d\n", lsystem[cols-2][cols], sol);
					return false;
				}
				else lsystem[cols-2][cols] = sol; 
			} else {
				int num = lsystem[r][cols-1]*c;
				int den = lsystem[r][r];
				for(int k = cols-2; k>r; k--) {
					num -= (lsystem[r][k]*lsystem[k][cols]);				
				}
				if (!den) {
					trace("ERROR: denominador 0 na solucao do sistema\n");
					return true;
				}
				if (num % den) {
					ok = false;
					break;
				}
				lsystem[r][cols] = num/den;				
			}
		}		 
		if (ok) {
			lsystem[cols-1][cols] = c;
			return true;
		} 
		para(r,0,cols) {
			lsystem[r][cols] = 0;
		}
	}
	return false;
}


/**
	Reduce the linear system to the triangular form.
	Returns false in case of an insolvable system.
*/
bool reduction(int lsystem[][MAXN], int rows, int cols) {
	int ik = 0;
	if (rows+1 < cols)
		return false;
	if (cols < 2)
		return false;

	para(ik,0,cols-2) {
		// selects the bigger absolute value from the ik column.
		int bigger = 0;
		int brow = 0;
		para(r,ik,rows) {
			if (abs(lsystem[r][ik]) > bigger) {
				bigger = abs(lsystem[r][ik]);
				brow = r;
			}
		}
		if (bigger == 0) {
			trace("ERROR: pivot = 0 !!!!!\n");
			return 0;
		}
		// swap the rows to pivote
		swap_rows(lsystem, ik, brow);
		// put zeros in the column bellow of ik		
		para(r,ik+1,rows) {
			int tmp = lsystem[r][ik];	
			if (!tmp)
				continue;
			para(k,ik,cols) {
				lsystem[r][k] = lsystem[r][k]*lsystem[ik][ik]-lsystem[ik][k]*tmp;
			}
			int div = -1;
			para(k,ik+2,cols) {
				if (div < 0) div = gcd(abs(lsystem[r][k-1]), abs(lsystem[r][k]));
				else div = gcd(div,abs(lsystem[r][k]));
			}
			if (div < 0) div = 1;
			if (div > 0) {
				para(k,ik+1,cols) {
					lsystem[r][k] /= div;
				}
			}
		}
		printSystem();
	}
	return true;
}

/***************************************************************** 
*	Functions to extract the linear system matrix from the input 
*
*****************************************************************/
inline int readInt(const string &in, int &k) {
	string digits = "";
	while (isdigit(in[k]) && k < in.size()) {
		digits += in[k++];
	}
	if (digits == "")
		return -1;
	int n = atoi(digits.c_str()); 
	trace("ReadInt: %d\n", n);
	return n;
}

inline int getElementRow(const string &element) {
	map<string,int>::iterator ite = idx.find(element);
	int row = 0;
	if (ite == idx.end()) {
		idx[element] = row = rows++;	
	} else {
		row = (*ite).second;
	}
	trace("Element %s, row %d\n", element.c_str(), row);
	return row;
}

deque<pii> q[20]; 

void extract_elements(const string &in, int col) {
	trace("Extracting %s\n", in.c_str());
	
	int sz = in.size();
	int inParenthesis = 0;
	for(int k=0; k < sz; ) {
		if (in[k] == '(') {
			k++;
			inParenthesis++;	
		} else if (in[k] == ')') {
			// get the parenthesis multiplier
			k++;
			int mult = readInt(in, k);
			trace("Multiplier: %d\n", mult);
			while (!q[inParenthesis].empty()) {
				pii par = q[inParenthesis].front();
				q[inParenthesis].pop_front();					
				if (inParenthesis > 1) {
					q[inParenthesis-1].push_back(par);
				}
				int row = par.first;
				if (lsystem[row][col] == 0)
					lsystem[row][col] += mult * par.second;
				else
					lsystem[row][col] *= mult;					
				if (inParenthesis == 1 && col >= L)
					lsystem[row][col]*=-1;				
			}			
			inParenthesis--;			
			if (inParenthesis == 0) {
				
			}
		} else {
			string element = "";
			if (isupper(in[k])) {
				element += in[k++];
				while(islower(in[k]) && k < sz) {
					element += in[k++];
				}
			}
			int n = readInt(in,k);
			if (n < 0)
				n = 1;		
			int row = getElementRow(element);
			if (!inParenthesis) {
				lsystem[row][col] += n;
				if (col >= L)
					lsystem[row][col]*=-1;
				trace("System[%d][%d] = %d\n", row, col, lsystem[row][col]);	
			} else {
				trace("Pushing %d = %d\n", 	row, n);	
				q[inParenthesis].push_back(pii(row, n));
			}
		}
	}
}

void getlsystem() {
	rows = 0;
	cols = L+R;
	memset(lsystem,0,sizeof(lsystem));
	idx.clear();
	string in;
	para(i,0,L+R) {
		cin >> in;
		extract_elements(in,i);
	}	
}
/***************************************************** End of Input functions */

int main() {
	int ncase = 1;
	while(1) {
		scanf("%d %d", &L, &R);
		if (!L && !R)
			break;
		getlsystem();
		printSystem();
		printf("Case %d:", ncase++);
		if (!reduction(lsystem, rows, cols)) {
			printf(" No\n");
			continue;
		}
		if (!solve(lsystem,rows,cols)) {
			printf(" No\n");
			continue;
		}
		// verify negative solutions (invalid)
		bool ok = true;
		para(k,1,cols-1) {
			if ((lsystem[k][cols] > 0 && lsystem[k-1][cols] < 0) ||
				(lsystem[k][cols] < 0 && lsystem[k-1][cols] > 0) || lsystem[k][cols] == 0) {
				ok = false;
				break;
			}
		}
		if (ok == false)
			printf(" No\n");
		else {
			para(k,0,cols) {
				printf(" %d", abs(lsystem[k][cols]));	
			}			
			printf("\n");
		}
	}		
	return 0;v
}	

