# -*- coding: utf-8 -*-
import cv2
import random
from informer import Informer, config

if __name__ == '__main__':
    # user settings
    config.ADDRESS = '233.233.233.233'
    config.VISION_PORT = 23333
    config.CMD_PORT = 23334
    
    ifm = Informer()
    # get your data
    cam = cv2.VideoCapture(0)
    cam.set(3,1920)
    while True:
        if cam.isOpened(): 
            success,image=cam.read()
            # send your image
            ifm.send_vision(image)
            
            v = random.random()*5
            w = random.random()*10 - 5
            c = False if random.random() > 0.3 else True
            # send your command
            ifm.send_cmd(v, w, c)

        else:
            cam.release()
            print("Service Exit !!!")