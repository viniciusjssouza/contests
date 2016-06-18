/***************************************************************************************
* UVA 742 - The MTM Machine - Final Sul-America - 1999
*
* Autor: Vinicius J. S. Souza
* Data: 20/04/2009
* Tecnicas utilizadas: backtracking
*********************************************************************************/

#include<iostream>
#include<string>

using namespace std;

string backtrack(string number, bool isFirst = true)
{
	if (number[0] == '2')
	{
		if (number.size() == 1) return "NOT ACCEPTABLE";
		else return (number.substr(1, number.size()-1));
	}
	else if (number[0] == '3')
	{
		if (number.size() == 1) return "NOT ACCEPTABLE";
		string result = backtrack(number.substr(1, number.size()-1), false);
		if (isdigit(result[0]))
			return (result + "2" + result);
		return result;
	}
	return "NOT ACCEPTABLE";		
}

int main()
{
	string line;
	bool isInicio = true;
	while (true)
	{
		cin >> line;
		if (!isInicio) putchar('\n');
		else isInicio = false;
		if ((line.size() == 1 && line[0] == '0') || line == "") break;
		if (line.find("0") != string::npos)
			printf("NOT ACCEPTABLE");
		else cout << backtrack(line);

	}
	return 0;
}
