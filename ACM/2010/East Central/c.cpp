/****************************************************************
* ACM 2010 - East Central USA - C - Maze
*
* Autor: Vinicius J. S. Souza
* Data: 24/10/2011
* Tecnicas: BFS + Grids
***************************************************************/
#include<iostream>
#include<cstdio>
#include<deque>
#include<cstdlib>
#include<cstring>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false

using namespace std;

char f[31][31], b[31][31], l[31][31], r[31][31], u[31][31], d[31][31];

int N;
char parent[31][31][31];
bool visited[31][31][31];

struct pos {
	int x,y,z;
	pos(int x, int y, int z) {
		this->x = x; this->y = y; this->z = z;
	}
};

void readFace(char face[][31]) {
	para(i,0,N) {
		para(k,0,N) {
			scanf("%c", &face[i][k]);
		}
		getchar();
	}	
}

bool canMove(pos p, int incX, int incY, int incZ) {
	int x = p.x+incX;
	int revX = N-1-x;

	int y = p.y+incY;
	int revY = N-1-y;

	int z = p.z+incZ;
	int revZ = N-1-z;
	
	if (revX < 0 || revX >= N || x < 0 || x >= N)
		return false;
	if (revY < 0 || revY >= N)
		return false;
	if (z < 0 || z >= N || revZ < 0 || revZ >= N)
		return false;
	
	if (visited[x][y][z])
		return false;
		
	if (debug) printf("Trying %d %d %d\n", incX, incY, incZ);

	if (f[revY][revX] == 'X') {
		if (debug) printf("Falha F [%d][%d]\n",  revY, revX);
		return false;
	} else if (l[revY][revZ] == 'X') {
		if (debug) printf("Falha L [%d][%d]\n",  revY, revZ);
		return false;
	} else if (u[revZ][revX] == 'X') {
		if (debug) printf("Falha U [%d][%d]\n",  revZ, revX);
		return false;
	} else if (b[revY][x] == 'X') {
		if (debug) printf("Falha B [%d][%d]\n",  revY, x);
		return false;
	} else if (r[revY][z] == 'X') {
		if (debug) printf("Falha R [%d][%d]\n",  revY, z);
		return false;
	} else if (d[z][revX] == 'X') {
		if (debug) printf("Falha D [%d][%d]\n",  z, revX);
		return false;
	} else {
		return true;
	}
}

void move(deque<pos> &fila, pos b, char m) {
	parent[b.x][b.y][b.z] = m;
	visited[b.x][b.y][b.z] = true;
	fila.push_back(b);
}

void bfs() {
	deque<pos> fila;
	fila.push_back(pos(1,1,1));
	memset(parent, '\0', sizeof(parent));
	memset(visited, false, sizeof(visited));
	visited[1][1][1] = true;

	while (!fila.empty()) {
		pos v = fila.front();
		fila.pop_front();
		
		if (debug)
			printf("Em %d %d %d\n", v.x, v.y, v.z);

		if (v.x == N-2 && v.y == N-2 && v.z == N-2) {
			if (debug)printf("No destino!\n");
			return;
		}
		if (canMove(v, 0,0,-1)) {
			if (debug) printf("Move F\n");
			move(fila, pos(v.x, v.y, v.z-1), 'F');
		}
		if (canMove(v, 0,0,1)) {
			if (debug) printf("Move B\n");
			move(fila, pos(v.x, v.y, v.z+1), 'B');
		}
		if (canMove(v, 1,0,0)) {
			if (debug) printf("Move L\n");
			move(fila, pos(v.x+1, v.y, v.z), 'L');
		}
		if (canMove(v, -1,0,0)) {
			if (debug) printf("Move R\n");
			move(fila, pos(v.x-1, v.y, v.z), 'R');
		}
		if (canMove(v, 0,1,0)) {
			if (debug) printf("Move U\n");
			move(fila, pos(v.x, v.y+1, v.z), 'U');
		}	
		if (canMove(v, 0,-1,0)) {
			if (debug) printf("Move D\n");
			move(fila, pos(v.x, v.y-1, v.z), 'D');
		}
	}
	printf("Nao cheguei ao destino!\n");
}

void writeSol(int x, int y, int z) {
	if (x == 1 && y == 1 && z == 1) {
		return;
	}
	if (parent[x][y][z] == 'F') {
		writeSol(x,y,z+1);
	} else if (parent[x][y][z] == 'B') {
		writeSol(x,y,z-1);
	} else if (parent[x][y][z] == 'L') {
		writeSol(x-1,y,z);
	} else if (parent[x][y][z] == 'R') {
		writeSol(x+1,y,z);
	} else if (parent[x][y][z] == 'U') {
		writeSol(x,y-1,z);
	} else if (parent[x][y][z] == 'D') {
		writeSol(x,y+1,z);
	}
	printf("%c", parent[x][y][z]);
}

int main()
{
	while (1) {
		scanf("%d", &N);
		getchar();
		if (!N)
			break;
		readFace(f);
		readFace(r);
		readFace(b);
		readFace(l);
		readFace(u);
		readFace(d);
		
		if (debug) {
			para(i,0,N) {
				para(k,0,N)
					printf("%c", l[i][k]);
				printf("\n");
			}
		}

		bfs();
		writeSol(N-2, N-2, N-2);
		printf("\n");
	}
	return 0;
}
