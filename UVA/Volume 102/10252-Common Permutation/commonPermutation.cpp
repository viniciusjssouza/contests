/**********************************************************************
 * UVa - Problema 10252 - Common Permutation - Programming Challenges
 * 
 * Autor: Vinicius J. S. Souza
 * Data : 14/07/2008 
 **********************************************************************/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	//freopen("input.txt", "r", stdin);
	bool isInicio = true;
	
	while (true)
	{
		string a, b, result = "";
		if (feof(stdin))break;
		if (!isInicio) cout << endl;
		else isInicio = false;

		getline(cin, a);
		getline(cin, b);
		if(a == "" || b == "")
			continue;
		//cout << a << endl << b << endl;
		for (int i = 0; i < a.size(); i++)
		{
			if (a == "" || b == "") break;
			string aux = a.substr(i, 1);
			//cout << aux << endl;
			int pos = b.find(aux);
			if (pos != string::npos)
			{
				result += aux;
				a.erase(i, 1);
				b.erase(pos, 1);
				i--;
			}
			//cout << a << endl << b << endl;						
		}
		sort(result.begin(), result.end());
		cout << result;
	}
	return 0;
}