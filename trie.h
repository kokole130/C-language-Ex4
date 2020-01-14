#ifndef TRIE
#define TRIE

#define NUM_LETTER 26

typedef struct Node
{
    char letter;
    int count;
    struct Node* children[NUM_LETTER];   
}Node;

typedef enum {FALSE=0,TRUE=1}boolean;

Node* newNode(char l);

void addWord(Node *root,char *word);

boolean isLeaf(Node *n);

char* getWord();

void dEachPrint(Node *node, char* str);

void uEachPrint(Node *node, char* str);

void TriePrintDown(Node *root);

void TriePrintUp(Node *root);

void freeTrie(Node *root);
#endif