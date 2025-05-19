TOPDIR := $(shell cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = FtdiPthreadIssue

CXX = g++
CXXFLAGS = $(CFLAGS)

SRCS = Main.cpp CFtdiDevice.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(APP)

$(APP): $(OBJS)
	$(CXX) $(OBJS) -o $(APP) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	-rm -f $(OBJS) $(APP)

