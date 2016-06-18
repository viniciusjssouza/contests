#include<iostream>
#include<deque>
#include<sstream>
#include<string>
#include<algorithm>

#define	LESTE	 0
#define	NORTE	 1
#define	OESTE	 2
#define	SUL	 3

#define MAX	1000000000

using namespace std;

struct Step
{
	int vertice;
	int anterior;
	int nChanges;
	int dist;
	deque<int> caminho;
};

int goal, nSquares, playerReach, nPlayers, size, nVertices, vInicio;
int nKicks, distanceFinal;
deque<int> parentFinal;

int toVertice(const int &lin, const int &col)
{
	return (lin*size + col);
}

void toXY(const int &lin, const int &col, int &x, int &y)
{
	y = (size-1) - lin;
	x = col - nSquares;    
}

void toMatriz(int &lin, int &col, const int &x, const int &y)
{
	lin = (size-1) - y;
	col = x + nSquares;
}

void toMatriz(int &lin, int &col, const int &v)
{
	lin = v / size;
	col = v % size;
}

void verticeToXY(const int &v, int &x, int &y)
{
	int lin, col;
	toMatriz(lin, col, v);
	toXY(lin, col, x, y);
}

bool changed(const int ant2, const int ant1, const int atual)
{
	if (ant1 < 0 || ant2 < 0) return false;
	int xant1, xant2, x, yant2, yant1, y;
	toMatriz(yant2, xant2, ant2);
	toMatriz(yant1, xant1, ant1);
	toMatriz(y, x, atual);
	if ( (xant2 == xant1 && xant1 != x) || (yant2 == yant1 && yant1 != y) )
		return true;
	return false;
}

void backtrack(const deque< deque<bool> > &campo, deque<int> &changes, deque<int> &dist, const Step &step)
{
	int x, y, lin, col;
	toMatriz(lin, col, step.vertice);
	toXY(lin, col, x, y);

	if (y == size-1 && x <= goal && x >= -goal && step.dist <= distanceFinal && step.nChanges < nKicks) 
	{
		parentFinal = step.caminho;
		nKicks = step.nChanges;
		distanceFinal = step.dist;
		return;
	}
			
	if (col +1 < size && !campo[lin][col+1] && (step.dist + 1) <= dist[step.vertice+1] && 
		changed(step.anterior, step.vertice, step.vertice+1) + step.nChanges <= changes[step.vertice+1])
	{
		Step next;
		next.vertice = step.vertice + 1;
		next.dist = step.dist+1;
		next.nChanges = step.nChanges + changed(step.anterior, step.vertice, next.vertice);
		next.anterior = step.vertice;
		next.caminho = step.caminho;
		next.caminho.push_back(next.vertice);
		dist[next.vertice] = next.dist;
		changes[next.vertice] = next.nChanges;
		backtrack(campo, changes, dist, next); 
	}
	if (lin-1 >= 0 && !campo[lin-1][col] && (step.dist+1) <= dist[step.vertice-size] && 
		changed(step.anterior, step.vertice, step.vertice-size) + step.nChanges <= changes[step.vertice-size])
	{
		Step next;
		next.vertice = step.vertice - size;
		next.dist = step.dist+1;
		next.nChanges = step.nChanges + changed(step.anterior, step.vertice, next.vertice);
		next.anterior = step.vertice;
		next.caminho = step.caminho;
		next.caminho.push_back(next.vertice);

		dist[next.vertice] = next.dist;
		changes[next.vertice] = next.nChanges;
		backtrack(campo, changes, dist, next); 
	}
	if (col -1 >= 0 && !campo[lin][col-1] && (step.dist + 1) <= dist[step.vertice-1] && 
		changed(step.anterior, step.vertice, step.vertice-1) + step.nChanges <= changes[step.vertice-1])
	{
		Step next;
		next.vertice = step.vertice - 1;
		next.dist = step.dist+1;
		next.nChanges = step.nChanges + changed(step.anterior, step.vertice, next.vertice);
		next.anterior = step.vertice;
		next.caminho = step.caminho;
		next.caminho.push_back(next.vertice);

		dist[next.vertice] = next.dist;
		changes[next.vertice] = next.nChanges;
		backtrack(campo, changes, dist, next); 
	}
	if (lin +1 < size && !campo[lin+1][col] && (step.dist + 1) <= dist[step.vertice+size] && 
		changed(step.anterior, step.vertice, step.vertice+size) + step.nChanges <= changes[step.vertice+size])
	{
		Step next;
		next.vertice = step.vertice + size;
		next.dist = step.dist+1;
		next.nChanges = step.nChanges + changed(step.anterior, step.vertice, next.vertice);
		next.anterior = step.vertice;
		next.caminho = step.caminho;
		next.caminho.push_back(next.vertice);

		dist[next.vertice] = next.dist;
		changes[next.vertice] = next.nChanges;
		backtrack(campo, changes, dist, next); 
	}
}

void find_path()
{
	stringstream resp;
	int x, y, xant1=MAX,xant2=MAX+1,yant1=MAX,yant2=MAX+1;
	int lin, col;
	resp << "(0,0)";
	for(int i = 0; i < parentFinal.size(); i++)
	{		
		verticeToXY(parentFinal[i],x, y);
		if((xant2==xant1 && xant1!=x) || (yant2==yant1 && yant1!=y))
		   resp<<"("<<xant1<<","<<yant1<<")";
		xant2=xant1;
		yant2=yant1;
		xant1=x;
		yant1=y;
	}
	verticeToXY(parentFinal.back(), x, y);
	resp<<"("<<x<<","<<y<<")";
	cout<<"Goal with "<< (nKicks+1) <<" kicks: "<< resp.str() << endl;
}


int main()
{
	int lin0, col0, x0 = 0, y0 = 0;
	int scenario = 0;
	while (true)
	{
		cin >> nSquares;
		if (!nSquares) break;
		scenario++;
		cin >> goal >> playerReach >> nPlayers;
		size = 2*nSquares+1;
		nVertices = size*size;
		toMatriz(lin0, col0, x0, y0);
		vInicio = toVertice(lin0, col0);

		deque< deque<bool> > campo(size, deque<bool>(size, false));
		for (int m = 0; m < nPlayers; m++) 
		{
			int posX, posY, lin, col;
			cin >> posX >> posY;
			toMatriz(lin, col, posX, posY);
			for (int i = lin-playerReach; i <= lin+playerReach; i++)
				for (int k = col-playerReach; k <= col+playerReach; k++)
					if (k >= 0 && k < size && i >= 0 && i < size)
						campo[i][k] = true;						 
		}
/*
		for (int i = 0; i < size; i++)
		{	
			for (int k = 0; k < size; k++)
				cout << campo[i][k] << " ";
			cout << endl;
		}			
		cout << endl;
*/
		nKicks = MAX, distanceFinal = MAX;
		Step step;
		step.dist = 0; step.nChanges= 0; step.vertice = vInicio; step.anterior = -1;
		deque<int> changes(nVertices, MAX), dist(nVertices, MAX);
		step.caminho.push_back(vInicio);
		dist[vInicio] = 0;
		changes[vInicio] = 0;
		backtrack(campo, changes, dist, step);				

/*
		cout << "Parent:\n";
		for (int i = 0; i < parentFinal.size(); i++)
		{
			int xc, yc;
			verticeToXY(parentFinal[i], xc, yc);	
			cout << xc << " : " << yc << endl;
		}
		cout << "\n\n";
*/

		printf("Scenario %d.\n", scenario);
		if (nKicks == MAX)
			printf("Situation Impossible\n");
		else
			find_path();		
		putchar('\n');
	}
	return 0;
}

