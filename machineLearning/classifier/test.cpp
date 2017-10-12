// Bibliotecas Padrao
#include <iostream>
#include <vector>
#include <string>

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

// TinyDir
#include "extra_libs/tinydir.h"

#include "extra_libs/evaluation.hpp"

// Rotulos dos arquivos de treino
std::vector<int> expectedLabels;
std::vector<int> predictedLabels;
std::vector<std::string> testFilenames;

//Pega os arquivos e teste e salva os rotulos/arquvios em uma classe vector
void getsTestFiles()
{

    //Abre o diretorio que contem as imagens
    tinydir_dir test_root_dir;
    tinydir_open(&test_root_dir, "test_files");

    // iterate over directories
    while (test_root_dir.has_next)
    {
        // pega o arquivo
        tinydir_file file;
        tinydir_readfile(&test_root_dir, &file);

        // se for um diretorio
        if (file.is_dir)
        {

            std::string numbersDirName = file.name;

            // pula . / .. / .DS_Store (OSX)
            if (numbersDirName != "." && numbersDirName != ".." && numbersDirName != ".DS_Store")
            {

                // atoi nao é muito seguro, porem suficiente para testes
                int currentLabel = atoi(file.name);

                // pega o diretorio com os aquivos de numeros
                numbersDirName.insert(0, "test_files/");

                // abre o diretorio que contem os numeros
                tinydir_dir test_number_dir;
                tinydir_open(&test_number_dir, numbersDirName.c_str());

                // itera pelo diretorio
                while (test_number_dir.has_next)
                {
                    //pega o aquivo
                    tinydir_file testJpgFile;
                    tinydir_readfile(&test_number_dir, &testJpgFile);

                    // pega o nome
                    std::string testJpgFileName = testJpgFile.name;

                    // pula . / .. / .DS_Store (OSX)
                    if (testJpgFileName != "." && testJpgFileName != ".." && testJpgFileName != ".DS_Store")
                    {

                        // diretorio foi iterado completament
                        testJpgFileName.insert(0, numbersDirName + "/");

                        //salva  o nome do arquivo de teste e seu rotulo
                        testFilenames.push_back(testJpgFileName);
                        expectedLabels.push_back(currentLabel);
                    }

                    // pega o proximo arquivo
                    tinydir_next(&test_number_dir);
                }

                // fecha o diretorio
                tinydir_close(&test_number_dir);
            }
        }

        // pega o proximo arquivo
        tinydir_next(&test_root_dir);
    }

    // close directory
    tinydir_close(&test_root_dir);
}

int main(int argc, char **argv)
{

    //Pega os arquivos de teste
    getsTestFiles();

    //Carrega a SVM
    cv::Ptr<cv::ml::SVM> svm = cv::ml::StatModel::load<cv::ml::SVM>("classifier2.yml");

    // Informacoes legais
    int totalClassifications = 0;
    int totalCorrect = 0;
    int totalWrong = 0;

    // itera pelos arquivos de teste
    for (int index = 0; index < testFilenames.size(); index++)
    {

        // le a imagem (grayscale)
        cv::Mat imgMat = cv::imread(testFilenames[index], 0);

        // converte de 2d para 1d
        cv::Mat testMat = imgMat.clone().reshape(1, 1);
        testMat.convertTo(testMat, CV_32F);

        // Tenta prever qual numero foi desenhado
        try
        {
            int predicted = svm->predict(testMat);
            //std::cout<< "expected: " << expectedLabels[index] << " -> predicted: " << predicted << std::endl;
            predictedLabels.push_back(predicted);
            // Status
            totalClassifications++;
            if (expectedLabels[index] == predicted)
            {
                totalCorrect++;
            }
            else
            {
                totalWrong++;
            }
        }
        catch (cv::Exception ex)
        {
        }
    }

    // Calcula as porcentagens
    float percentageCorrect = ((float)totalCorrect / totalClassifications) * 100;
    float percentageIncorrect = 100 - percentageCorrect;

    // Mostras as informacoes legais
    std::cout << std::endl
              << "Numero de classificacoes: " << totalClassifications << std::endl;
    std::cout << "Corretas:  " << totalCorrect << " (" << percentageCorrect << "%)" << std::endl;
    std::cout << "Erradas: " << totalWrong << " (" << percentageIncorrect << "%)" << std::endl;
    std::cout << std::endl;

    Confusion confusion = Confusion(expectedLabels, predictedLabels);
    confusion.print_noInd();

    Evaluation evaluation = Evaluation(confusion);
    evaluation.print();

    
}
