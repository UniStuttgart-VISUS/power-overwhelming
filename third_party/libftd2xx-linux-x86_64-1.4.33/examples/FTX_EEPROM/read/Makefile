TOPDIR  := $(shell cd ..; cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = ftx_eeprom_read

all: $(APP)

$(APP): ftx-eeprom-read.c	
	$(CC) ftx-eeprom-read.c -o $(APP) $(CFLAGS)
	
clean:
	-rm -f *.o ; rm $(APP)
