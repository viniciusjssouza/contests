#include<iostream>
#include<vector>
#include<algorithm>

#define NEG	-1
#define POS	 1
#define NONE 0

using namespace std;

class ZigZag
{
public:
	ZigZag()
	{}
	
	int longestZigZag(vector<int> &seq)
	{
		vector<int> sinais(seq.size(), NONE);
		vector<int> tabela(seq.size(), 1);
		
		for (int i = 1; i < seq.size(); i++)
		{
			for (int k = i; k >= 0; k--)
			{
				if (seq[i] - seq[k] < 0 && sinais[k] != NEG)
				{
					if (tabela[k] + 1 > tabela[i])
					{
						tabela[i] = tabela[k]+1;
						sinais[i] = NEG;
					}									
				}
				else if (seq[i] - seq[k] > 0 && sinais[k] != POS)
				{
					if (tabela[k] + 1 > tabela[i])
					{
						tabela[i] = tabela[k]+1;
						sinais[i] = POS;
					}
				}
			}
		}
		return tabela[seq.size()-1];
	}
};

int main()
{
	
	return 0;
}
