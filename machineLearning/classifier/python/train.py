import os
import numpy as np
import cv2

labels = []
trainingFilenames = []
root = "training_files/"

def gets_training_files():
    """
    Pega todas os nomes das aquivos em training_files
    """
    for classe in os.listdir(root):    
        for img in os.listdir(root+str(classe)):
            trainingFilenames.append(root+str(classe)+"/"+img)
            labels.append(classe)

gets_training_files()

data = []

print("Analizando rotulos....")
for index, file in enumerate(trainingFilenames):
    #print("Analizando rotulo (Classe|Arquivo)-> {}|{}".format(labels[index], trainingFilenames[index]))
    img = cv2.imread(trainingFilenames[index],0)
    data.append(img)
    
'''
cv2.imshow('Mice',data[132])
cv2.waitKey(0)
cv2.destroyAllWindows()
'''

