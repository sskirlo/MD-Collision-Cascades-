#include<stdio.h>

int main()
{
	int i; 
	int *pi; 
	i=4; 
	printf("this is %d \n",i); //&acts on address of i 
	pi=&i; 
	printf("this is %d \n",*pi); //pi is an address
	//what if we want to print the pointer address itself
	int **ppi; 
	ppi=&pi; 
	printf("this is the address %d \n",*ppi); 
	//what if we want to alter the contents of the data with just the address given
	*(pi)=3; //* is dereferencing operator
	printf("this is altered %d \n", i);
	*(*(ppi))=5; 
	printf("this is altered %d \n", i); 


	return 0; 
}
