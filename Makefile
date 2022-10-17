SRC		= sf-pwgen.c
LIBS	= -framework CoreFoundation -framework SecurityFoundation

PROGRAM	= sf-pwgen

all: format $(PROGRAM)

$(PROGRAM):
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(PROGRAM)

format:
	clang-format -style=file -fallback-style=Google -i $(SRC) $(wildcard *.h)

clean:
	rm -f $(PROGRAM)

.PHONY: clean
