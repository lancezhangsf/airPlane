	
all: airPlane

CC       ?=arm-fsl-linux-gnueabi-gcc
CFLAGS   ?= -Wall -g

CXX      ?=arm-fsl-linux-gnueabi-g++
CXXFLAGS ?= -Wall -g

COBJS     = \
	
	
CPPOBJS   = \
	./Gps/gps.o\
	./Gps/SerialPort.o\
	./Camera/stdafx.o\
	./Cfgini/inifile.o\
    ./main.o\

OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -L /lib -lflycapture 
INCLUDES ?= -I/usr/local/include


airPlane: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o airPlane

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o airPlane *log *.jpeg *.ini

.PHONY: clean