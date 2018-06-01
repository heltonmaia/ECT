#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 19 21:57:41 2018

@author: helton
"""
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.mlab as mlab

#%%
NFFT= 1024  
Fs = int(1.0 / dt)
f1 = 2
f2 = 15
dt  = 0.01
t   = np.arange(0, 10, dt)
s = np.sin(2 * np.pi *f1* t)+ 0.5*np.sin(2 * np.pi * f2*t)

#%%
plt.subplot(311)
plt.plot(t, s)
plt.subplot(312)
plt.psd(s, 512, 1 / dt)
plt.subplot(313)
plt.specgram(s, NFFT=NFFT, Fs=Fs, noverlap=100)

plt.show()
