CC = gcc
CFLAGS = -g -ansi -pedantic -Wall

TARGET = myset
OBJECTS = myset.o set.o validations.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

myset.o: myset.c set.h validations.h
	$(CC) -c $(CFLAGS) myset.c -o myset.o

set.o: set.c set.h
	$(CC) -c $(CFLAGS) set.c -o set.o

validations.o: validations.c validations.h
	$(CC) -c $(CFLAGS) validations.c -o validations.o

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
