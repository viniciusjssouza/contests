#include <stdio.h>
#include <math.h>
#include <map>

using namespace std;

int bc[1001];

// combinação de x e 2
void binomial_coefficient(){
   for (int i=1; i<=1000; i++)
      bc[i] = (i-1) + bc[i-1];
}

unsigned long long distancia(int x1, int y1, int x2, int y2){
   return ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
}

int main(){    
    binomial_coefficient();        
    int n, x, y;
    while(true){       
       scanf("%d",&n);
       if(!n)
          break;
       int pontos[n][2];
		unsigned long long dist;
       int cont=0, quant;
       map<unsigned long long,int> distancias;
       for(int i=0; i<n; i++){
          scanf("%d %d",&x,&y);          
          pontos[i][0]=x;
          pontos[i][1]=y;          
       }
       for(int i=0; i<n; i++){
          for(int j=0; j<n; j++){
             if(i!=j){                
                dist=distancia(pontos[i][0], pontos[i][1], pontos[j][0], pontos[j][1]);
                quant=++distancias[dist];
                if(quant==2)
                   cont++;
                if(quant>2){
                   cont-=bc[quant-1];
                   cont+=bc[quant];
                }   
             }
          }
          //distancias.clear();
       }
       printf("%d\n",cont);
    }
    return 0;
}
