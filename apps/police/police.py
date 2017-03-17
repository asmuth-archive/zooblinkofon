#!/usr/bin/env python
import serial
import time
import struct
import math

s = serial.Serial('/dev/ttyUSB0', 250000)

def set_color(r,g,b):
  pkt="\x80"
  for i in range(0, 32):
    pkt += struct.pack("BBB", r / 2, g / 2, b / 2)
  s.write(pkt)

j = 0
speed = 2.0
while True:
  j = j + 1
  set_color(128 + math.sin(j / speed) * 128, 0, 128 + math.sin(j / speed + math.pi / 2) * 128);
  time.sleep(0.016)
