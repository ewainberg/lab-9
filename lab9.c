#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order; 
};

// Node for the linked list
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// Hash table structure
struct HashType
{
    struct Node* head;
};

// Hash table size constant
#define HASH_SIZE 10

// Hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Inserts a record into the hash table
void insertRecord(struct HashType hashTable[], struct RecordType record)
{
    int index = hash(record.id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = record;
    newNode->next = hashTable[index].head;
    hashTable[index].head = newNode;
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType hashTable[], int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = hashTable[i].head;
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("\n");
    }
}

// Parse input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(EXIT_FAILURE);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    struct HashType hashTable[HASH_SIZE] = {0}; // Initialize all heads to NULL
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    
    // Insert records into the hash table
    for (int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(hashTable, HASH_SIZE);
    
    // Free dynamically allocated memory
    free(pRecords);

    return 0;
}
