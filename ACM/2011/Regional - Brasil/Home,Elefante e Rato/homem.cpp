/****************************************************************
* ACM 2011 - Regional Brasil -Homem Elefante e Rato
*
* Autor: Vinicius J. S. Souza
* Data: 15/10/2011
* Tecnicas: Segmentation Tree + lazy propagation + SCANF!!
***************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>

#define para(i,B,N) for(int i = B; i < N; i++)
#define debug false
#define trace(x...) 	if(debug)printf(x);

using namespace std;

class SegmentTree
{
     public:
	 int *h, *e, *r;
	 int *updates;
	 int size;
	 int qh, qr, qe;

     SegmentTree(int N) {
          int x = (int)(ceil(log2(N)))+1;
          size = 2*(int)pow(2,x);
          h = new int[size];
		  e = new int[size];
		  r = new int[size];	
		  updates = new int[size];          
		  para(i,0,size)
			updates[i] = 0;
     }
	 
	 void calcul(int node) {
		 h[node] = h[2*node] + h[2*node+1];
		 e[node] = e[2*node] + e[2*node+1];
		 r[node] = r[2*node] + r[2*node+1];
	 }

	 inline void refresh(int node) {
		if (updates[node] == 0)
			return;
		if (node*2+1 < size) {
			updates[node*2] += updates[node];
	    	updates[node*2+1] += updates[node];
		}
		int mod = updates[node] % 3;
		int htemp = h[node];
		int etemp = e[node];
		int rtemp = r[node];
		if (mod == 1) {
			e[node] = htemp;
			r[node] = etemp;
			h[node] = rtemp;
		} else if (mod == 2) {
			r[node] = htemp;
			e[node] = rtemp;
			h[node] = etemp;
		}
		updates[node] = 0; 
     }	

     void initialize(int node, int start,
                         int end) {
          if (start==end) {
             h[node] = 1;
			 e[node] = r[node] = 0;
		  } else {
              int mid = (start+end)/2;
              initialize(2*node,start,mid);
              initialize(2*node+1,mid+1,end);
			  calcul(node);
          }
     }

     void query(int node, int start,
                   int end, int i, int j) {
		 trace("Em (%d, %d)\n", start, end);
		 if (updates[node] > 0) {
			trace("Query Refreshing %d x\n", updates[node]);
			refresh(node);
		 }	
		 if (i>end || j<start) {
			trace("Fora do intervalo\n");
            return;
		 }
		 if (start>=i && end<=j) {
			trace("Dentro do intervalo: %d %d %d\n", h[node], e[node], r[node]);
		    qh += h[node];
			qr += r[node];
			qe += e[node];
			return;
		 }
         int mid = (start+end)/2;

         query(2*node,start,mid,i,j);
         query(2*node+1,mid+1,end,i,j);
		 trace("Soma: %d %d %d\n", qh, qe, qr);
     }
	
	 void update(int node, int start, int end, int i, int j) {
		trace("Em (%d %d)\n", start, end);
		if (updates[node] > 0) {
			trace("Refreshing %d x\n", updates[node]);
			refresh(node);	
		}
		if (i>end || j<start) {
			trace("Fora do intervalo\n");
			return;
		}
		if (start >= i && end <= j) {
			trace("Dentro do intervalo\n");
			trace("Refreshing back\n");
			updates[node] = 1;
			return refresh(node);						
		} else {
			trace("Descendo...\n");
			int mid = (start+end)/2;
		    update(2*node,start,mid, i, j);
		    update(2*node+1,mid+1,end, i, j);
			trace("Refreshing back (%d %d)\n", start, end);
			calcul(node);
			updates[node] = 0;			
		}
	 }
};

int main()
{
    int i,j,N, M;
	char op;
	while (scanf("%d %d" ,&N, &M) == 2) {
		SegmentTree s(N);
		s.initialize(1,0,N-1);
		para(m, 0, M) {
			getchar();
			scanf("%c %d %d", &op, &i, &j);
			if (op == 'C') {
				s.qr = s.qe = s.qh = 0;
				s.query(1,0,N-1,i-1,j-1);
				printf("%d %d %d\n", s.qh, s.qe, s.qr);				
			} else {
				s.update(1,0,N-1,i-1,j-1);
			}			
		}
		printf("\n");
	}
	return 0;
}
