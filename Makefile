prefix	= /usr/local

DSTMODE	= 0755

INSTALL	= /usr/bin/install

bindir	= ${prefix}/bin

SRC		= sf-pwgen.c
LIBS	= -framework CoreFoundation -framework SecurityFoundation

PROGRAM	= sf-pwgen

all: ${PROGRAM}

${PROGRAM}:
	${CC} ${CFLAGS} ${SRC} ${LIBS} -o ${PROGRAM}

format:
	clang-format -style=file -fallback-style=Google -i ${SRC} ${wildcard *.h}

clean:
	rm -f ${PROGRAM}

distclean: clean

install: ${PROGRAM} installdirs
	${INSTALL} -m ${DSTMODE} ${PROGRAM} ${DESTDIR}${bindir}

installdirs:
	mkdir -p ${DESTDIR}${bindir}

uninstall:
	rm -f ${DESTDIR}${bindir}/${notdir ${PROGRAM}}

.PHONY: clean
