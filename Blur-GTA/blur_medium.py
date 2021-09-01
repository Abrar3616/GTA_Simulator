#!/usr/bin/env python

import os
import numpy as np
import cv2 as cv
from time import sleep

#dir = "/home/abrar/gta_live/images/"
dir = "/home/abrar/trajectory-6/"

i = 2
h = 480
w = 640
arr = np.zeros((h,w,3),np.float)

while(True):
    im1 = cv.imread(dir + "{:04d}".format(i) + ".jpg")
    if im1 is None:
        sleep(1)
        if im1 is None:
            break
    im2 = cv.imread(dir + "{:04d}".format(i-1) + ".jpg")
    im3 = cv.imread(dir + "{:04d}".format(i-2) + ".jpg")
    #im1r = cv.resize(im1, (640, 480), interpolation = cv.INTER_AREA)
    #im2r = cv.resize(im2, (640, 480), interpolation = cv.INTER_AREA)
    #im3r = cv.resize(im3, (640, 480), interpolation = cv.INTER_AREA)
    imarr1 = np.array(im1,dtype=np.float)
    imarr2 = np.array(im2,dtype=np.float)
    imarr3 = np.array(im3,dtype=np.float)
    arr = imarr1/3 + imarr2/3 + imarr3/3
    arr = np.array(np.round(arr),dtype=np.uint8)
    cv.imwrite("/home/abrar/trajectory-6-blur/medium1_{:04d}.jpg".format(i), arr)
    i+=1
