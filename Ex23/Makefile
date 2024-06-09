CC = gcc
CFLAGS = -g -ansi -pedantic -Wall

TARGET = Ex23
OBJECTS = hash.o hashtable.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

hash.o: hash.c hashtable.h
	$(CC) -c $(CFLAGS) hash.c -o hash.o

hashtable.o: hashtable.c hashtable.h
	$(CC) -c $(CFLAGS) hashtable.c -o hashtable.o

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
