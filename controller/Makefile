CC=avr-gcc
CFLAGS=-DF_CPU=16000000UL -mmcu=atmega328p -Os

OBJ := bin
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(OBJ)/%.o, $(SOURCES))

.PHONY: all clean upload

all: $(OBJECTS) bin/controller

clean:
	rm -r ./bin

$(OBJ)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/controller: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OBJ)/controller

$(OBJ)/controller.hex: $(OBJ)/controller
	avr-objcopy -R .eeprom -O ihex $(OBJ)/controller $(OBJ)/controller.hex

upload: bin/controller.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$(OBJ)/controller.hex
