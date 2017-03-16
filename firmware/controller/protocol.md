UART Protocol
=============

This page describes the simple protocol that is used to control the lights
and read button presses.

## TX Commands

Messages that may be sent (i.e. written to the uart) by a user:

### set led colors

    0x80 <rgb_data>

where rgb data is 3 bytes per led (r/g/b). the interval of valid values for each
colors brightness is [0-128), not [0-256)

### set button lights on/off

    0x81 <bool_data>

where bool data is 1 bit per button, but only the lower 7 bits of each byte are
used (the highest bit must always be zero)


## RX Commands

Commands that may be received (i.e. read from the uart) by a user

### button down/up

the following one-byte messages indicate button up and down events:

    0x00  BUTTON01_DOWN
    0x01  BUTTON02_DOWN
    0x02  BUTTON03_DOWN
    0x03  BUTTON04_DOWN
    0x04  BUTTON05_DOWN
    0x05  BUTTON06_DOWN
    0x06  BUTTON07_DOWN
    0x07  BUTTON08_DOWN
    0x08  BUTTON09_DOWN
    0x09  BUTTON10_DOWN
    0x0a  BUTTON11_DOWN
    0x0b  BUTTON12_DOWN
    0x0c  BUTTON13_DOWN
    0x0d  BUTTON14_DOWN
    0x0e  BUTTON15_DOWN
    0x0f  BUTTON16_DOWN
    0x10  BUTTON01_UP
    0x11  BUTTON02_UP
    0x12  BUTTON03_UP
    0x13  BUTTON04_UP
    0x14  BUTTON05_UP
    0x15  BUTTON06_UP
    0x16  BUTTON07_UP
    0x17  BUTTON08_UP
    0x18  BUTTON09_UP
    0x19  BUTTON10_UP
    0x1a  BUTTON11_UP
    0x1b  BUTTON12_UP
    0x1c  BUTTON13_UP
    0x1d  BUTTON14_UP
    0x1e  BUTTON15_UP
    0x1f  BUTTON16_UP

