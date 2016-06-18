/****************************************************************
* Uva 136 - Ugly Numbers
*
* Autor: Vinicius J. S. Souza
* Data: 09/01/2011
* Tecnicas: teoria dos numeros
* Encontre todas as 1500th combinacoes de 2^x * 3^y * 5^z, com 
*  0 < x,y,z < N, onde N e um valor que estabilize o 1500th ugly number. 
****************************************************************/
#include<iostream>
#include<set>
#include<map>
#include<cmath>
#include<deque>
#include<vector>
#include<algorithm>

using namespace std;

#define N 30


typedef unsigned long long int int64;
int64 divs[N][3];

int main() {
	divs[1][0] = 2;
	divs[1][1] = 3;
	divs[1][2] = 5;
	vector<int64> u;
	u.push_back(1); 
	u.push_back(2); 
	u.push_back(3); 
	u.push_back(5);
	for (int i = 2; i < N; i++) {
		divs[i][0] = divs[i-1][0] * divs[1][0];
		divs[i][1] = divs[i-1][1] * divs[1][1];
		divs[i][2] = divs[i-1][2] * divs[1][2];
		u.push_back(divs[i][0]);
		u.push_back(divs[i][1]);
		u.push_back(divs[i][2]);
	} 
	
	for (int i = 1; i < N; i++) {
		for (int k = 1; k < N; k++) {
			u.push_back(divs[i][0] * divs[k][1]);
		}
	}
	for (int i = 1; i < N; i++) {
		for (int k = 1; k < N; k++) {
			u.push_back(divs[i][0] * divs[k][2]);
//			cout << divs[i][0] * divs[k][1] << endl;
		}
	}
	for (int i = 1; i < N; i++) {
		for (int k = 1; k < N; k++) {
			u.push_back(divs[i][1] * divs[k][2]);
//			cout << divs[i][0] * divs[k][1] << endl;
		}
	}

	for (int i = 1; i < N; i++) {
		for (int k = 1; k < N; k++) {
			for (int m = 1; m < N; m++)
				u.push_back(divs[i][0] * divs[k][1] * divs[m][2]);
		}
	}
		
	sort(u.begin(), u.end());
//	for (int i = 1; i < 100; i++)
//		printf("%lld\n", u[i]);
	cout << "The 1500'th ugly number is " << u[1499] << "." << endl;
	return 0;
}
