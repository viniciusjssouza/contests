#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	freopen("test.txt", "r", stdin);
	vector<string> meu;
	while (!feof(stdin))
	{
		string aux;
		getline(cin, aux);
		//cout << aux << endl; 
		meu.push_back(aux);
	}
	
	cin.clear();
	freopen("output.txt", "r", stdin);
	for (int i = 0; i < meu.size(); i++)
	{
		string aux;
		getline(cin, aux);
		//cout << aux;
				
		if (aux != meu[i]) 
		{
			cout << "Errado-linha " << i + 1;
			break;
		}
	}
	return 0;
}

