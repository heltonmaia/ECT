#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 19 21:57:41 2018

@author: helton
"""
import matplotlib.pyplot as plt
import numpy as np

#%% create signal
NFFT = 1024  
dt   = 0.01
Fs   = int(1.0 / dt)
f1   = 2
f2   = 8
t    = np.arange(0, 10, dt)
s    = np.sin(2 * np.pi *f1* t) + 0.5*np.sin(2 * np.pi * f2*t)

#%% plot values
plt.subplot(311)
plt.plot(t, s)
plt.subplot(312)
plt.psd(s, 512, Fs)
plt.subplot(313)
plt.specgram(s, NFFT, Fs, noverlap=100)

plt.show()
