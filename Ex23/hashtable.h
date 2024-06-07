#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Occurrence {
    char *filename;
    int count;
    struct Occurrence *next;
} Occurrence;

typedef struct {
    Occurrence *occurrences;
} HashNode;

typedef struct {
    HashNode buckets[29]; /* Fixed-size array for numbers 0-28 */
} HashTable;

HashTable *create_table();
void add_occurrence(HashTable *table, int key, const char *filename);
void print_occurrences(HashTable *table);
void free_table(HashTable *table);

#endif /* HASHTABLE_H */
