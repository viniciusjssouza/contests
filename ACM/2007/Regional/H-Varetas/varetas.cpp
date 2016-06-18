/***************************************************************************
* H-Varetas - Regional 2007
*
* Autor: Vinicius J. S. Souza
* Data: 14/09/2009
* Tecnicas: ad-hoc
*****************************************************************************/

#include<iostream>

using namespace std;

int main()
{
	while(true)
	{
		int N, total = 0, comp, qnt;
		scanf("%d", &N);
		if (!N) break;
		for (int i = 0; i < N; i++)
		{
			scanf("%d %d", &comp, &qnt);
			total += (qnt / 2);
		}
		printf("%d\n", (total/2));			
	}
	return 0;
}
