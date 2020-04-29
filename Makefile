CTAGS= ctags -x >tags
CFLAGS=-O2 -pipe -Wall -fomit-frame-pointer
# `xml2-config --cflags`
LDFLAGS= -s `xml2-config --libs` -lpthread
LIBS=-lpanel -lmenu -lncurses 
CC=g++
GET=co
SRCS=*.cpp
SHAR=shar
RELNAME=apfli_`date +%d_%m_%y-%H-%M`
APFLIDIR=~/.apfli
ARCHFILES=include/*.h src/*.cpp src/Makefile src/plugins/Makefile src/plugins/*.cpp src/plugins/*.h scripts/ Makefile Changelog Todo INSTALL
all:
	make apfli

%.o %.cpp:
	
    
apfli:  src/*.o src/plugins/*.o
	make -C "src/"
	rm -f apfli
	ln -s src/apfli apfli

install:
	make -C "src/" install

# clean out the dross
clean:
	make -C "src/" clean
	rm -f apfli

shar:
	make clean
	$(SHAR) -z $(ARCHFILES) > $(RELNAME).shar
	@chmod +x $(RELNAME).shar

#rchive:
rsource:
	mkdir -p release/source/apfli
	tar -cvvf release/source/$(RELNAME).tar $(ARCHFILES) 
	bzip2 -z release/source/$(RELNAME).tar

#total unflexibel muss ma dynamischer gemacht werden
rbin:
	mkdir -p release/bin/apfli
	cp scripts/install release/bin/apfli
	cp src/apfli release/bin/apfli
	cp LIZENS release/bin/apfli
	cp HELP release/bin/apfli
	cp ABOUT release/bin/apfli
	cd release/bin && \
	tar -cvvf $(RELNAME)_bin.tar apfli  &&\
	bzip2 -z $(RELNAME)_bin.tar &&\
	mv $(RELNAME)_bin.tar.bz2 "../" &&\
	mv "../$(RELNAME)_bin.tar.bz2" .
	rm -f release/bin/apfli/apfli
	rm -f release/bin/apfli/install
	rm -f release/bin/apfli/LIZENS
	rm -f release/bin/apfli/HELP
	rm -f release/bin/apfli/ABOUT	
	rmdir -f release/bin/apfli


release:
	make
	make rbin
	make rsource