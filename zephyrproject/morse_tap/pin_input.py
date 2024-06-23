#! /usr/bin/python3/
import serial
import time

def word_to_morse(str: str) -> str:
    message = ""
    for letter in str[:-1]:
        message += letter_to_morse[letter]
        message += "000"
    message += letter_to_morse[str[-1]]
    return message

letter_to_morse = {
    'A' : "10111",
    'B' : "111010101",
    'C' : "11101011101",
    'D' : "1110101",
    'E' : "1",
    'F' : "101011101",
    'G' : "111011101",
    'H' : "1010101",
    'I' : "101",
    'J' : "1011101110111",
    'K' : "111010111",
    'L' : "101110101",
    'M' : "1110111",
    'N' : "11101",
    'O' : "11101110111",
    'P' : "10111011101",
    'Q' : "1110111010111",
    'R' : "1011101",
    'S' : "10101",
    'T' : "111",
    'U' : "1010111",
    'V' : "101010111",
    'W' : "101110111",
    'X' : "11101010111",
    'Y' : "1110101110111",
    'Z' : "11101110101",}



def main():
    words = input("What wish you to send? ").split(' ')
    port = '/dev/ttyUSB0'
    message = ""

    for word in words[:-1]:
        message += word_to_morse(word)
        message += "0000000"
    message += word_to_morse(words[-1])

    ser = serial.Serial(port)
    ser.dtr = True
    time.sleep(0.5)        

    for bit in message:
        if '1' == bit:
            ser.dtr = False
        if '0' == bit:
            ser.dtr = True
        time.sleep(0.05)
    ser.dtr = True
    time.sleep(5)        


if __name__ == "__main__":
    main()