import serial

def main():
    ser = serial.Serial('/dev/ttyUSB1')
    injection = input("Word to inject: ").encode()
    ser.write(injection + b'\n')
        
if __name__ == "__main__":
    main()
    