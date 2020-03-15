import socket
from threading import Thread
from time import sleep
 
UDPSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
data = 'server'.encode("utf-8")

# the public IP server
addr = ("47.100.46.11", 3386)
 
# send UDP package to another computer
def threaded_function(arg):
    for i in range(100):
        print('Send ' , str(999) ,'to ', arg)
        UDPSock.sendto(str(999).encode("utf-8"), (arg.split(':')[0], int(arg.split(':')[1])))
        sleep(1)
 
# ask the public IP server for another computer IP
UDPSock.sendto(data, addr)

# receive another computer IP from the public IP server
dest = ''
while len(dest) < 1:
	dest,adr = UDPSock.recvfrom(1024)

dest = str(dest, encoding = "utf-8")
print('Get IP/port', dest.split(':')[0], int(dest.split(':')[1]), 'from 47.100.46.11')

thread = Thread(target = threaded_function, args = (dest, ))
thread.start()

# receive UDP package to another computer
while True:
    data,adr = UDPSock.recvfrom(1024)
    print('Recv' , data , 'from' ,adr)