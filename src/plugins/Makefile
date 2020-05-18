OBJS=	Plugin_About.o\
	Plugin_Download.o\
	Plugin_Help.o\
	Plugin_Edit_Settings.o\
	Plugin_Lizens.o\
	Plugin_Main.o\
	Plugin_Upload.o\
	Plugin_Status.o

CFLAGS= -s -pipe -Wall `xml2-config --cflags`
CC=g++
GET=co
SRCS=*.cpp
APFLIDIR=~/.apfli
BINDIR=/usr/local/bin
DEPEND= makedepend $(CFLAGS)
all:    plugins

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

plugins: $(OBJS)
	rm -f ../apfli

clean:
	rm -f Plugin_*.o

