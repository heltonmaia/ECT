#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

#define MICRO_PER_SECOND 1000000

using namespace std;
using namespace cv;

int blue=0, green=0, red=0, num_foto=0, Range_rgb=20;
int posicao[4]= {0}, coord=0,tam_total_final=300;
int xpos, ypos, frame_width, frame_height;

bool gravar_video=false, gravar_vid_restrito=false, trava=false, foto=false;

Mat cameraFrame,frame_restrito, imagem_salva,saida;

Point centro_massa,centro_orig, Rectp1, Rectp2;

VideoCapture cap;
VideoWriter video;

void condicoes_esp_fot(int xt, int yt, int xcorte, int ycorte, int tam_cortey, Mat D)
{
//copia a imagem para outra (mat) para que possa ser retirada as faixas de texto
//originais do video sem que seja apresentada na imagem original
    Mat mat;
    D.copyTo(mat);

//cria uma faixa preta onde aparece alguns digitos no video

    if(ycorte<=19)
    {
        Point pt1,pt2;
        pt1.x=0;
        pt1.y=0;
        pt2.x=0+340;
        pt2.y=0+(19-ycorte);
        cout<<pt1<<" "<<pt2<<endl;
        rectangle(mat, pt1,  pt2, Scalar(0,0,0), -1);

    }

    else  if(xcorte>=0 && xcorte<=154 && (ycorte+tam_total_final)>=463)
    {
        int apaga, apaga_final;
        if((ycorte + tam_total_final)>=463)
        {
            apaga_final=tam_cortey;
            if((ycorte+tam_total_final)>480)  apaga=tam_cortey-15;
            else apaga=tam_cortey-(15-(frame_height-(ycorte+tam_total_final)));
        }
        Point pt1,pt2;
        pt1.x=0;
        pt1.y=apaga;
        pt2.x=(154-xcorte);
        pt2.y=( apaga_final);
        rectangle(mat, pt1,  pt2, Scalar(0,0,0), -1);
    }


//conjunto de condiçoes para deixar o camundongo sempre no cento da imagem
    if(xt>0 && xt<=frame_width && yt<0)
    {
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));

        vconcat(preto2,mat, saida);

    }
    else if(xt>0 && xt<=frame_width && yt>frame_height)
    {
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));

        vconcat(mat, preto2, saida);
    }
    else if(yt>0 && yt<=frame_height && xt<0)
    {
        Mat preto2(tam_total_final,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));

        hconcat(mat, preto2, saida);
    }
    else if(yt>0 && yt<=frame_height && xt>frame_width)
    {
        Mat preto2(tam_total_final,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));

        hconcat(preto2,mat, saida);
    }
    else if(xt<0 && yt<0)
    {
        Mat preto1(mat.rows,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));
        hconcat(preto1,mat, saida);
        vconcat(preto2,saida, saida);
    }
    else if(xt>frame_width && yt>frame_height)
    {
        Mat preto1(mat.rows,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));
        hconcat(mat,preto1, saida);
        vconcat(saida,preto2, saida);
    }
    else if(xt>frame_width && yt<0)
    {
        Mat preto1(mat.rows,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));
        hconcat(mat,preto1, saida);
        vconcat(preto2,saida, saida);
    }
    else if(xt<0 && yt>frame_height)
    {
        Mat preto1(mat.rows,tam_total_final-mat.cols, CV_8UC3, Scalar(255,255,255));
        Mat preto2(tam_total_final-mat.rows,tam_total_final, CV_8UC3, Scalar(255,255,255));
        hconcat(preto1,mat, saida);
        vconcat(saida,preto2, saida);
    }


// salva a foto
    char nome[30];
    sprintf(nome,"figures/%d.jpg",num_foto);
    if(xt>0 && xt<=frame_width && yt>0 && yt<=frame_height)
    {
        imwrite( nome, mat );

    }
    else imwrite( nome, saida );
    num_foto++;
}

//função relacionada a detecção do mouse
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    //definem a posiçao para o comando abaixo identificar o valor rgb do pixel
    if (event == EVENT_RBUTTONDOWN)
    {
        Vec3f intensity = frame_restrito.at<Vec3b>(y, x);
        blue = intensity.val[0];
        green = intensity.val[1];
        red = intensity.val[2];
        gravar_video=true;
    }
    //pega as posicoes de area desejada para rasteamento do rato
    if (event == EVENT_LBUTTONDOWN)
    {

        posicao[coord]=x;
        coord++;
        posicao[coord]=y;
        coord++;

        if(coord==4)
        {
            gravar_vid_restrito=true;

            //Algumas variáveis que definem o tamanho e os limites dos frames utilizados para todo o processo
            xpos=posicao[2]-posicao[0];
            ypos=posicao[3]-posicao[1];
            Rectp1.x=posicao[0];
            Rectp1.y=posicao[1];
            Rectp2.x=posicao[2];
            Rectp2.y=posicao[3];
            video.open("video/video_resultado.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));
        }
    }
}

//função de modificação da imagem,onde ocorre uma varredura e seleção de pixels em determinado intervalo
// efeitos de redução de ruido, cálculo de centro de massa, e recorte da magem que será salva
void transform(Mat frame)
{
    Mat saida, restrit_cor;

    //compara os valores dos pixels no intervalo dado, e joga o resultado na matriz restrit_cor
    inRange(frame, Scalar(blue - Range_rgb, green - Range_rgb, red - Range_rgb), Scalar(blue + Range_rgb, green + Range_rgb, red + Range_rgb), restrit_cor);

    //efeitos para reduzir ruido
    erode(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(2, 2)));
    dilate(restrit_cor, restrit_cor, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    //retorna aos valores de rgb
    bitwise_and(frame, frame, saida, restrit_cor = restrit_cor);

    //centro de massa
    Moments mu = moments(restrit_cor, true);

    centro_massa.x = mu.m10 / mu.m00;
    centro_massa.y = mu.m01 / mu.m00;

    //captura de imagens tam_total_finalxtam_total_final a partir da imagem original
    if(foto==true)
    {
        int tam_medio=150 ;
        int xcorte = posicao[0]+centro_massa.x-tam_medio;
        int ycorte = posicao[1]+centro_massa.y-tam_medio;
        int tam_cortex=tam_total_final, tam_cond_x=xcorte+tam_cortex;
        int tam_cortey=tam_total_final, tam_cond_y=ycorte+tam_cortey;

        //Verifica a posição do corte e se ajusta para nao pegar fora do frame
        if(ycorte>(frame_height-tam_total_final))
        {
            tam_cond_y=ycorte+tam_total_final;
            tam_cortey=tam_total_final-(ycorte-(frame_height-tam_total_final));
        }
        if(xcorte>(frame_width-tam_total_final))
        {
            tam_cond_x=xcorte+tam_total_final;
            tam_cortex=tam_total_final-(xcorte-(frame_width-tam_total_final));
        }
        if(ycorte<0)
        {
            tam_cond_y=ycorte;
            tam_cortey=tam_total_final+ycorte;
            ycorte=ycorte*(-1)+posicao[1]+centro_massa.y-tam_medio;
        }
        if(xcorte<0)
        {
            tam_cond_x=xcorte;
            tam_cortex=tam_total_final+xcorte;
            xcorte=xcorte*(-1)+posicao[0]+centro_massa.x-tam_medio;
        }
        Mat imagem_Primaria = cameraFrame( Rect(xcorte,ycorte,tam_cortex,tam_cortey));



        condicoes_esp_fot(tam_cond_x, tam_cond_y, xcorte, ycorte, tam_cortey, imagem_Primaria);
    }
}

//função de exibição da imagem capturada e ja modificada
void frame(Mat original)
{

    //seleciona uma parte indicada pelo usuario
    if(gravar_vid_restrito==true)
        frame_restrito = original( Rect(posicao[0],posicao[1],xpos,ypos) );

    transform(frame_restrito);
    namedWindow("original", 1);

    //posição do contro na imagem original
    centro_orig.x=centro_massa.x+posicao[0];
    centro_orig.y=centro_massa.y+posicao[1];

    //Pequeno circulo que marca o centro de massa
    circle(original, centro_orig, 3, Scalar(0, 0, 255), -1);

    //função responsável de gravar os videos
    if (gravar_video==true)
    {
        //myfile << centro_massa.x << " " << centro_massa.y << endl;
        video.write(original);
    }

    //Retangulo que mostra a área onde acontece o tracking
    rectangle(original, Rectp1, Rectp2,Scalar(0, 0, 255),1, 8, 0);

    //exibe o video
    imshow("original", original);
}

//função principal, onde ocorre a captura da imagem
void principal(char *argv[])
{

    char nome_vid[50];
    cout << argv[1];
    sprintf(nome_vid,"%s",argv[1]);
    cap.open(nome_vid);

    //variaveis tamanho do video
    frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    // myfile.open("coordenadas.txt");

    cap >> cameraFrame;

    //mostra o primeiro frame, para o usuário poder selecionar a área do tracking
    if(!cameraFrame.empty())
        imshow("original",cameraFrame);
    else
    {
        cout <<  "Could not open the video file" << endl ;
    }
    while (true)
    {
        if(trava==true) cap >> cameraFrame;

        //funcoes do mouse
        setMouseCallback("original", CallBackFunc, NULL);
        if(trava==true) frame(cameraFrame);
        char c = (char)waitKey(1);

        //esc clicada fecha o prog.
        if (c == 27)
            break;

        //play e pause do video
        if (c == 'p' || c=='P')
        {
            if(trava==true)trava=false;
            else trava=true;
        }
        //captura uma foto do camundongo
        if (c == 'f' || c=='F')foto=true;
        if (c == 'r' || c=='R')coord=0;
    }
    cap.release();
    video.release();

    // Closes all the windows
    destroyAllWindows();
    // myfile.close();
}
