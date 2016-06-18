/************************************************************************
* ACM 2010 - Greater New York - Fax Machine
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

string bytes;

int run(int i) {
	int sz = bytes.size();
	if (sz - i < 6) {
		return 0;		
	} 
	int k = i+4;
	while (k < sz && bytes[k] == bytes[k-4] && bytes[k+1] == bytes[k-3] && 
		bytes[k] == bytes[k-2] && bytes[k+1] == bytes[k-1] && (k-i) <= 260) {
		k+=2;
	}
	if (k-i > 260)
		return 260;
	if (k >= i+6) {
		return (k-i);			 
	}
	return 0;

}

int nonRun(int i) {
	int sz = bytes.size();
	if (sz - i < 6) {
		return sz - i;	
	} 	
	int k = i+4;	
	while (k < sz && (bytes[k] != bytes[k-2] || bytes[k+1] != bytes[k-1] || 
		bytes[k] != bytes[k-4] || bytes[k+1] != bytes[k-3]) && (k-i) <= 256) {
		k+=2;
	}
	if ((k-i) > 256)
		return 256;
	if (k >= sz)
		return (k-i);			 		
	return (k-4-i);
}

int main() {
	if (debug) {
		bytes = "f4a5a5a5a5";
		cout << run(0) << endl;
		cout << run(2) << endl;
		cout << run(4) << endl;
		cout << run(6) << endl;
		cout << nonRun(0) << endl;
		cout << nonRun(2) << endl;
		cout << nonRun(4) << endl;
		cout << nonRun(6) << endl;
	}

	int P;
	scanf("%d", &P);

	para(p, P) {
		int B, X;
		cin>>X >> B;
		string aux;
		bytes = "";
		for (int s=0; s < B*2; s+=80) {
			cin >> aux;
			bytes+= aux; 
		}
		if (debug)
			cout << "Bytes:" << bytes << endl;
		int sz = bytes.size();
		int n = 0;
		int len = 0;
		for (int i = 0; i < sz; i += len) {
			if ((len = run(i))) {
				n+=2;
			} else {
				len = nonRun(i);
				n += 1 + (len/2);				
			}			
		}

		len = 0;
		printf("%d %d", X, n);
		int conta = 0;
		for (int i = 0; i < sz; i += len) {
			if ((len = run(i))) {
				if (debug)
					cout << "len = " << len << " " << "RUN!\n";
				if (conta % 80 == 0) putchar('\n');
				conta+=2; 	
				printf("%.2X", ((len/2 - 3) | 0x80));
				if (conta % 80 == 0) putchar('\n');
				conta+=2; 	
				printf("%c%c", bytes[i], bytes[i+1]);						
			} else {
				len = nonRun(i);
				if (debug)
					cout << "len = " << len << " " << "NOT RUN!\n";
				if (conta % 80 == 0) putchar('\n');
				conta+=2; 	
				printf("%.2X", ((len/2 - 1)));
				for (int k = 0; k < len; k++) {
					if (conta % 80 == 0) putchar('\n');
					conta++;			
					printf("%c", bytes[i+k]);
				}
			}
			
		}
		putchar('\n');
	}
	return 0;
}
