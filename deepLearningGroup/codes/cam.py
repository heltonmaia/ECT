# -*- coding: utf-8 -*-
"""
@author:helton
"""
import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):
    # Capture camera frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # show live video
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# release the capture
cap.release()
cv2.destroyAllWindows()
