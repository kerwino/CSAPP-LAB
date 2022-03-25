# Student's Makefile for the CS:APP Performance Lab
TEAM = YQ
VERSION = 1
HANDINDIR = /root/Lab4-preformance/handin

CC = gcc
CFLAGS = -Wall -O2 -m32
LIBS = -lm

OBJS = driver.o kernels.o fcyc.o clock.o
SRCS = driver.c kernels.c fcyc.c clock.c

all: obj driver 
obj: $(SRCS)
	@gcc -Wall -O2 -m32 -c -o driver.o driver.c
	@gcc -Wall -O2 -m32 -c -o kernels.o kernels.c
	@gcc -Wall -O2 -m32 -c -o fcyc.o fcyc.c
	@gcc -Wall -O2 -m32 -c -o clock.o clock.c

driver: $(OBJS) fcyc.h clock.h defs.h config.h
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o driver

handin:
	@cp kernels.c $(HANDINDIR)/$(TEAM)-$(VERSION)-kernels.c

clean: 
	@rm -f $(OBJS) driver core *~ *.o


