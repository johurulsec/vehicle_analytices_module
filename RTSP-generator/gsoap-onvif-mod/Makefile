CC = g++
CPPFLAG = -Wall -g -w -fPIC -DWITH_NONAMESPACES -fno-use-cxa-atexit -fexceptions -DWITH_DOM  -DWITH_OPENSSL -DSOAP_DEBUG  

BASE_DIR=.
SOURCE=$(BASE_DIR)

INCLUDE +=-I$(SOURCE)/soap-include -I$(BASE_DIR)
LIB= -lssl -lcrypto
PROXYSOURCE=$(BASE_DIR)/proxycpp
ProxyOBJ=$(PROXYSOURCE)/soapDeviceBindingProxy.o $(PROXYSOURCE)/soapMediaBindingProxy.o $(PROXYSOURCE)/soapPTZBindingProxy.o \
		 $(PROXYSOURCE)/soapPullPointSubscriptionBindingProxy.o $(PROXYSOURCE)/soapRemoteDiscoveryBindingProxy.o
PluginSOURCE=$(BASE_DIR)/plugin
PluginOBJ=$(PluginSOURCE)/wsaapi.o $(PluginSOURCE)/wsseapi.o $(PluginSOURCE)/threads.o $(PluginSOURCE)/duration.o \
		  $(PluginSOURCE)/smdevp.o $(PluginSOURCE)/mecevp.o $(PluginSOURCE)/dom.o
SRC= $(SOURCE)/stdsoap2.o  $(SOURCE)/soapC.o $(SOURCE)/soapClient.o $(SOURCE)/main.o $(PluginOBJ) $(ProxyOBJ)
OBJECTS = $(patsubst %.cpp,%.o,$(SRC))
TARGET=ipconvif
all: $(TARGET) 
$(TARGET):$(OBJECTS) 
	$(CC) $(CPPFLAG) $(OBJECTS)  $(INCLUDE)  $(LIB) -o $(TARGET)
$(OBJECTS):%.o : %.cpp
	$(CC) -c $(CPPFLAG) $(INCLUDE) $< -o $@
clean:
	rm -rf  $(OBJECTS) 

