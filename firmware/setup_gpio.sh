#!/bin/bash
set -ue

for pin in 2 3 4 7 9 10 11 17 22 27; do
  echo ${pin} > /sys/class/gpio/export || true
  echo in > /sys/class/gpio/gpio${pin}/direction
  echo 1 > /sys/class/gpio/gpio${pin}/active_low
  gpio -g mode ${pin} up 
done
