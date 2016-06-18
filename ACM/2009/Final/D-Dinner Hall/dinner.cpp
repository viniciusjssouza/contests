/********************************************************************************
* Dinner Hall - ACM - Latin America 2009
*
* Autor: Vinicius J. S. Souza
* Data: 06/10/2010
* Tecnicas: greedy
*********************************************************************************/
#include<iostream>
#include<cstdio>
#include<vector>
#include<deque>
#include<algorithm>

using namespace std; 

typedef pair<int,char> pic;

int N;

int main() {
	while (1) {
		scanf("%d", &N);
		if (!N)
			break;
		deque<int> undef;	
		vector<pic> data;
		for (int i = 0; i < N;i++) {
			int hh, mm, ss;
			char c;
			scanf("%d:%d:%d %c", &hh, &mm, &ss, &c);
			data.push_back(pic(hh*3600 + mm *60 + ss, c));
		}
		sort(data.begin(), data.end());
		int conta = 0;
		for (int i = 0; i < N; i++) {
			if (data[i].second == '?')
				undef.push_back(i);
			else if (data[i].second == 'E')
				conta++;
			else if (data[i].second == 'X')
				conta--;				
		}
		
		while (conta > 0) {
			data[undef.back()].second = 'X';
			undef.pop_back();
			conta--;
		}
		while (conta < 0) {
			data[undef.front()].second = 'E';
			undef.pop_front();
			conta++;
		}
		int half = undef.size() / 2;
		for (int i = 0; i < undef.size(); i++) {
			if (i < half)
				data[undef[i]].second = 'E';
			else	
				data[undef[i]].second = 'X';
		}
		
		int maior = 0;
		conta = 0;
		for (int i = 0; i < N; i++) {
			if (data[i].second == 'E')
				conta++;
			else if (data[i].second == 'X')
				conta--;
			maior = max(conta, maior);
		}
		printf("%d\n", maior);
	}
	return 0;
}