#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <fstream>

#define MICRO_PER_SECOND 1000000

using namespace std;
using namespace cv;

int blue=0, green=0, red=0,fps, num_foto=0, Range_rgb=20;
int posicao[4]= {0}, coord=0;
int xpos, ypos;

bool gravar_video=false,gravar_vid_restrito=false,trava=false, foto=false;

Mat cameraFrame,frame_restrito, imagem_salva;
Mat preto = imread("preto.png");

Point centro_massa, centro_orig, Rectp1,Rectp2;
VideoCapture cap;
ofstream myfile;

//variaveis de salvamento do video
int frame_width, frame_height;
VideoWriter video1,video2;


void condicoes_esp_fot(int xt, int yt, Mat mat) {

    if(xt>0 && xt<=frame_width && yt<0) {
        for(int x = (preto.rows-mat.rows), xi=0; x <=300 ; x++,xi++) {
            for(int y =0, yi=0; y <=300 ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(xt>0 && xt<=frame_width && yt>frame_height) {
        for(int x =0, xi=0; x <mat.rows ; x++,xi++) {
            for(int y =0, yi=0; y < 300 ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(yt>0 && yt<=frame_height && xt<0) {
        for(int x =0, xi=0; x <300 ; x++,xi++) {
            for(int y =(preto.cols-mat.cols), yi=0; y < 300 ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(yt>0 && yt<=frame_height && xt>frame_width) {
        for(int x = 0, xi=0; x <300 ; x++,xi++) {
            for(int y =0, yi=0; y < mat.cols ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(xt<0 && yt<0) {
        for(int x = (preto.rows-mat.rows), xi=0; x <300 ; x++,xi++) {
            for(int y =(preto.cols-mat.cols), yi=0; y < 300 ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(xt>frame_width && yt>frame_height) {
        for(int x = 0, xi=0; x <mat.rows ; x++,xi++) {
            for(int y =0, yi=0; y < mat.cols ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(xt>frame_width && yt<0) {
        for(int x = (preto.rows-mat.rows), xi=0; x <300 ; x++,xi++) {
            for(int y =0, yi=0; y < mat.cols ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    if(xt<0 && yt>frame_height) {
        for(int x = 0, xi=0; x <mat.rows ; x++,xi++) {
            for(int y =(preto.cols-mat.cols), yi=0; y < 300 ; y++,yi++) {
                preto.at<Vec3b>(x, y)[0] =mat.at<Vec3b>(xi, yi)[0] ;
                preto.at<Vec3b>(x, y)[1] =mat.at<Vec3b>(xi, yi)[1] ;
                preto.at<Vec3b>(x, y)[2] =mat.at<Vec3b>(xi, yi)[2] ;

            }
        }
    }
    char nome[30];
    sprintf(nome,"figures/%d.jpg",num_foto);
    if(xt>0 && xt<=frame_width && yt>0 && yt<=frame_height) {
        imwrite( nome, mat );


    } else imwrite( nome, preto );
    num_foto++;


}


//função relacionada a detecção do mouse
void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
    //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
    if (event == EVENT_RBUTTONDOWN) {
        Vec3f intensity = frame_restrito.at<Vec3b>(y, x);
        blue = intensity.val[0];
        green = intensity.val[1];
        red = intensity.val[2];
        gravar_video=true;
    }

//pega as posicoes de area desejada para rasteamento do rato
    if (event == EVENT_LBUTTONDOWN) {
        posicao[coord]=x;
        coord++;
        posicao[coord]=y;
        coord++;

        if(coord==4) {
            gravar_vid_restrito=true;
            xpos=posicao[2]-posicao[0];
            ypos=posicao[3]-posicao[1];
            Rectp1.x=posicao[0];
            Rectp1.y=posicao[1];
            Rectp2.x=posicao[2];
            Rectp2.y=posicao[3];
            video1.open("video_sem_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
            video2.open("video_com_pontos.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
        }
    }
}

//função de modificação da imagem
Mat transform(Mat entrada) {
    Mat saida, restrit_cor;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz restrit_cor
    inRange(entrada, Scalar(blue - Range_rgb, green - Range_rgb, red - Range_rgb), Scalar(blue + Range_rgb, green + Range_rgb, red + Range_rgb), restrit_cor);

    //efeitos para reduzir ruido
    erode(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
    dilate(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //retorna aos valores de rgb
    bitwise_and(entrada, entrada, saida, restrit_cor = restrit_cor);

    //centro de massa
    Moments mu = moments(restrit_cor, true);
    centro_massa.x = mu.m10 / mu.m00;
    centro_massa.y = mu.m01 / mu.m00;

    //captura de imagens 300x300 a partir da imagem original
    if(foto==true) {
        int tam_total=300,tam_medio=150 ;
        int xcorte = posicao[0]+centro_massa.x-tam_medio;
        int ycorte = posicao[1]+centro_massa.y-tam_medio;
        int tam_cortex=300, tam_cond_x=100;
        int tam_cortey=300, tam_cond_y=100;

        //Verifica a posição do corte e se ajusta para nao pegar fora do frame
        if(ycorte>(frame_height-tam_total)) {
            tam_cond_y=ycorte+tam_total;
            tam_cortey=tam_total-(ycorte-(frame_height-tam_total));
        }
        if(xcorte>(frame_width-tam_total)) {
            tam_cond_x=xcorte+tam_total;
            tam_cortex=tam_total-(xcorte-(frame_width-tam_total));
        }
        if(ycorte<0) {
            tam_cond_y=ycorte;
            cout<<endl<<ycorte<<" yseg "<<endl;
            tam_cortey=tam_total+ycorte;
            ycorte=ycorte*(-1)+posicao[1]+centro_massa.y-tam_medio;
        }
        if(xcorte<0) {
            tam_cond_x=xcorte;
            cout<<endl<<xcorte<<" seg "<<endl;
            tam_cortex=tam_total+xcorte;
            xcorte=xcorte*(-1)+posicao[0]+centro_massa.x-tam_medio;
        }
        Mat imagem_Primaria = cameraFrame( Rect(xcorte,ycorte,tam_cortex,tam_cortey));
        cout<<tam_cond_x<<"  "<<tam_cond_y<<endl;
        condicoes_esp_fot(tam_cond_x, tam_cond_y,imagem_Primaria );
    }
    return saida;
}

//função de exibição da imagem capturada e ja modificada
void frame(Mat original) {

    //seleciona uma parte indicada pelo usuario
    if(gravar_vid_restrito==true)
        frame_restrito = original( Rect(posicao[0],posicao[1],xpos,ypos) );

    Mat Framevid=transform(frame_restrito);

    //exibe a imagem em conjunto com os frames
    putText(original, format("FPS=%d ", fps), Point2f(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255, 255));

    namedWindow("original", 1);

    //posição do contro na imagem original
    centro_orig.x=centro_massa.x+posicao[0];
    centro_orig.y=centro_massa.y+posicao[1];

    //salva o video sem a marca de centro
    if (gravar_video==true) {
        myfile << centro_massa.x << " " << centro_massa.y << endl;
        video1.write(original);
    }

    //Pequeno circulo que marca o centro de massa
    circle(original, centro_orig, 3, Scalar(0, 0, 255), -1);

    //salva o video com a marca de centro
    if (gravar_video==true) video2.write(original);

    //Retangulo que mostra a área onde acontece o tracking
    rectangle(original, Rectp1, Rectp2,Scalar(0, 0, 255),1, 8, 0);

    //namedWindow("Identificação", 1);
    imshow("Identificação", Framevid);
    imshow("original", original);
}

//funnção principal, onde ocorre a captura da imagem
void principal(char *argv[]) {
    //captura o primeiro dispositivo abilitado para camera
    cap.open(0);

    //variaveis tamanho do video
    frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    double resul, tempo = 0;
    int cont_frames = 0;
    struct timeval start_time;
    struct timeval stop_time;

    myfile.open("coordenadas.txt");

    cap >> cameraFrame;

    //mostra o primeiro frame, para o usuário poder selecionar a área do tracking
    if(!cameraFrame.empty())
        imshow("original",cameraFrame);

    gettimeofday(&start_time, NULL);

    while (true) {
        if(trava==true) cap >> cameraFrame;
        cont_frames++;
        gettimeofday(&stop_time, NULL);
        resul = (float)(stop_time.tv_sec - start_time.tv_sec);
        resul += (stop_time.tv_usec - start_time.tv_usec) / (float)MICRO_PER_SECOND;
        tempo += resul;

        if (tempo >= 1.0000) {
            fps = cont_frames;
            tempo = 0;
            cont_frames = 0;
            resul = 0;
            gettimeofday(&start_time, NULL);
        }
        //funcoes do mouse
        setMouseCallback("original", CallBackFunc, NULL);
        if(trava==true) frame(cameraFrame);
        char c = (char)waitKey(1);
        //esc clicada fecha o prog.
        if (c == 27)
            break;
        //play video
        if (c == 'p' || c=='P') {
            if(trava==true)trava=false;
            else trava=true;

        }
        //captura um frame do camundongo
        if (c == 'f' || c=='F')foto=true;

        if (c == 'r' || c=='R')coord=0;
    }
    cap.release();
    video1.release();
    video2.release();

    // Closes all the windows
    destroyAllWindows();
    myfile.close();
}
