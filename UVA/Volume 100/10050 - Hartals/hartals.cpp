/************************************************************************************
 *  Uva Problem 10050 - Hartals - Programming Challenges
 *  
 *  Autor: Vinicius J. S. de Souza
 *  Data: 25/03/2008
 ***********************************************************************************/


#include <iostream>

#define		FRIDAY		6
#define		SATURDAY	0


using namespace std;


int main()
{
//	freopen("input.txt", "r", stdin);
	
	unsigned long long t = 0;
	cin >> t;
	
	for (unsigned long long i = 0; i < t; i++)
	{
		unsigned int counter = 0;
		unsigned int n = 0;
		cin >> n;
		n++;
		bool table[n];
		for (unsigned int k = 0; k < n; k++)
			table[k] = false;
		
		unsigned int p = 0;
		cin >> p;
		for (unsigned int k = 0; k < p; k++)
		{
			unsigned int h = 0;
			cin >> h;
			
			for (unsigned int m = h; m < n; m += h)
			{
				if (table[m])
					continue;
				else
				{
					unsigned int day = 0;
					if (m >= 7)
						day = m % 7;
					else
						day = m;
					if (day != FRIDAY && day != SATURDAY)
					{
						table[m] = true;
						counter++;
					}
				}
			}
		}
		cout << counter << endl;
	}
	return 0;
}
