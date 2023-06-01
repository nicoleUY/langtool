#include <stdio.h>

/*
To  support the two  language  tools,  your  project will  also  manage  the  collection  of  words  as  language 
and translation pairs that will be used. It is, thus, important to note that each translation and language pair can 
be  at  most  20  letters  each.  And  there  can  be  at  most  10  pairs  of  language  and  translation  per  entry  and  a 
count for the number of pairs encoded in the entry. One entry (with a count of 6) would look something like this: 

*/
#define MAX_LEN_word 20
#include <stdio.h>
#include <string.h>

#define MAX_LEN_name 30
#define MAX_pairs 10
#define MAX 150

typedef char Str20[MAX_LEN_word+1];
typedef char Str30[MAX_LEN_name+1];
typedef char longString[MAX];

struct Entry{
	Str20 language[MAX_pairs];
	Str20 translation[MAX_pairs];
	int count;
	
};

/*Note  that  there  can  be  at  most  150  entries,  but  not  all  entries  will  have  the  same  number  of  language  -
translation pairs.*/
struct Table{
	struct Entry entries[MAX];
	int nEntries;
};

typedef struct Table Dictionary; 
