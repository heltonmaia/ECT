import os
import numpy as np
from PIL import Image

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

STANDARD_SIZE = (300, 300)
def img_to_matrix(filename):
    """
    Pega um nome de arquivo e o transforma em um array numpy de pixels RGB
    """
    img = Image.open(filename)
    img = img.resize(STANDARD_SIZE)
    img = list(img.getdata())
    img = map(list, img)
    img = np.array(img)
    return img

def flatten_image(img):
    """
    Pega um (m, n) numpy array e o transforma em um array (1, m * n)
    """
    s = img.shape[0] * img.shape[1]
    img_wide = img.reshape(1, s)
    return img_wide[0]

gets_training_files()
data = []
for file in trainingFilenames:
    img = img_to_matrix(file)
    img = flatten_image(img)
    data.append(img)

data = np.array(data)
print data 


