# -*- coding: utf-8 -*-
import cv2
import math
import time
import base64
import socket
from time import sleep

port = 23333
resize = 0.8
address = '233.233.233.233'
MAX_LENGTH = 65535 - 16*4

def sendDataSimple():
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

def create_head(data, length=8):
    data_str = str(data)
    return '0'*(length-len(data_str)) + data_str

def sendData(debug=False):
    if cam.isOpened(): 
        success,image=cam.read()
        timestamp = int(round(time.time()*1000*1000))
        timestamp_head = bytes(str(timestamp), 'utf-8')
        res = cv2.resize(image,None,fx=resize, fy=resize, interpolation = cv2.INTER_CUBIC)
        # print(res.shape)
        ret, jpeg=cv2.imencode('.jpg', res)
        data = jpeg.tobytes()
        length = len(data)
        length_head = create_head(length)

        package_remain =  math.ceil(length/MAX_LENGTH)
        send_id = 0
        while package_remain > 0:
            package_head = create_head(package_remain-1)
            if package_remain > 1:
                send_data =  bytes(package_head + length_head, 'utf-8') + timestamp_head + data[send_id*MAX_LENGTH:(send_id+1)*MAX_LENGTH]
            else:
                send_data = bytes(package_head + length_head, 'utf-8') + timestamp_head + data[send_id*MAX_LENGTH:]

            ret = clisocket.sendto(send_data,(address,port))
            if ret != len(send_data):
                continue
            if debug:
                print('Send', str(len(send_data)), 'Bytes, ', str(send_id+1), '/', str(math.ceil(length/MAX_LENGTH)))
            send_id += 1
            package_remain -= 1
    else:
        cam.release()
        clisocket.close()
        print("Service Exit !!!")
        return


if __name__ == '__main__':
    cam = cv2.VideoCapture(0)
    cam.set(3,1920) # width
    # cam.set(4,576) # height
    clisocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    clisocket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 32)
    while True:
        data_len = sendData(True)