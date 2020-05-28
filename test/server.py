# server
import cv2
import socket

cap = cv2.VideoCapture('video.mp4')

address = ('127.0.0.1', 10001)
cnt = 0

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(address)
    s.listen(5)
    ss, addr = s.accept()
    while(cap.isOpened()):
        cnt += 1
        
        ret, img = cap.read()
        img = cv2.resize(img, (img.shape[1],img.shape[0]), interpolation=cv2.INTER_AREA)
        ret, jpeg=cv2.imencode('.jpg', img)

        data = jpeg.tobytes()
        
        # @1
        ss.send(str(len(jpeg)).encode())
        ra = ss.recv(5)
        
        # @2
        print('send')
        ss.sendall(data)
        print('recv')
        ra = ss.recv(5)

    ss.close()
    print('finish')
