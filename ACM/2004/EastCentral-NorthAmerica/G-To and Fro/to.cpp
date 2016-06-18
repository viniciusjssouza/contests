/*******************************************************************
* G - To and Fro - East Central - North America - 2004 
*
* Autor: Vinicius J. S. Souza
* Data: 07/09/2010
*********************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

string msg;
int col, row;
int rect[20][20];

int main() {
	while (true) {
		scanf("%d", &col);
		if (!col)
			break;
		cin >> msg;
		row = msg.size() / col;
		int pos = 0;
		for (int i = 0; i < row; i++) {
			if (!(i % 2)) {
				for (int k = 0; k < col; k++) 
					rect[i][k] = msg[pos++]; 	
			} else {
				for (int k = col-1; k >= 0; k--) 
					rect[i][k] = msg[pos++]; 	
			}
		}
		pos = 0;
		for (int k = 0; k < col; k++) {
			for (int i = 0; i < row; i++) {
				msg[pos++] = rect[i][k];
			}
		}
		cout << msg << endl;		
	}
	return 0;
} 

