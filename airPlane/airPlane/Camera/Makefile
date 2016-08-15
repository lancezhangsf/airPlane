	
all: flycapture

CC       =arm-fsl-linux-gnueabi-gcc
CFLAGS   ?= -Wall -g

CXX      =arm-fsl-linux-gnueabi-g++
CXXFLAGS ?= -Wall -g

COBJS     = \
	
	
CPPOBJS   = \
	./FlyCapture2Test.o\
	./stdafx.o\


OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -L /lib -lflycapture
INCLUDES ?= -I/usr/local/include


flycapture: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o flycapture

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o flycapture *log

.PHONY: clean