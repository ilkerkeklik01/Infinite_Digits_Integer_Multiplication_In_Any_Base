#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Ilker Keklik 150120074
int base=10;

FILE *readFilePtr; 

FILE *writeFilePtr; 

typedef struct digitList{
	
int digit;
struct digitList* next;		
	
} digitList;

enum bool{
	true =1,false=0
};
typedef enum bool bool;

typedef digitList* digitListPtr;

//This function pushes the integer value to the linked list that its root is rootPtr
void push(digitListPtr* rootPtr,int x);
//This function gets input from a file
void getInput(digitListPtr* rootPtr);
//This function calculate the multiplication of numbers
void calculate2(digitListPtr num1Root,digitListPtr num2Root,digitListPtr* resultRoot,int base);
//This function gets base from the input file
void getBase();
//This function returns a length of the linked list given its root
int listLen(digitListPtr root);
//This function takes reverse of the linked list and print messages to console and also print outputs to output file
void takeReverseFixAndPrint(digitListPtr root,char* str);
//This function convert any base of number given by parameter to decimal number and prints as output
void convertToDecimalAndPrint(char* str , int size, int _base,char* str2){
	
	int k = 0;
	for(int a=0;a<size;a++){
		if(str[a]!=NULL){
		k++;
		}
		
		
	}
	long int sum = 0;
	size = k;
	int pw = 0;
	int i = size -1 ;
	
	for(i; i >= 0 ; i--){
		sum += ((int)(pow(_base,pw++))*(str[i]-'0'));
	}
	
	char* num = (char*) calloc(size,sizeof(char)); 
	
	printf("\n%s in base %d: %ld",str2,10,sum);
	
}

int main(int argc,char* argv[]){
	
	if(argc==1)
		printf("Error Message!");
	if(argc>=2){
		readFilePtr = fopen(argv[1],"r");
	}
//	readFilePtr = fopen("150120074_p1_input.txt","r");

	writeFilePtr = fopen("150120074_p1_output.txt","w");

	digitListPtr number1Root=NULL;
	
	digitListPtr number2Root = NULL;
	
	digitListPtr resultRoot = NULL;	
	
	getInput(&number1Root);
	getInput(&number2Root);
	getBase();
		
	calculate2(number1Root,number2Root,&resultRoot,base);
	
	printf("\nMultiplicand in base %d : ",base);
	takeReverseFixAndPrint(number1Root,"Multiplicand\0");
	printf("\nMultiplier in base %d : ",base);
	takeReverseFixAndPrint(number2Root,"Multiplier\0");
	
	printf("\nResult in base %d : ",base);
	takeReverseFixAndPrint(resultRoot,"Result\0");
	
	fclose(readFilePtr);
	fclose(writeFilePtr);

	return 0;
}

void calculate2(digitListPtr num1Root,digitListPtr num2Root,digitListPtr *resultRoot,int base){
	digitListPtr num1Iter =num1Root;
	digitListPtr num2Iter =num2Root;
	int multiplication=0;
	
	int num1Len =listLen(num1Root);
	int num2Len=listLen(num2Root);
	int len =num1Len+num2Len;
	
	for(int i=0;i<len;i++){
		push(resultRoot,0);
	}
	
	digitListPtr iter = *resultRoot;
	
	int k=1;
	//num2
	while(num2Iter!=NULL){
		
		//num1
		while(num1Iter!=NULL){
			multiplication=num1Iter->digit*num2Iter->digit;
			
			iter->digit+=multiplication;
			
			num1Iter=num1Iter->next;
			
			iter=iter->next;
			
		}
		iter=*resultRoot;
		for(int z=0;z<k;z++){
			iter=iter->next;
		}
		
		
		k++;
		num1Iter=num1Root;
		num2Iter=num2Iter->next;
	}
	num2Iter=num2Root;
	
	int remainder=0;
	int carrier=0;
	
	iter=*resultRoot;
	
	for(int j=0;j<len;j++){
		remainder = iter->digit%base;
		carrier = iter->digit/base;
		
		if(carrier>0){
			iter->next->digit+=carrier;
			iter->digit= remainder;
		}
		iter=iter->next;
		
	}
	
}//FUNC END

void takeReverseFixAndPrint(digitListPtr root,char*str){
	
	int len =listLen(root);
	
	int* arr = (int*)calloc(len,sizeof(int));
	
	
	digitListPtr iter = root;
	for(int i=len-1;i>=0;i--){
		
			
		arr[i]=iter->digit;
		iter=iter->next;	
	}
	
	char c;
	int k =0;
	while(arr[k]==0){
		k++;
	}
	
	char* strNum = (char*)calloc(len+1,sizeof(char));
	
	if(k!=0){
		int s =k;
		for(k;k<len;k++){
		c=48+arr[k];
		fputc(c,writeFilePtr);
		strNum[k-s] = c;
		printf("%d ",arr[k]);
	}
	strNum[k]='\0';
	
	}else{
	for(k;k<len;k++){
		c=48+arr[k];
		fputc(c,writeFilePtr);
		strNum[k] = c;
		printf("%d ",arr[k]);
	}
	strNum[k]='\0';
		
	}
	
	fputc('\n',writeFilePtr);
		
	convertToDecimalAndPrint(strNum,len,base,str);
	
	
}//func end

void getBase(){
	fscanf(readFilePtr,"%d",&base);
		
}

void push(digitListPtr* rootPtr,int x){
		
		if(*rootPtr==NULL){
		
			*rootPtr= (digitListPtr)malloc(sizeof(digitList));
			(*rootPtr)->next=NULL;
			(*rootPtr)->digit=x;
			
			return ;
		}
	
		digitListPtr temp = (digitListPtr)malloc(sizeof(digitList));
		temp->next=*rootPtr;
		*rootPtr=temp;
		temp->digit=x;
	
}

void getInput(digitListPtr* rootPtr){	
	char c;
	
	if(readFilePtr==NULL){
		printf("Hata");
		return;
	}
	
	do{
		c=fgetc(readFilePtr);
		
		if(c>=48&&c<=57){
		push(rootPtr,c - 48);	
		}
		
	}while(c!='\n');	             

}

int listLen(digitListPtr root){
	
	int i=0;
	while(root!=NULL){
		root=root->next;
		i++;
	}
	return i;
	
}