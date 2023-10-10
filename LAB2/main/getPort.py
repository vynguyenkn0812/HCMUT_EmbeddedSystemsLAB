import serial.tools.list_ports

for port in list(serial.tools.list_ports.comports()):
    print(port)  # or do whatever you want with the object
