#include "DataTypes.h"


/************FOR GENERAL USE******************/

/* getFName gets a string of 30 characters to be used as a file name
   @param strFile is of data type Str30 (char[31])
*/
void
getFName(Str30 strFile)
{
    char cDump;
    printf("Enter filename: ");
    scanf("%s%c", strFile, &cDump); // cDump is throwing away extra char
}  
  
/* getString gets a string including spaces. stops only when \n is entered or 
  the string length is already at full capacity
   @param str is a char*  where the string will be stored
   Precondition:
		before getString do this first just in case of white spaces
  		scanf("%c", &ch);
  		printf("Enter Sentence: ");
*/
void
getString(char * str)
{
    int i;
    char ch;
    i=0;
    do
    {
        scanf("%c", &ch);
        if (ch != '\n')
        {
            str[i] = ch;
            i++;
        }
    } while(ch != '\n' && i <= MAX);
}

/* displaySentence displays words from array in sentence form
   @param aWords[] - string array containing words
   @param nElem - int that is the number of elems in the array 
   Precondition:
    - nElem must not excede 75
*/
void
displaySentence(Str20 aWords[75], int nElem)
{
    int i;
    for (i=0; i<nElem; i++)
        if (i<nElem-1)
            printf("%s ", aWords[i]);
        else 
            printf("%s\n", aWords[i]);
}

/* search
search returns index where key word was found
*/
/* search returns the index where key word was found
   @param key - Str20 key word
   @param A[] - array of Str20, array to search whether or not keyword is found
   @param n - int number of elements in Str20 A[]
   @return index where key is found within the entry 
   @returns -1 if no pair found 
   Pre-condition: 
*/
int
search(Str20 key, Str20 A[], int n)
{
    int i;
    for (i=0; i<n; i++)
        if (strcmp(key, A[i]) == 0)
            return i;
    return -1;
}
/*findMax returns the index with the highest value inside*/
/* searchOneEntry returns the 1 or 0 depending if a match was found in the entry
   @param e - the structure Entry
   @param lang - the language searching for
   @param trans - the translation searching for
   @return 1 if pair is found within the entry and returns 0 if no pair found 
   Pre-condition: 
*/
int
findMax(int A[], int n)
{
    int i, max=0;
    for(i=0; i<n; i++)
        if (A[max] < A[i])
            max = i;
    return max;
}


/*********************MANAGE DATA***************************/



/*FOR ADD ENTRY*/

/* searchOneEntry returns the 1 or 0 depending if a match was found in the entry
   @param e - the structure Entry
   @param lang - the language searching for
   @param trans - the translation searching for
   @return 1 if pair is found within the entry and returns 0 if no pair found 
   Pre-condition: 
*/
int
searchOneEntry(struct Entry e, Str20 lang, Str20 trans)
{
	int i, compLan, compTrans;
	
	for (i=0; i<e.count; i++)
	{
		compLan = strcmp(lang, e.language[i]);
		compTrans = strcmp(trans, e.translation[i]);
		if (compLan == 0 && compTrans == 0)
			return 1; //returns 1 if pair is found in entry 
	}
	
	return 0; //returns 0 if pair is not found in entry
	
}

/*
searchAllEntry searches the whole table for the translation and language pair
*/
/* searchAllEntry returns the number of matches found in entry
   @param Dictionary - struct Table, where all the data is stored
   @param lang - the language searching for
   @param trans - the translation searching for
   @param int *foundIn - address of array that will contain the indexes where matches were found
   @return - int returns the number of matches found in entry 
   Pre-condition: 
*/
int 
searchAllEntry(struct Table Dictionary, Str20 lang, Str20 trans, int *foundIn)
{
    int i, j=0, found = 0;
    for (i=0; i<Dictionary.nEntries; i++)
    {
        if (searchOneEntry(Dictionary.entries[i], lang, trans) == 1)
        {
            foundIn[j] = i;
            j++;
            found++; 
        }
    }
    return found; // number of entries that have that pair
}

/*FOR DELETE ENTRY*/
/* copyEntry
    copyEntry copies the source entry to the destination entry. 
    Destination entry is first made empty before being copied to. 
    @param *eDest - pointer to destination entry
    @param eSource - source entry 
*/
void
copyEntry(struct Entry *eDest, struct Entry eSource)
{
    int i;

    //resetting destination entry to empty
    for (i=0; i<eDest->count; i++)
    {
        strcpy(eDest->language[i], "");
        strcpy(eDest->translation[i], "");
    }
    eDest->count = 0; 

    //copying data in source entry to destination entry
    for (i=0; i<eSource.count; i++)
    {
        strcpy(eDest->language[i], eSource.language[i]);
        strcpy(eDest->translation[i], eSource.translation[i]);
        eDest->count++;
    }

}

/*FOR DELETE TRANSLATION*/


//to move the entries forward once deleted
/* movePair moves all the language translation pairs to the previous index starting with the index given
   @param *e - pointer to an entry
   @param index - start moving from this index
   @param n - index of last pair in entry
   Precondition:
   	- index cannot be negative
*/
void
movePair(struct Entry *e, int index, int n)
{
    int i;
    for (i=index; i<n; i++)
    {
        strcpy(e->language[i], e->language[i+1]);
        strcpy(e->translation[i], e->translation[i+1]);
    }
    strcpy(e->language[i], "");
    strcpy(e->translation[i], "");
}
/*FOR DISPLAY ENTRY*/

/* dispEntry displays all translation and language pairs in the entry
   @param e - data type  structure Entry
   Pre-condition: 
    - struct Entry e has data inside
*/
void
dispEntry(struct Entry e)
{
    int i;
    printf("-------------------------------------\n");
    printf("| Language        || Translation     |\n");
    printf("--------------------------------------\n");
    for (i=0; i < e.count; i++)
        printf("%s: %s\n", e.language[i], e.translation[i]);
}

/* dispEntry displays all entries that matched the translation and language pair
   @param Dictionary - struct Table Dictionary is the data structure where all data is stored
   @param lang - the language searching for
   @param trans - the translation searching for
   Pre-condition: 
   	- Dictionary has data inside
*/
void
dispPairs(struct Table Dictionary, Str20 lang, Str20 trans)
{
    int i, found, foundIn[Dictionary.nEntries], index;
    found = searchAllEntry(Dictionary, lang, trans, foundIn);
    if (found > 0)
    {
        for (i=0;i<found; i++)
        {
            index = foundIn[i];
            dispEntry(Dictionary.entries[index]);
        }
        
    }
}


/****************FOR LANGUAGE TOOLS*******************/

/* isSymbol checks if the character is == to the symbol
   @param char c - char input
   @return 1 if c is a special character 
   @return 0 if c is not a special character 
   Pre-condition: 
*/
int
isSymbol(char c)
{
    if (c == ',' || c == '.' || c == '!' || c == '?')
        return 1;
    else 
        return 0;
}
/* split performs tokenization on a sentence
   @param Str20 *aWords - string[] pointer where words will be stored
   @param int *pElem - int pointer that refers to the number of elements in aWords[]
   @param longString sentence - sentence that split() will split
   Pre-condition: 
*/
void 
split(Str20 *aWords, int *pElem, longString sentence)
{
   int i, j = 0;
   *pElem = 0;
  
//included the index where the '\0' is to include the last word
   for (i = 0; i <= strlen(sentence); i++)
    if (sentence[i] != ' ' && sentence[i] != '\0')
    {
        if (!isSymbol(sentence[i])) // checks if .,?!
        {
            aWords[*pElem][j] = sentence[i]; 
            j++;
        }        
    }
    else 
    {	
        aWords[*pElem][j] = '\0';
        j = 0;
        (*pElem)++;
    }
}





/*********************MENU*DISPLAY***********************/

/*FOR MANAGE DATA*/
void 
displayManDataMenu(){
	printf("=====MANAGE DATA MENU=====\n");
	printf("\t1: Add Entry\n");
	printf("\t2: Add Translations\n");
	printf("\t3: Modify Entry\n");
	printf("\t4: Delete Entry\n");
	printf("\t5: Delete Translations\n");
	printf("\t6: Display All Entries\n");
	printf("\t7: Search Translations\n");
	printf("\t8: Search Word\n");
	printf("\t9: Export\n");
	printf("\t10: Import\n");
	printf("\t11: Exit\n");
	printf("=========================\n");
}



/*FOR LANGUAGE TOOL MENU*/
void 
displayLangToolMenu()
{
	printf("=====LANGUAGE TOOL MENU=====\n");
	printf("\t1: Identify Main Language\n");
	printf("\t2: Simple Translation\n");
	printf("\t3: Exit\n");
	printf("============================\n");
}



/*FOR MAIN MENU*/
void 
displayMainMenu(){
	printf("=====MAIN TOOL MENU=========\n");
	printf("\t1: Manage Data\n");
	printf("\t2: Langage Tools\n");
	printf("\t3: Exit\n");
	printf("============================\n");
}

