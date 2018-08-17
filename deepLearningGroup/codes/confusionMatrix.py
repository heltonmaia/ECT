#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Aug 12 10:16:39 2018

@author: helton
"""
import seaborn as sn
import pandas as pd

array = [[13,1,1,0,2,0],
     [3,9,6,0,1,0],
     [0,0,16,2,0,0],
     [0,0,0,13,0,0],
     [0,0,0,0,15,0],
     [0,0,1,0,0,15]]     
   
df_cm = pd.DataFrame(array, range(6), range(6))
#plt.figure(figsize = (10,7))
sn.set(font_scale=1.1)#for label size
sn.heatmap(df_cm, annot=True, annot_kws={"size": 11})# font size