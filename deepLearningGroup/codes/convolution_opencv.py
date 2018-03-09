import cv2
import numpy as np
from scipy import signal

'''
@author: richardson
#convolution example - Book CNN, Figure 3
k = np.array([[1,1], [1,1]])
img = np.array([[1, 2, 3, 1], [4, 5, 6, 1], [7, 8, 9, 1]])

result =  signal.convolve2d(k, img, 'valid')

print(result)
'''

#convolution example - Book CNN, Figure 4
lenna = cv2.imread('lenna.png')
k = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])

cLenna = cv2.filter2D(lenna, -1, k)

cv2.imshow('Lenna', lenna)
cv2.imshow('Convolved Lenna', cLenna)
cv2.waitKey(0)
