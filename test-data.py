import socket
import time
import math

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
# PORT = 51496  # Port to listen on (non-privileged ports are > 1023)
MAX = 2**31-1
MIN = -2**31


def func(t):
    print(math.sin(2*math.pi*t))
    return int(math.sin(2*math.pi*t)*MAX).to_bytes(4, byteorder='big', signed=True)


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, 5000))
    s.listen()
    s.accept()
    print('connected')
    y = [1, 1/2, 0, ]
    bs = bytearray()  # b'\x11\x11'

    t = time.time()/1000
    print(int.from_bytes(func(t), byteorder='big', signed=True))
    # while True:
    #     try:
    #         s.send(b'\x7F')
    #     except:
    #         break
    s.close()
