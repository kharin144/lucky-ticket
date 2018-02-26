CC=gcc
#CFLAGS=-c -Wall
CFLAGS= -std=c99 -O1
LDFLAGS= -lm -fopenmp
#SOURCES=main.cpp hello.cpp factorial.cpp
SOURCES=luckyomp.c
#OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mlucky

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cpp .o:
.c.o:
	$(CC) $(CFLAGS) $< -o $@
