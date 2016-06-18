#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <hash_set.h>
#include <iostream>

using namespace std;

struct eqstr
{
	bool operator ()(const char* s1, const char* s2)const
	{
		return (strcmp(s1, s2) == 0); 
	}
};

typedef hash_set<const char*, hash<const char*>, eqstr> HashSet; 

bool isPalindromo(string str);
bool contains(string s, HashSet set);
long getIndex(string s);


int main()
{
	char in[100];
	freopen("input.txt", "r", stdin);
	
	while (gets(in) != NULL)
	{
		string s = in;
		HashSet set;
		int numPalindromos = 0;
		for (int k = s.length()-1; k >= 0; k--)
		{
			int begin = 0;
			int len = k+1;
			for (; begin + len <= s.length(); begin++)
			{
				string subs = s.substr(begin,len);
				if (isPalindromo(subs) == true && contains(subs, set) == false)
				{
					numPalindromos ++;
					set.insert(subs.c_str());
				}
			}
		}
		printf("The string '%s' contains %d palindromes.\n", s.c_str(), numPalindromos);
	}
	return 0;
}

bool isPalindromo(string str)
{
	stack<char> pilha;
	queue<char> fila;
	for (int i = 0; i < str.length(); i++)
	{
		pilha.push(str[i]);
		fila.push(str[i]);
	}

	for (int i = 0; i < str.length(); i++)
	{
		if (pilha.top() != fila.front()) return false;
		pilha.pop();
		fila.pop();
	}
	return true;
}

bool contains(string s, HashSet set)
{
	HashSet::iterator it = set.find(s.c_str());
	if (it == set.end()) return false;
	else return true;
}
