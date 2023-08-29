
# printing
V = 0
Q = $(if $(filter 1,$V),,@)
M = $(shell printf "\033[34;1m▶\033[0m")

BUILDROOT_DIR=/home/sslim/buildroot/buildroot/
TOOLCHAIN_PATH=${BUILDROOT_DIR}/output/host/bin
CC=${TOOLCHAIN_PATH}/aarch64-buildroot-linux-gnu-gcc
CXX=${TOOLCHAIN_PATH}/aarch64-buildroot-linux-gnu-g++

#CC=gcc
#CXX=g++

TARGET = toy_system
SYSTEM = ./system/system
UI = ./system/ui
WEB_SERVER = ./system/web_server
HAL = ./system/hal
ENGINE = ./system/engine

INCLUDES = -I$(SYSTEM) -I$(UI) -I$(WEB_SERVER) -I$(HAL) -I$(HAL)/include -I./system/ -I$(ENGINE)

#CC = gcc
CXXLIBS = -lpthread -lm -lrt -Wl,--no-as-needed -ldl -lseccomp
CXXFLAGS = $(INCLUDEDIRS) -g -O0 -std=c++14

objects = main.o \
		system_server.o \
		web_server.o \
		input.o \
		gui.o \
		shared_memory.o \
		dump_state.o \
		hardware.o \
		Allocator.o \
		Engine.o \
		Fault.o \
		LeftMotor.o \
		RightMotor.o \
		StateMachine.o \
		stdafx.o \
		xallocator.o

# cxx_objects = camera_HAL.o ControlThread.o
cxx_objects =
shared_libs = system/libcamera.oem.so system/libcamera.toy.so

$(TARGET): $(objects) $(cxx_objects) $(shared_libs) $(modules)
	$(CXX) -o $(TARGET) $(objects) $(cxx_objects) $(CXXLIBS)
	make modules

main.o: system/main.c
	$(CC) -g $(INCLUDES) -c system/main.c

system_server.o: $(SYSTEM)/system_server.h $(SYSTEM)/system_server.c
	$(CC) -g $(INCLUDES) -c ./system/system/system_server.c

dump_state.o: $(SYSTEM)/dump_state.h $(SYSTEM)/dump_state.c
	$(CC) -g $(INCLUDES) -c ./system/system/dump_state.c

shared_memory.o: $(SYSTEM)/shared_memory.h $(SYSTEM)/shared_memory.c
	$(CC) -g $(INCLUDES) -c ./system/system/shared_memory.c

gui.o: $(UI)/gui.h $(UI)/gui.c
	$(CC) -g $(INCLUDES) -c $(UI)/gui.c

input.o: $(UI)/input.h $(UI)/input.c
	$(CC) -g $(INCLUDES) -c $(UI)/input.c

web_server.o: $(WEB_SERVER)/web_server.h $(WEB_SERVER)/web_server.c
	$(CC) -g $(INCLUDES) -c $(WEB_SERVER)/web_server.c

hardware.o: $(HAL)/hardware.c
	$(CC) -g $(INCLUDES) -c  $(HAL)/hardware.c

Allocator.o: $(ENGINE)/Allocator.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/Allocator.cpp

Engine.o: $(ENGINE)/Engine.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/Engine.cpp

Fault.o: $(ENGINE)/Fault.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/Fault.cpp

LeftMotor.o: $(ENGINE)/LeftMotor.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/LeftMotor.cpp

RightMotor.o: $(ENGINE)/RightMotor.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/RightMotor.cpp

StateMachine.o: $(ENGINE)/StateMachine.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/StateMachine.cpp

stdafx.o: $(ENGINE)/stdafx.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/stdafx.cpp

xallocator.o: $(ENGINE)/xallocator.cpp
	$(CC) -g $(INCLUDES) -c  $(ENGINE)/xallocator.cpp

.PHONY: libcamera.oem.so
libcamera.oem.so:
	$(CC) -g -shared -fPIC -o libcamera.oem.so $(INCLUDES) $(CXXFLAGS) $(HAL)/oem/camera_HAL_oem.cpp $(HAL)/oem/ControlThread.cpp

TOY_HAL_SOURCE = $(HAL)/toy/camera_HAL_toy.cpp \
					$(HAL)/toy/ControlThread.cpp \
					$(HAL)/toy/Callbacks.cpp \
					$(HAL)/toy/CallbackThread.cpp \
					$(HAL)/utils/Thread.cpp

.PHONY: libcamera.toy.so
libcamera.toy.so:
	$(CC) -g -shared -fPIC  $(CXXLIBS) -o libcamera.toy.so $(INCLUDES) $(CXXFLAGS) $(TOY_HAL_SOURCE)

# libcamera.toy.so:
# 	$(CC) -g -shared -fPIC -o libfoo2.so foo2.c

# libfoo3.so:
# 	cc -g -Wl,-Bsymbolic -Wl,-allow-shlib-undefined \
# 		-shared -fPIC -o libfoo3.so foo3.

# camera_HAL.o: $(HAL)/camera_HAL.cpp
# 	$(CXX) -g $(INCLUDES) $(CXXFLAGS) -c  $(HAL)/camera_HAL.cpp

# ControlThread.o: $(HAL)/ControlThread.cpp
# 	$(CXX) -g $(INCLUDES) $(CXXFLAGS) -c  $(HAL)/ControlThread.cpp

## build: Build

.PHONY: modules
modules:
	cd drivers/state_machine && make
	cd drivers/engine && make
	cd drivers/sensor && make
	cd drivers/simple_io && make

.PHONY: nfs
nfs:
	cp $(TARGET) ~/nfs/
	cp drivers/state_machine/state_machine.ko ~/nfs/
	cp drivers/engine/engine.ko ~/nfs/
	cp drivers/sensor/sensor.ko ~/nfs/

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(TARGET)

