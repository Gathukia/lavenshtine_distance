#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"


unsigned int hash(const char* key){
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

HashTable* ht_create(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->size = size;
    table->entries = malloc(sizeof(Entry *) * size);
    for (int i = 0; i < size; ++i) {
        table->entries[i] = NULL; // Initialize all buckets to empty
    }
    return table;
}
void insert(HashTable *table, char *key) {
    int slot = hash(key) % table->size; // Calculate hash index
    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = strdup(key); // Duplicate key string
    new_entry->next = NULL;

    // Handle collision (bucket not empty)
    if (table->entries[slot] != NULL) {
        Entry *last = table->entries[slot];
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_entry;
    } else {
        table->entries[slot] = new_entry;
    }
}

// Function to search for a key
bool search(HashTable *table, char *key) {
    int slot = hash(key) % table->size;
    Entry *current = table->entries[slot];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return true; // Key found
        }
        current = current->next;
    }
    return false; // Key not found
}

// Function to delete a key
void delete(HashTable *table, char *key) {
    int slot = hash(key) % table->size;
    Entry *current = table->entries[slot];
    Entry *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) { // Head of the list
                table->entries[slot] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to clear the hash table
void clear(HashTable *table) {
    for (int i = 0; i < table->size; ++i) {
        Entry *current = table->entries[i];
        while (current != NULL) {
            Entry *next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
        table->entries[i] = NULL;
    }
}
