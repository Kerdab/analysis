#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
using namespace std;

#define MAX_SPCH 57  //Number of speeches
FILE* Fp; 

typedef struct speech_Num{
	int wordCount, sentenceCount, lineCount, parCount;
    int iCount, iveCount, illCount, meCount, myCount, mineCount, myselfCount; 
    int weCount, weveCount, wellCount, usCount, ourCount, oursCount, ourselvesCount;
    float avgWordLength, avgSentLength;

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

//Counts words, sentences, and paragraphs
void countAndPrintInfo(SPEECH_NUM speechNum[], int i, const char* fileName){

  char *speech = NULL, ch, *token;
  int k = 0, size = 0;
  float alphabetCount=0.0, avgWordLength;
  //const char *pronouns[] = {"I've", "I'll", "me", "my", "mine", "myself"};
  char speechYear[4]; 
  char filePath[25] = "./datafiles/"; 

  	//To get the speech year
  	strncpy(speechYear, fileName, sizeof(speechYear)); 
  	//Merges fileName with filePath to give the complete file path
  	strcat(filePath, fileName); 

	//Initializing counters
  	speechNum[i].wordCount=0, 
  	speechNum[i].sentenceCount=0, 
  	speechNum[i].lineCount=0, 
  	speechNum[i].parCount=0;
  	speechNum[i].iCount=0;
  	speechNum[i].iveCount=0;
  	speechNum[i].illCount=0;
  	speechNum[i].meCount=0;
  	speechNum[i].myCount=0;
  	speechNum[i].mineCount=0;
  	speechNum[i].myselfCount=0;
  	speechNum[i].weCount=0;
  	speechNum[i].weveCount=0;
  	speechNum[i].wellCount=0;
  	speechNum[i].usCount=0;
  	speechNum[i].ourCount=0;
  	speechNum[i].oursCount=0;
  	speechNum[i].ourselvesCount=0;

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

		//Counts words
		if(speech[k] == ' ' || speech[k] == '\r')
			speechNum[i].wordCount++;

		//Counts sentences
		if(speech[k] == '.')
			speechNum[i].sentenceCount++;

		//Counts paragraphs
		if(speech[k] == '\r')
			speechNum[i].parCount++;

		if(isalpha(speech[k])) // This is used for average word length
			alphabetCount++;

		k++;
    }
	fclose( Fp);   // close input file

	//Breaks the array 'speech' into tokens ignoring spaces, commas, and dots
	token = strtok( speech, " ,."); 

	//Counts singular and plural pronouns
	while( token != NULL){

		if(strcmp( token, "i") == 0)
			speechNum[i].iCount++;
		if(strcmp( token, "i've") == 0)
			speechNum[i].iveCount++;
		if(strcmp( token, "i'll") == 0)
			speechNum[i].illCount++;
		if(strcmp( token, "me") == 0)
			speechNum[i].meCount++;
		if(strcmp( token, "my") == 0)
			speechNum[i].myCount++;
		if(strcmp( token, "mine") == 0)
			speechNum[i].mineCount++;
		if(strcmp( token, "myself") == 0)
			speechNum[i].myselfCount++;

		if(strcmp( token, "we") == 0)
			speechNum[i].weCount++;
		if(strcmp( token, "we've") == 0)
			speechNum[i].weveCount++;
		if(strcmp( token, "we'll") == 0)
			speechNum[i].wellCount++;
		if(strcmp( token, "us") == 0)
			speechNum[i].usCount++;
		if(strcmp( token, "our") == 0)
			speechNum[i].ourCount++;
		if(strcmp( token, "ours") == 0)
			speechNum[i].oursCount++;
		if(strcmp( token, "ourselves") == 0)
			speechNum[i].ourselvesCount++;

		token = strtok( NULL, " ,.");	
    }

	//Average length of words in each speech
	speechNum[i].avgWordLength = alphabetCount/(speechNum[i].wordCount); 

	//Average length of sentences (in words)
	speechNum[i].avgSentLength = (float)speechNum[i].wordCount
								 /speechNum[i].sentenceCount;

	//Word count is correct according to MS Word
	//Takes care of the absence of the last space in the file
	speechNum[i].wordCount++; 

	//Prints all acquired info
    printf("%s\t%d\t %d\t\t%d\t%f\t\t%f \t\t", speechYear,
   			speechNum[i].wordCount, speechNum[i].sentenceCount, 
   			speechNum[i].parCount, speechNum[i].avgWordLength, 
   			speechNum[i].avgSentLength);
    printf("%d   %d\t   %d\t%d   %d\t %d\t %d", speechNum[i].iCount, 
    		speechNum[i].iveCount, speechNum[i].illCount, 
    		speechNum[i].meCount, speechNum[i].myCount,
    		speechNum[i].mineCount, speechNum[i].myselfCount);
    printf("\t%d\t%d\t%d\t%d\t%d\t%d\t   %d\n", speechNum[i].weCount,
    		speechNum[i].weveCount, speechNum[i].wellCount,
    		speechNum[i].usCount, speechNum[i].ourCount,
    		speechNum[i].oursCount, speechNum[i].ourselvesCount);

	free( speech); //Frees allocated memory
}


int main( int argc, char *argv[]){

  SPEECH_NUM speechNum[MAX_SPCH]; //  57 speeches
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

  	printTableHeaders(); //Prints table headers and lines

  	for(i=0; i<MAX_SPCH; i++){
  		//Counts and displays the required information
		countAndPrintInfo(speechNum, i, fileName[i]);
	}

  return 0;
}
