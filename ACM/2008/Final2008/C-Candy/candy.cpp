#include <stdio.h>
#include <vector>

using namespace std;

int main(){
    while(true){
       int m,n,atual_col,atual_lin,resultado=0;
       scanf("%d %d",&m,&n);
       if(!m && !n)
          break;
       vector < int > maxcol(n);
       vector < int >  maxlin(m);
       for(int i=0; i<m; i++){
          atual_lin=0;
          for(int j=0; j<n; j++){
             scanf("%d",&atual_col);             
             maxcol[j]=atual_col;
             if(atual_col>atual_lin)
                atual_lin=atual_col; 
             for(int k=j-2; k>=j-3 && k>=0; k--){
                if(maxcol[j]<atual_col+maxcol[k]){
                   maxcol[j]=atual_col+maxcol[k];
                   if(maxcol[j]>atual_lin)
                      atual_lin=maxcol[j];
                }
             }
          }
          maxlin[i]=atual_lin;
          if(atual_lin>resultado)
             resultado=atual_lin; 
          for(int k=i-2; k>=i-3 && k>=0; k--){
             if(maxlin[i]<atual_lin+maxlin[k]){
                maxlin[i]=atual_lin+maxlin[k];
                if(maxlin[i]>resultado)
                   resultado=maxlin[i];
             }
          }
       }
       printf("%d\n",resultado);
    }
    return 0;
}
