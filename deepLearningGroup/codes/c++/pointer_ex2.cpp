//1-alocacao dinamica de memoria
//2-aritmetica de ponteiros
#include <iostream>
using namespace std;

int main(){

  int *p = new int;
  *p = 10;
  cout << "Endereco de p: " << p << endl;
  cout << "Valor de p: " << *p << endl;
  delete p;

  //---vetores
  int n=5, i, *v;
  v = new int[n];

  for(i=0; i<n; i++) v[i]=i;
  for(i=0; i<n; i++) cout << "v[" << i << "]="<<v[i]<< endl;

  //---aritmetica de ponteiros
  int cont=10,*p2;
  p2 = p;

  for(i=0; i<n; i++){
      *p2 = cont; //coloca o valor de cont na posicao i
      p2++; // avanca o apontador
      cont++; //incrementa o contador
  }
  cout << "--------------------" << endl;
  for(i=0; i<n; i++) cout << "v[" << i << "]="<<v[i]<< endl;

return 0;
}
