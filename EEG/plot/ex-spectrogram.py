#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May 31 17:50:36 2018

@author: helton
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def ssignal(t):
    freq  = 10
    
    sig1  = 0.5*np.sin(2*np.pi*freq*t)
    sig2  = np.sin(2*np.pi*freq*2*t)
    sig   = sig1+sig2
    
    return sig
    
def fourier(sig):
    fftS  = np.abs(np.fft.fft(sig))
    
    return fftS
  

def main():
    sr   = 0.001
    t    = np.arange(0,1,sr)
   
    s       = ssignal(t)
    f       = fourier(s)
    f2,t2,Sxx = signal.spectrogram(s, 1/sr, scaling = 'spectrum')
    
    
    ax1 = plt.subplot(221)
    ax1.plot(t,s)
    ax1.set_title("time")
    plt.ylabel('Amplitude')
    plt.xlabel('Time [sec]')
    
    ax2 = plt.subplot(222)
    plt.xlim(0, 50)
    ax2.plot(f)
    ax2.set_title("Freq")
    
    ax3 = plt.subplot(223)  
    plt.pcolormesh(t2, f2, Sxx)
    plt.colorbar();
    plt.ylim(0, 50)
    plt.ylabel('Frequency [Hz]')
    plt.xlabel('Time [sec]')
    
    plt.show()


if __name__ == "__main__": 
    main()