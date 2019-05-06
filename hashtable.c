// HashTable Implementation Starter Code
// CMS 230, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hashtable struct definitions and function prototypes
#include "hashtable.h"


//*** Hash a string to an integer ***//
// Input
//    char *s: the string to hash
// Output
//    The integer hash code
//
// Implements the basic hashing String hashing algorithm used by Java.
unsigned long int hash(char *s) {
    unsigned long int h = 0;

    int i;
    for (i = 0; i < strlen(s); i++) {
        h += h * 31 + (unsigned long int) s[i];
    }

    return h;
}


//*** Create a new hashtable_t ***//
// Input
//    tableSize: the number of buckets in the new table
// Output
//    A pointer to the new table
HashTable * hashtableInit(int tableSize) {

    // Allocate memory for a new HashTable
    HashTable *hashTable = malloc(sizeof(HashTable));

    // Allocate memory for an array of buckets and assign
    // them to the table's buckets field
    hashTable->buckets = malloc(tableSize * sizeof(HashNode));

    // Set the new HashTable's size field
    hashTable->size = tableSize;

    // Return the new HashTable
    return hashTable;
}


//*** Insert a key-value pair into a table ***//
// Inputs
//    hashtable *h: the hashtable performing the insertion
//    char *key: the key string
//    char *value: the value string
// Output
//    Nothing
// Key -> hash function -> Number -> % division size of table -> where its placed
void hashtableInsert(HashTable *h, char *key, char *value) {
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    
    HashNode *hnode = malloc(sizeof(HashNode));
    hnode->key = key;
    hnode->value = value;
    
    HashNode *temp = h->buckets[index];
    
    if(temp == NULL)
        h->buckets[index] = hnode;
    else{
        hnode->next = h->buckets[index];
        h->buckets[index] = hnode;
    }
}


//*** Lookup the value associated with a particular key ***//
// Inputs
//    hashtable_t *h: the table
//    char *key: the key to find
// Output
//    The char *value associated with the key or NULL if no match exists
char * hashtableLookup(HashTable *h, char *key) {
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    
    HashNode *temp = h->buckets[index];
    
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL;
}


//*** Remove a key-value pair from the table if it exists ***//
// Inputs
//    hashtable_t *h: the table
//    char *key: the key to find and remove
// Output
//    The char *value associated with the key or NULL if no match exists
//    The pair is removed if it exists in the table
char * hashtableRemove(HashTable *h, char *key) {
    unsigned long int hashCode = hash(key);
    int index = hashCode % h->size;
    
    HashNode *current = malloc(sizeof(HashNode));
    current = h->buckets[index];
    
    HashNode *previous = malloc(sizeof(HashNode));
    previous = NULL;
    
    char *abc = malloc(sizeof(char));

    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            abc = current->value;
            
            if(previous == NULL)
                h->buckets[index] = current->next;
            else
                previous->next = current->next;
            
            return abc;
        }
        else{
            previous = current;
            current = current->next;
        }
    }
    return NULL;
}


//*** Print a hashtable ***//
// Input
//    hashtable_t *h: the table
void hashtablePrint(HashTable *h) {
    int i;
    for (i = 0; i < h->size; i++){
        HashNode *node = h->buckets[i];
        printf("Contents of bucket %d:\n", i);

        while (node != NULL){
            printf("    <%s, %s>\n", node->key, node->value);
            node = node->next;
        }
    }
}

//*** There is no main function --- use the Python test script ***//