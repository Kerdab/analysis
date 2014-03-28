#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
using namespace std;

#define MAX_SPCH 57
FILE *Fp;


typedef struct speech_Num{
	int wordCount, sentenceCount, lineCount, peace;
    

} SPEECH_NUM;


void printTableHeaders(){

  	printf("\n");
  	printf("Speech\n");
  	printf("YEAR  Words  \tSentences  Paragraphs\tAvg Word Length\t Avg Sentence Length(in words)");
    printf("\t I  I've  I'll  me  my\tmine\tmyself");
    printf("\twe\twe've\twe'll\tus\tour\tours\tourselves\n");
    printf("====  ------ \t---------  ----------\t---------------\t -----------------------------");
    printf("\t--- ----  ----  --  --\t----\t------");
    printf("\t--\t-----\t-----\t--\t---\t----\t---------\n");

}


//Counts frequency of words
void counter( const char* fileName){

  char *speech = NULL, ch, *token;
  char speechYear[4]; 
  char filePath[25] = "./datafiles/"; 
  int k = 0, size = 0;
  int peace=0, government=0, war=0, america=0, american=0, responsibility=0;
  int people=0, freedom=0, country=0, nation=0, defend=0, commitment=0;
  int liberty=0, ally=0, allies=0, interest=0, interests=0;
  int constitution=0, slave=0, slavery=0, equal=0;

  	//To get the speech year
  	strncpy(speechYear, fileName, sizeof(speechYear)); 
  	//Merges fileName with filePath to give the complete file path
  	strcat(filePath, fileName); 

  	Fp = fopen( filePath, "r"); //Reads from file

	if( Fp == NULL){  // Verify input file was found
	   printf("Attempt to open file failed. Exitting ... \n");
	   exit( -1);
	}
	//Counts number of characters in the file
    while( (fgetc(Fp)) != EOF){
    		size++;
    }
    //Allocate memory according to number of characters in file
    speech = (char*)malloc(sizeof(char)*(size+1));

    //Reads from file again to check back from the beginning
	Fp = fopen( filePath, "r");
	// Verify input file was found
	if( Fp == NULL){
	   printf("Attempt to open file failed. Exitting ... \n");
	   exit( -1);
	}

	//Loop counts number of words, sentences, and paragraphs
    while( (ch = fgetc(Fp)) != EOF){

		speech[k] = tolower(ch); //Converts chars to lowercase
		k++;
	}

	fclose( Fp);   // close input file

	//Breaks the array 'speech' into tokens ignoring spaces, commas, and dots
	token = strtok( speech, " ,."); 

	//Counts words
	while( token != NULL){

		if(strcmp( token, "peace") == 0)
			peace++;
		if(strcmp( token, "freedom") == 0)
			freedom++;
		if(strcmp( token, "liberty") == 0)
			liberty++;
		if(strcmp( token, "america") == 0)
			america++;
		if(strcmp( token, "american") == 0)
			american++;
		if(strcmp( token, "war") == 0)
			war++;
		if(strcmp( token, "government") == 0)
			government++;
		if(strcmp( token, "country") == 0)
			country++;
		if(strcmp( token, "nation") == 0)
			nation++;
		if(strcmp( token, "ally") == 0)
			ally++;
		if(strcmp( token, "allies") == 0)
			allies++;
		if(strcmp( token, "people") == 0)
			people++;			
		if(strcmp( token, "defend") == 0)
			defend++;
		if(strcmp( token, "interest") == 0)
			interest++;
		if(strcmp( token, "interests") == 0)
			interests++;	
		if(strcmp( token, "responsibility") == 0)
			responsibility++;
		if(strcmp( token, "commitment") == 0)
			commitment++;
		if(strcmp( token, "constitution") == 0)
			constitution++;
		if(strcmp( token, "slave") == 0)
			slave++;
		if(strcmp( token, "slavery") == 0)
			slavery++;
		if(strcmp( token, "equal") == 0)
			equal++;

		token = strtok( NULL, " ,.");
	}

	printf("%s\t%d\t%d\t%d\t%d\t   %d\t   %d", speechYear,
		peace, freedom, liberty, america, american, country);
	printf("\t   %d\t   %d\t %d\t %d\t  %d", 
		nation, ally, allies, people, defend);
	printf("\t   %d\t\t%d\t  %d\t    %d\t\t  %d",
		interest, interests, commitment, government, responsibility);
	printf("\t\t %d\t\t%d\t%d\t%d\n",
		constitution, slave, slavery, equal);

	free( speech); //Frees allocated memory
}


int main(){

  SPEECH_NUM speechNum[MAX_SPCH];
  const char* fileName[] = //File Names
   { "1789.txt", "1793.txt", "1797.txt", "1801.txt", "1805.txt", 
	 "1809.txt", "1813.txt", "1817.txt", "1821.txt", 
	 "1825.txt", "1829.txt", "1833.txt", "1837.txt", 
	 "1841.txt", "1845.txt", "1849.txt", "1853.txt", 
	 "1857.txt", "1861.txt", "1865.txt", "1869.txt", 
	 "1873.txt", "1877.txt", "1881.txt", "1885.txt", 
	 "1889.txt", "1893.txt", "1897.txt", "1901.txt",
	 "1905.txt", "1909.txt", "1913.txt", "1917.txt", 
	 "1921.txt", "1925.txt", "1929.txt", "1933.txt", 
	 "1937.txt", "1941.txt", "1945.txt", "1949.txt", 
	 "1953.txt", "1957.txt", "1961.txt", "1965.txt", 
	 "1969.txt", "1973.txt", "1977.txt", "1981.txt",
	 "1985.txt", "1989.txt", "1993.txt", "1997.txt",
	 "2001.txt", "2005.txt", "2009.txt", "2013.txt"
   };

   int i;

    printf("\n");
  	printf("Speech\n");
  	printf("YEAR  peace freedom  liberty  america  american  country  ");
    printf("nation  ally  allies  people  defend  ");
    printf("interest  interests  commitment  government  responsibility  ");
    printf("constitution    slave  slavery  equal\n");
    printf("====  ----- -------  ------- --------  --------  ------   ");
    printf("------  ----  ------  ------  ------  ");
    printf("--------  ---------  ----------  ----------  --------------  ");
    printf("------------    -----  -------  -----\n");

    for(i=0; i<57; i++){

    	counter( fileName[i]);
    }

   return 0;
}


