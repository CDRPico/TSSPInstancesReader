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

SRCS = src/InstanceSFLP.cpp main.cpp

OBJS = src/InstanceSFLP.o main.o

.c.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $*.c

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~
