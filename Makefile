CC = gcc
CFLAGS = -Wall
EXECUTABLE = AleksanyanAlif3

all: run

run: $(EXECUTABLE)
	@echo "\n\t-------------|   DEBUT   |-------------\n\n" && ./$(EXECUTABLE)
	@echo "\n\n\t-------------|    FIN    |-------------\n" && rm -f $(EXECUTABLE)

$(EXECUTABLE): AleksanyanAlif3.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE)

