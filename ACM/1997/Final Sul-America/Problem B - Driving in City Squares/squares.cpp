/**************************************************************************
* Maratona - Final Brasileira 1998 - Problema B - Driving in City Squares
* UVA - 774
* Autor: Vinicius J. S. Souza
* Data: 23/03/2009
* Tecnicas utilizadas: grafos + dijkistra
*****************************************************************************/

#include<iostream>
#include<string>
#include<cmath>
#include<vector>

#define MAX 1000000

using namespace std;

int h, v, n, m, total;
vector<int> lin, col;
vector<bool> isLin, isCol;
vector< vector<int> > mapa;

int toIndex(int y , int x)
{
	return (y*v + x);
}

void toPair(int index, int &x, int &y)
{
	y = index / n;
	x = index % n;
}

/******* Dijkistra *************/
int getCaminhoMin(vector< vector<int> > &grafo, int x1, int y1, int x2, int y2)
{
    vector<bool> intree(total, false);
    vector<int> distance(total, MAX);
    
    int w; 
    int weight;
    int dist; 
    int v = mapa[y1][x1];
    distance[v] = 0;
    bool isInicio = true;    

    while (intree[v] == false) 
    {
        intree[v] = true;
	//cout << v << endl;        
	//cout << y << " : " << x << "     " << distance[hum] << "\n";				
	for (int i=0; i< total; i++) 
        {
	    if (grafo[v][i] >= MAX) continue;	
            if (isInicio && isLin[y1] && (mapa[y1][x1] == i || mapa[y1-1][x1] == i))	
	    	weight = 0;
	    else if  (isCol[x1] && (mapa[y1][x1] == i || mapa[y1][x1-1] == i))
		weight = 0;		
	    else if  (isLin[y2] && (mapa[y2][x2] == i || mapa[y2-1][x2] == i))
		weight = 0;
	    else if  (isCol[x2] && (mapa[y2][x2] == i || mapa[y2][x2-1] == i))
		weight = 0;	  
            else weight = grafo[v][i];
            if (distance[i] > (distance[v]+weight)) 
            	distance[i] = distance[v]+weight;            
        }
	isInicio = false;
	dist = MAX;
	
        for (int i=0; i < total; i++)
        {
        	if ((intree[i]==false) && (distance[i] < dist)) 
        	{
        		dist = distance[i];
        		v = i;
        	}
        }

	
    }
/* 
   for (int i = 0; i < total; i++)
		cout << "Dist de "<< i << ": " << distance[i] << endl;	
*/
    return distance[mapa[y2][x2]];
}



int main()
{
	while (scanf("%d %d", &n, &m) == 2)
	{
		cin >> h >> v;
		total = h*v;
		n++,m++;
		lin = vector<int>(1,0);
		col = vector<int>(1, 0);	
		isLin = vector<bool>(m,false);
		isCol = vector<bool>(n, false); 	
		vector< vector<int> > grafo(total, vector<int>(total, MAX));
		mapa = vector<vector<int> > (m, vector<int> (n)); 
		int taxas[h][v];
		register int aux;

		for (int i = 1; i < h; i++)
		{
			cin >> aux;
			lin.push_back(aux);	
			isLin[aux] = true;		
		}
		lin.push_back(m);
		for (int i = 1; i < v; i++)
		{
			cin >> aux;
			col.push_back(aux);
			isCol[aux] = true;			
		}	 		
		col.push_back(n);
		for (int i = 0; i < h; i++)
		{
			for (int k = 0; k < v; k++)
			{
				cin >> aux;
				int w = toIndex(i,k);
				
				if (k+1 < v)
				{
	//				cout << toIndex(i, k+1) << endl;
					grafo[toIndex(i,k+1)][w] = aux;
				}
				if (i-1 >= 0)			
					grafo[toIndex(i-1,k)][w] = aux;
				if (k-1 >= 0)
					grafo[toIndex(i,k-1)][w] = aux;
				if (i+1 < h)
					grafo[toIndex(i+1, k)][w] = aux;
			}
		}
		int x = 0, y = 0, regiao = 0;
		for (int i = 0; i < lin.size()-1; i++)
		{
			for (int k = 0; k <col.size()-1; k++)
			{
				for (int y = lin[i]; y < lin[i+1]; y++)
				{
					for (int x = col[k]; x < col[k+1]; x++)
					{
						mapa[y][x] = regiao;	
					}
				} 
				regiao++;
			}
		}
/*		
		for (int i = 0; i < m; i++)
		{
			for (int k = 0; k < n; k++)
			{
				cout << mapa[i][k] << ' ';	
			}
			cout << endl;
		}
*/
		int x1, y1, x2, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		cout << getCaminhoMin(grafo, x1, y1, x2, y2) << endl; 
		char end; 
		cin >> end;
	}
	return 0;
}
