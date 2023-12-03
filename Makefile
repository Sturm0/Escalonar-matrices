.PHONY: clean

ifndef CC
CC=cc
endif

ifndef OUTPUT
OUTPUT=main.elf
endif

INCFLAGS_M=${INCFLAGS}
LDFLAGS_M=${LDFLAGS} -lc -lm
CFLAGS_M=${CFLAGS} -O2 -pipe
TARGETS=main.o

%.o: %.c
	$(CC) $(CFLAGS_M) $(INCFLAGS_M) -c $^ -o $@


main: $(TARGETS)
	$(CC) $(TARGETS) $(LDFLAGS_M) $(INCFLAGS_M) -o $(OUTPUT)

clean:
	@rm *.o 2> /dev/null
	@rm $(OUTPUT) 2> /dev/null
