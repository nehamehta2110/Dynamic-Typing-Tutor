#ifndef __TRIE_PREDICTION_H
#define __TRIE_PREDICTION_H

#define MAX_WORDS_PER_LINE 30
#define MAX_CHARACTERS_PER_WORD 1023


// Magic Unit Test Directive

// The following line is modified automatically by the test-all.sh script to
// enable and disable unit testing. Uncomment the following line if you are
// compiling your code with one of the unit tests (UnitTest10.c through
// UnitTest16.c) provided with the assignment.

// OTHER THAN COMMENTING/UNCOMMENTING THE FOLLOWING LINE, DO NOT MAKE ANY
// MODIFICATIONS TO THIS HEADER FILE!

//#define main __hidden_main__


typedef struct TrieNode
{
	// number of times this string occurs in the corpus
	int count;

	// 26 TrieNode pointers, one for each letter of the alphabet
	struct TrieNode *children[26];

	// the co-occurrence subtrie for this string
	struct TrieNode *subtrie;
} TrieNode;


// Functional Prototypes

TrieNode *buildTrie(char *filename);

int processInputFile(TrieNode *root, char *filename);

TrieNode *destroyTrie(TrieNode *root);

TrieNode *getNode(TrieNode *root, char *str);

void getMostFrequentWord(TrieNode *root, char *str);

int containsWord(TrieNode *root, char *str);

int prefixCount(TrieNode *root, char *str);

double difficultyRating(void);

double hoursSpent(void);


#endif