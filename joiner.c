
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
	char *file2;
	char *output;  
	float offset;
	float buffspace;  
	printf("Arg number %d \n", argc); 
	file1=argv[1];
	file2=argv[2];
	output=argv[3];
	offset=(float)atof(argv[4]);   
	buffspace=(float)atof(argv[5]); 
	 
	printf("%s %s \n", file1, file2); 

	FILE *master;
	master=fopen(output, "w"); 

	FILE *bob; 
	FILE *bob2;
	
	bob=fopen(file1,"r"); 
	bob2=fopen(file2,"r"); 
	if(bob==NULL||bob2==NULL)
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
	{
		fgets(text,buff1,bob);
		//printf("%s",text);  
		fgets(text,buff1,bob2); 
	}
	//get number of atoms in each file
	int size1; 
	int size2;   
	fscanf(bob, "%d \n",&size1); 
	fscanf(bob2, "%d \n",&size2); 
	fgets(text,buff1,bob); 
	fgets(text,buff1,bob2);
	printf("%s",text);  
    //get dimensions of each box
	printf("size %d %d \n", size1, size2); 
	float dim1[3]; 
	float dim2[3]; 
	float joe; //place holder
	for(n=0; n<3;n++)
	{
		fscanf(bob, "%f %f \n", &joe,&dim1[n]); 
		fscanf(bob2, "%f %f \n", &joe,&dim2[n]); 	
	}
	printf("dims %f %f %f \n", dim1[0],dim1[1],dim1[2]); 
	fgets(text,buff1,bob); 
	fgets(text,buff1,bob2); 
	//write lattice information to file, then begin transfer of coordinates 
 	
	printf("last index of first lattice %d \n",size1); 

	fprintf(master,"# This lattice constructed from %s and %s \n \n", file1, file2);  
	fprintf(master,"%d atoms \n \n",(size1+size2) ); 
	fprintf(master,"%d atom types \n\n", 2); 
	fprintf(master,"%f %f xlo xhi \n", 0.0, dim1[0]);
	fprintf(master,"%f %f ylo yhi \n", 0.0, dim1[1]);
	fprintf(master,"%f %f zlo zhi \n", 0.0, dim1[2]+dim2[2]+offset+2*buffspace); //add buffer space, not too much or else won't relax together
	printf("the height of first grain is %f and 2nd grain is %f \n",dim1[2],dim2[2]); 
	printf("the offset is %f \n",offset); 
	fprintf(master, "0.0 0.0 0.0 xy xz yz \n \n"); 
	fprintf(master,"Masses \n \n"); 
	fprintf(master,"1 26.98 \n2 58.69 \n \n");
	
	//transfer coordinate data, shift id number and z coordinate positions of atoms in second file 
	fprintf(master,"Atoms \n \n"); 
	
	//now we need to remove entries which do not satisfy energy criteria
	for(n=0;n<size1;n++)
	{ 
    		fscanf(bob,formin,&b1,&b2,&dat1[0], &dat1[1],&dat1[2]); //dat1 is pointer to start of pointer array
    		dat1[2]=dat1[2]+buffspace; //shift z coordinate
		fprintf(master, formout, b1,b2,dat1[0],dat1[1],dat1[2]); 
	}
	for(n=0;n<size2;n++)
	{ 
    		fscanf(bob2,formin,&b1,&b2, &dat1[0], &dat1[1],&dat1[2]); //dat1 is pointer to start of pointer array  
    		b1=b1+size1; //shift id number
    		dat1[2]=dat1[2]+dim1[2]+offset+buffspace; //shift z coordinate
		fprintf(master, formout,b1,b2, dat1[0], dat1[1],dat1[2]); 
	}
	
	fclose(bob2); 
	fclose(bob); 
	fclose(master); 

	return 0; 
}


