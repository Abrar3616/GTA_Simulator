#!/usr/bin/env python

import os
import numpy as np
import cv2 as cv
from PIL import Image
from time import sleep

dir = "/home/abrar/gta_live/images/"
i = 1
h = 480
w = 640
arr = np.zeros((1080,1920,3),np.float)

while(True):
    im1 = cv.imread(dir + "{:04d}".format(i) + ".jpg")
    if im1 is None:
        sleep(1)
        if im1 is None:
            break
    im2 = cv.imread(dir + "{:04d}".format(i-1) + ".jpg")
    im1r = cv.resize(im1, (640, 480), interpolation = cv.INTER_AREA)
    im2r = cv.resize(im2, (640, 480), interpolation = cv.INTER_AREA)
    imarr1 = np.array(im1,dtype=np.float)
    imarr2 = np.array(im2,dtype=np.float)
    arr = imarr1/2+imarr2/2
    arr = np.array(np.round(arr),dtype=np.uint8)
    cv.imwrite("/home/abrar/blur_gta/low_{:04d}.jpg".format(i), arr)
    i+=1
