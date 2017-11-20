# Python script for confusion matrix creation.
from sklearn.metrics import confusion_matrix, classification_report, accuracy_score

target =    [ 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8]
outputed = [ 1, 1, 1, 1, 1, 6, 2, 2, 2, 2, 3, 3, 4, 3, 3, 4, 4, 8, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 4]
results = confusion_matrix(target, outputed)
print 'Confusion Matrix :'
print(results)
print 'Accuracy Score :', accuracy_score(target, outputed)
print 'Report : '
print classification_report(target, outputed)
