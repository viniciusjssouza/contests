/***********************************************************************************
 *  UVa Problem 843 - Volume 8 - Crypt Kicker - Programming Challenges
 * 
 *  Autor: Vinicius J. S. Souza
 *  Data: 17/04/2008
 ***********************************************************************************/

#include <iostream>
#include <string> 
#include <vector>

#define ARRAY_SIZE	200
#define NULL_CHAR	'.'

using namespace std;

string decrypt(string& in);
string getNoSolutionString(string& in);
string analisaPalavra(string& word);

char decod[ARRAY_SIZE], cod[ARRAY_SIZE];
vector<string> dicionario;

int main()
{
	//freopen("input.txt", "r", stdin);
	
	// recebe a entrada
	int n;
	cin >> n;
	// recebe o dicionario
	for (int i = 0; i < n; i++)
	{
		string aux;
		cin >> aux;
		dicionario.push_back(aux);		 
	}
	string aux;
	getline(cin, aux);
	// recebe as linhas e as decodifica
	while (true)
	{
		string input;
		
		if (feof(stdin)) break;
		getline(cin, input);
		if (input == " ") break;
		else if (input == "") continue;
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			decod[i] = NULL_CHAR;
			cod[i] = NULL_CHAR;
		}
		//cout << decrypt(input) << endl;
		
	}
	return 0;	
}


string decrypt(string& in)
{	
	string result = "";
	string word = "";
	for (unsigned int i = 0; i < in.size(); i++)
	{
		if (in[i] == ' ') 
		{
			if (word != "")
			{				
				string aux = analisaPalavra(word);
				if (aux == "")
					result += getNoSolutionString(word);
				else result += aux;				
				word = "";				
			}
			result += ' ';
		}
		else
			word += in[i];		
	}
	if (word != "")
	{
		string aux = analisaPalavra(word);
		if (aux == "")
			result += getNoSolutionString(word);
		else result += aux;				
	}
	return result;
}

string getNoSolutionString(string& in)
{
	string result = "";
	for (int i =0; i < in.size(); i++)
	{
		if (in[i] == ' ') result += ' ';
		else result += '*';		
	}
	return result;
}

string analisaPalavra(string& word)
{
	string result = "";
	for (int i = 0; i < dicionario.size(); i++)
	{
		string dic = dicionario[i];
		if (dic.size() == word.size())
		{
			bool equal = true;
			for (int k = 0; k < dic.size() - 1; k++)
			{
				if ((dic[k] == dic[k+1] && word[k] != word[k+1]) ||
					(word[k] == word[k+1] && dic[k] != dic[k+1]))
				{
					equal = false;
					break;
				}				
			}
			if (equal)
			{
				bool valid = true;
				for (int k = 0; k < dic.size(); k++)
				{
					if (cod[dic[k] + 0] != NULL_CHAR)
					{
						if (cod[dic[k] + 0] != word[k])
						{
							valid = false;
							break;
						}
					}
					else if (decod[word[k] + 0] != NULL_CHAR)
					{
						if (decod[word[k] + 0] != dic[k])
						{
							valid = false;
							break;
						}
					}						
				}
				if (valid)
				{
					for (int k = 0; k < dic.size(); k++)
					{
						decod[word[k] + 0] = dic[k];
						cod[dic[k] + 0] = word[k];
					}
					return dic;
				}
			}
		}
	}
	return result;
}
