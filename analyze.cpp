/*
* Program #4: Analysis
*
* System: Linux, GCC.
*
* Authors: Abraheem Irheem, Sabine Ye 
*
*/

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
    int weCount, weveCount, wellCount, usCount, ourCount, oursCount; 
    int ourselvesCount;
    float avgWordLength, avgSentLength;

} SPEECH_NUM;

void printTableHeaders(){

	printf("\nAuthors: Abraheem Irheem, Sabine Ye\n");
	printf("Labs: Thur 2pm and 12pm\n");
	printf("Program #4: Analysis\n");
	printf("\n");

  	printf("\t\t\t\t\t\t\t\tAvg Word \t  Avg Sentence\n");
  	printf("  President Name   \tYEAR\tWords\tSentences   Paragraphs\t Length \t Length(in words)");
    printf("\tSingular Pronouns\t Plural Pronouns\tRatio Singular/Plural\n");

    printf("===================\t====\t-----\t---------   ----------\t--------\t-----------------");
    printf("\t-----------------\t-----------------\t---------------------\n");
}


//Names of Presidents
void getPresidentName( char presidentName[], int i){

const char* allNames[] = {"1.George Washington    ", "2.George Washington    ", 
					"3.John Adams           ", "4.Thomas Jefferson     ",
					"5.Thomas Jefferson     ", "6.James Madison        ", 
					"7.James Madison        ", "8.James Monroe         ",
					"9.James Monroe         ", "10.John Q Adams        ",
					"11.Andrew Jackson      ", "12.Andrew Jackson      ",
					"13.Martin Van Buren    ", "14.William H Harrison  ",
					"15.James K Polk        ", "16.Zachary Taylor      ",
					"17.Franklin Pierce     ", "18.James Buchanan      ",
					"19.Abraham Lincoln     ", "20.Abraham Lincoln     ",
					"21.Ulysses S Grant     ", "22.Ulysses S Grant     ",
					"23.Rutherford B Hayes  ", "24.James A Garfield    ",
					"25.Grover CLeveland    ", "26.Benjamin Harrison   ",
					"27.Grover Cleveland    ", "28.William McKinley    ",
					"29.William McKinley    ", "30.Theodore Roosevelt  ",
					"31.William H Taft      ", "32.Woodrow Wilson      ",
					"33.Woodrow Wilson      ", "34.Warren G Harding    ",
					"35.Calvin Coolidge     ", "36.Herbert C Hoover    ",
					"37.Franklin D Roosevelt", "38.Franklin D Roosevelt",
					"39.Franklin D Roosevelt", "40.Franklin D Roosevelt",
					"41.Harry S Truman      ", "42.Dwight D Eisenhower ",
					"43.Dwight D Eisenhower ", "44.John F Kennedy      ",
					"45.Lyndon B Johnson    ", "46.Richard M Nixon     ",
					"47.Richard M Nixon     ", "48.Jimmy Carter        ",
					"49.Ronald Reagan       ", "50.Ronald Reagan       ",
					"51.George HW Bush      ", "52.Bill Clinton        ",
					"53.Bill Clinton        ", "54.George W Bush       ",
					"55.George W Bush       ", "56.Barack Obama        ",
					"57.Barack Obama        " };

		strcpy( presidentName, allNames[i]);
}


//Counts words, sentences, and paragraphs
void countAndPrintInfo(SPEECH_NUM speechNum[], int i, const char* fileName){

  char *speech = NULL, ch, *token;
  int k = 0, size = 0;
  float alphabetCount=0.0, avgWordLength;
  char presidentName[25]; //Name of president
  char speechYear[4]; 
  char filePath[25] = "./datafiles/"; 
  float ratioSingToPlur;
  int totalSing, totalPlur;

  	//To get name of president
  	getPresidentName( presidentName, i);
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

	//Calculate ratio of singular pronouns to plural pronouns
	totalSing = speechNum[i].iCount + speechNum[i].iveCount + 
				speechNum[i].illCount + speechNum[i].meCount + 
				speechNum[i].myCount + speechNum[i].mineCount + 
				speechNum[i].myselfCount;

	totalPlur = speechNum[i].weCount + speechNum[i].weveCount + 
				speechNum[i].wellCount + speechNum[i].usCount + 
				speechNum[i].ourCount + speechNum[i].oursCount + 
				speechNum[i].ourselvesCount;

	ratioSingToPlur = (float)totalSing/(float)totalPlur;

	//Prints all acquired info
	printf("%s%5s %7d %8d %11d %11.2f %20.2f \t", presidentName, 
				speechYear,
				speechNum[i].wordCount, speechNum[i].sentenceCount, 
				speechNum[i].parCount, speechNum[i].avgWordLength, 
				speechNum[i].avgSentLength);
	//printf("\n");
	printf("\t      %3d \t\t      %3d\t\t\t%3.2f\n", totalSing, totalPlur,
				ratioSingToPlur);

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
