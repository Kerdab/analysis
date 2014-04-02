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

#define MAX_SPCH 57
FILE *Fp;


void printTableHeaders(){

	printf("\nAuthors: Abraheem Irheem, Sabine Ye\n");
	printf("Labs: Thur 2pm and 12pm\n");
	printf("Program #4: Analysis\n");
    printf("\n");
    
    printf("President Name\t\tYEAR   peace  war  economy  slave  slavery  ");
    printf("women  families  business  jobs  government  unemployment  ");
    printf("taxes  work  future  leadership  \n");

    printf("==============\t\t====   -----  ---  -------  -----  -------  ");
    printf("-----  --------  --------  ----  ----------  ------------  ");
    printf("-----  ----  ------  ----------  \n");
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


//Counts frequency of words
void counter( const char* fileName, int i){

  char *speech = NULL, ch, *token;
  char presidentName[25]; //Name of president
  char speechYear[4]; 
  char filePath[25] = "./datafiles/"; 
  int k = 0, size = 0;
  int peace=0, government=0, war=0, america=0, american=0, responsibility=0;
  int people=0, freedom=0, country=0, nation=0, defend=0, commitment=0;
  int liberty=0, ally=0, allies=0, interest=0, interests=0;
  int constitution=0, slave=0, slavery=0, equal=0;
  int social=0, capitalism=0, economy=0, taxes=0, progressive=0, women=0;
  int business=0, businesses=0, families=0, jobs=0, unemployment=0;
  int god=0, work=0, future=0;
  int leadership=0;

	//To get name of president
  	getPresidentName( presidentName, i);
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

	//Loop counts number of each word
    while( (ch = fgetc(Fp)) != EOF){

		speech[k] = tolower(ch); //Converts chars to lowercase
		k++;
	}

	fclose( Fp);   // close input file

	//Breaks the array 'speech' into tokens ignoring spaces, commas, and dots
	token = strtok( speech, " ,."); 

	//Counts words
	while( token != NULL){
		
		if(strcmp( token, "slave") == 0)
			slave++;
		if(strcmp( token, "slavery") == 0)
			slavery++;
		if(strcmp( token, "government") == 0)
			government++;
		if(strcmp( token, "economy") == 0)
			economy++;
		if(strcmp( token, "taxes") == 0)
			taxes++;
		if(strcmp( token, "peace") == 0)
			peace++;
		if(strcmp( token, "war") == 0)
			war++;
		if(strcmp( token, "women") == 0)
			women++;
		if(strcmp( token, "families") == 0)
			families++;
		if(strcmp( token, "business") == 0)
			business++;
		if(strcmp( token, "businesses") == 0)
			business++;
		if(strcmp( token, "jobs") == 0)
			jobs++;
		if(strcmp( token, "unemployment") == 0)
			unemployment++;
		if(strcmp( token, "work") == 0)
			work++;
		if(strcmp( token, "future") == 0)
			future++;
		if(strcmp( token, "leadership") == 0)
			leadership++;

		token = strtok( NULL, " ,.");
	}

	printf("%s %4s%6d %5d %5d %7d %7d ", presidentName, speechYear,
		peace, war, economy, slave, slavery);
	printf("%8d %8d %8d %8d %8d %11d ",
		women, families, business, jobs, government, unemployment);
	printf("%10d %6d %6d %6d\n",
		taxes, work, future, leadership);

	free( speech); //Frees allocated memory
}


int main(){

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

    printTableHeaders();

    for(i=0; i<MAX_SPCH; i++){

    	counter( fileName[i], i);
    }

   return 0;
}


