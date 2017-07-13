Das Zooblinkofon
================

### Main Firmware (x64/armhf)

Build main firmware (for host):

    $ cd firmware
    $ ./autogen.sh
    $ ./configure
    $ make

Run main firmware on host (with virtual display):

    $ cd firmware
    $ ./zooblinkofon --virtual


### LED Driver (atmega328p/avr)

Build LED driver firmware (cross for avr):

    $ cd firmware/led_driver
    $ make

Flash LED driver to atmega328p:

    $ cd firmware/led_driver
    $ make flash

Set HW fuses on atmega328p:

    $ avrdude -c usbasp -p m328p -B 20 -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0x07:m

