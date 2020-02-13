# -*- coding: utf-8 -*-
import json
import socket
import random
from time import sleep

port = 23334
address = '233.233.233.233'

def sendData():
    data = {'v':random.random()*5, 'w':random.random()*10-5, 'c':False if random.random() > 0.3 else True}
    print('send data:', data)
    data = json.dumps(data).encode()
    ret = clisocket.sendto(data,(address,port))
    return ret

if __name__ == '__main__':
    clisocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    clisocket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 32)
    while True:
        sendData()
        sleep(0.5)