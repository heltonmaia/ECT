//Declarando e imprimindo com ponteiros
#include <iostream>
using namespace std;

int main(){
  int a = 1024;
  int *p;
  p = &a;

  cout << "Endereco de p: " << p << endl;
  cout << "Valor de p: " << *p << endl;

  *p = 5;
  cout << "Endereco de p: " << p << endl;
  cout << "Agora p vale: " << *p << endl;

return 0;
}
