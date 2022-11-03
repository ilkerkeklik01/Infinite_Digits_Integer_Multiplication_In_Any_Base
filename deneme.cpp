#include <stdio.h>
#include <stdlib.h>


int main(){
	
	FILE *filePtr = fopen("deneme.txt","r");
	int base =10;
	fscanf (filePtr, "%d", &base);
	printf("%d",base);
	
	
	return 0;
}