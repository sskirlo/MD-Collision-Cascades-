#include<stdio.h>
#include<math.h>

int main()
{
	int i; 
	float f; 
	double d;
	//let's study what the effect is of casting one data type into the other
	d=3.2;
	printf("weirdness, can't just print out double \n"); 
	printf("double %d \n", d);  
	printf("double (float spot)  %f \n", d); //this can work
	f=(float)d;
	printf("float cast d %f \n",f); 
	f=4.53; 
	d=(double)f; 
	printf(" double cast f %f \n", d);  
	i=(int)f; 
	printf("int cast of f %d \n",i); 
	i=(int)d; 
	printf("int cast of d %d \n",i); 
	
	printf("We can't use percent d for output, what happens for input? \n"); 
	printf("enter double \n"); 
	scanf("%f ", &f);  //works 
	//scanf("%f \n", &d);// this doesn't work
	printf("Entered %f \n", f); //if don't use %f and float type input program gets very slow, and then outputs wrong answer 	

	return 0; 
}
