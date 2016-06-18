//////////////////////////////////////////////////////
//########### Transformacao de bases ################
/////////////////////////////////////////////////////
/** Obs: o numero deve ser lido do final do vector para o inicio.*/
void toBaseB(int x, int b, vector<int> &num) {
	int q = x, r = 0;
	while (q >= b) {
		r = q % b;
		q = q / b;
	  	num.push_back(r);
	} 	
	num.push_back(q);
} 

long int fromBaseB(const vector<int> &num, int b) {
	long int dec = 0;
	long int mult = 1;
	for (int i = 0; i < num.size(); i++) {
		dec += (num[i]*mult);
		mult *= b;
	}
	return dec;
}
//////////////////////////////////////////////////////
//####################################################
//////////////////////////////////////////////////////
Quantos divisores tem um número?
Sabendo a decomposição em fatores primos de um número, podemos saber quantos divisores ele 
tem se adicionarmos a cada expoente uma unidade e multiplicarmos os resultados.
Exemplo:  120 = 2^3, 3^1, 5^1 => (3 + 1) * ( 1 + 1) * (1 + 1) = 16

/************** Fatoracao em numeros primos ***************************/
typedef map<int, int> prime_map;                                                
void squeeze(prime_map& M, int& n, int p) { for (; n % p == 0; n /= p) M[p]++; }
prime_map factor(int n) {
  prime_map M;
  if (n < 0) return factor(-n);
  if (n < 2) return M;
  squeeze(M, n, 2); squeeze(M, n, 3);
  int maxP = sqrt(n) + 2;
  for (int p = 5; p < maxP; p += 6) {
    squeeze(M, n, p); squeeze(M, n, p+2);
  }
  if (n > 1) M[n]++;
  return M;
}

/************* MDC **************************/

****  Algoritmo de Euclides 

	Suponha dois numeros a,b | a <= b. O algoritmo basea-se no fato de que
o mdc(b,a) = mdc(a, b-a);

**********************************************************************/

  Um modo de calcular o m.d.c. de dois ou mais números é utilizar a decomposição desses números em fatores primos.

1) decompomos os números em fatores primos;
2) o m.d.c. é o produto dos fatores primos comuns.

Acompanhe o cálculo do m.d.c. entre 36 e 90:
36 = 2 x 2 x 3 x 3
90 =       2 x 3 x 3 x 5

O m.d.c. é o produto dos fatores primos comuns =>   m.d.c.(36,90) = 2 x 3 x 3
Portanto m.d.c.(36,90) = 18.

Escrevendo a fatoração do número na forma de potência temos:
36 = 2^2 x 3^2
90 = 2  x 3^2 x5
Portanto m.d.c.(36,90) = 2 x 3^2 = 18.

*********************************************
*  CÁLCULO DO M.D.C. PELO PROCESSO DAS DIVISÕES SUCESSIVAS

        Nesse processo efetuamos várias divisões até chegar a uma divisão exata. O divisor desta divisão é o m.d.c. Acompanhe o cálculo do m.d.c.(48,30).

Regra prática:

1º) dividimos o número maior pelo número menor;
        48 / 30 = 1 (com resto 18)

2º) dividimos o divisor 30, que é divisor da divisão anterior, por 18, que é o resto da divisão anterior, e assim sucessivamente;
        30 / 18 = 1 (com resto 12)

        18 / 12 = 1 (com resto 6)

        12 / 6 = 2 (com resto zero - divisão exata)


3º) O divisor da divisão exata é 6. Então m.d.c.(48,30) = 6.

//Implementacao
private long mdc(long p, long q)
{
    long g;                         /* value of gcd(p,q) */
    if (q > p) return(mdc(q,p));
    if (q == 0)
      return(p);
    g = mdc(q, p%q);
    return(g);
}


