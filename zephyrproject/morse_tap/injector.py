import serial

def main():
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    while True:
        injection = input("Word to inject: ").encode()
        ser.write(injection + b'\n')
        
        
if __name__ == "__main__":
    main()
    