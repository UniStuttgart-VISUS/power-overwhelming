TOPDIR  := $(shell cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = simpleConfig

all: $(APP)

$(APP): config.c	
	$(CC) config.c -o $(APP) $(CFLAGS)
	
clean:
	-rm -f *.o ; rm $(APP)
