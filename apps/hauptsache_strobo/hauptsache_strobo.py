#!/usr/bin/env python
import serial
import time
s = serial.Serial('/dev/ttyUSB0', 38400)

while True:
  s.write('q')
  time.sleep(0.05)
  s.write('w')
  time.sleep(0.01)
