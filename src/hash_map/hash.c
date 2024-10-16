#include "../shell.c"

#define TABLE_SIZE 100

typedef struct Node {
    char *key;
    CommandFunc func;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *buckets[TABLE_SIZE];
} HashMap;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

void init_hashmap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->buckets[i] = NULL;
    }
}

Node *create_node(const char *key, CommandFunc func) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->func = func;
    new_node->next = NULL;
    return new_node;
}

void hashmap_insert(HashMap *map, const char *key, CommandFunc func) {
    unsigned int index = hash(key);
    Node *new_node = create_node(key, func);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

CommandFunc hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    Node *current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->func;
        }
        current = current->next;
    }
    return NULL;
}

void hashmap_free(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = map->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}
