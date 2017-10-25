import os

labels = []
trainingFilenames = []
root = "images/"

def getImages():
    for classe in os.listdir(root):    
        for img in os.listdir(root+str(classe)):
            trainingFilenames.append(root+str(classe)+"/"+img)
            labels.append(classe)
 
getImages()
print labels