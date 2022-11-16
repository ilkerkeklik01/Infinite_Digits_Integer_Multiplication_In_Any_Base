#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


void push(digitListPtr* rootPtr,int x);

void printDigitList(digitListPtr root);

void getInput(digitListPtr* rootPtr);

void calculate2(digitListPtr num1Root,digitListPtr num2Root,digitListPtr* resultRoot,int base);

void getBase();

int listLen(digitListPtr root);

void pushSequentially(digitListPtr* rootPtr,int x);

void takeReverseFixAndPrint(digitListPtr root);




int main(){
	 readFilePtr = fopen("input.txt","r");

		writeFilePtr = fopen("output.txt","w");

	

	
	
	
	digitListPtr number1Root=NULL;
	
	digitListPtr number2Root = NULL;
	
	digitListPtr resultRoot = NULL;	
	
	getInput(&number1Root);
	getInput(&number2Root);
	getBase();
	
	
	
	calculate2(number1Root,number2Root,&resultRoot,base);
	
	
	

	takeReverseFixAndPrint(number1Root);
	takeReverseFixAndPrint(number2Root);
	
	if(base!=10){
		fputc(48+base,writeFilePtr);
	}else{
		fputc(49,writeFilePtr);
		fputc(48,writeFilePtr);
	}
	
	fputc('\n',writeFilePtr);
	
	printf("CEVAP:\n\n");
	takeReverseFixAndPrint(resultRoot);
	
	
	
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

void takeReverseFixAndPrint(digitListPtr root){
	
	int len =listLen(root);
	
	int* arr = (int*)calloc(len,sizeof(int));
	
	
	digitListPtr iter = root;
	for(int i=len-1;i>=0;i--){
		
			
		arr[i]=iter->digit;
		iter=iter->next;	
		
		
		
		
	}
	
	
	
//	printf("\n");
//	printf("\n");
//	printf("\n");
//	printf("Tersi cevrilmis \n");
//	
//	for(int i=0;i<len;i++){
//		
//		printf("%d ",arr[i]);
//	}
//	
//	printf("Basinda sifir olmadan yazdiriliyor\n");
	
	char c;
	int k =0;
	while(arr[k]==0){
		k++;
	}
	

	
	for(k;k<len;k++){
		c=48+arr[k];
		fputc(c,writeFilePtr);
	//	printf("%d ",arr[k]);
	}
	fputc('\n',writeFilePtr);
	
	
	
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

void printDigitList(digitListPtr root){
	
	while(root!=NULL){
		printf("%d ",root->digit);
		root=root->next;
	}	
	printf("\n");
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
		}else{
		printf("%c is not a number\n",c);	
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

void pushSequentially(digitListPtr* rootPtr,int x){
		if(*rootPtr==NULL){
		
			*rootPtr= (digitListPtr)malloc(sizeof(digitList));
			(*rootPtr)->next=NULL;
			(*rootPtr)->digit=x;
			
			return ;
		}
		
		digitListPtr iter = *rootPtr;
	
	while(iter->next!=NULL){
		iter=iter->next;
	}
	
	iter->next = (digitListPtr)malloc(sizeof(digitList));
	iter->next->digit=x;
	iter->next->next=NULL;
	return ;
	
}

