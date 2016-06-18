/** 
* UVA 10029 - Edit Steps Ladder - Programming Challenges 
* Tecnica: Programacao Dinamica
* Autores: Vinicius J. S. Souza, Diego Carvalho Domingues
* Data: 04/03/2009
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector< string > dicionario(25001);
vector< int > tamanhos(25001);
vector< int > maximo(25001,0);

bool isEditStep(const string &str1, int tam1, const string &str2, int tam2){
	int size1 = tam1, size2 = tam2;
	if (abs(size2-size1) > 1)
		return false;
	int conta = 0;
	for (int i = 0, k = 0; i < size1 || k < size2; i++, k++){
		if (str1[i] != str2[k])
		{
			if (size1 < size2)
				i--;				
			else if (size2 < size1)
				k--;
			conta++;
			if (conta > 1) return false;
		}
	}
	if (conta == 1)
		return true;
	return false;
}

int main(){
   int palavras=1,max=-1;
   maximo[0]=1;
   while(cin>>dicionario[palavras]){
      tamanhos[palavras]=dicionario[palavras].size();
      for(int i=palavras-1; i>=0; i--){
         if(maximo[palavras]<maximo[i]+1){
            if(isEditStep(dicionario[i],tamanhos[i],dicionario[palavras],tamanhos[palavras])){
               maximo[palavras]=maximo[i]+1;
               if(maximo[palavras]>max)
                  max=maximo[palavras];
            }
         }
      }
      palavras++;
   }
   cout<<max+1<<endl;
   return 0;
}
