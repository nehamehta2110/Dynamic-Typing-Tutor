#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "TriePrediction.h"

#define MAX_WORD_LENGTH 1023
#define CMMD_LENGTH 1024


// Suggested Helper Functions

// Creates a new TrieNode.
TrieNode *createTrieNode(void) 
{
	
	return calloc(1, sizeof(TrieNode));
}

// Inserts String at the root of a TrieNode.
TrieNode *insertString(TrieNode *root, char *str) // (Credit: Dr. S.) 
{
	int i, idx, len = strlen(str);
	TrieNode *temp_root;

	// Check if the root is NULL
	if (root == NULL)
		root = createTrieNode();

	// If root != NULL, assign root to a temp variable.
	temp_root = root;

	// Then check every child in the TrieNode against str[i] for a match
	for (i = 0; i < len; i++)
	{
		// Check if character at str[i] is not in alphabet
		if (!isalpha(str[i]))
		{
			fprintf(stderr, "Error: (%s) contains non-alpha characters (%c) and will not be inserted---InsertString():48.\n", str, str[i]);
			return NULL;
		}		

		// Else if char is in alphabet, set the index
		idx = tolower(str[i]) - 'a';

		// Before jumping to the child TrieNode, Check if NULL
		if ( temp_root->children[idx] == NULL)
			temp_root->children[idx] = createTrieNode();

		// Move the temp_root to its correct child TrieNode
		temp_root = temp_root->children[idx];

	//	printf("\nSuccessfully inserted (%c) at root->children[%d]!\n", str[i], idx);
	}

	// The str is inserted, increment the count variable
	temp_root->count++;
	return root;
}

// Strips away any punctuators from a string. 
void stripPuncuators(char *str) 
{
	int i, j = 0;
	int len = strlen(str);

	// printf("Old: %s\n", str);


	// Loop through every char in the string.
	for(i = 0; i < len; i++)
	{	
		if (isalpha(str[i]) && !isspace(str[i]))
			str[j++] = str[i];
	}
	str[j] = '\0';

	// printf("New: %s\n", str);
}

// Determines whether a string has any punctuators.
int noPuncuators(char *str) 
{	
	int i;
	int len = strlen(str);

	for (i = 0; i < len; i++) 
		if (!isalpha(str[i]))
			return 1;

	return 0;
}


// Determines Min of two numbers.
int findMin(int A, int B)
{
	return ((A < B)? A:B);
}

// Prioritizes two strings passed by their alphabetical order.
void alphabetizePriority(char *strA, char *strB, char *winner)
{
	int i;
	int lenA = strlen(strA);
	int lenB = strlen(strB);
	int maxlen = (findMin(lenA, lenB));

	// ASCII value variables for each char in both strings.
	int A;
	int B;
	int order = 0; 

	if (lenA == lenB)
	{
		// Both strings are the same in length.
		for (i = 0; i < lenA; i++)
		{	
			if (strA[i] < strB[i])
			{
				order = 1;
				break;
			}
			else if (strA[i] > strB[i])
			{
				order = 0;
				break;
			}
	
			else
				order = 2;
		}
	}
	else
	{
		// Both strings are NOT the same in length.
		// Need to worry about overstepping bounds of each array.
		for (i = 0; i < maxlen; i++)
		{
			if (strA[i] < strB[i])
			{
				order = 1;
				break;
			}
			else if (strA[i] > strB[i])
			{
				order = 0;
				break;
			}
			// If you have two of the same strings, but one 
			// has a extra char at the end, priority is given to
			// the shorter string, order 2;
			else if (strA[i] == strB[i])
			{
				order = 2;
			}
		}
	}
	if (order == 1)
		strcpy(winner, strA);
	else if (order == 0)
		strcpy(winner, strB);
	else if (order == 2)
	{
		if ( lenA < lenB )
			strcpy(winner, strA);
		else
			strcpy(winner, strB);
	}
}

// This function finds the number of active children nodes
int activeChildren(TrieNode *root)
{
	int i, active = 0;

	for (i = 0; i < 26; i++)
		if (root->children[i] != NULL)
			active++;

	return active;
}

// This function determines whether or not trie is empty.
int isSubtrieEmpty(TrieNode *root) // :)
{
	return ((activeChildren(root) == 0)? 1:0);
}

// This function is a tweaked version of getNode().
// getPrefixNode() is used to help find the terminal node
// of a given prefix in a trie.
TrieNode *getPrefixNode(TrieNode *root, char *str) 
{
	int i;
	int idx;
	int len = strlen(str);
	TrieNode *temp_root;
	TrieNode *terminal;

	// Check if root passed is NULL
	if (root == NULL)
		return NULL;

	// Assign root to a temporay variable
	temp_root = root;

	for (i = 0; i < len; i++)
	{
		// Find index of children[] corresponding to character
		idx = tolower(str[i]) - 'a';

		// Move temp_root to that index
		temp_root = temp_root->children[idx];

		// Check its count
		if ( temp_root != NULL)
			terminal = temp_root;
		else 
			terminal = NULL;
	}
	return terminal;
}

int countStrings(TrieNode *root) 
{
	int i;
	int count = 0;

	if (root == NULL)
		return 0;

	if (root->count > 0)
		count += 1;

	for (i = 0; i < 26; i++)
	{
		if (root->children[i] != NULL)
			count += countStrings(root->children[i]);
	}
	return count;
}

void getMostFreqHelper(TrieNode *root, char *actual, char *temp, int k, int max)
{
	int i, new_max;
	char prev[MAX_WORD_LENGTH];
	char current[MAX_WORD_LENGTH];
	char newStr[MAX_WORD_LENGTH];

	if (root == NULL)
		return;


	if (root->count > 0)
	{
		
		if (root->count == max)
		{
			new_max = root->count;
			//strcpy(current, temp);
			//printf("(max: %d count: %d)prev word: (%s)\n", new_max, root->count, actual);
			//printf("(max: %d count: %d)current word: (%s)\n", new_max, root->count, current);
			alphabetizePriority(actual, current, newStr);
			strcpy(actual, newStr);
			//printf("prioritized word: %s\n", actual);
		}
		else
		{
			strcpy(actual, temp);
			new_max = root->count;
			//printf("(max: %d count: %d)current word: %s\n", new_max, root->count, actual);
		}		
	}

	temp[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		temp[k] = 'a' + i;
		getMostFreqHelper(root->children[i], actual, temp, k+1, new_max);
	}
	temp[k] = '\0';
}

// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k) 
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting) 
{
	char buffer[1026];
	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

TrieNode *buildTrie(char *filename)
{
	TrieNode *root = NULL;
	TrieNode *last_node = NULL;
	int i, len, sentenceEnded = 0; // 1 = true, sentence has ended
	int word_count = 0;
	char buffer[MAX_WORD_LENGTH + 1];

	// Initialize the buffers that contain nothing but empty strings
	char prev[MAX_WORD_LENGTH + 1];
	char current[MAX_WORD_LENGTH + 1];

	FILE *ifp;

	if ((ifp = fopen(filename, "r")) == NULL)
	{
		fprintf(stderr, "Failed to open \"%s\" in buildTrie().\n", filename);
		return NULL;
	}

	// Insert strings one-by-one into the trie.
	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		// New word is read & inserted, increment word_count
		word_count++;

		// Find length of string
		len = strlen(buffer);

		// Reset sentenceEnded to 0 every time when entering loop 
		sentenceEnded = 0;

		// Check each string for punctuators '.', '?', '!'
		for (i = 0; i < len; i++)
			if (buffer[i] == '.' || buffer[i] == '?' || buffer[i] == '!')
				sentenceEnded = 1;

		// Strip the string of any punctuators
		stripPuncuators(buffer);

		// Check what the word count is.
		if (word_count == 1)
		{
			// simply insert the first word into the trie.
			strcpy(current, buffer);
			// printf("(%d)first word on line: %s\n\n", word_count, current);
			root = insertString(root, current);

		}
		else
		{
			// check if the word is the last in its sentence.
			if (sentenceEnded) 
			{	
				// If it is the last word.
				// simply insert the last word into the trie.
				strcpy(current, buffer);
				// printf("(%d)last word on line: %s\n", word_count, current);
				root = insertString(root, current);

				// Set the the terminal node of the last word's
				// subtrie equal to NULL.
				last_node = getNode(root, current);
				last_node->subtrie = NULL;


				// Reset word_count back to zero for next line
				word_count = 0;
			}
			else 
			{
				// The word is not the last in the sentence.
				// Insert it into the trie.
				strcpy(current, buffer);
				// printf("(%d)prev word on line: %s\n", word_count, prev);
				// printf("(%d)current word on line: %s\n", word_count, current);
				root = insertString(root, current);

				// // Insert the word into the subtrie of the prev word.
				last_node = getNode(root, prev);
				if (last_node != NULL)
				{
					// printf("Last_node = TERMINAL NODE OF (%s)\n", prev);
				}
				last_node->subtrie = insertString(last_node->subtrie, current);
				// printf("\n\n===============\n");
				// printf("SubTrie of (%s)\n", prev);
				// printf("===============\n\n");
				// printTrie(last_node->subtrie, 1);
				// printf("\n----------------\n\n");
			}
		}


		// The new word is no longer needed, now put in previous.
		strcpy(prev, current); 

	}
	fclose(ifp);
	return root;
}

int processInputFile(TrieNode *root, char *filename) // :(
{
	int n, len, increment = 0;
	int signal = 0;
	char buffer[MAX_WORD_LENGTH];
	char strBuffer[MAX_WORD_LENGTH + 1];
	char digitsBuffer[MAX_WORD_LENGTH];
	TrieNode *terminal = NULL;

	FILE *fp;

	// Open The Input File
	if ((fp = fopen(filename, "r")) == NULL)
	{
		return 1;
	}

	// Reads each line with "%[^\n]\n", if using %s it reads one word at a time. 
	while (fscanf(fp, "%s", buffer) != EOF)
	{
		if (increment == 1)
		{
			signal++;
			if (signal == 1)
			{
				strcpy(strBuffer, buffer);
				// Find "str" length + 1 for '\0'
				stripPuncuators(strBuffer);
				len = strlen(strBuffer);
				strBuffer[len + 1] = '\0';
				//printf("(%d) strBuffer = %s\n", len, strBuffer);
			}
			if (signal == 2)
			{
				strcpy(digitsBuffer, buffer);
				// Find int n
				n = atoi(digitsBuffer);
				//printf("n = %d\n", n);

				// Set signal back to 0;
				signal = 0;
				increment = 0;
			}
		}

		// String has puncuator "!"
		if ((strcmp(buffer, "!") == 0))
		{
			// '!'
			//printf("Read input.....%s\n", buffer);
			printTrie(root, 0);
		}
		// String has puncuators "@ str n"
		else if ((strcmp(buffer, "@") == 0))
		{				
			increment = 1;

		}
		// String has no puncuators
		else 
		{

			
			if (!containsWord(root, buffer))
			{
				printf("%s\n", buffer);
				printf("(INVALID STRING)\n");
			}
			// Search for the string in the trie
			else if(containsWord(root, buffer))
			{
				terminal = getNode(root, buffer);
				if (terminal->subtrie == NULL)
				{
					printf("%s", buffer);
					printf("(EMPTY)");
				}
				else 
				{
					printf("%s\n", buffer);
					printTrie(terminal->subtrie, 1);
				}					
			}
			// -------------------------------
		}
	}
	fclose(fp);
	return 0;
}

TrieNode *destroyTrie(TrieNode *root) 
{
	int i;
	if (root == NULL)
		return NULL;


	for (i = 0; i < 26; i++)
	{
		destroyTrie(root->children[i]);
		
	}
	destroyTrie(root->subtrie);
	free(root);
	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str) 
{
	int i;
	int idx;
	int len = strlen(str);
	TrieNode *temp_root;
	TrieNode *terminal;

	// Check if root passed is NULL
	if (root == NULL)
		return NULL;

	// Assign root to a temporay variable
	temp_root = root;

	for (i = 0; i < len; i++)
	{
		// Find index of children[] corresponding to character
		idx = tolower(str[i]) - 'a';

		// Move temp_root to that index
		temp_root = temp_root->children[idx];

		// Check its count
		if ( temp_root->count >= 1)
			terminal = temp_root;
		else 
			terminal = NULL;
	}
	return terminal;
}

void getMostFrequentWord(TrieNode *root, char *str) // :(
{
	int i; 
	char buffer[MAX_WORD_LENGTH];

	// Check if the root is NULL
	if (root == NULL)
		return;

	// Check if the root of trie passed is empty
	if (isSubtrieEmpty(root))
		strcpy(str, "");

	// First Check if the str passed is NON-empty.
	if (strcmp(str, "") != 0)
		strcpy(str, "");

	getMostFreqHelper(root, str, buffer, 0, 0);
	printf("Most Frequent Word: %s\n", str);
}

int containsWord(TrieNode *root, char *str) 
{
	TrieNode *last = getNode(root, str);
	return ( last == NULL)? 0:1;
}

int prefixCount(TrieNode *root, char *str) 
{
	TrieNode *wizard, *terminal = NULL;
	int i;
	int len = strlen(str);
	int index;
	int count = 0;
	int prefix_branches = 0;
	int level = 0;

	wizard = root;

	// Create an aux char array to hold the prefix
	char *aux = malloc(sizeof(char) * len);

	//Check if the word itself is contained in the trie.
	if (containsWord(wizard, str))
	{
		terminal = getNode(wizard, str);
		count += terminal->count;

		// Now check the last node and test for any active children
		prefix_branches = activeChildren(terminal);
		// If there are no active children,
		// This word that is contained is the only common prefix 
		// It is not shared with any other words, return its count.
		if (prefix_branches == 0)
		{
			printf("Word Contained---count for prefix(%s): %d\n", str, count);
			return count;
		}
	}
	// If you surpass the conditional above, the prefix entered
	// Is not a contained word in the trie. 
	else
	{
		// Check each letter of the prefix that was given.
		for (i = 0; i < len; i++)
		{
			// Enter each char of prefix into aux char array
			// This will be used for comparison later on.
			aux[i] = str[i];

			// Find the corresponding index for each prefix character.
			index = tolower(str[i]) - 'a';

			if (wizard->children[index] == NULL)
			{
				count = 0;
				printf("prefix(%s) NOT FOUND.\n", str);
				return count;
			}

			// If i = the len of the prefix, 
			// Get the terminal node of prefix,
			// And if it has 1 active children, 
			// Add to the count and return it.
			if (i == (len - 1))
			{
				terminal = getPrefixNode(root, str);
				if (activeChildren(terminal) == 1)
				{
					count += 1;
					break;
				}
			}

			// Continue entering this loop while the node at index exists
			// And its count value is equal to zero.
			while (wizard->children[index] != NULL &&  wizard->children[index]->count < 1)
			{

				// Find its number of active (NON-NULL) children nodes
				prefix_branches = activeChildren(wizard->children[index]);

				// If the number of active child nodes exceeds 1, 
				// Then we know that there are multiple words that
				// Contain the given prefix, add these words to the count.
				if ((strcmp(str, aux) == 0) && prefix_branches > 1)
				{
					count += prefix_branches;
					free(aux);
				}
				else 
					// Move the temporary root to the prefix character node
					wizard = wizard->children[index];

			}
		}
	}

	printf("count for prefix(%s): %d\n", str, count);
	return count;
}

int main(int argc, char **argv)
{

	TrieNode *root = NULL, *last_node;
	char corpus[100];
	char input[100];
	int result;

	if (argc < 3)
	{
		fprintf(stderr, "Error: proper syntax requires < 3 > arguments in main().\n");
	}

	strcpy(corpus, argv[1]);
	strcpy(input, argv[2]);

	root = buildTrie(corpus);
	result = processInputFile(root, input);
	root = destroyTrie(root);
	return 0;
}
