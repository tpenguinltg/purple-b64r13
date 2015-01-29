LIBPURPLE_CFLAGS = -I/usr/include/libpurple -DPURPLE_PLUGINS -DENABLE_NLS
GLIB_CFLAGS = `pkg-config --cflags glib-2.0` -I/usr/include

.PHONY: all clean install uninstall

all:
	gcc ${LIBPURPLE_CFLAGS} -Wall -pthread ${GLIB_CFLAGS} -I. -g -pipe b64r13.c -o b64r13.so -shared -fPIC -DPIC

clean:
	rm -f b64r13.so

install:
	cp b64r13.so ~/.purple/plugins/

uninstall:
	rm ~/.purple/plugins/b64r13.so
