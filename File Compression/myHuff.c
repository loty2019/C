// Lorenzo Orio
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// Constants
#define MAX_SIZE 256
#define MAX_TREE_HEIGHT 100

// Global variables
char *huffmanEncoded[MAX_SIZE];

// Structs definitions
typedef struct
{
    // Initialize the character and frequency
    char character;
    long frequency;
} CharacterFrequency;

typedef struct Node
{
    // Initialize the data, frequency, and left and right child nodes
    char data;
    unsigned int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct MinHeap
{
    // Initialize the size and capacity
    unsigned size;
    unsigned capacity;
    Node **array;
} MinHeap;

// Function to create a new node with data and frequency
Node *newNode(char data, unsigned freq)
{
    // Allocate memory for a new node and initialize its data and frequency
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

// Function to create a new MinHeap with a specific capacity
MinHeap *createHeap(unsigned capacity)
{
    // Allocate memory for MinHeap and initialize size to 0
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;                                                    
    minHeap->capacity = capacity;  

    // Allocate memory for array of Nodes                                       
    minHeap->array = (Node **)malloc(minHeap->capacity * sizeof(Node *)); 

    return minHeap;                                              
}

// Swap the two nodes
void swapNodes(Node **a, Node **b)
{
    Node *t = *a;
    *a = *b;
    *b = t;
}

void makeHeap(MinHeap *minHeap, int idx)
{
    // Initialize the smallest frequency node as the parent node
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // Find the smallest frequency node among the parent and its children
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        // Swap the parent node with the smallest frequency node
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);

        // Recursively make the heap for the smallest frequency node
        makeHeap(minHeap, smallest);
    }
}

Node *extractMin(MinHeap *minHeap)
{
    // Extract the minimum frequency node from the minHeap
    Node *temp = minHeap->array[0];

    // Replace the minimum frequency node with the last node
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;

    // Rebuild the minHeap
    makeHeap(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap *minHeap, Node *node)
{
    // Increase the size of the minHeap and insert the new node
    ++minHeap->size;
    int i = minHeap->size - 1;

    // Find the correct position for the new node
    while (node->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        // Move the parent node down
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    // Insert the new node at the correct position
    minHeap->array[i] = node;
}

void buildMinHeap(MinHeap *minHeap)
{
    // Rebuild the minHeap after extracting the minimum frequency nodes
    int n = minHeap->size - 1;
    int i;

    // Starting from the parent of the last node, perform makeHeap operation on each parent node
    for (i = (n - 1) / 2; i >= 0; --i)
    {
        makeHeap(minHeap, i);
    }
}

Node *buildHuffmanTree(CharacterFrequency characters[], int size)
{
    Node *left;
    Node *right;
    Node *index;

    // Create a min heap
    MinHeap *minHeap = createHeap(size);
    for (int i = 0; i < size; ++i)
    {
        // Add nodes to the minHeap for characters with non-zero frequency
        if (characters[i].frequency > 0)
        {
            minHeap->array[minHeap->size++] = newNode(characters[i].character, characters[i].frequency);
        }
    }

    // Build the minHeap
    buildMinHeap(minHeap);

    // Build the Huffman tree by repeatedly extracting the two minimum frequency nodes and merging them
    while (minHeap->size != 1)
    {
        // Extract the two nodes with the minimum frequency from the minHeap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Create a new node with '$' as the data and the sum of frequencies of the extracted nodes
        index = newNode('$', left->freq + right->freq);
        index->left = left;
        index->right = right;

        // Insert the new node back into the minHeap
        insertMinHeap(minHeap, index);
    }

    // Return the root of the Huffman tree
    return extractMin(minHeap);
}

void printDebug(Node *root, int arr[], int length)
{
    // Print the character and its frequency looking for special characters
    if (!(root->left) && !(root->right))
    {
        if (root->data == (char)(10))
        {
            printf("LF\t%d\t", root->freq);
        }
        else if (root->data == (char)(9))
        {
            printf("TAB\t%d\t", root->freq);
        }
        else if (root->data == (char)(32))
        {
            printf("SPACE\t%d\t", root->freq);
        }
        else
        {
            printf("%c\t%d\t", root->data, root->freq);
        }

        // Print the codes
        for (int i = 0; i < length; ++i)
        {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void storeCodes(Node *root, int arr[], int index, int debug)
{
    // Assign 1 to the left edge and 0 to the right edge
    if (root->left)
    {
        arr[index] = 1;
        storeCodes(root->left, arr, index + 1, debug);
    }

    if (root->right)
    {
        arr[index] = 0;
        storeCodes(root->right, arr, index + 1, debug);
    }

    // If the node is a leaf node, store the code in the huffmanEncoded array
    if (!(root->left) && !(root->right))
    {
        huffmanEncoded[(unsigned char)root->data] = (char *)malloc(index + 1);
        for (int i = 0; i < index; i++)
        {
            huffmanEncoded[(unsigned char)root->data][i] = arr[i] + '0';
        }
        huffmanEncoded[(unsigned char)root->data][index] = '\0';

        // Print debug information if enabled
        if (debug)
        {
            printDebug(root, arr, index);
        }
    }
}

void writeEncodedHuff(FILE *inputFile, FILE *outputFile)
{
    fseek(inputFile, 0, SEEK_SET); // Reset file pointer to beginning
    int ch;
    char buffer = 0;
    int bitCount = 0;

    // Read characters from the inputFile and encode them using Huffman codes
    while ((ch = fgetc(inputFile)) != EOF)
    {
        char *code = huffmanEncoded[(unsigned char)ch];

        // Skip characters that don't have a Huffman code
        if (code == NULL)
        {
            continue;
        }

        // Encode each bit of the Huffman code
        for (int i = 0; code[i] != '\0'; i++)
        {
            buffer = buffer << 1 | (code[i] - '0');
            bitCount++;

            // Write the encoded byte to the outputFile when the buffer is full
            if (bitCount == 8)
            {
                fwrite(&buffer, 1, 1, outputFile);
                bitCount = 0;
                buffer = 0;
            }
        }
    }

    // Write the remaining bits in the buffer to the outputFile
    if (bitCount > 0)
    {
        buffer = buffer << (8 - bitCount);
        fwrite(&buffer, 1, 1, outputFile);
    }
}

void getFrequency(FILE *file, CharacterFrequency characters[])
{
    int ch;

    // Count the frequency of each character in the file
    while ((ch = fgetc(file)) != EOF)
    {
        characters[ch].frequency++;
    }
}

int main(int argc, char **argv)
{
    // Set the default input and output file names
    char *inputFileName = "completeShakespeare.txt";
    char *outputFileName = "myHuff.out";
    int debug = 0;

    int opt;
    while ((opt = getopt(argc, argv, "i:o:d")) != -1)
    {
        switch (opt)
        {
        case 'i':
            // Set the input file name based on the command line argument
            inputFileName = optarg;
            break;
        case 'o':
            // Set the output file name based on the command line argument
            outputFileName = optarg;
            break;
        case 'd':
            // Enable debug mode
            debug = 1;
            break;
        default:
            exit(1);
        }
    }

    // Open the file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Initialize the  array to store the frequency of characters
    CharacterFrequency characters[MAX_SIZE] = {0};
    for (int i = 0; i < MAX_SIZE; i++)
    {
        characters[i].character = (char)i;
    }

    // Calculate the frequency of characters in the file
    getFrequency(inputFile, characters);
    fclose(inputFile);

    // Build Huffman tree
    Node *root = buildHuffmanTree(characters, MAX_SIZE);

    // Open the file for writing
    FILE *outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Initialize an array to store the Huffman codes
    int huffmanCode[MAX_TREE_HEIGHT];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        huffmanEncoded[i] = NULL;
    }
    int index = 0;

    // Generate and store Huffman codes
    storeCodes(root, huffmanCode, index, debug);

    // Reopen the input file for reading
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        printf("Error reopening file.\n");
        fclose(outputFile);
        return 1;
    }

    // Encode and write the data
    writeEncodedHuff(inputFile, outputFile);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}