#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
	int count;
	struct Trie* next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie* temp=pTrie;

	for(int i=0;i<strlen(word);i++)
	{
		int idx=word[i]-'a';

		if(temp->next[idx]==NULL)
			temp->next[idx]=createTrie();
	
		temp=temp->next[idx];
	}

	temp->count=1;
	
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie* temp=pTrie;

	for(int i=0;i<strlen(word);i++)
	{
		int idx=word[i]-'a';

		if(temp->next[idx]==NULL)
			return 0;

		temp=temp->next[idx];
	}

	return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	if(pTrie==NULL)
		return pTrie;

	for(int i=0;i<26;i++)
	{
		if(pTrie->next[i]!=NULL)
			deallocateTrie(pTrie->next[i]);
	}

	free(pTrie);

	return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie()
{
	struct Trie* myTrie=(struct Trie*)malloc(sizeof(struct Trie));

	myTrie->count=0;
	int i;

	for(i=0;i<26;i++)
		myTrie->next[i]=NULL;

	return myTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE* file=fopen(filename, "r");

	int num=0;
	char word[256];

	while(fscanf(file, "%s", word)!=EOF)
	{
		pInWords[num]=strdup(word);
		num++;
	}

	fclose(file);
	return num;
}

int main(void)
{
	char *inWords[256];

	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
