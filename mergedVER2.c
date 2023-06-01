/*********************************************************************************************************  
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts 
learned.  I have constructed the functions and their respective algorithms and corresponding code by myself.  The 
program was run, tested, and debugged by my own efforts.  I further certify that I have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons. 	

All the code below has been an improved version of both of our codes
																												Pair 7
                                                                                                                Lanz Martin U. Tan, DLSU ID# 12118850
                                                                                                                Nicole Kate T. Uy, DLSU ID# 12195073  
*********************************************************************************************************/ 

#include "helpFunctions.c"

/*
Add Entry 
Your program should ask for a language and translation pair (for example, Tagalog and mahal, 
respectively).  The  program  first  checks  if  there  is  already  an  existing  entry  with  the  indicated 
language  and  translation  pair.    If  yes,  then  program  first  shows  all  information  about  entries 
information, same as with the given input (so if the given 2 examples above already exist, then 
both entries above should be shown first).  Then, the user is asked if this is a new entry.  If no, 
then the program goes back to the Manage Data menu options.  If the user answered yes, then 
a  new  entry  is  created  with  the  input  as  the  entry,  then  language-translation  pairs  should  be 
taken in as input to be included as part of this new entry. Note that you are not allowed to ask 
the  user  how  many  language-translation  pairs  will  be  given  as  input.    However,  the  program 
may ask the user if he wants to encode another pair or to use a sentinel value to terminate the 
input series.  Both language and translation should each have at least 1 character.  
*/

//ADD ENTRY ONLY ASKS FOR 1 LANGTRANS PAIR
int 
addEntry(struct Table *Dictionary)
{
	Str20 tempLan, tempTrans;
	int foundIn[Dictionary->nEntries], found, index;
    char cOpt, cChoice;

    do
    {
        /*getting trans and lang pair*/
        printf("Enter language: ");
        scanf("%s", tempLan);
        printf("Enter translation: ");
        scanf("%s", tempTrans);

        /*searching if there is an entry with a match*/
        //match found
        found = searchAllEntry(*Dictionary, tempLan, tempTrans, foundIn);
        if (found > 0)  // greater than 1 indicates it's found
        {
            dispPairs(*Dictionary, tempLan, tempTrans);

            //option yes or no
            printf("Is this a new entry? (Y/N) ");
            scanf(" %c", &cOpt);
            if (cOpt == 'Y' || cOpt == 'y')
            {
                index = Dictionary->nEntries; 
                if (index < 150) // as long as less than maximum number of pairs
                {
                    strcpy(Dictionary->entries[index].language[0], tempLan);
                    strcpy(Dictionary->entries[index].translation[0], tempTrans);
                    Dictionary->entries[index].count = 1;
                    Dictionary->nEntries++;
                }
                else 
                {
                    printf("Error! Cannot add more entries.\n"); // reaches maximum number of pairs
                    return -1;
                }
                printf("Do you want to add more entries? (Y/N) ");
                scanf(" %c", &cChoice);
            }
            else 
                return 0;
        }
        
        //match not found
        else
        {   
            index = Dictionary->nEntries ;
            if (index < 150)
            {
                strcpy(Dictionary->entries[index].language[0], tempLan);
                strcpy(Dictionary->entries[index].translation[0], tempTrans);
                Dictionary->entries[index].count = 1;
                Dictionary->nEntries++;
                printf("Do you want to add more entries? (Y/N) ");
                scanf(" %c", &cChoice);
            }
            else 
            {
                printf("Error! Cannot add more entries.\n");
                return -1;
            }
            
        }

    } while (cChoice != 'N' && cChoice != 'n');
    //Dictionary->nEntries--;
    return 0;

}


/*
Add Translations 
Your program should ask for a language and translation pair (for example, Tagalog and mahal, 
respectively).  The  program  first  checks  if  there  is  already  an  existing  entry  with  the  indicated 
language and translation pair.  If no, then a message indicating that such an entry do not exist 
yet  and  thus  the  user  should  first  use  the  Add  Entry  option.    However,  if  there  is  an  existing 
entry,  then  program  first  shows  all  information  about  entries’  information.    If  there  is  only  one 
entry that exists, then the language and translation pair is asked from the user and it is added to 
the same entry.  The count now should be updated.  In situations where there is more than one 
result, then the user is asked which particular entry is the one where a new language-translation 
pair  will  be  added  to.    In  this  case,  an  integer  input  is  expected.  [Let  us  say  the  two  samples 
above exist and we want to add a new translation pair for the first entry.  So let’s say the user 
inputs  1  to  represent  addition  to  the  first  entry,  then  the  user  is  asked  to  input  the  language-
translation pair (example French and amour, respectively).  Lastly the count should be updated 
to 7.]   The user is asked if more translations to the same entry is going to be given, if yes, then 
language-translation  pairs  will  be  asked  and  added  to  the  entry.    If  the  answer  is  no,  the 
program  reverts  back  to  the  Manage  Data  menu.  Note  that  again  language  and  translation 
should  each  have  at  least  1  character.    Also,  note  that  if  the  entry  already  has  a  count  of  10 
(language-translation  pairs),  no  additional  translation  pairs  can  be  added  to  this  entry;  a 
message should be shown in this situation before going back to the Manage Data menu. 
*/
void
addTrans(struct Table *Dictionary)
{
    int found, entryIndex, count, foundIn[Dictionary->nEntries];
    Str20 tempLan, tempTrans, lang, trans;
    char cChoice;
	
    printf("Input language and translation: ");
    scanf("%s %s", tempLan, tempTrans);
    found = searchAllEntry(*Dictionary, tempLan, tempTrans, foundIn);
    if (found <= 0) 
    {
        printf("Does not exist yet, please use the Add Entry option.");
    }

    else if (found > 0) // entry found from entries in addEntry
    {
        dispPairs(*Dictionary, tempLan, tempTrans);
        if (found == 1) 
        {
        	entryIndex = foundIn[0];
        	count = Dictionary->entries[entryIndex].count;
        	if (count < MAX_pairs)
        	{
	        	printf("Input new language and translation pair: ");
	            scanf("%s %s", lang, trans);
	            
	            strcpy(Dictionary->entries[entryIndex].language[count], lang);
	            strcpy(Dictionary->entries[entryIndex].translation[count], trans);
	            Dictionary->entries[entryIndex].count++;
			}
			else
				printf("Error! Can not add to that entry.\n");
             
        }

        else
        {
            printf("Which entry do you want to add a new language-translation pair to? ");
            scanf("%d", &entryIndex); 
			entryIndex--;
			count = Dictionary->entries[entryIndex].count;
			
			if (count < MAX_pairs)
        	{
	            printf("Input new language and translation pair: ");
	            scanf("%s %s", lang, trans);
	            
	            strcpy(Dictionary->entries[entryIndex].language[count], lang);
	            strcpy(Dictionary->entries[entryIndex].translation[count], trans);
	            Dictionary->entries[entryIndex].count ++;
        	}
        	else
				printf("Error! Can not add to that entry.\n");
        }
        
        printf("Do you still want to add translations to the same entry? (Y/N) ");
        scanf(" %c", &cChoice);
        while(cChoice != 'N' && cChoice != 'n' && Dictionary->entries[entryIndex].count < MAX_pairs) 
        {
            printf("Input new language and translation pair: ");
            scanf("%s %s", lang, trans);
            count = Dictionary->entries[entryIndex].count;
            strcpy(Dictionary->entries[entryIndex].language[count], lang);
            strcpy(Dictionary->entries[entryIndex].translation[count], trans);
            Dictionary->entries[entryIndex].count ++;
            if (Dictionary->entries[entryIndex].count < MAX_pairs)
            {
                printf("Do you still want to add translations to the same entry? (Y/N) ");
                scanf(" %c", &cChoice);
            }
            
        } 
    }
}

/*
Display All Entries  
Provide a listing of all entries. Display one entry (all language-translation pairs and the count) at 
a time. Each entry is displayed alphabetically (using the ASCII value) based on language.  That 
is,  within  an  entry  (intra-entry)  if  the  languages  are  “Spanish”,  “English”,  “Cebuano”  and 
“Filipino”, the sequence of the  sorted display will be “Cebuano”, “English”, “Filipino”, “Spanish”.  
Of  course,  their  corresponding  words  are  displayed  beside  the  language.  [Note  that  inter-
entries are not sorted.  That is if the first entered word is about the “love”, and the second entry 
is “expensive”, these will not be sorted.] Provide a way for the user to view the next or previous 
word or exit the view (i.e., press ‘N’ for next, ‘P’ for previous, ‘X’ to end the display). Make sure 
that  garbage  values  are  not  displayed  (i.e.,  do  not  display  the  7th,  8th,  9th,  and  10th  language-
translation pair if there are only 6 in that entry).  Do not also display all 150 entries if there are 
only 5 entries initialized. 
*/

void
displayAll(struct Table Dictionary)
{
    int i, j, min, m=0;
	char response;
	struct Entry temp;
	Str20 tempStr;
    do
    {
    	if (m >=0 && m < Dictionary.nEntries)
    	{
	    	printf("------------------------------------------\n");
	        printf("| %d | Language        || Translation     |\n", m+1);
	        printf("------------------------------------------\n");
	        
		    copyEntry(&temp, Dictionary.entries[m]);
	        
	         
	        for (i=0;i<Dictionary.entries[m].count;i++)
	        {
	            min = i; // min is the lowest element 
	    
	            for (j=i;j<Dictionary.entries[m].count;j++)
	                if (strcmp(temp.language[min], temp.language[j]) > 0)
	                    min = j;
	            
	            if (i!= min)
	            {
	            	//Swapping places of language
	            	strcpy(tempStr, temp.language[i]);
			        strcpy(temp.language[i], temp.language[min]);
			        strcpy(temp.language[min], tempStr);
			        //swapping places of translation
			        strcpy(tempStr, temp.translation[i]);
			        strcpy(temp.translation[i], temp.translation[min]);
			        strcpy(temp.translation[min], tempStr);
			        
				}
	        }
	            
	        
	        for (i=0;i<Dictionary.entries[m].count;i++)
	            printf("%s: %s\n", temp.language[i], temp.translation[i]);
	        
	    	printf("View next or previous word?\n" );
	        printf("Type 'N' or 'n' to check next word.\n");
	        printf("Type 'P' or 'p' to check previous word.\n");
	        printf("Type 'X' or 'x' to exit.\n");
	        scanf(" %c", &response);
		}
		

        if (response == 'N' || response == 'n')
        {
        	m++;
        	if (m>=Dictionary.nEntries)
        	{
        		printf("Error! No more entries.\n");
			}
        		
		}
            
        else if (response == 'P' || response == 'p')
        {
        	m--;
        	if (m<0)
        	{
        		printf("Error! No more entries.\n");
			}
		}
            
        else if (response != 'x' && response != 'X')
            printf("Error. Invalid input.\n");
        
    } while ((response == 'P' || response == 'N' || response == 'p' || response == 'n') && response != 'X'  && response != 'x' && m >=0 && m < Dictionary.nEntries);
    
}
/*
Modify Entry 
Your program should allow your user to modify an entry.  This option will first display all entries 
before asking which he wants to modify. [Refer to Display All Entries for details on how info are 
to  be  displayed.]  The  input  for  this  is  a  number.  A  valid  input  starts  from  1  to  the  number  of 
entries initialized.  Note that the first entry is referred to as entry 1, but should be stored in index 
0.  If an invalid number is given, a message is displayed before going back to the Manage Data 
menu. If a valid number is given, then the user is asked which item is to be modified.  Again, an 
input number 1 signifies the first language-translation pair in this entry, but this is stored in index 
0.  The user is also asked which of this entry is to be modified, the language or the translation, 
before  proceeding  to  ask  for  the  new  value  for  that  entry.    Note  that  the  user  is  also  asked  if 
other language-translation pairs is going to be modified.  When the user is satisfied and no more 
modifications are to be done on this current entry, the program reverts back to the Manage Data 
menu.  If the user wishes to modify a different entry, the user has to chose Modify Entry again. 
Note that no additional translations will be done in this option and no deletions will also be done 
in this option.  
*/
void
modEntry(struct Table *Dictionary)
{
    int input, item, choice;
    char option;
    Str20 replace_trans, replace_lang;
    int i, j, min;
	struct Entry temp;
	Str20 tempStr;
    

  	printf("Enter entry number you want to modify: ");
        scanf("%d", &input);
    
    if (input >= 1 && input <= Dictionary->nEntries) // checks if valid entry
    {
    	input--; //to get index of entry number
    	
    	//making a copy in alphabetical order
    	copyEntry(&temp, Dictionary->entries[input]);
	         
        for (i=0;i<Dictionary->entries[input].count;i++)
        {
            min = i; // min is the lowest element 
    
            for (j=i;j<Dictionary->entries[input].count;j++)
                if (strcmp(temp.language[min], temp.language[j]) > 0)
                    min = j;
            
            if (i!= min)
            {
            	//Swapping places of language
            	strcpy(tempStr, temp.language[i]);
		        strcpy(temp.language[i], temp.language[min]);
		        strcpy(temp.language[min], tempStr);
		        //swapping places of translation
		        strcpy(tempStr, temp.translation[i]);
		        strcpy(temp.translation[i], temp.translation[min]);
		        strcpy(temp.translation[min], tempStr);
			}
        }
    	
	    do
	    {
            printf("Enter item number to be modified: "); // ask what pair to be modified
            scanf("%d", &item);  
            
			
			if (item >= 1 && item <= Dictionary->entries[input].count)
			{
				//to get index of item number
				item--;
				printf("'1' to modify translation || '2' to modify language: "); // if language or translation
            	scanf("%d", &choice);
				
				if (choice == 1)
	            {
	                printf("Input the changes in translation: ");
	                scanf("%s", replace_trans);
	                //looking for original position
	                item = search(temp.translation[item], Dictionary->entries[input].translation, temp.count);
	                strcpy(Dictionary->entries[input].translation[item], replace_trans);
	            }
	
	            else if (choice == 2)
	            {
	                printf("Input the changes in language: ");
	                scanf("%s", replace_lang);
	                //looking for original position
	                item = search(temp.language[item], Dictionary->entries[input].language, temp.count);
	                strcpy(Dictionary->entries[input].language[item], replace_lang); // replace the previous entry
	            }
	            else
	            {
	            	printf("Input not among the options.\n");
				}
	            printf("Modify other language-translation pairs in the entry?\n");
	            printf("Type 'Y' or 'y' to modify other pairs.\n");
	            printf("Type 'N' or 'n' to exit.\n");
	            scanf(" %c", &option);
			}
            else
            {
            	printf("Error! Item number not in entry.\n");
            	option = 'N';
			}
            
        } while (option != 'N' && option != 'n');
	        
	}
	else
    {
        printf("Error invalid entry. No pair found.\n");
        option = 'N';
    }

        
    
}


/*
Delete Entry 
The  program  first  shows  all  entries’  information  before  asking  which  entry  the  user  wants 
deleted. [Refer to Display All Entries for details on how info are to be displayed.].  The input for 
this is a number. A valid input starts from 1 and ends at the number of entries initialized.  Note 
that the first entry is referred to as entry 1, but should be stored in index 0.  If an invalid number 
is  given,  a  message  is  displayed  before  going  back  to  the  Manage  Data  menu.  Note  that  in 
deleting an entry, all language-translation pairs are included in the deletion. 
*/

/* input only works for 1 to nEntries*/

void
delEntry(struct Table *Dictionary, int input)
{
    int i; 

    if (input >= 1 && input <= Dictionary->nEntries)
    {
        input--;
        //moving entries backward 1 index
        for(i=input; i<Dictionary->nEntries-1; i++)           
            copyEntry(&Dictionary->entries[i], Dictionary->entries[i+1]);
        Dictionary->nEntries--;
    }
        
    else
        printf("Invalid input!\n");
    
}


/*
Delete Translation 
Your  program  should  allow  your  user  to  delete  a  language-translation  pair  from  an  entry.  This 
option will first display all entries before asking which he wants to delete from. [Refer to Display 
All  Entries  for  details  on  how  info  are  to  be  displayed.]  
The  input  for  this  is  a  number.  A  valid input starts from 1 to the number of entries initialized.  Note that the first entry is referred to as 
entry 1, but should be stored in index 0.  If an invalid number is given, a message is displayed 
before going back to the Manage Data menu. If a valid number is given, then the user is asked 
again which language-translation pair from this entry is to be deleted.  Make sure that the input 
number  is  valid  (before  you  delete).    A  valid  number  is  from  1  to  10  only  and  it  should  be  an initialized entry (meaning, the user cannot choose 7 if there are only 6 language-translation pair 
under the chosen word).  If an invalid value is given, the user is notified with a message and is 
asked  if  a  deletion  will  still  be  done.    If  not,  then  the  program  goes  back  to  the  Manage  Data 
menu.   If  yes,  then  the program  proceeds to  ask  again  for  which  language-translation  pair  will 
be removed and continue to do so as long as the user still wants to delete language-translation 
pairs from this same entry. If there is only 1 language-translation pair in this entry and this is to 
be deleted, then the whole entry is also deleted. 
*/
/*make sure when using this function, in the menu, ask for input*/

void
delTrans(struct Table *Dictionary)
{
    int entry, pair, nDeleted=0; 
    char cOpt;

    printf("Enter entry number where you want translation to be deleted: ");
    scanf("%d", &entry);
    if (entry >= 1 && entry <= Dictionary->nEntries)
    {
        entry--; // to get the actual index of entry
        while (cOpt != 'N' && cOpt != 'n' && Dictionary->entries[entry].count > 0 && nDeleted != 1)
		{
        	if (Dictionary->entries[entry].count > 0)
        		dispEntry(Dictionary->entries[entry]);
        		
            printf("Enter language translation pair you want to delete: ");
            scanf("%d", &pair);
            if (pair >= 1 && pair <= Dictionary->entries[entry].count)
            {
                pair--; //to get the actual index of pair
                //deletes pair
                movePair(&Dictionary->entries[entry], pair, 
                        Dictionary->entries[entry].count);
                        
                Dictionary->entries[entry].count -= 1;
                
                if (Dictionary->entries[entry].count == 0)
                {
                	entry++;
                	delEntry(Dictionary, entry);
                	entry--;
                	nDeleted=1;
				}
        	
            }
                
            else {
                printf("Invalid input! Do you still want to continue? (Y/N) ");
                scanf(" %c", &cOpt);
            }
            
            if (Dictionary->entries[entry].count != 0 && nDeleted != 1)
        	{
	            printf("Do you still want to continue? (Y/N) ");
	            scanf(" %c", &cOpt);
			}
        } 
        

    }
        
    else
        printf("Invalid input!\n");
}


/*
Search Word 
This option first asks for an input word, then the program proceeds to show a listing of all entries 
where that input word appears as a translation. Display is similar to how the Display All Entries 
work (with a way to view next, previous, and exit) but only those that matches the given word. 
[For  example,  if  the  word  is  to  be  searched  is  mahal,  then  both  entries  in  the  given  example 
should be shown.  But, if the word to be searched is gui, then only the last entry (all language-
trvoidanslation  pairs  in  this  entry)  should  be  displayed.  If  no  word  matches,  a  message  should  be 
shown prior to reverting back to the Manage Data menu. 
*/
void
searchWord(struct Table Dictionary)
{

    int i,j, cmp, foundWord[MAX]={0}, numFound=0;
    Str20 input;
	char response;
	
    printf("Input word: "); // asking what word to search
    scanf("%s", input);
    
    for (i=0;i<Dictionary.nEntries;i++)
	{
		for (j=0;j<Dictionary.entries[i].count;j++)
		{
			cmp=strcmp(input, Dictionary.entries[i].translation[j]);
        	
        	if (cmp==0)
        	{
        		//printf("%s == %s\n", input, Dictionary.entries[i].translation[j]);

				if (numFound > 0)
				{
					if (foundWord[numFound-1] != i)
					{
						foundWord[numFound] = i;
	        			numFound++;
					}
				}
				else
				{
					foundWord[numFound] = i;
        			numFound++;
				}
        	}
		}
    }
    i=0;    
    do
    {
        if (numFound == 0)
	    {
	        printf("\nNo word matches\n");
	        response = 'X';
	    }
	    else
	    {
		    j=foundWord[i];
	    	dispEntry(Dictionary.entries[j]);
	    	
	        printf("View next or previous word?\n" );
	        printf("Type 'N' or 'n' to check next word.\n");
	        printf("Type 'P' or 'p' to check previous word.\n");
	        printf("Type 'X' or 'x' to exit.\n");
	        scanf(" %c", &response);
	        	
	        if (response == 'N' || response == 'n')
	        {
	        	i++;
	        	if (i>=numFound)
	        		printf("Error! No more entries.\n");
	        		
			}
	            
	        else if (response == 'P' || response == 'p')
	        {
	        	i--;
	        	if (i<0)
	        		printf("Error! No more entries.\n");
			}
	            
	        else if (response != 'x' && response != 'X')
	            printf("Error. Invalid input.\n");
		}
    	

    } while ((response == 'P' || response == 'p' || response == 'N' || response == 'n') && response != 'X'  && response != 'x' && i>0 && i < numFound);
	
	

}

/*
Search Translation 
This  option  is  similar  to  Search  Word,  except  that  the  searching  is  of  a  specific  language  and 
translation. Meaning input for this option is both the language and the translation and the display 
are all entries where a language-translation appears. [For example, if the search is for Tagalog 
mahal, then both entries in the given example should be shown.  But, if  search is for Cebuano 
and gugma (the language and translation, respectively), then only the first entry in the example 
should be shown. If there is no match, a message should be shown prior to reverting back to the 
Manage Data menu.  
*/
void
searchTrans(struct Table Dictionary)
{
    int found=0, foundIn[Dictionary.nEntries];
    Str20 inputLang, inputTrans;

    printf("Input languange and translation: ");
    scanf("%s %s", inputLang, inputTrans);
		
	found = searchAllEntry(Dictionary, inputLang, inputTrans, foundIn); 
	
	if (found > 0)
    {
        dispPairs(Dictionary, inputLang, inputTrans);
    }

	else
		printf("\nNo word matches\n");
  
}
/*
Export 
Your program should allow all data to be saved into a text file.  The data stored in the text file 
can  be  used  later  on.    The  system  should  allow  the  user  to  specify  the  filename.    Filenames 
have  at  most  30  characters  including  the  extension.    If  the  file  exists,  the  data  will  be 
overwritten. 
*/
/*
Note  that  the  sample  content  above,  assumes  a  scenario  where  the  user  chose  Export, 
immediately  after  a  series  of  Add  Entry.  Should  the  user  choose  other  options  (like  Add 
Translation or Delete Entry) where the display triggered the sorting, then the exported file will 
reflect the sorted result. 
*/
void
Export(struct Table Dictionary)
{
    Str30 strFileName;
    int i, j;
    FILE *fp;

    getFName(strFileName); //this function gets the file name and makes sure the \n is not included
    fp = fopen (strFileName, "w"); // writing in the file

    if (fp != NULL)
    {
        for (i=0; i<Dictionary.nEntries; i++)
        {
            for (j=0; j<Dictionary.entries[i].count; j++)
	                fprintf(fp, "%s: %s\n", Dictionary.entries[i].language[j], 
	                                        Dictionary.entries[i].translation[j]);
            
            fprintf(fp, "\n");
        }
        

        fclose(fp); 
    }
    else printf("File was not able to open for writing\n");
    
}


/*
Import 
Your program should allow the data stored in the text file to be added to the list of entries in the 
program.      The  user  should  be  able  to  specify  which  file  (input  filename)  to  load.    If  there  are 
already  some  entries  added  (or  loaded  previously)  in  the  current  run,  the  program  shows  one 
entry loaded from the text file and asks if this is to be added to the list of entries (in the array).  If 
yes,  it  is  added  as  another  entry.    If  no,  this  entry  is  skipped.    Whichever  the  choice,  the 
program  proceeds  to  retrieve  the  next  entry  in  the  file  and  asks  the  user  again  if  this  is  to  be 
included  in  the  array  or  not,  until  all  entries  in  the  file  are  retrieved.  The  data  in  the  text  file  is 
following the format indicated in Export.  [Based on the last note in the Export, do not assume 
that each entry in the file to be imported are already sorted.] 

	@return -1 if fail to open
	@return 0 if successfully imported
*/
int
Import(struct Table *Dictionary, Str30 strFileName)
{
    //Str30 strFileName;
    Str20 lang[10], trans[10];
    int i=0, ctr=0, numEntries, len;
    char option, sym, sym2;
    FILE *fp;
    
     //this function gets the file name and makes sure the \n is not included
    fp = fopen (strFileName, "r"); // open to reading the file

    if (fp != NULL)
    {
        while (fscanf(fp,"%c", &sym) != -1)
        {
        	fseek(fp, -1, SEEK_CUR);
            i=0;
            ctr=0;
            
            while(sym != '\n' && i <= MAX_pairs && fscanf(fp,"%c", &sym) != -1)
            {
            	fseek(fp, -1, SEEK_CUR);
            	//language<:><space>translation<\n>
                fscanf(fp, "%s%c%s", lang[i], &sym, trans[i]);
                len = strlen(lang[i]);
                lang[i][len-1] = '\0';
                printf("%s: %s\n", lang[i], trans[i]);
                i++;
                ctr++;
                fscanf(fp, "%c%c", &sym2, &sym);
                if (sym != '\n')
                    fseek(fp, -2, SEEK_CUR);
            }
			if (sym == '\n')
			{
				printf("Do you want to add this entry? (Y / N) ");
	            scanf(" %c", &option);
		        if (option == 'Y' || option == 'y')
	            {
	                for (i=0; i<ctr; i++)
	                {
	                	numEntries = Dictionary->nEntries;
	                    strcpy(Dictionary->entries[numEntries].language[i], lang[i]);
	                    strcpy(Dictionary->entries[numEntries].translation[i], trans[i]);
	                }
	                Dictionary->entries[numEntries].count = ctr;
	                (Dictionary->nEntries)++;
	            }
			}
			sym = '0';
        }
        

        fclose(fp); 
        return 0;
    }
    else 
	{
		printf("File was not able to open for reading\n");
		return -1;
	}
}


/*----------------LANGUAGE TOOLS-----------------------*/

/*
IDENTIFY MAIN LANGUAGE
In this feature, the program asks the user to input a phrase or sentence. Assume this input is at 
most 150 characters and could consist of many words. The program then splits this into words –
this is called tokenization. Any comma, period, exclamation point, or question mark should be 
removed from the word. Assume that a space will separate the tokens. From these words, the 
program will determine what language it is by checking against the list of entries loaded from the 
file. Note that it is possible that the sentence used a combination of words from different 
languages, thus the result should be the one with the highest count. Note that it is possible that 
some of the words in the sentence cannot be found in the list of entries, in which case, these 
words are just ignored. For cases where the result is more than one language with the same 
count, the program can have any of these languages as the result. [For example, let’s say the 
array of entries contain the given 2 example entries in page 1 and if the sentence is “mahal, 
expensive eh”, the count for English is 1, Tagalog is 1 (not 2, since it is the same word),
Cebuano is 1, then the program can produce English or Tagalog or Cebuano as the output 
language. If the example sentence is “mahal, mahal ito ha”, then count for Tagalog is 2 
(because mahal appeared in the input twice so this means checking is per word) and Cebuano 
is also 2; again the result of your program can be either of these languages. But if the example 
page 5
sentence is “love, this is expensive!”, the count for found English words is 2, thus the result 
should be English. Last example, if none of the words are found in the array of entries, like “mi 
casa su casa”, then the result is a message to say that it cannot determine the language.]
The program goes back to the Language Tools menu after processing one text.
*/

void
mainLang(struct Table Dictionary)
{
    /*algo
    1. get sentence/phrase. max 150 char
    2. splits into words. space separates.
    3. comma, period exclamation, question mark. remove
    4. search the words indiv. count per language. */

	//a is the number of languages found. 
    int i, j, k, a=0, found=0, nElem, cmp=0;
	int countOfLang[75] = {}; //countOfLang is the array containing the count of each language.
    longString sentence;
    Str20 aWords[75]={}, languages[75]={}; //languages[] is the language of the words
    char cDump;
    
	printf("Enter Sentence: ");
	scanf("%c", &cDump);
    getString(sentence);
    split(aWords, &nElem, sentence);
    
    for (i=0;i<nElem;i++) //for each word
    {
        for (j=0;j<Dictionary.nEntries;j++) //looking thru each entry
        {
            for (k=0;k<Dictionary.entries[j].count;k++) //looking thru the translations of each entry
            {
            	//comparing word to dictionary
                cmp = strcmp (Dictionary.entries[j].translation[k], aWords[i]); 
                			
				/*
                1. compare word to all translations stored in dictionary
                2. if found, get the language of the word. 
                3. add count to language. if language is = to other languages, add there
                4. repeat for next word
                */
				
				if (cmp == 0) //word found in index k
				{
//					printf("\n%s: %s was found\n", 
//							Dictionary.entries[j].language[k],Dictionary.entries[j].translation[k]);

					//finding index of current languages
					found = search(Dictionary.entries[j].language[k], languages, a);
					if (found == -1) //language[k] is not in the array of languages[]
					{
						strcpy(languages[a], Dictionary.entries[j].language[k]);
						countOfLang[a] += 1; //increment the count of that language
						a++; //increment number of languages in array
					}
					//language is in the array of languages
					else
					{
						strcpy(languages[found], Dictionary.entries[j].language[k]);
						countOfLang[found] += 1;
					}
				}
            }
        }
    }
            
    if(a!= 0)
    {
    	printf("\n===============TOP=LANGUAGES=================\n");
    	for (i=0; i<a; i++)
    	{
	    	found = findMax(countOfLang, a);
	        printf("Top %d language used is %s with %d words\n", i+1, languages[found], countOfLang[found]);
	        countOfLang[found] = 0;
		}
    }
	else
        printf("Cannot determine language.\n");    

}
/*
SIMLE TRANSLATION
In this feature, the program asks the user for the language of the source text, the text to be 
translated and the language to be translated to. Assume the text is most 150 characters and 
could consist of many words. Similar to the previous option, tokenization and removal of the 
symbols from the words need to be done. The translation need not include the symbols that 
were removed. For words that do not have corresponding translations, just use the same word 
as in the given text. If there is more than one translation, the first that it encountered in the 
array is the one to be used. [For example, if the source text is in English “i love ccprog2” and 
this is supposed to be translated to Tagalog, then the result is “i mahal ccprog2”. If the source 
text is in Tagalog “mahal ba ito?” and should be translated to English, the result should be “love 
ba ito”, assuming the first entry in page 1 is the first that the program found Tagalog-mahal with 
an available translation to English.]
After processing one text, the user is again asked if another text is to be translated from the 
same source and output language. If yes, a new text is asked. Once the user says no (maybe
the user wants a different source or a different output language or maybe just wants to use 
other features of the program), then the program goes back to the Language Tools Menu.

	@param struct Table Dictionary is the structure containing all the data
*/
void
simpTrans(struct Table Dictionary)
{
    /*algo
    1. get inputs. og lang, to translate to lang, text
    2. tokenization. remove symbols
    3. search for translation for each word
    4. */
    Str20 ogTxt, resTxt, aWords[75]={}, bWords[75]={};
    longString text;
    int i, j, k, m, len, nElem, cmp=0, cmp2;
    char opt, cDump;
    
    printf("Enter language of original text: ");
    scanf("%s", ogTxt);
    printf("Enter language to translate to: ");
    scanf("%s", resTxt);
    do 
    {
    	strcpy(text, "");
        printf("Enter text to be translated: ");
        scanf("%c", &cDump);
        getString(text);
        split(aWords, &nElem, text);
		len = strlen(aWords[nElem-1]);
		aWords[nElem-1][len] = '\0';
        for (i=0; i<nElem; i++) //for each word in text
        {
            for (j=0; j<Dictionary.nEntries; j++) //looking per entry
                for (k=0; k<Dictionary.entries[j].count; k++) //looking inside entry
                {
                    cmp = strcmp(Dictionary.entries[j].translation[k], aWords[i]);
                    if (cmp == 0)
                    {//cmpare also for the translation equivalent pla, like the language to translate to
                    	for (m=0; m<Dictionary.entries[j].count; m++)
                    	{
	                    	cmp2 = strcmp(Dictionary.entries[j].language[m], resTxt);
	                    	
	                    	if (cmp2 == 0)
	                    	{
		                    	strcpy(bWords[i], Dictionary.entries[j].translation[m]);
		                        k = Dictionary.entries[j].count;
		                        j = Dictionary.nEntries;
							}
						}
                    }
                }
                
            if (cmp != 0)
                strcpy(bWords[i], aWords[i]);
        }
        
        len = strlen(bWords[nElem-1]);
		bWords[nElem-1][len] = '\0';
		
        displaySentence(bWords, nElem);

        printf("Do you still want to translate another text using the same source and output languages? (Y / N) ");
        scanf(" %c", &opt);
    } while (opt == 'Y' || opt == 'y');
    
}
/*
EXIT
The exit option will just allow the user to quit the Language Tools menu. The information in the 
lists should be cleared after this option. The program then reverts back to the Main Menu.
*/
void 
EXIT (struct Table *Dictionary)
{
    int i, j;

    for (i=0;i<Dictionary->nEntries;i++)
    {
        for (j=0;j<Dictionary->nEntries;j++)
        {
		strcpy(Dictionary->entries->language[j], "");
        strcpy(Dictionary->entries->translation[j], "");
        Dictionary->entries->count = 0;
		}
    }
    Dictionary->nEntries = 0;
    //mainMenu (Dictionary);
}

/*
Exit  
The exit option will just allow the user to quit the  Manage Data menu.  Only those exported to 

    
files are expected to be saved.  The information in the lists should be cleared after this option. 
The program goes back to the Main Menu.  
*/


/*MENU OPTIONS & MENUS*/
void 
manData(struct Table *Dictionary)
{
	int nOpt, input;
	Str30 strFileName;
	do
	{
		displayManDataMenu();
	    printf("Enter choice: ");
	    scanf("%d", &nOpt);
		switch(nOpt)
		{
			case 1: addEntry(Dictionary); break;
			case 2: addTrans(Dictionary); break;
			case 3: displayAll(*Dictionary);
					modEntry(Dictionary); break;
			case 4: printf("Enter entry you want to delete: ");
					scanf("%d", &input);
					delEntry(Dictionary, input); break;
			case 5: displayAll(*Dictionary);
					delTrans(Dictionary); break;
			case 6: displayAll (*Dictionary); break;
			case 7: searchTrans(*Dictionary); break;
			case 8: searchWord(*Dictionary); break;
			case 9: Export (*Dictionary); break;
			case 10: getFName(strFileName);
					Import(Dictionary, strFileName); break;
			case 11: EXIT(Dictionary); break;
			default: printf("Input not in options.\n");
		}
	} while(nOpt != 11);
    
}
void 
langTool(struct Table Dictionary)
{
	int nOpt, success, ctr=0;
    Str30 strFileName;
    
    do
    {
	    displayLangToolMenu();
	    printf("Enter choice: ");
	    scanf("%d", &nOpt);
	    if (nOpt != 3 && ctr==0)
	    {
	    	getFName(strFileName);
		    success = Import(&Dictionary, strFileName);
		    ctr++;
		}
	   if (success != -1)
	   {
		   	switch(nOpt)
			{
				case 1: mainLang(Dictionary); break;
				case 2: simpTrans(Dictionary); break;
				case 3: EXIT(&Dictionary); break;
				default: printf("Input not in options.\n");
			}
	   }
	   else
	   		printf("Error! Not able to open file.\n");
		
	} while (nOpt != 3);
    
}
