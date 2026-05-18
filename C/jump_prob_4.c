#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 100003

// Linked list for storing indexes
typedef struct Node {
    int index;
    struct Node* next;
} Node;

// Hash table entry
typedef struct Entry {
    int key;
    Node* indices;
    struct Entry* next;
} Entry;

Entry* hashTable[HASH_SIZE];

// Hash function
int hash(int key) {
    if(key < 0)
        key = -key;

    return key % HASH_SIZE;
}

// Insert value -> index mapping
void insert(int key, int index) {

    int h = hash(key);

    Entry* temp = hashTable[h];

    while(temp) {

        if(temp->key == key) {

            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->index = index;
            newNode->next = temp->indices;
            temp->indices = newNode;

            return;
        }

        temp = temp->next;
    }

    // Create new entry
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    newEntry->key = key;
    newEntry->indices = NULL;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->index = index;
    newNode->next = NULL;

    newEntry->indices = newNode;

    newEntry->next = hashTable[h];
    hashTable[h] = newEntry;
}

// Get list of indexes for a value
Entry* getEntry(int key) {

    int h = hash(key);

    Entry* temp = hashTable[h];

    while(temp) {

        if(temp->key == key)
            return temp;

        temp = temp->next;
    }

    return NULL;
}

int minJumps(int* arr, int arrSize) {

    if(arrSize == 1)
        return 0;

    // Initialize hash table
    for(int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = NULL;

    // Build hash map
    for(int i = 0; i < arrSize; i++) {
        insert(arr[i], i);
    }

    // BFS queue
    int* queue = (int*)malloc(sizeof(int) * arrSize);

    bool* visited = (bool*)calloc(arrSize, sizeof(bool));

    int front = 0;
    int rear = 0;

    queue[rear++] = 0;
    visited[0] = true;

    int steps = 0;

    while(front < rear) {

        int size = rear - front;

        for(int i = 0; i < size; i++) {

            int current = queue[front++];

            // Reached end
            if(current == arrSize - 1) {

                free(queue);
                free(visited);

                return steps;
            }

            // Move right
            if(current + 1 < arrSize &&
               !visited[current + 1]) {

                visited[current + 1] = true;
                queue[rear++] = current + 1;
            }

            // Move left
            if(current - 1 >= 0 &&
               !visited[current - 1]) {

                visited[current - 1] = true;
                queue[rear++] = current - 1;
            }

            // Same value jumps
            Entry* entry = getEntry(arr[current]);

            if(entry) {

                Node* temp = entry->indices;

                while(temp) {

                    int nextIndex = temp->index;

                    if(!visited[nextIndex]) {

                        visited[nextIndex] = true;
                        queue[rear++] = nextIndex;
                    }

                    temp = temp->next;
                }

                // Important optimization
                entry->indices = NULL;
            }
        }

        steps++;
    }

    free(queue);
    free(visited);

    return -1;
}

int main() {
    int arr[] = {100,-23,-23,404,100,23,23,23,3,404};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    int result = minJumps(arr, arrSize);
    printf("Minimum jumps to reach end: %d\n", result);

    return 0;
}