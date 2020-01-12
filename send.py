# -*- coding: utf-8 -*-
import socket
import cv2
import base64
from time import sleep

port = 23333
resize = 0.8
address = '233.233.233.233'

def sendData():
    if cam.isOpened(): 
        success,image=cam.read()
        res = cv2.resize(image,None,fx=resize, fy=resize, interpolation = cv2.INTER_CUBIC)
        ret, jpeg=cv2.imencode('.jpg', res)
        data = jpeg.tobytes()
        if len(data) > 65535:
        	print(str(len(data)), ' > 65535')
        	res = cv2.resize(image,None,fx=resize/2, fy=resize/2, interpolation = cv2.INTER_CUBIC)
	        ret, jpeg=cv2.imencode('.jpg', res)
	        data = jpeg.tobytes()
        print(res.shape)
        ret = clisocket.sendto(data,(address,port))
        return ret

    else:
        cam.release()
        clisocket.close()
        print("Service Exit !!!")
        return

if __name__ == '__main__':
    cam = cv2.VideoCapture(0)
    ret = cam.set(4,320)
    clisocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    clisocket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 32)
    while True:
        data_len = sendData()