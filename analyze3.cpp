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
    int singularCount, pluralCount; 
    float avgWordLength, avgSentLength;

} SPEECH_NUM;

void printTableHeaders(){

	printf("\n");
  	printf("Meaningful Data");
  	printf("\t\t\t\t\tRepublicans\t  Democrats\t Others\n");
    printf("===============\t\t\t\t\t-----------\t  ---------\t ------\n");
}

void initData(SPEECH_NUM &speech, const char* fileName){
	char *speech_mem = NULL, ch, *token;
	int k = 0, size = 0;
	float alphabetCount=0.0, avgWordLength;
	//const char *pronouns[] = {"I've", "I'll", "me", "my", "mine", "myself"};
	char speechYear[4]; 
	char filePath[25] = "./datafiles/"; 
	float ratioSingToPlur;
	int totalSing, totalPlur;

	//To get the speech year
	strncpy(speechYear, fileName, sizeof(speechYear)); 
	//Merges fileName with filePath to give the complete file path
	strcat(filePath, fileName); 

	//Initializing counters
	speech.wordCount=0, 
	speech.sentenceCount=0, 
	speech.lineCount=0, 
	speech.parCount=0;
	speech.singularCount=0;
	speech.pluralCount=0;

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
	speech_mem = (char*)malloc(sizeof(char)*(size+1));

	//Reads from file again to check back from the beginning
	Fp = fopen( filePath, "r");
	// Verify input file was found
	if( Fp == NULL){
	   printf("Attempt to open file failed. Exitting ... \n");
	   exit( -1);
	}

	//Loop counts number of words, sentences, and paragraphs
	while( (ch = fgetc(Fp)) != EOF){
		speech_mem[k] = tolower(ch); //Converts chars to lowercase

		//Counts words
		if(speech_mem[k] == ' ' || speech_mem[k] == '\r')
			speech.wordCount++;

		//Counts sentences
		if(speech_mem[k] == '.')
			speech.sentenceCount++;

		//Counts paragraphs
		if(speech_mem[k] == '\r')
			speech.parCount++;

		if(isalpha(speech_mem[k])) // This is used for average word length
			alphabetCount++;

		k++;
	}

	fclose( Fp);   // close input file

	token = strtok( speech_mem, " ,."); 

	//Counts singular and plural pronouns
	while( token != NULL){

		if(strcmp( token, "i") == 0)
			speech.singularCount++;
		if(strcmp( token, "i've") == 0)
			speech.singularCount++;
		if(strcmp( token, "i'll") == 0)
			speech.singularCount++;
		if(strcmp( token, "me") == 0)
			speech.singularCount++;
		if(strcmp( token, "my") == 0)
			speech.singularCount++;
		if(strcmp( token, "mine") == 0)
			speech.singularCount++;
		if(strcmp( token, "myself") == 0)
			speech.singularCount++;

		if(strcmp( token, "we") == 0)
			speech.pluralCount++;
		if(strcmp( token, "we've") == 0)
			speech.pluralCount++;
		if(strcmp( token, "we'll") == 0)
			speech.pluralCount++;
		if(strcmp( token, "us") == 0)
			speech.pluralCount++;
		if(strcmp( token, "our") == 0)
			speech.pluralCount++;
		if(strcmp( token, "ours") == 0)
			speech.pluralCount++;
		if(strcmp( token, "ourselves") == 0)
			speech.pluralCount++;

		token = strtok( NULL, " ,.");	
	}

}


int main( int argc, char *argv[]){

  SPEECH_NUM speechNum[MAX_SPCH]; //  57 speeches

  const char* fileName[][2] = //File Names
  	{
  		{"1789.txt", "O"}, {"1793.txt", "O"}, {"1797.txt", "O"}, 
  		{"1801.txt", "O"}, {"1805.txt", "O"}, {"1809.txt", "O"}, 
  		{"1813.txt", "O"}, {"1817.txt", "O"}, {"1821.txt", "O"}, 
  		{"1825.txt", "O"}, {"1829.txt", "D"}, {"1833.txt", "D"}, 
  		{"1837.txt", "D"}, {"1841.txt", "O"}, {"1845.txt", "D"}, 
  		{"1849.txt", "O"}, {"1853.txt", "D"}, {"1857.txt", "D"}, 
  		{"1861.txt", "R"}, {"1865.txt", "D"}, {"1869.txt", "R"}, 
  		{"1873.txt", "R"}, {"1877.txt", "R"}, {"1881.txt", "R"}, 
  		{"1885.txt", "D"}, {"1889.txt", "R"}, {"1893.txt", "D"}, 
  		{"1897.txt", "R"}, {"1901.txt", "R"}, {"1905.txt", "R"}, 
  		{"1909.txt", "R"}, {"1913.txt", "D"}, {"1917.txt", "D"}, 
  		{"1921.txt", "R"}, {"1925.txt", "R"}, {"1929.txt", "R"}, 
  		{"1933.txt", "D"}, {"1937.txt", "D"}, {"1941.txt", "D"}, 
  		{"1945.txt", "D"}, {"1949.txt", "D"}, {"1953.txt", "R"}, 
  		{"1957.txt", "R"}, {"1961.txt", "D"}, {"1965.txt", "D"}, 
  		{"1969.txt", "R"}, {"1973.txt", "R"}, {"1977.txt", "D"}, 
  		{"1981.txt", "R"}, {"1985.txt", "R"}, {"1989.txt", "R"}, 
  		{"1993.txt", "D"}, {"1997.txt", "D"}, {"2001.txt", "R"}, 
  		{"2005.txt", "R"}, {"2009.txt", "D"}, {"2013.txt", "D"} 
  	};
  	int i;
  	int republicans, democrats, others;
  	int repWordCount, demWordCount, othWordCount;
  	int repSingCount,demSingCount,othSingCount;
  	int repPlurCount,demPlurCount,othPlurCount;

  	//Averages
  	float repWordRatio, demWordRatio, othWordRatio;
  	float repSingUse, demSingUse, othSingUse;
  	float repPlurUse, demPlurUse, othPlurUse;

  	printTableHeaders(); //Prints table headers and lines
 
  	for(i=0; i<MAX_SPCH; i++){
  		//Counts and displays the required information
  		if(fileName[i][1] == "R"){
  			SPEECH_NUM speech;
  			initData(speech, fileName[i][0]);
			republicans +=1;
			repWordCount += speech.wordCount;
			repSingCount += speech.singularCount;
			repPlurCount += speech.pluralCount;
  		}
  		else if(fileName[i][1] == "D"){
  			SPEECH_NUM speech;
  			initData(speech, fileName[i][0]);
			democrats +=1;
			demWordCount += speech.wordCount;
			demSingCount += speech.singularCount;
			demPlurCount += speech.pluralCount;
  		}
  		else if(fileName[i][1] == "O"){
  			SPEECH_NUM speech;
  			initData(speech, fileName[i][0]);
			others +=1;
			othWordCount += speech.wordCount;
			othSingCount += speech.singularCount;
			othPlurCount += speech.pluralCount;
  		}
	}

	//Average words in speeches
	repWordRatio = (float)repWordCount/republicans;
	demWordRatio = (float)demWordCount/democrats; 
	othWordRatio = (float)othWordCount/others; 

	//Average use of singular pronouns
	repSingUse = (float)repSingCount/republicans;
	demSingUse = (float)demSingCount /democrats;
	othSingUse = (float)othSingCount / others;

	//Average use of plural pronouns
	repPlurUse = (float)repPlurCount/republicans;
	demPlurUse = (float)demPlurCount /democrats;
	othPlurUse = (float)othPlurCount / others;


  	printf("Number of Speeches:\t\t\t\t\t%d\t\t %d\t     %d \n", republicans, democrats, others);
  	printf("Avg words in speeches:\t\t\t\t   %.2f\t    %.2f\t%.2f \n", repWordRatio, demWordRatio, othWordRatio);
  	printf("Average use of singular pronouns:\t\t     %.2f\t      %.2f\t  %.2f\n", repSingUse, demSingUse, othSingUse);
  	printf("Average use of plural pronouns:\t\t\t     %.2f\t      %.2f\t  %.2f\n", repPlurUse, demPlurUse, othPlurUse);
  	

  return 0;
}
