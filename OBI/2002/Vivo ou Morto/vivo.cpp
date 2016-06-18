#include <cstdio>
#include <list>

using namespace std;

int caso=1;

int main(){
	int p,r,j,ordem,acao;
	while(true){	
		scanf("%d %d",&p,&r);
		if(!p && !r)
			break;
		list<int> jogadores;				
		for(int i=0; i<p; i++){
		   scanf("%d",&j);
			jogadores.push_back(j);
		}
		for(int i=0; i<r; i++){
			scanf("%d %d",&j,&ordem);
			list<int>::iterator ite=jogadores.begin();
			for(int k=0; k<j; k++){
				scanf("%d",&acao);
				if(acao!=ordem)
					ite =jogadores.erase(ite);
				else
					ite++;
			}
		}
		printf("Teste %d\n%d\n", caso++,*jogadores.begin());
	}
}	
		
