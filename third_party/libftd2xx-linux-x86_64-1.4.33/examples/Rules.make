# Define dependencies
DEPENDENCIES := -lftd2xx -lpthread

# Determine the operating system
UNAME := $(shell uname)

# Additional dependencies based on OS
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

# Current working directory
CURRENT_DIR := $(TOPDIR)/../build

# Embed in the executable a run-time path to libftd2xx
ifeq ($(UNAME), Darwin)
LINKER_OPTIONS := -Wl,-rpath,$(CURRENT_DIR)
else
LINKER_OPTIONS := -Wl,-rpath /usr/local/lib
endif

# Compiler flags
ifeq ($(UNAME), Darwin)
CFLAGS = -Wall -Wextra $(DEPENDENCIES) $(LINKER_OPTIONS) -L$(CURRENT_DIR)
else
CFLAGS = -Wall -Wextra $(DEPENDENCIES) $(LINKER_OPTIONS) -L/usr/local/lib
endif
