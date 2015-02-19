LIBPURPLE_CFLAGS = -I/usr/include/libpurple -DPURPLE_PLUGINS -DENABLE_NLS
GLIB_CFLAGS = `pkg-config --cflags glib-2.0` -I/usr/include
CC = gcc
RM = rm -f

.PHONY: all clean install uninstall

all: br64r13.so

br64r13.so: b64r13.c
	${CC} ${LIBPURPLE_CFLAGS} -Wall -pthread ${GLIB_CFLAGS} -I. -g -pipe b64r13.c -o b64r13.so -shared -fPIC -DPIC

clean:
	${RM} b64r13.so

install:
	cp b64r13.so ${HOME}/.purple/plugins/

uninstall:
	${RM} ${HOME}/.purple/plugins/b64r13.so
