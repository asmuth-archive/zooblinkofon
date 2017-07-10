#!/usr/bin/env python3
import serial
import time
import struct
import sys

s = serial.Serial('/dev/ttyUSB0', 38400)

def update_display(r, g, b, buttons):
  s.write(struct.pack("<BBBH", r, g, b, buttons))

i=0
while True:
  i+=1
  update_display(i % 255, 0, 255 - (i % 255), 1 << (int(i / 10) % 10))
  time.sleep(0.01)

