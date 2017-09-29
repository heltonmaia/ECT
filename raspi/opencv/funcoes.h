#ifndef FUNCOES_H
#define FUNCOES_H

using namespace std;
using namespace cv;


//funnção principal, onde ocorre a captura da imagem
void principal();

//função de modificação da imagem
Mat transform(Mat frame);

//função de transformação, restrição e exibição da imagem capturada
void frame(Mat frame, double fps);

//função relacionada a detecção do mouse
void CallBackFunc(int event, int x, int y, int flags, void* userdata);



#endif