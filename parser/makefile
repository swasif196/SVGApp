#Sohaib Wasif
#0874921

CC = gcc
CFLAGS = -Wall -std=c11 -g

all: ../libsvgparse.so
../libsvgparse.so: LinkedListAPI.o SVGParser.o helper.o
	gcc `xml2-config --cflags --libs` -shared -o ../libsvgparse.so LinkedListAPI.o SVGParser.o helper.o
mac: ../libsvgparse.dylib
../libsvgparse.dylib: LinkedListAPI.o SVGParser.o helper.o
	gcc `xml2-config --cflags --libs` -shared -o ../libsvgparse.dylib LinkedListAPI.o SVGParser.o helper.o
LinkedListAPI.o: src/LinkedListAPI.c include/LinkedListAPI.h
	gcc -Wall -std=c11 -g -c -fpic -Iinclude src/LinkedListAPI.c
SVGParser.o: src/SVGParser.c include/helper.h include/SVGParser.h
	gcc -Wall -std=c11 -g `xml2-config --cflags --libs` -lm -c -fpic -Iinclude src/SVGParser.c
helper.o: src/helper.c include/helper.h
	gcc -Wall -std=c11 -g `xml2-config --cflags --libs` -lm -c -fpic -Iinclude src/helper.c
clean:
	rm ../*.so
	rm *.o
cleanm:
	rm ../*.dylib
	rm *.o