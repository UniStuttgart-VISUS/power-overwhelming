ARCH   := $(shell getconf LONG_BIT)

ifeq (${ARCH},$(filter ${ARCH},32 64))
   NVML_LIB := ../lib/
else
   $(error Unknown architecture!)
endif

CFLAGS  := -I ../include -I /usr/include/nvidia/gdk/
LDFLAGS := -lnvidia-ml -L $(NVML_LIB)

example: example.o
	$(CC) $< $(LDFLAGS) -o $@

clean:
	-@rm -f example.o
	-@rm -f example
