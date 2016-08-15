	
all: Clientini

CC       ?=arm-fsl-linux-gnueabi-gcc
CFLAGS   ?= -Wall -g

CXX      ?=arm-fsl-linux-gnueabi-g++
CXXFLAGS ?= -Wall -g

COBJS     = \
	
	
CPPOBJS   = \
	../fileoperator.o\
	./clientsocket.o\
	../socket.o\
	../Cfgini/inifile.o\
	./client.o\


OBJS      = $(COBJS) $(CPPOBJS)
LIBS      = -lpthread 
INCLUDES ?= -I/usr/local/include


Clientini: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o Clientini

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o Clientini *log 

.PHONY: clean
