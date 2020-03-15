import socket

UDPSock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
listen_addr = ("", 3386)
UDPSock.bind(listen_addr)

server_addr = {}
client_addr = {}

while True:
    data, addr = UDPSock.recvfrom(1024)
    data = str(data, encoding = "utf-8")
    if str(data) == 'server':
        server_addr = {} # clear
        server_addr[str(addr[0])] = str(addr[1])
        print(addr , 'is connected as a server')
    elif str(data) == 'client':
        client_addr = {} # clear
        client_addr[str(addr[0])] = str(addr[1])
        print(addr , 'is connected as a client')
    else:
        print('Error data:', data, 'from', addr)

    if len(server_addr) > 0 and len(client_addr) > 0 :
        print('Ready to start NAT ！')
        for server_ip in list(server_addr.keys()):
            for client_ip in list(client_addr.keys()):
                # exchange IP & port to each other
                data_s2c = server_ip + ":" + server_addr[server_ip]
                data_c2s = client_ip + ":" + client_addr[client_ip]
                UDPSock.sendto(data_s2c.encode("utf-8"), (client_ip, int(client_addr[client_ip])))
                UDPSock.sendto(data_c2s.encode("utf-8"), (server_ip, int(server_addr[server_ip])))