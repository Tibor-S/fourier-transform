import socket
import time

HOST = "127.0.0.1"  # Standard loopback interface address (localhost)
# PORT = 51496  # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, 0))
    s.connect((HOST, 5000))
    print(int.from_bytes(b'\x7F', byteorder='big'))
    print(time.time())
    s.send(b'\x7F')
    s.close()
