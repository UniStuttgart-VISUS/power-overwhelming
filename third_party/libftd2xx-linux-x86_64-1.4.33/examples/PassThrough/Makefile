TOPDIR := $(shell cd ..; pwd)
include $(TOPDIR)/Rules.make

# Define applications and their corresponding source files
APPS = TestCase1 TestCase2
SOURCES = $(APPS:=.c)

all: $(APPS)

# Pattern rule for compiling .c files into executables
%: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm -f *.o $(APPS)
