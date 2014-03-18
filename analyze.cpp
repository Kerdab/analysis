#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
using namespace std;

#define SPCH_NUM 57  //Number of speeches
FILE* fp; 

typedef struct President{
	int wordCount, sentenceCount, lineCount, parCount;
    int iCount, iveCount, illCount, meCount, myCount, mineCount, myselfCount; 
    int weCount, weveCount, wellCount, usCount, ourCount, oursCount, ourselvesCount;
    float avgWordLength, avgSentLength;

} PRESIDENT;


//Counts words, sentences, lines, and paragraphs
void countStuff(PRESIDENT president[], int i, const char* fileName){

  char *speech = NULL;
  char temp, ch;
  int k = 0, size = 0;
  float alphabetCount=0.0;
  float avgWordLength;

  //You will need to change this according to your own file path
  char filePath[50] = "/home/user_name/analysis"; 

  	strcat(filePath, fileName); //To get the rest of the file path from fileName in main

	//Initializing counters
  	president[i].wordCount=0, 
  	president[i].sentenceCount=0, 
  	president[i].lineCount=0, 
  	president[i].parCount=0;

	fp = fopen( filePath, "r"); //Reads from file
	
	if( fp == NULL){  // Verify input file was found
	   printf("Attempt to open file failed. Exitting ... \n");
	   exit( -1);
	}

	//Counts number of characters in the file
    while( (fgetc(fp)) != EOF){
    		size++;
    }

    //Allocate memory according to number of characters in file
    speech = (char*)malloc(sizeof(char)*(size+1));

    //Reads from file again to check back from the beginning
	fp = fopen( filePath, "r");
	// Verify input file was found
	if( fp == NULL){
	   printf("Attempt to open file failed. Exitting ... \n");
	   exit( -1);
	}

	//Loop counts number of words, sentences, lines, and paragraphs
    while( (ch = fgetc(fp)) != EOF){

			speech[k] = ch;

			if(speech[k] == ' ' || speech[k] == '\r')
				president[i].wordCount++;

			if(speech[k] == '.')
				president[i].sentenceCount++;

			//This is an approximation since each line has approx 100 chars
			//The way the text files are formatted did work for line count using \n
			//It would just give the same number as paragraph count
			if(k%100 == 0) //speech[k] == '\n') 
				president[i].lineCount++;

			if(speech[k] == '\r')
				president[i].parCount++;

			if(isalpha(speech[k])) // This is used for average word length
				alphabetCount++;

			k++;
    }
	fclose( fp);   // close input file
	free( speech); //Frees allocated memory
	speech[size] = '\0'; //Initializes last index to NULL

	//Average length of words in each speech
	president[i].avgWordLength = alphabetCount/(president[i].wordCount); 

	//Average length of sentences (in words)
	president[i].avgSentLength = (float)president[i].wordCount/president[i].sentenceCount;

	//Word count is correct according to MS Word
	president[i].wordCount++; //Takes care of the absence of the last space in the file

    //printf("Speech \t%d\t   %d\t  %d\t\t   %d \t\t  %f \t\t %f\n",
    printf("Speech \t%d\t   %d\t\t %d\t %d\t\t%f\t\t%f\n",
   			president[i].wordCount, president[i].sentenceCount, 
   			president[i].lineCount, president[i].parCount,
   			president[i].avgWordLength, president[i].avgSentLength);
}


int main( int argc, char *argv[]){

  PRESIDENT president[SPCH_NUM]; //  57 speeches

  //You could also delete the string "/datafiles" and move it the the function above
  //It can easily be done using sublime's multi selection tool
  const char* fileName[] = //File Names
   { "/datafiles/1789.txt", "/datafiles/1793.txt", "/datafiles/1797.txt", "/datafiles/1801.txt", "/datafiles/1805.txt", 
	 "/datafiles/1809.txt", "/datafiles/1813.txt", "/datafiles/1817.txt", "/datafiles/1821.txt", 
	 "/datafiles/1825.txt", "/datafiles/1829.txt", "/datafiles/1833.txt", "/datafiles/1837.txt", 
	 "/datafiles/1841.txt", "/datafiles/1845.txt", "/datafiles/1849.txt", "/datafiles/1853.txt", 
	 "/datafiles/1857.txt", "/datafiles/1861.txt", "/datafiles/1865.txt", "/datafiles/1869.txt", 
	 "/datafiles/1873.txt", "/datafiles/1877.txt", "/datafiles/1881.txt", "/datafiles/1885.txt", 
	 "/datafiles/1889.txt", "/datafiles/1893.txt", "/datafiles/1897.txt", "/datafiles/1901.txt",
	 "/datafiles/1905.txt", "/datafiles/1909.txt", "/datafiles/1913.txt", "/datafiles/1917.txt", 
	 "/datafiles/1921.txt", "/datafiles/1925.txt", "/datafiles/1929.txt", "/datafiles/1933.txt", 
	 "/datafiles/1937.txt", "/datafiles/1941.txt", "/datafiles/1945.txt", "/datafiles/1949.txt", 
	 "/datafiles/1953.txt", "/datafiles/1957.txt", "/datafiles/1961.txt", "/datafiles/1965.txt", 
	 "/datafiles/1969.txt", "/datafiles/1973.txt", "/datafiles/1977.txt", "/datafiles/1981.txt",
	 "/datafiles/1985.txt", "/datafiles/1989.txt", "/datafiles/1993.txt", "/datafiles/1997.txt",
	 "/datafiles/2001.txt", "/datafiles/2005.txt", "/datafiles/2009.txt", "/datafiles/2013.txt"
   };

  int i;

  	printf("\n");

  	printf("\tWords  \tSentences    Lines \tParagraphs\tAvg Word Length\t Avg Sentence Length(in words)\n");
    printf("\t------ \t----------   ------\t----------\t---------------\t -----------------------------\n");

  	for(i=0; i<SPCH_NUM; i++){
		countStuff(president, i, fileName[i]);
	}

  return 0;
}
