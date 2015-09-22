
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include<string.h>

//purpose of code is to sort through files and remove those with energy below threshold value
//not most effecient with memory, reads in memory into dynamically sized arrays

//input format is file1.dump file2.dump file3.data offset buffspace
//offset is gap between two grains, buffspace is space on ends of z boundary to allow for expansion w/o having atoms pass out

int main(int argc, char* argv[])
{
	int n;  
	char *file1;
	char *output;  
	int stacks;  
	printf("Arg number %d \n", argc); 
	file1=argv[1];
	output=argv[2];
	stacks=(int)atof(argv[3]);   
	 
	printf("%s \n", file1); 

	FILE *master;
	master=fopen(output, "w"); 

	FILE *bob; 
	
	bob=fopen(file1,"r"); 
	if(bob==NULL)
	{
		printf("null pointer \n"); 
		return 1; 	
	} 

	char *formin;
	char *formout; 
	formin="%d %d %f %f %f \n"; //need the \n for the file reader to go to the next line 
	formout="%d %d %.2f %.2f %.2f \n";
	
	int b1;  
	int b2; 
	float dat1[3];         //array for transfering atom data

	int buff1=100; 
	char text[100]; //generally safe assumption that all lines manipulating are shorter than 100 characters
	
	printf("begin scanning \n"); 
	//get header lines out
	for(n=0; n<3; n++)
		fgets(text,buff1,bob);

	//get number of atoms in each file
	int size1;  
	fscanf(bob, "%d \n",&size1); 
	fgets(text,buff1,bob); 
	printf("%s",text);  
    //get dimensions of each box
	printf("size %d \n", size1); 
	float dim1[3]; 
	float joe; //place holder
	float joe2; 
	for(n=0; n<3;n++)
		fscanf(bob, "%f %f %f \n", &joe,&dim1[n],&joe2); 	
		
	printf("dims %f %f %f \n", dim1[0],dim1[1],dim1[2]); 
	fgets(text,buff1,bob); 
	//write lattice information to file, then begin transfer of coordinates 
 	
	printf("last index of first lattice %d \n",size1); 

	fprintf(master,"# This lattice constructed from %s \n \n", file1);  
	fprintf(master,"%d atoms \n \n",size1*stacks ); 
	fprintf(master,"%d atom types \n\n", 2); 
	fprintf(master,"%f %f xlo xhi \n", 0.0, dim1[0]);
	fprintf(master,"%f %f ylo yhi \n", 0.0, dim1[1]*stacks);
	fprintf(master,"%f %f zlo zhi \n", 0.0, dim1[2]); //add buffer space, not too much or else won't relax together
	fprintf(master, "0.0 0.0 0.0 xy xz yz \n \n"); 
	fprintf(master,"Masses \n \n"); 
	fprintf(master,"1 26.98 \n2 58.69 \n \n");
	
	//transfer coordinate data, shift id number and z coordinate positions of atoms in second file 
	fprintf(master,"Atoms \n \n"); 
	

	float * data; 
	data=(float *)calloc(size1*5,sizeof(float));
	if(data==NULL)
	{
		printf("no data \n"); 
		return 1;
	}  

	//now we need to remove entries which do not satisfy energy criteria
	int n2; 
	
	for(n2=0; n2<size1*5; n2+=5)
	{
		fscanf(bob,formin,&b1,&b2,&data[n2+2], &data[n2+3],&data[n2+4]); //dat1 is pointer to start of pointer array
		data[n2]=(float)b1; 
		data[n2+1]=(float)b2;
		//printf("%f %f ", data[n2],data[n2+1]);  
	}

	for(n=0; n<stacks; n++ )
	{
		for(n2=0;n2<size1*5;n2+=5)
		{ 
	        	fprintf(master, formout, ((int)data[n2])+size1*n,(int)(data[n2+1]),data[n2+2],data[n2+3]+dim1[1]*n,data[n2+4]); 
		}
	}
			
	fclose(bob); 
	fclose(master); 

	return 0; 
}


