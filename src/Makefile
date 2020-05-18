CTAGS= ctags -x >tags
CFLAGS= -s -Wall -pipe `xml2-config --cflags`
LDFLAGS= 
LIBS=-s -lpanel -lmenu -lncurses -lform  -lpthread `xml2-config --libs`
CC=g++
GET=co
SRCS=*.cpp
OBJS=	xml_functions.o Form.o main.o aux_functions.o Core_Download_Item.o \
	Core_Data.o  md5.o sockfunc.o settings.o Content.o Apfli.o Menu.o\
	Plugin.o Colors.o Keyboard.o Window.o types.o
PLUGINS= plugins/Plugin_*.o
APFLIDIR=~/.apfli
all:    
	make -C "plugins/"
	make apfli


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

apfli: 	$(OBJS) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(PLUGINS) $(LIBS)
	mkdir -p $(APFLIDIR)
	cp LIZENS $(APFLIDIR)
	cp ABOUT  $(APFLIDIR)
	cp HELP	  $(APFLIDIR)	

install: 
	cp apfli /usr/local/bin
	chmod 755 /usr/local/bin/apfli

# clean out the dross
clean:
	rm -f apfli *.o apfli.err
	make -C "plugins/" clean

