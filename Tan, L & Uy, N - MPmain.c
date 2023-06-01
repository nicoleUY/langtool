//#include "merged.c"
#include "mergedVER2.c"

int main()
{
    struct Table Dictionary;
    Dictionary.nEntries = 0;
    int nOpt;
	do
	{
		displayMainMenu();
	    printf("Enter choice: ");
	    scanf("%d", &nOpt);
		switch(nOpt)
		{
			case 1: manData(&Dictionary); break;
			case 2: langTool(Dictionary); break;
			case 3: EXIT(&Dictionary); break;
			default: printf("Input not in options.\n");
		}
	} while (nOpt != 3);
   
    return 0;
}



