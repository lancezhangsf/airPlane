	
all: gps

CC       ?=arm-fsl-linux-gnueabi-gcc
CFLAGS   ?= -Wall -g

CXX      ?=arm-fsl-linux-gnueabi-g++
CXXFLAGS ?= -Wall -g

COBJS     = \
	
	
CPPOBJS   = \
	./gps.o\
	./SerialPort.o\
    ./maingps.o\

OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -lpthread
INCLUDES ?= -I/usr/local/include


gps: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o gps

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o gps *log

.PHONY: clean