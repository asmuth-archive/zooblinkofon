TARGET_CPU     = atmega328p
TARGET_CPUFREQ = 16000000UL

SOURCES = firmware.cc serial.cc led_controller.cc protocol.cc
OBJECTS = $(SOURCES:.cc=.o)

all: firmware.hex

%.o: %.cc
	avr-gcc -Os -DF_CPU=$(TARGET_CPUFREQ) -mmcu=$(TARGET_CPU) -c $(CC_FLAGS) -std=gnu++11 -o $@ $<

firmware.bin: $(OBJECTS)
	avr-g++ -mmcu=$(TARGET_CPU) $(OBJECTS) -o firmware.bin

firmware.hex: firmware.bin
	avr-objcopy -O ihex -R .eeprom firmware.bin firmware.hex

flash: all
	avrdude -c usbasp -p m328p -B 5 -U flash:w:firmware.hex

clean:
	rm -rf firmware.bin firmware.hex *.o **/*.o

.PHONY: clean
