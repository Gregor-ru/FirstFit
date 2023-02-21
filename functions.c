#include "framework.h"
#include "functions.h"

typedef struct SBlock
{
    int*    bufBlockArray;
    int*    inBlockArray;
    int     bufBlockLen;
    int     inBlockLen;

} TBlock;

static TBlock block;

void initBlock(int* bufBl, int* inBl, int bufBlSize, int inBlSize) {

    block.bufBlockArray = (int*)malloc(bufBlSize * sizeof(int));
    block.inBlockArray = (int*)malloc(bufBlSize * sizeof(int));
    block.bufBlockLen = bufBlSize;
    block.inBlockLen = inBlSize;

    for (int i = 0; i < bufBlSize; i++) block.bufBlockArray[i] = bufBl[i];
    for (int i = 0; i < inBlSize; i++) block.inBlockArray[i] = inBl[i];
}

void firstFit() {

    int* allocation = (int*)malloc(block.bufBlockLen * sizeof(int));
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < block.bufBlockLen; i++) {
        for (int j = 0; j < block.inBlockLen; j++) {
            if (block.bufBlockArray[j] >= block.inBlockArray[i]) {
                allocation[i] = j;
                block.bufBlockArray[j] -= block.inBlockArray[i];
                break;
            }
            else allocation[i] = -1;
        }
    }

    printf("N\tIn block size\tNum of block allocate\n");
    for (int i = 0; i < block.bufBlockLen; i++) {
        printf("%i\t%i\t\t", i + 1, block.inBlockArray[i]);
        if (allocation[i] != -1) printf("%i", allocation[i] + 1);
        else printf("Not allocated");
        printf("\n");
    }
}

void my_fread(int** arr, int* length, char* name) {
    FILE* file;
    file = fopen(name, "r+");
    int arrLen = *length;
    int temp;

    if (arrLen == 0) {
        while ((fscanf(file, "%d", &temp) != EOF))
        {
            if (!file) break;
            arrLen += 1;
        }
    }

    *arr = (int*)malloc(arrLen * sizeof(int));

    rewind(file);
    for (int i = 0; i < arrLen; i++) fscanf(file, "%i", &(*arr)[i]);

    *length = arrLen;
    fclose(file);
}

void* my_malloc(int size)
{
    int* bufferBlockSizes = (int*)malloc(size);
    int* inBlockSizes = (int*)malloc(size);

    my_fread(&bufferBlockSizes, &size, "D:/C-C++Projects/Files/buffer.txt");
    my_fread(&inBlockSizes, &size, "D:/C-C++Projects/Files/in.txt");

    initBlock(bufferBlockSizes, inBlockSizes, size, size);
    firstFit();
    return block.bufBlockArray;
}

void my_free(void* data)
{
    free((int*)data);
}