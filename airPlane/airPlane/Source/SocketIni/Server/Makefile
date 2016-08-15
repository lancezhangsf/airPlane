	
all: Serverini	

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


Serverini: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LIBS) -o Serverini

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS) *.o Serverini *log *.jpeg

.PHONY: clean
