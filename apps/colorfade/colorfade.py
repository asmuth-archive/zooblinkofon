#!/usr/bin/env python
import serial
import time
import struct
import math

s = serial.Serial('/dev/ttyUSB0', 38400)

def set_color(r,g,b):
  pkt=""
  for i in range(0, 32):
    pkt += struct.pack("BBB", r / 2, g / 2, b / 2)
  pkt+="\xff"
  s.write(pkt)

j = 0
speed = 2.0
while True:
  j = j + 1
  set_color(170 + math.sin(j / speed) * 85, 0, 170 + math.sin(j / speed + math.pi) * 75);
  time.sleep(0.033)
