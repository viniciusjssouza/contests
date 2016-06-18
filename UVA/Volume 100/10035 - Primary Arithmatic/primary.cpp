#include<iostream>
#include<string>

using namespace std;

int main()
{
	while (1)
	{
		string s1, s2;
		cin >> s1 >> s2;
		if (s1 == "0" && s2 == "0") break;
		int min = s1.size()-1;
		if (s2.size()-1 < min)
			min = s2.size()-1;
		int carries = 0;
		int carry = 0;
		int i1 = s1.size()-1, i2 = s2.size()-1;
		for (; min >= 0; min--, i1--, i2--)
		{
			if (carry + (s1[i1] - '0') + (s2[i2] - '0') > 9)
			{
				carries++;
				carry = 1;
			}
			else carry = 0;
		}
		
		for(;i1 >= 0; i1--)
		{
			if (carry + (s1[i1] - '0') > 9)
			{
				carries++;
				carry = 1;
			}
			else carry = 0;
		}
		for (; i2 >= 0; i2--)
		{
			if (carry + (s2[i2] - '0') > 9)
			{
				carries++;
				carry = 1;
			}
			else carry = 0;
		}
		
		if (!carries)
			cout << "No carry operation.\n";
		else if (carries == 1)
			cout << "1 carry operation.\n";
		else
			cout << carries << " carry operations.\n";
	}	
	return 0;
}
