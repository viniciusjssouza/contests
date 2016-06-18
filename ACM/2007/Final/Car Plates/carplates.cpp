#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;

string sm = "", si = "";
long c = 0;

long coef[2][7] = {260000*26, 260000, 10000, 1000, 100, 10 ,1, 
		2100*21*21*21, 2100*21*21, 2100*21, 2100, 100, 10 ,1};
long MAX = 0;

bool isLegal()
{
	if (si == sm) return false;
	if (si.size() != 7)
		return false;
	if (!isalpha(si[0]) || !isalpha(si[1]) || !isalpha(si[2]))
		return false;
	if ((isalpha(si[3]) && !isalpha(si[4])) || 
		(!isalpha(si[3]) && isalpha(si[4])))
		return false;
	if (!isdigit(si[5]) || !isdigit(si[6]))
		return false;
	
	if (isalpha(si[3]))
	{
		string aux = si;
		if (aux.find("A") != string::npos)
			return false;
		if (aux.find("C") != string::npos)
			return false;
		if (aux.find("M") != string::npos)
			return false;
		if (aux.find("I") != string::npos)
			return false;
		if (aux.find("P") != string::npos)
			return false;
	}
	return true;
}	

long getNumber(string &str)
{
	long number = 0;
	int base = 1;
	if (isdigit(str[3]))
		base = 0;
	for (int i = 0; i < 7; i++)
	{
		if (isalpha(str[i]))
		{
			int decr = 0;
			if (base == 1)
			{
				if (str[i] >= 'P') decr = 5;
				else if (str[i] >= 'M') decr = 4;
				else if (str[i] >= 'I') decr = 3;
				else if (str[i] >= 'C') decr = 2;
				else decr= 1;				
			}
			number += (str[i] - 'A' - decr) * coef[base][i];
		}
		else if (isdigit(str[i]))
			number += (str[i] - '0') * coef[base][i];
	}
	return number;
}

bool isNewer(string &sm)
{
	int i = 0;
		
	if (isdigit(si[3]) && isalpha(sm[3]))
		return false;
	if (isalpha(si[3]) && isdigit(sm[3]))
		return true;

	while(si[i] == sm[i])
		i++;
	if (si[i] > sm[i])
		return true;
	else
		return false;
}

bool isInInterval()
{
	long numM = getNumber(sm);
	long numI = getNumber(si);

	if (isalpha(sm[3]))
	{
		if (numM + c >= numI)
			return true;
		else 
			return false;
	}
	else
	{
		if (numM + c < MAX)
		{
			if (isalpha(si[3]))
				return false;
			else
			{
				if (numM + c >= numI)
					return true;
				else 
					return false;
			}
		}
		else if (isdigit(si[3]))
			return true;
		else
		{
			long aux = numM + c - MAX -1;
			if (aux >= numI)
				return true;
			else 
				return false;			
		}
	}
}


int main()
{
	//freopen("in.txt", "r", stdin);
	string max = "ZZZ9999";
	MAX = getNumber(max);
	while (1)
	{
		cin >> sm >> si  >> c;
		if (sm == "*" && si == "*" && !c)
			break;
		if (!isLegal() || !isNewer(sm) || !isInInterval())
		{
			cout << "N\n";
			continue;
		}
		else cout << "Y\n";
	}
	return 0;
}
