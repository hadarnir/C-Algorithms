#include "hashtable.h"

/**
 * Create a new hash table.
 * @return Pointer to the newly created hash table.
 */
HashTable *create_table() {
    int i;
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (table == NULL) {
        perror("Failed to create table");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 29; i++) {
        table->buckets[i].occurrences = NULL;
    }
    return table;
}

/**
 * Create a new occurrence.
 * @param filename - Name of the file where the occurrence was found.
 * @return Pointer to the newly created occurrence.
 */
Occurrence *create_occurrence(const char *filename) {
    Occurrence *occ = (Occurrence *)malloc(sizeof(Occurrence));
    if (occ == NULL) {
        perror("Failed to create occurrence");
        exit(EXIT_FAILURE);
    }
    occ->filename = strdup(filename);
    occ->count = 1;
    occ->next = NULL;
    return occ;
}

/**
 * Add an occurrence to the hash table.
 * @param table - Pointer to the hash table.
 * @param key - The number to add an occurrence for.
 * @param filename - Name of the file where the occurrence was found.
 */
void add_occurrence(HashTable *table, int key, const char *filename) {
    Occurrence *occ, *last_occ;
    HashNode *node = &table->buckets[key];
    occ = node->occurrences;

    /* Traverse the occurrences linked list */
    while (occ != NULL) {
        if (strcmp(occ->filename, filename) == 0) {
            occ->count++;
            return;
        }
        last_occ = occ;
        occ = occ->next;
    }

    /* Add a new occurrence if not found */
    occ = create_occurrence(filename);
    if (node->occurrences == NULL) {
        node->occurrences = occ;
    } else {
        last_occ->next = occ;
    }
}

/**
 * Print occurrences from the hash table.
 * @param table - Pointer to the hash table.
 */
void print_occurrences(HashTable *table) {
    int i;
    for (i = 0; i < 29; i++) {
        HashNode *node = &table->buckets[i];
        if (node->occurrences != NULL) {
            Occurrence *occ = node->occurrences;
            printf("%d appears in ", i);
            while (occ != NULL) {
                printf("file %s - %d time%s", occ->filename, occ->count, occ->count > 1 ? "s" : "");
                occ = occ->next;
                if (occ != NULL) {
                    printf(", ");
                }
            }
            printf("\n");
        }
    }
}

/**
 * Free the memory allocated for the hash table.
 * @param table - Pointer to the hash table to be freed.
 */
void free_table(HashTable *table) {
    int i;
    for (i = 0; i < 29; i++) {
        Occurrence *occ = table->buckets[i].occurrences;
        while (occ != NULL) {
            Occurrence *temp_occ = occ;
            occ = occ->next;
            free(temp_occ->filename);
            free(temp_occ);
        }
    }
    free(table);
}
