CFLAGS = -I/usr/include/gtk-3.0 -Wall -g `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`

test: main.c
	$(CC) -o test main.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *~
	rm -f *.o
	rm -f test

