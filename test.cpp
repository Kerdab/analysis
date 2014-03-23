#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
using namespace std;

int main(){

  int i = 0;
  char str[] = "the fact is, I like this fact example.";
  char word[] = "I";
  char *p;
  int theCount=0, factCount=0, iCount=0;

	printf("\n");
	p = strtok( str, " ,.");
	while( p != NULL){
		if( strcmp( p ,word) == 0)
			iCount++;
		printf("%s\n", p);
		p = strtok( NULL, " ,.");
	}
	printf("%d\n", iCount);

return 0;
}
