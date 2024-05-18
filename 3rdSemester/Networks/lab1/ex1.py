import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

v = [1, 2, 3, 4, 5]

s.connect(("192.168.1.4", 1234))

# Pack the length of the list v as a short int (16 bits) in network representation
s.send(struct.pack("!H", len(v)))

# Pack each value in v as a short int (16 bits) in network representation
for value in v:
    s.send(struct.pack("!H", value))

# Receive the sum from the server (assuming it's sending a short int, 16 bits)
sum_received = s.recv(2)

# Unpack the content received from the network into a short int
# and convert from network representation back to host
sum_value = struct.unpack('!H', sum_received)[0]

print('sum =', sum_value)

s.close()
