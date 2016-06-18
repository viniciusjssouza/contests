/**********************************************************************
* Pole Position - Final Sul-Americana 2008
*
* Autor: Vinicius J. S. Souza
* Data: 02/09/2009
* Tecnicas: Nenhuma...problema ad-hoc
*********************************************************************/

#include<iostream>
#include<vector>

using namespace std;

typedef pair<int, int> pii;

int main()
{
	while (true)
	{
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int input[n][2];
		for (int i = 0; i < n; i++)
			scanf("%d %d", &input[i][0], &input[i][1]);			
		vector<int> out(n, 0);		
		bool ok = true;
		for (int i = 0; i < n; i++)
		{
			int pos = i + input[i][1]; 
			if (pos >= 0 && pos < n && !out[pos] )
				out[pos] = input[i][0];
			else
			{
				ok = false;
				break;
			}	
		} 
		if (ok)
		{
			for (int i = 0; i < n; i++)
			{
				if (i)
					putchar(' ');
				printf("%d", out[i]);
			}
			putchar('\n');	
		}
		else 
			printf("-1\n");
	}	
	return 0;
}
