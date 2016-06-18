/************************************************************************
* ACM 2010 - Greater New York - Show me the fax
*
* Autor: Vinicius J. S. Souza
* Data: 13/07/2011
* Tecnicas: nenhuma em especial.
* Dificuldade: 4
***********************************************************************/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>

#define para(i, N) for(int i = 0; i < N; i++)
#define debug false

using namespace std;

string bytes, result;
map<char,int> val;
int nibbles = 0;

inline int parse(int i) {
	return 16*val[bytes[i]]+val[bytes[i+1]];
}

inline void addResult(int i) {
	result += bytes.substr(i, 2);
	nibbles+=2;	
	if (nibbles % 80 == 0) {
		result += "\n";
	}
}

int main() {	
	val['0'] = 0;
	val['1'] = 1;
	val['2'] = 2;
	val['3'] = 3;
	val['4'] = 4;
	val['5'] = 5;
	val['6'] = 6;
	val['7'] = 7;
	val['8'] = 8;
	val['9'] = 9;
	val['A'] = 10;
	val['B'] = 11;
	val['C'] = 12;
	val['D'] = 13;
	val['E'] = 14;
	val['F'] = 15;	
	int P;
	scanf("%d", &P);
	para (p, P) {
		int X, B;
		scanf("%d %d", &X, &B);
		bytes = "";
		string aux;
		for(int b = 0; b < B; b+=40) {
			cin >> aux;
			bytes += aux;
		}
		if (debug)
			cout << "Bytes: " << bytes << endl;
		result = "";
		nibbles = 0;
		for (int i = 0; i < bytes.size();) {
			int count = parse(i);
			if (count >= 128) {
				count = count - 128 + 3;
				i+=2;
				para(c, count) {	
					addResult(i);
				}
				i+=2;				
			} else {
				count++;				
				i+=2;
				para(c, count) {
					addResult(i);
					i+=2;
				}	
			}				
		}
		printf("%d %d\n", X, nibbles/2);
		cout << result;
		if (result[result.size()-1] != '\n')
			cout << endl;
	}
	return 0;
}
