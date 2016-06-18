#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int caso = 1;

int main(){
	while(true){	
		int n,m;
		cin>>n;
		if(!n)
			break;
		string nome1,nome2;
		map<string,int> nomes;
		vector<string> amigos(n);	
		vector<int> graus(n);
		vector< vector<int> > relacoes(n,vector<int>());
		for(int i=0; i<n; i++){
			cin>>nome1;
			amigos[i]=nome1;
			nomes[nome1]=i;
		}
		for(int i=0; i<n; i++){
			cin>>nome1;
			cin>>m;
			graus[nomes[nome1]]=m;
			for(int j=0; j<m; j++){
				cin>>nome2;
				relacoes[nomes[nome2]].push_back(nomes[nome1]);
			}
		}
		bool ok;
		string resp;
		int cont=0;		
		//for(int i=0; i<n; i++)
				//for(int j=0; j<relacoes[i].size(); j++)
						//cout<<relacoes[i][j]<<" ";
		//cout<<endl;		
		while (true){
      	ok=false;			
			for(int i=0; i<n; i++){
				if(graus[i]==0){
 					graus[i]=-1;
					cont++;
					ok=true;
					resp+=amigos[i] + "";
					if (cont < n)
						resp += " ";
					for(int j=0; j<relacoes[i].size(); j++)
						graus[relacoes[i][j]]--;
				}
			}
			if(ok==false || cont==n)
   			break;
		}
		printf("Teste %d\n", caso++);
		if(cont==n)
			cout<<resp<<endl;
		else
			cout<<"impossivel"<<endl;
	}
}
	
	
