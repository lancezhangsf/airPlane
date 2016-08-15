	
all: Server

CC       ?=arm-fsl-linux-gnueabi-gcc
CFLAGS   ?= -Wall -g

CXX      ?=arm-fsl-linux-gnueabi-g++
CXXFLAGS ?= -Wall -g

COBJS     = \
	
	
CPPOBJS   = \
	./serversocket.o\
	../fileoperator.o\
	../socket.o\
	../Cfgini/inifile.o\
	./server.o\


OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -lpthread 
INCLUDES ?= -I/usr/local/include


Server: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o Server

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o Server *log *.jpeg

.PHONY: clean
