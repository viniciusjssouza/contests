/************************************************************
* Electric Bill - ACM 2009 - Final sul americana
*
* Autor: Vinicius J. S. Souza
* Data: 09/10/2010
* Tecnicas: busca binaria
*************************************************************/
#include<iostream>
#include<cstdio>
#include<algorithm>

const long double EPS = 1e-4;

const long double  n1 = 100.0;
const long double  n2 = 10000.0-100.0;
const long double  n3 = 1000000.0-10000;

using namespace std;

long double A, B;

inline int cmp(long double x, long double y = 0, long double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}

long double cwh(long double s) {
	long double c= 0;
	if (cmp(s,2.0*n1) >= 0) {
		c += n1;
		s -= 2.0*n1;
	} else {
		return (c + (s / 2.0));
	}
	if (cmp(s,3.0*n2) >= 0) {
		c += n2;
		s -= 3.0*n2;
	} else {
		return (c+(s / 3.0));
	}
	if (cmp(s,5.0*n3) >= 0) {
		c += n3;
		s -= 5.0*n3;
	} else {
		return (c+(s/5.0));
	}
	return (c+(s/7.0));
}

long double americus(long double c) {
	long double s = 0;
	if (cmp(c,n1) >= 0) {
		s += 2.0*n1;
		c -= n1;
	} else {
		return (s + (c*2.0));
	}
	if (cmp(c,n2) >= 0) {
		s += 3.0*n2;
		c -= n2;
	} else {
		return (s + (c*3.0));
	}
	if (cmp(c,n3) >= 0) {
		s += 5.0*n3;
		c -= n3;
	} else {
		return (s + (c*5.0));
	}
	return (s+(c*7.0));
}


int isSol(long double cm, long double ca) {
	long double cv = ca - cm;
	long double sm = americus(cm);
	long double sv = americus(cv);
	long double dif = (sv - sm);
	cmp(dif - B);
	
}

int main() {
	while (true) {
		scanf("%llf %llf", &A, &B);
		if (!A && !B)
			break;
		long double ca = cwh(A);
		long double fim = ca / 2.0;
		long double atual = fim / 2.0;
		long double inicio = 0;
		//cout << "CA = " << ca << endl;
		// busca binaria
		while (true) {
			int dif = isSol(atual, ca);
			if (cmp(dif) == 0)
				break;
			//printf("Atual: %lf\n", atual);
			if (dif > 0) {
				inicio = atual;
			} else {
				fim = atual;
			}		
			atual = (inicio + fim) / 2.0;
		}	
		printf("%.0llf\n", americus(atual));	
	}
	return 0;
}
