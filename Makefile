##--------------------------------
# Created by CDRPico
# 09/06/2020 23:06
## -------------------------------

rm = /bin/rm -f
CC = g++
PROGNAME = read_instances_TSSP
INCLUDES = -I. -I~/cppProjects/tsspInstancesReader/TSSPInstancesReader/inc
LIBS = #-lm -lpthread -ldl

DEFS= 

DEFINES= -DIL_STD $(INCLUDES) $(DEFS) -DSYS_UNIX=1 -std=c++0x -Wall
CFLAGS= -g $(DEFINES)
CPPFLAGS= -g $(DEFINES)
CXXFLAGS='-D_GLIBCXX_USE_CXX11_ABI=0'

SRCS = src/UsefulFunctions.cpp src/GenerateInstanceSFLP.cpp src/InstanceSFLP.cpp main.cpp

OBJS = src/UsefulFunctions.o src/GenerateInstanceSFLP.o src/InstanceSFLP.o main.o

.c.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $*.c

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~
