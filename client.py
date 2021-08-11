import socket
import array
import struct

msgFromClient = "Hello UDP Server"

bytesToSend = str.encode(msgFromClient)

serverAddressPort = ("127.0.0.1", 8080)

bufferSize = 40

# Create a UDP socket at client side

UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Send to server using created UDP socket
UDPClientSocket.sendto(bytesToSend, serverAddressPort)


msgFromServer = UDPClientSocket.recvfrom(bufferSize)
#int.from_bytes(msgFromServer, byteorder='big', signed=False)

doubles_sequence = array.array('d', msgFromServer[0])
#NaN = struct.unpack('>d', msgFromServer[0])[0]


print(doubles_sequence)

