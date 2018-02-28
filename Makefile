CC=gcc
CFLAGS= -std=c99 -O1 -lm -fopenmp
LDFLAGS= -std=c99 -O1 -lm -fopenmp

SOURCES=luckyomp.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mlucky

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
