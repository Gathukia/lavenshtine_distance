
#define maximum_length 255
typedef struct{
      int buffer_size;
      char* buffer_start;
      char* buffer_position;
      int buffer_remaining;
      char **str_arr;
      int words_no;
}BUFFER;

typedef struct Entry{
    char* key;
    struct Entry *next;
}Entry;

typedef struct{
    Entry** entries;
    int size;
}HashTable;

HashTable* ht_create(int size);
void insert(HashTable *table, char *key);
bool search(HashTable *table, char *key);
