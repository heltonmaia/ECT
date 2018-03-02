#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar  2 12:34:54 2018

@author: helton
"""

#convolution example - Book CNN, Figure 3
import numpy as np
from scipy import signal

k       = np.array([[1,1],[1,1]])
img     = np.array([[1,2,3,1],[4,5,6,1],[7,8,9,1]])

result  = signal.convolve2d(img, k, 'valid')
print(result)
