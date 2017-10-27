import os
import numpy as np
import cv2
import time

labels = []
trainingFilenames = []
imgs = []
root = "training_files/"

def gets_training_files():
    """
    Pega todas os nomes das aquivos em training_files
    """
    for classe in os.listdir(root):    
        for img in os.listdir(root+str(classe)):
            trainingFilenames.append(root+str(classe)+"/"+img)
            labels.append(classe)

def SVMParams(svm):
    print("Parametros da SVM:\n\
           Kernel type     :{}\n\
           Type            :{}\n\
           C               :{}\n\
           Degree          :{}\n\
           Nu              :{}\n\
           Gamma           :{}\n\
    ".format(svm.getKernelType(), svm.getType(), svm.getC(), svm.getDegree(), svm.getNu(), svm.getGamma()))


gets_training_files()

i = time.clock()
print("\nAnalizando rotulos....")
for index, file in enumerate(trainingFilenames):    
    #print("Analizando rotulo (Classe|Arquivo)-> {}|{}".format(labels[index], trainingFilenames[index]))
    img = cv2.imread(trainingFilenames[index], 0)
    imgs.append(img.flatten())
imgs = np.array(imgs, dtype=np.float32)
labels = np.array(labels, dtype=np.int32)
f = time.clock()
print("A analise dos rotulos levou: {}s".format(f-i))


#Configura a SVM
#Seta os melhores parametros 
svm = cv2.ml.SVM_create()
svm.setType(cv2.ml.SVM_C_SVC)
svm.setKernel(cv2.ml.SVM_POLY)
svm.setC(1)
svm.setGamma(0.50625)
svm.setDegree(3)

i = time.clock()
print("Treinando o classificador.......")
svm.train(imgs, cv2.ml.ROW_SAMPLE, labels)
f = time.clock()
print("O treinamento levou: {}s".format(f-i))

#Salva a SVM
print("Salvando a SVM.......")
svm.save("rats_and_pitons.yml")
SVMParams(svm)