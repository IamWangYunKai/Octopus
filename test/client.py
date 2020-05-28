# client
import cv2
import socket
import numpy as np

address = ('127.0.0.1', 31506)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(address)

while True:
    length_data = s.recv(10)
    s.send('OK'.encode())
    cnt = int(length_data.decode())

    data = b''
    while cnt > 0:
        sp_data = s.recv(cnt)
        data += sp_data
        cnt -= len(sp_data)

    image = cv2.imdecode(np.frombuffer(data, dtype='uint8'), cv2.IMREAD_COLOR)

    cv2.imshow('get',image)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

s.close()