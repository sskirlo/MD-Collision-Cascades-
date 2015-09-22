
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//desktop version


//purpose of code is to sort through files and remove those with energy below threshold value
//not most effecient with memory, reads in memory into dynamically sized arrays

struct entry
{
	double ent[12]; 
};  //dont forget this ;
struct list  
{
	struct entry* add[40];    
	int len; 
};
struct listlist  
{
	struct entry* add[40];    
	int len[10]; 	        //break into 10 lists, have 1 int keeping track of length
	int lent; 
};
int printentry(struct entry * bob)
{
	char * form; 
	form="%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %d %d %d %d %d \n"; 
 	printf(form,bob[0].ent[0],bob[0].ent[1],bob[0].ent[2],bob[0].ent[3],bob[0].ent[4],bob[0].ent[5],bob[0].ent[6],(int)bob[0].ent[7],bob[0].ent[8],bob[0].ent[9],bob[0].ent[10],bob[0].ent[11]);
	return 0;  
}
int printllist(struct listlist *bob)
{
	int n,n1;
	printf("length of list is %d \n", (*bob).lent);  
	for(n=0; n<(*bob).lent; n++)
	{
		printf("head \n"); 
		printentry(((*bob).add[4*n])); //pass pointer to print entry
		for(n1=1; n1<(*bob).len[n]; n1++)
		{
			printentry((*bob).add[4*n+n1]); 	
		}
	}
	return 0; 
}
int printcontents(struct listlist **bob, int *dim)
{
	int nx,ny,nz; 
	for(nx=0; nx<dim[0]; nx++)
	{
		for(ny=0; ny<dim[1]; ny++)
		{
			for(nz=0; nz<dim[2]; nz++)
			{
				printf("The address of this list is %d, %d, %d \n",nx,ny,nz); 
				printllist(&((*bob)[nx+dim[0]*ny+dim[0]*dim[1]*nz])); 
			}
		}
	}
}
//use trash and trash counter to get track of data allocated in program
int getmemory(void ** mark, int size, struct entry ** tr, int * trc , char * datatype) //gets structure memory of size, size
{
	//dereference address of address to place address 
	if(strcmp(datatype,"entry")==0)
	{
		*mark=(void*)calloc(size,sizeof(struct entry)); 
		printf("making entry memory allocation \n"); 
	}
	if(strcmp(datatype,"llist")==0)
	{
		*mark=(void*)calloc(size,sizeof(struct listlist));
		printf("making list memory allocation \n"); 
	} 
	if((*mark)==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	printf("%d memory allocated \n", size); 
	tr[*trc]=(struct entry *)*mark; 
	(*trc)=(*trc)+1; 
	return 0; 
}
//puts together three strings in master char 
int join(char* mas,char * one, char * two, char *three)
{
	//printf("joining \n");
	//mas is 30 chars long, so will be able to hold all the data
	char* joe[3]; 
	joe[0]=one; 
	joe[1]=two; 
	joe[2]=three;
	int n1,n2;
	int len;
	int pos;  
	pos=0; 
	for(n1=0; n1<3; n1++)
	{
		for(n2=0; n2<strlen(joe[n1]); n2++)
		{
				mas[pos]=*(joe[n1]+n2); 
				pos++; 
		}
	}
	printf("length of word %d \n",pos); 
	mas[pos]='\0'; 
	//printf("finish joining \n"); 
}
//function compares based on id number, sorted this way after entering
int compare1(const void *ptr1, const void *ptr2) //compare function to be passed to 	qsort
{
	double e1, e2, an1, an2; 
	struct entry* p1;
	struct entry* p2; 
	p1=(struct entry*)ptr1; 
	p2=(struct entry*)ptr2;  
	e1=p1[0].ent[7]; 
	e2=p2[0].ent[7];
	if(e1>e2)
		return 1;
	else if(e1<e2)
		return -1;
	else
		return 0;
}
//function compares based on coordination number, sorted this way after entering
int compare3(const void *ptr1, const void *ptr2) //compare function to be passed to qsort
{
	double e1, e2, an1, an2; 
	struct entry* p1;
	struct entry* p2; 
	p1=(struct entry*)ptr1; 
	p2=(struct entry*)ptr2;  
	e1=p1[0].ent[5]; 
	e2=p2[0].ent[5];
	if(e1>e2)
		return 1;
	else if(e1<e2)
		return -1;
	else
		return 0;
}
//used for sorting before printing out, sorts based on atom type, then id. 
int compare2(const void *ptr1, const void *ptr2) //compare function to be passed to qsort
{
	double e1, e2, an1, an2; 
	struct entry* p1;
	struct entry* p2; 
	p1=(struct entry*)ptr1; 
	p2=(struct entry*)ptr2;  
	e1=p1[0].ent[7]; 
	e2=p2[0].ent[7];
	an1=p1[0].ent[3]; 
	an2=p2[0].ent[3]; 
	//if(((int)e1) % 5000==0)
	//	printf("%d %d \n",e1,e2);
	if(an1>an2)
		return 1; 
	else if(an1<an2)
		return -1; 
	else
	{
		if(e1>e2)
			return 1;
		else if(e1<e2)
			return -1;
		else
			return 0;
	}
}
//compares ints
int compareint(const void *ptr1, const void *ptr2)
{
	int* p1;
    int* p2; 
	p1=(int*)ptr1; 
	p2=(int*)ptr2; 
	if((*p1)>(*p2))
		return 1; 
	else if((*p2)>(*p1))
		return -1; 
	else 
		return 0;  
}
int comparefloat(const void *ptr1, const void *ptr2)
{
	float* p1;
    float* p2; 
	p1=(float*)ptr1; 
	p2=(float*)ptr2; 
	if((*p1)>(*p2))
		return 1; 
	else if((*p2)>(*p1))
		return -1; 
	else 
		return 0;  

}
int getTempMemory(struct entry ** mark, int size)  //used to get memory within function methods, expected to throw away at end of method
{
	*mark=(struct entry *)calloc(size,sizeof(struct entry)); 
	if(mark==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	printf("%d memory allocated \n", size); 
	return 0; 
}
int checkAtoms(struct entry * dat, int atomnumber, int number, int sd )// purpose of command is to check that all atom ids present
{
	int count;
	int first=0; 
	int second=sd; 
	/*if(number==2)//allow code to search both arrays
	{
		for(count=0; count<atomnumber; count++)
		{
			if((int)(dat[second].ent[7])==(count+1))
			{
				second++;
			}
			else if((int)(dat[first].ent[7])==(count+1))
 			{
				first++;
			}
			else
			{
				printf("missing atom %d \n", (count+1)); 
				return 1; 
			}
		}
	}
	else //simpler to check for single list
	{*/
	for(count=0; count<atomnumber; count++)
	{
		if( ((int)(dat[count].ent[7]))!=(count+1))
		{
			printentry(&dat[count]); 
			printf("missing atom %d \n", (count+1)); 
			return 1;
		} 
	}

	printf("have %d of %d atoms accounted for \n", count,number); 
	return 0; 	
}
//method assumes all atoms ordered and accouted for, and directly accesses, and adds atom to list
int searchAtoms(int sid,struct entry* d1,struct entry* dd1,struct entry** ptr, int size, int* count)//method will search for atom with id, sid
{
	int n; 
	int found=0; 
	if(((int)(d1[(sid-1)].ent[7]))==sid)
	{ 
		*ptr=&(d1[(sid-1)]); 
   		dd1[*count]=d1[(sid-1)]; 
   		(*count)++;
	    found=1; 
	}

	if(found==1)
	{
		printf("found atom %d \n", sid);
		return 0;  
	}
	else
	{
		printf("did not find atom %d \n", sid); 
		return 1; 
	}
}
//does not assume in ordered list just does O(n) search, returns index of dd1
//if entries=2 does search in reverse so picks up other atom in matrix
int fullSearch(int sid, struct entry * dd1, int size, int entries)
{
	int n; 
	int index=-1; 
	if(entries==1)
	{
		for(n=size-1; n>=0; n--)
		{
			if(((int)dd1[n].ent[7])==sid)
			{
				index=n; 
				break;
			} 
		}
	}
	else
	{
		for(n=0; n<size; n++)
		{
			if(((int)dd1[n].ent[7])==sid)
			{
				index=n; 
				break;
			} 
		}
	}
	return index; 
}
//prints out given quantity from given atom id, prints entnum entries after given address, if 1 just prints info at entry
int quantityOutput(FILE* fp,int index, int sid,struct entry* d1,struct entry* dd1, int size, int* count, int entnum)
{
	int n,n1; 
	struct entry * ptr; 
	n=searchAtoms(sid,d1,dd1,&ptr,size,count); //locate atom of interest
	if(n==0)//find successful
	{
		if((*count)==1)
		{
			for(n1=0; n1<entnum; n1++)
				fprintf(fp,"%f ",((float)dd1[0].ent[index+n1])); //print out all desired information from entry
			fprintf(fp,"\n "); 
			return 0; 	
		}
		else
		{
			printf("counts off \n"); 
			return 1; 	
		}
	}
	else
	{
		printf("counts off \n"); 
		return 1;  
	}
}	
int writeOver(struct entry* temp1, struct entry* dat1, int count1  )
{
	int n; 
	for(n=0; n<count1; n++)
	{
		dat1[n]=temp1[n]; 	
	}
	//printf("writeover complete \n"); 	
}
//method determines position of atom in neighborlist matrix, returns complete index and acts on position to matrix also
int roundi(double x,double len, int bin)
{
	double b=(double)bin; 
	int n=(int)b*x/len;
	double inc=len/b; 
	//check if binned appropriately, if not keep looping until value is in correct bin
	restart:
	if(inc*(n+1)<x)
	{
		n=n+1;
		//printf("off %f \n",(float)x);  //give coordinate, so can see what's going wrong 
		goto restart;  
	}
	else if(inc*n>x)		
 	{
		//printf("off %f \n",(float)x); 
		n=n-1; 
		goto restart; 
	}
	else
	{
		return n;
	} 
}
int getmatpos(int * pos, struct entry data, int * adim, double * dim)
{
	int ind,n1; 
	for(n1=0; n1<3; n1++)
	{
		pos[n1]=roundi(data.ent[n1],dim[n1],adim[n1]); //get position into matrix coordinates
		if(pos[n1]>=adim[n1])
		{				
			pos[n1]=adim[n1]-1; //if out of bounds just map to closest inner wall
		}
		if(pos[n1]<0)
		{
			pos[n1]=0; 
		}
	} 
	ind=pos[0]+pos[1]*adim[0]+pos[2]*adim[0]*adim[1];
	return ind; 	
}
double dist(struct entry * one, struct entry * two,double * dimr, int * boundi)//want to compute distance between one and two, if boundary==1 look for boundary problem
{	
	//if a given boundary in a given orientation run over, boundi input will be 1
	double d[3];
	int n, count; 
	count=0; //count number of boundary incidents
	for(n=0; n<3; n++)
		d[n]=((*one).ent[n]-(*two).ent[n]);
		//printf("found boundary \n"); 
 
	for(n=0; n<3; n++)//if any coordinates more than half the distance apart, know not neighboring cells
	{
		if(boundi[n]!=0) //if have run over boundary in given direction
		{
			if(d[n]>0)
			{
				d[n]=d[n]-dimr[n]; 
				count++;	
			}
			else
			{
				d[n]=d[n]+dimr[n]; 
				count++; 
			}
		}	
	}
	for(n=0;n<3;n++)
		d[n]=pow(d[n],2);
	d[0]=pow(d[0]+d[1]+d[2],0.5);
	return d[0]; 
}
//calculate vector between two points, also returns distance
double vec(struct entry * one, struct entry * two, double * vecs, double * dimr, int * boundi)
{	
	//if a given boundary in a given orientation run over, boundi input will be 1
	double d[3];
	int n, count; 
	count=0; //count number of boundary incidents
	for(n=0; n<3; n++)
		d[n]=((*one).ent[n]-(*two).ent[n]);
		//printf("found boundary \n"); 
 
	for(n=0; n<3; n++)//if any coordinates more than half the distance apart, know not neighboring cells
	{
		if(boundi[n]!=0) //if have run over boundary in given direction
		{
			if(d[n]>0)
			{
				d[n]=d[n]-dimr[n]; 
				count++;	
			}
			else
			{
				d[n]=d[n]+dimr[n]; 
				count++; 
			}
		}	
	}
	for(n=0;n<3;n++)
		vecs[n]=d[n];
	for(n=0;n<3;n++)
		d[n]=pow(d[n],2);
	d[0]=pow(d[0]+d[1]+d[2],0.5);
	return d[0];  
}
//isclose takes entry structures as inputs and checks if two points are within etol, if true returns 1, if not 0
int isclose(struct entry * one, struct entry * two, double tolerence, double * dimr, int * boundary)
{	
	double d1; 
	d1=dist(one, two, dimr ,boundary); 
	if(d1>tolerence)//if particle is outside tolerance range, return 0, else 1
	{
		return 0; 
	}
	else
	{
		return 1;
	} 
}
//searches for info with given atom id, if entries =2, method searches for 2 atom entries by searching ids in reverse order 
int printinfo(int id,struct entry * rd1, struct entry * d1, struct entry *dd1, int * count, double * dim, int entries)
{
	int boundi []={0,0,0}; 
	double db; 
	printf("\n print info \n"); 
	printentry(&rd1[id-1]);
	printentry(&dd1[fullSearch(id,dd1,(*count),1)]);
	printf("%d \n",(int)d1[id-1].ent[4]); 
	db=dist(&d1[id-1],&rd1[id-1],dim,boundi);
	printf("%lf \n",db); 
	if(entries==2)
	{
		printf("second entry with same id \n"); 
		printentry(&rd1[id-1]);
		printentry(&dd1[fullSearch(id,dd1,(*count),2)]);
		printf("%d \n",(int)d1[id-1].ent[4]); 
		db=dist(&d1[id-1],&rd1[id-1],dim,boundi);
		printf("%lf \n",db); 		
	}
}
//will print main statistical data and print out to outfile visualization of filling, defect int controls whether or not looks at defect bits when printing
int matrixStatistics(struct listlist * dat, int* dims, int atomcount, char * app,int defect)//will go through and check everything important in matrix 
{
	int nx[3]; 
	int n1; 
	int nmin[3]; 
	int nmax[3]; 
	int count, max, min, le,count2;  
	struct entry * head; 
	int antial=0; 
	int antini=0; 
	int vacc=0; 
	int inti=0; 
	int jointal=0; 
	int jointni=0; 
	min=30;  
	max=0;
	count=0; 
	count2=0; 
	FILE * fp; 
	char mat[50]; 
	if(defect==0)
		join(mat,app,"mat",".stat");
	else
	 	join(mat,app,"dmat",".stat");
	fp=fopen(mat,"w"); 
	fprintf(fp,"dims of the matrix are %d, %d, %d \n", dims[0],dims[1],dims[2]); 
	fprintf(fp,"total atom count before read in is %d \n", atomcount ); 
	for(nx[2]=0; nx[2]<dims[2]; nx[2]++)
	{
		for(nx[0]=0; nx[0]<dims[0]; nx[0]++)
		{
			for(nx[1]=0; nx[1]<dims[1]; nx[1]++)
			{
				le=(int)dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].lent; 
				count=count+le; 
				for(n1=0;n1<le;n1++) //add up sublist contributions
				{
					count2=dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].len[n1]+count2; 	
					if(defect==1)//take statistics on all defects
					{
						head=dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].add[n1*4]; 
						if((*head).ent[4]==1)
							antini++;
						if((*head).ent[4]==-1)
							antial++;
						if((*head).ent[5]==-1)
							vacc++;
						if((*head).ent[5]==1)
							inti++;
						if(((*head).ent[5]==1)&&((*head).ent[4]==1))
							jointni++;
						if(((*head).ent[5]==1)&&((*head).ent[4]==-1))
							jointal++;
					}
				}
				count2=count2-dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].lent; //don't include heads in count		
				if(le>max)
				{
					max=le; 
					for(le=0; le<3; le++)
					{
						nmax[le]=nx[le]; 	
					}
				}
				if(le<min)
				{
					min=le; 
					for(le=0; le<3; le++)
					{
						nmin[le]=nx[le]; 	
					}
				}
			}	
		}	
	}
	float avg=count; 
	avg=avg/(dims[0]*dims[1]*dims[2]); 		
	fprintf(fp,"total atom count after read in is %d \n", count);
	fprintf(fp,"total sublist count after read is %d \n",count2);  
	fprintf(fp,"location of max of %d is at %d, %d, %d \n", max, nmax[0],nmax[1],nmax[2]); 
	fprintf(fp,"location of min of %d is at %d, %d, %d \n", min, nmin[0],nmin[1],nmin[2]);
	fprintf(fp,"average is %f atoms per cell \n", avg);  
	if(defect==1)
	{
		fprintf(fp,"ni anti, al anti, vaccs, ints, jointal, jointni \n");
		fprintf(fp,"%4d    ,%4d     ,%4d   ,%4d   ,%4d     ,%4d      \n",antini,antial,vacc,inti/2,jointal,jointni);
	}		
	
	for(nx[2]=0; nx[2]<dims[2]; nx[2]++)
	{
		fprintf(fp," %d \n ", nx[2]); 
		for(nx[0]=0; nx[0]<dims[0]; nx[0]++)
		{
			for(nx[1]=0; nx[1]<dims[1]; nx[1]++)
			{
				count2=0; 
				for(n1=0;n1<10;n1++) //add up sublist contributions
				{
					count2=dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].len[n1]+count2; 		
				}
				count2=count2-dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].lent; //don't include heads in count	
				fprintf(fp,"%5d,%d",dat[nx[0]+nx[1]*dims[0]+nx[2]*dims[0]*dims[1]].lent,count2); 
			}
			fprintf(fp," \n"); //go to next line	
		}	
		fprintf(fp," \n"); //print out section then move on
	}
	fclose(fp); 
	return 0; 	
}
int fillLLists(struct listlist * neighlist, struct entry * data, int * adim, double * dim,int size, char * app )
{	
	int pos[3]; 
	int ind,ny,n,n1; 
	int maxlen=0; 
	printf("initializing lengths %d %d %d \n",adim[0],adim[1],adim[2]); 
	for(n=0; n<(adim[0]*adim[1]*adim[2]); n++)
	{
		neighlist[n].lent=0; 
		for(n1=0; n1<10; n1++)
			neighlist[n].len[n1]=0; //initialize length to 0
	}
	printf("populating neighbor lists, %d atoms \n",size); 
	for(n=0;n<size;n++)
	{
		ind=getmatpos(pos,data[n],adim,dim); 
		ny=neighlist[ind].lent; //get length of current list
		neighlist[ind].add[ny*4]=&data[n]; //put address at matrix coordinate 
		neighlist[ind].lent++; //increment position counter, lent keeps track of number of reference atoms
		neighlist[ind].len[ny]++; //len keeps track of number of atoms in given sublist including reference atoms
		if(ny>maxlen)
		{
			maxlen=ny+1; 
			printf("max length is at %d , %d , %d with %d \n", pos[0],pos[1],pos[2],maxlen); 	
		}
	}
	//we want to check that all atoms made it in
	int count; 
	count=0; 
	for(n=0; n<adim[0]*adim[1]*adim[2]; n++)
	{
		count=count+neighlist[n].lent; //add up all lengths of linked list
	} 	
	if(count!=size)	
	{
		printf("not all atoms accounted for in neighbor lists, only have %d of %d \n", count, size); 
		matrixStatistics(neighlist, adim, size, app,0); 
		return 1; 
	}
	printf("all atoms present and accounted for in neighbor lists \n"); 
	return 0; 
}
//look through vaccinity of a given entry in a given cell, and return number of neighbors within radius,
int searchRadius(struct listlist * dat, int * nx1, struct entry * center, int * idim, double * ddim, double a0, int scale, double r, struct list * found, double * dists, int verb)
{
	int nx2[3]; 
	int dx1[3]; 
	int boundi[3]={0,0,0}; 
	int index1, c1, len1, rng, n, neighcount,a; 
	double d; 
	a=0; 
	neighcount=0; 
	struct entry * neigh; 
	rng=(int)(r/a0*scale)+1;  //determine range of cells we sweep
 	//printf("range of sweep %d \n ", rng); 
	if(rng<1)//set minimum range for sweep
	{	
		printf("reset sweep range \n"); 
		rng=1; 	
	}

	for(nx2[0]=-rng; nx2[0]<(rng+1); nx2[0]++)
	{
		for(nx2[1]=-rng; nx2[1]<(rng+1); nx2[1]++)
		{
			for(nx2[2]=-rng; nx2[2]<(rng+1); nx2[2]++)
			{
				for(n=0; n<3; n++)//check boundaries, set appropriate flag if overrun
				{
					dx1[n]=nx1[n]+nx2[n];//add coords of checked cell to get search cell 
					if(dx1[n]>(idim[n]-1))
					{
						dx1[n]=(-idim[n]+dx1[n]); //make sure wraps around proper amount, as long as doesn't pass over old cell we're fine 
						boundi[n]=1;
						//printf("reached boundary \n");  
					}
					else if(dx1[n]<0)	
					{
						dx1[n]=idim[n]+dx1[n]; 
						boundi[n]=1; 
						//printf("reached boundary \n"); 
					}	
				}
				index1=dx1[0]+idim[0]*dx1[1]+idim[0]*idim[1]*dx1[2];
				len1=(int)dat[index1].lent;
				for(c1=0; c1<len1; c1++) //run through contents of neighbor list to check coordination
				{ 
					neigh=dat[index1].add[c1*4];
					if((center)!=(neigh)) //i.e. we are not accessing the same address
					{ 
						if(verb==1)
						{
							printf("boundaries %d %d %d \n",boundi[0],boundi[1],boundi[2]); 	
						}
						if( isclose(center, neigh, r,ddim,boundi)==1 ) 
						{
							(*found).add[(*found).len]=neigh; 
							dists[(*found).len]=dist(center, neigh,ddim,boundi);  //add distance to list
							if(dists[(*found).len]>r)  //self consistency check
								printf("distance further than supposed to be %f > %f \n",(float)dists[(*found).len],(float)r); 
							((*found).len)++; 	
						}
					}
				}
				for(n=0; n<3; n++)
					boundi[n]=0; 	
			}		
		}	
	}
	return 0;
}
//does linear comparision of reference to current data and checks if a given atom has shifted by some threshold, good way to determine probable defects
//will also label 4th field of d1 with -20 if not defect or 20 for defect for quick hash access
int findDist(struct entry* rd1, struct entry* d1,struct entry* dd1,int size, int *count, double * dmir, double deltaz, char * app,char * type, int dim)
{
	int count1=0;  
	double * accums; 
	int * counts; 
	int len1, len2; 
	FILE * fp; 
	char mat[50]; 
	join(mat,app,type,".stat");
	fp=fopen(mat,"w");
	
	if(dim==1)
	{
		len2=1; 
		len1=(int)(dmir[2]/deltaz); 
		printf("number of bins is %d \n", len1); 
		printf("size of bins is %f \n",(float)deltaz); 
		fprintf(fp,"%d \n",len1); 
		counts=(int *)calloc(len1*2,sizeof(int));
		accums=(double *)calloc(len1*2,sizeof(double));
	}
	if(dim==2)
	{
		len1=(int)(dmir[2]/deltaz);
		len2=(int)(dmir[1]/deltaz);  
		printf("number of bins is %d by %d \n", len1,len2); 
		printf("size of bins is %f \n",(float)deltaz); 
		fprintf(fp,"%d %d \n",len1, len2); 
		counts=(int *)calloc(len1*len2*2,sizeof(int));
		accums=(double *)calloc(len1*len2*2,sizeof(double));
	}
	
	int entr=0; 
	
	if(strcmp(type,"pedist")==0)
		entr=11; //set to find potenial energy
	if(strcmp(type,"kedist")==0)
		entr=6;   //set to find kinetic energy distribution
		
	
	if(counts==NULL || accums==NULL )
	{
		printf("no memory \n"); 
		return 0; 
	}
	int n,n2,n3; 
	int bin1,bin2; 
	for(n=0; n<size; n++)
	{
		bin1=(int)d1[n].ent[2]/deltaz; 
		bin2=(int)d1[n].ent[1]/deltaz; 
		if(dim==1)
			bin2=0; 
			
		if(d1[n].ent[3]==1)  //add to Al list
		{
			counts[bin1+bin2*len1]++;               //increment counter
			accums[bin1+bin2*len1]=accums[bin1+bin2*len1]+d1[n].ent[entr]; //add potential energy
		}	
		else   //add to Ni list
		{
				counts[bin1+bin2*len1+len1*len2]++;               //increment counter
				accums[bin1+bin2*len1+len1*len2]=accums[bin1+bin2*len1+len1*len2]+d1[n].ent[entr]; //add potential energy
		}	
	}
	for(n3=0; n3<2; n3++)
	{
		for(n=0; n<len1; n++) //print out accumulation
		{
			for(n2=0; n2<len2; n2++)
			{
				fprintf(fp,"%f ",accums[n+len1*n2+len1*len2*n3]);
			}
			fprintf(fp,"\n");
		}
	}   

	fprintf(fp,"\n"); 
	for(n3=0; n3<2; n3++)
	{
		for(n=0; n<len1; n++) //print out accumulation
		{
			for(n2=0; n2<len2; n2++)
			{
				fprintf(fp,"%d ",counts[n+len1*n2+len1*len2*n3]);  
			}
			fprintf(fp,"\n");
		}
	}

	fprintf(fp,"\n"); 
	for(n3=0; n3<2; n3++)
	{
		for(n=0; n<len1; n++) //print out accumulation
		{
			for(n2=0; n2<len2; n2++)
			{ 
				if(counts[n+len1*n2+len1*len2*n3]!=0)
					accums[n+len1*n2+len1*len2*n3]=accums[n+len1*n2+len1*len2*n3]/counts[n+len1*n2+len1*len2*n3]; 
				count1=counts[n+len1*n2+len1*len2*n3]+count1;
				fprintf(fp,"%f ",accums[n+len1*n2+len1*len2*n3]);  
			}
			fprintf(fp,"\n");
		}
	}

	fprintf(fp,"\n"); 
	fprintf(fp,"%f %f \n",dmir[0],dmir[1]); //print xy dimensions to be used in grain boundary energy calculation

	if(count1!=size)
	{
		printf("count off, we have %d instead of %d \n",count1,size);
		return 0;  
	}
	fclose(fp); 
	return 0; 	
}
int findStressdist(struct entry* rd1, struct entry* d1,struct entry * dd1,int size, int * count, double * dmir, double deltaz, char * app)
{
	int count1=0;  
	double * accums; 
	int * counts; 
	int len; 
	FILE * fp; 
	char mat[50]; 
	join(mat,app,"stressdist",".stat");
	fp=fopen(mat,"w");
	len=(int)(dmir[2]/deltaz); 
	printf("number of bins is %d \n", len); 
	printf("size of bins is %f \n",(float)deltaz); 
	fprintf(fp,"%d \n",len); 
	counts=(int *)calloc(len*6,sizeof(int));
	accums=(double *)calloc(len*6,sizeof(double));
	if(counts==NULL || accums==NULL )
	{
		printf("no memory \n"); 
		return 0; 
	}
	int n; 
	int n1; 
	int n2; 
	int bin; 
	for(n=0; n<size; n++)
	{
		for(n1=0; n1<6; n1++)
		{
			n2=n1+4; 
		    	if(n1>2)
				n2+=1; //skip next two entries
			
			bin=(int)d1[n].ent[2]/deltaz;
			 
			counts[bin+n1*len]++;               //increment counter
			accums[bin+n1*len]=accums[bin+len*n1]+d1[n].ent[n2]; //add stress
		}	
	}
	/*for(n=0; n<6*len; n++) //print out accumulation
		fprintf(fp,"%f \n",accums[n]);  

	fprintf(fp,"\n"); 
	for(n=0; n<6*len; n++) //print out numbers of atoms
		fprintf(fp,"%d \n",counts[n]);  */  

	fprintf(fp,"\n"); 
	for(n=0; n<len*6; n++) //average, and make sure count correct
	{
		if(counts[n]!=0)
			accums[n]=accums[n]/counts[n]; 
		count1=counts[n]+count1;
		fprintf(fp,"%f \n",accums[n]);  
	}
	fprintf(fp,"%f %f %f \n",dmir[0],dmir[1],dmir[2]); //print xyz dimensions to be used in conversion

	if(count1!=size*6)
	{
		printf("count off, we have %d instead of %d \n",count1,size);
		return 0;  
	}
	fclose(fp); 
	return 0; 	
}
//searches for defects to apply defect algorithims to, removes any ids matching nid list before processing
//fills up dd1 with canidates and then sets d1.ent[4] field to 20 if defect and -20 otherwise, information is still located in d1
int findJacked(struct entry* rd1,struct entry* d1,struct entry* dd1,int size, int *count,double tol, double * dmir, int nidlen, int * nid )
{
	printf("searching for jacked_up crystal \n"); 
	int n1,f1,n2,id, c; 
	int disinc; 
	int b[3]={0,0,0};
	c=0; 

	//label defects don't want to include in main list with -10, need to assume nid ordered
	for(n1=0; n1<size; n1++)
	{
		if( (nidlen-c)!=0 )  //structure this way so don't get segfault with null case
		{
			if(nid[c]-1 == n1)
			{
				d1[n1].ent[4]=-10; //if labeled this will ignore in finding jacked method
				c++;
			} 
		}
		else
		{
			d1[n1].ent[4]=10;
		} 
	}
 
	for(n1=0; n1<size; n1++)
	{

		for(n2=0;n2<3; n2++) //safe to assume atom didn't channel 5/6 of a side dimension, means that wrapped around
		{
			if( (rd1[n1].ent[n2]-d1[n1].ent[n2])> (dmir[n2]*5/6)   )	
			{
				b[n2]=1; 
			}	
			else if( (d1[n1].ent[n2]-rd1[n1].ent[n2])> (dmir[n2]*5/6)   )
			{
				b[n2]=-1;  	
			}
			else
			{
				b[n2]=0; 
			}
		}
		
		f1=isclose(&rd1[n1],&d1[n1],tol,dmir,b);
		/*if((n1==8255-1) || (n1==5453-1) || (n1==8254-1) || (n1==5450-1) )
		{
			printf("isclose % d \n", f1); 
			printf("seperation distance %lf \n",dist(&d1[n1],&rd1[n1],dmir,b)); 
		}*/
		if(f1==0 &&  ((int)(d1[n1].ent[4]))!=-10 )//command returns 0 when not close to old position
		{
			dd1[*count]=d1[n1];
			d1[n1].ent[4]=20; 
			(*count)++; 	
		}
		else
		{
			d1[n1].ent[4]=-20; 
		}
	}
	//printf("found %d possible defects \n ", (*count)); 
}
//recursive method which goes down chain, ref and mdata only filled with positions of jacked up atoms
int followChain(struct entry * node,struct entry *rd1 , struct listlist *mdata, FILE * fp, double a0, int scale ,double * dim, int * adim, int max, int min, int chain)
{
	//node is defect of previous spot, now go back to start, reference, and search for next defect near
	int n, id, leng, call;
	int pos[3]; 
	struct entry neighs [10];
	struct entry * next; 
	id=node[0].ent[7]; 
	printf("recursive call chain %d, id %d \n",chain,id); 
	getmatpos(pos,rd1[id-1],adim,dim); //get position
	leng=0; 
   	searchNeighbors(mdata,pos,&rd1[id-1],adim,dim,a0,scale,a0,neighs,&leng,10,1); //find neighbor vectors and distances
	qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort by distances 5th entry
	
	printf("entering decisions \n"); 
	if( (neighs[0].ent[5]>a0/2/pow(2.0,0.5) && chain>min)|| (chain>max) )  //terminates if can't find another defect within wigner seitz, or if chain too long
	{
		printf("chain terminated position %d \n",chain);
		fprintf(fp," %f %f %f ",rd1[id-1].ent[0],rd1[id-1].ent[1],rd1[id-1].ent[2]); 
		fprintf(fp," %f %f %f \n",node[0].ent[0],node[0].ent[1],node[0].ent[2]);  	
		return 1; 
	}
	else if((neighs[0].ent[5]>a0/2/pow(2.0,0.5) && chain<min))
	{
		printf("too short \n"); 
		return -1; //we don't save chains which are too short
	}
	else  //conditions that are left are chain<max, and neighs<a0/2/2^(1/2), so want to look further
	{
		call=followChain(&neighs[0],rd1,mdata,fp,a0,scale,dim, adim, max, min,chain+1);
		if(call>0)
		{ 
			printf("going back up chain position %d \n",chain);
			fprintf(fp," %f %f %f ",rd1[id-1].ent[0],rd1[id-1].ent[1],rd1[id-1].ent[2]); 
			fprintf(fp," %f %f %f \n",node[0].ent[0],node[0].ent[1],node[0].ent[2]);
			return 1; 
		} 
		if(call<0)
		{
			printf("going back up chain position, not printing anything too short %d \n",chain);
			return -1; 
		} 
	}
	return 0; 
}
//keep track of history of atoms which have kinetic energy greater than cutoff value
//histcounter runs from 1 to maxhistory-1
int locateCascades(struct entry * rd1,int size,struct entry * d1,double cutoff,struct entry * history,int histcounter, int maxhistory, int * histlistcounter)
{
	int n,id;
	int max=(int)10000/cutoff*10; //determine max number of atoms in list 
	printf("locating cascade links cutoff is %lf eV \n",cutoff);
	printf("max number of atoms is %d histcount is %d \n",max,histcounter);
	int added=0;  
	if(histcounter>maxhistory)
	{
		printf("exceeded maximum history size  \n"); 
		return 0; 	
	}
	//1st indentify new atoms and add their rd1 to -1 current position
	for(n=0; n<size; n++)
	{
		if((*histlistcounter)>=max)
		{
			printf("exceeded max atom count \n"); 
			break; 
		} 
		if(((double)d1[n].ent[6])>cutoff)
		{
			history[(*histlistcounter)*maxhistory+histcounter-1]=rd1[n]; 
			(*histlistcounter)++;
			//printentry(&d1[n]); 
			added++;  	
		}
	}
	printf("Added %d atoms during cycle \n",added); 
	//update with current coordinate of all atoms in list, get id from entry before to determine which atom information should grab
	for(n=0; n<(*histlistcounter); n++)
	{
		id=history[n*maxhistory+histcounter-1].ent[7];	
		history[n*maxhistory+histcounter]=d1[id-1]; 
	}
	return 0; 
}
//prints out information of atoms contained in history
int printCascades(struct entry * history, int histcounter, int maxhistory, int histlistcounter)
{
	printf("printing cascades histcounter %d histlistcounter %d \n",histcounter,histlistcounter); 
	FILE *fp; 
	struct entry ref; 
	fp=fopen("cascades.stat","w"); 
	int n,n2; 
	for(n=0; n<histlistcounter; n++)
	{
		for(n2=0; n2<histcounter; n2++)
		{
			ref=history[n*maxhistory+n2]; 
			fprintf(fp,"%f %f %f %f %d \n",ref.ent[0],ref.ent[1],ref.ent[2],ref.ent[6],(int)ref.ent[7]); 
			
		}	
		fprintf(fp," \n"); 
	}
	fclose(fp); 
}
int findChains(struct listlist * mref,struct listlist * mdata,struct entry * rd1,struct entry * d1,struct entry * dd1,int atoms,int * count,double a0,int scale,double * dim,int * adim,char * append)
{
	int n, leng,max,min,chaincounts, id;
	int pos[3];
	double center, width;    
	struct entry neighs [50];
	FILE * fp; 
	char mat[50]; 
	join(mat,append,"chains",".stat");
	fp=fopen(mat,"w");
	max=30; 
	min=20; 
	chaincounts=0;
	center=251.542; //this is center z coordinate
	width=10.71;  

	//find jacked up final positions

	findJacked(rd1,d1,dd1,atoms,count,a0/2/pow(2.0,0.5),dim,0,NULL);
	fillLLists(mdata, dd1, adim, dim, (*count),NULL); //populates neighbor lists
	for(n=0; n<(*count); n++)
	{
		d1[n]=rd1[(int)(dd1[n].ent[7]-1)]; 
	}
	fillLLists(mref, d1, adim, dim, (*count),NULL); //only fill reference lists with atoms that have been displaced, so we can only search for 
                                                        //ones which will be links
	printf("finding chains \n"); 
	for(n=0; n<(*count); n++)
	{ 
		id=dd1[n].ent[7]; 
		leng=0; 
		//we search rd1, we are searching from lattice tesselated by reference atom BZs. 
		getmatpos(pos,dd1[n],adim,dim); //get position
		searchNeighbors(mref,pos,&dd1[n],adim,dim,a0,scale,a0,neighs,&leng,50,1); //search reference, for near tails to build on 
		qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort by distances 5th entry
		//assume last position displaced from was a0/2/(2)^(1/2) away, want to only find ends of RCSs, so will make sure no other 
                //reference heads within this distance,if this condition is satisfied, potentially means at intermediate location on chain
		if(neighs[0].ent[5]<a0/pow(2.0,0.5)/2)
		{
			continue;
		}
		/*else if(chaincounts>2)
		{
			break; 
		} */ 
		else //call helper method which will recurse down chain, and print out as comes back up
		{
			//if(dd1[n].ent[2]>(center-width/2) && dd1[n].ent[2]<(center+width/2) ) //only take if final atom inside grainboundary
			
				printf("id %d \n", n+1); 	
				if(followChain(&dd1[n],rd1,mdata,fp,a0,scale,dim, adim,max,min,0)==1)
				{
					fprintf(fp,"%d \n",chaincounts); 
					chaincounts++;
				}
			
		}
		
	}
	printf("chain counts %d \n",chaincounts); 
}
//method counts displacements and keeps adding to a buffer of integrated displacements, outputs a text file each time with filtered results based on some 
//minimum number of accumulated displacements, use as criteria to determine if certain atoms are in melt state 
int displacementCount(struct entry * rd1,struct entry * d1,struct entry * dd1,int atoms,int * count,double a0,double * dim,char * append, int *disps,int cutoff)
{ 
	int n,n2, ct2,id,totaldisps,output; 
	double d; 
	findJacked(rd1,d1,dd1,atoms,count,a0/2/pow(2.0,0.5),dim,0,NULL); 
	FILE * fp;
	char mat[50]; 
	int hist[100]; 
	int boundi[3]={0,0,0}; 
	totaldisps=0; 
	fp=fopen("disps.list","w"); 

	//all items should be sorted 
	for(n=0; n<(*count); n++)
	{
		id=(int)dd1[n].ent[7]; 
		for(n2=0;n2<3; n2++) //safe to assume atom didn't channel 5/6 of a side dimension, means that wrapped around
		{
			if( (rd1[id-1].ent[n2]-dd1[n].ent[n2])> (dim[n2]*5/6)   )	
			{
				rd1[id-1].ent[n2]=rd1[id-1].ent[n2]-dim[n2]; 	
			}	
			if( (dd1[n].ent[n2]-rd1[id-1].ent[n2])> (dim[n2]*5/6)   )
			{
				dd1[n].ent[n2]=dd1[n].ent[n2]-dim[n2]; 	
			}
		}
		d=dist(&dd1[n], &rd1[id-1],dim,boundi);
		disps[id-1]=disps[id-1]+round(d/(a0/pow(2.0,0.5))); 
	}
	//read d1 into rd1 and use as new reference
	for(n=0; n<atoms; n++)
	{
		rd1[n]=d1[n]; 	
	}
	//create histogram of results and display a few
	//initialize hist
	for(n=0;n<100; n++)
		hist[n]=0;
	output=0;  
	for(n=0;n<atoms;n++)
	{
		if(disps[n]<100 && disps[n]>0)
		{
			totaldisps=totaldisps+disps[n]; 
			hist[disps[n]]++;
		} 
		if(disps[n]>=cutoff)
		{
			output++; 	
		}	
	}
	//print out histogram results
	printf("\n"); 
	for(n=1; n<20; n++)
	{
		printf("%d  ",n); 	
	}
	printf("\n"); 
	for(n=1; n<20; n++)
	{
		printf("%d ",hist[n]); 	
	}
	printf("\n Currently have %d total displacements \n",totaldisps);
	printf("\n Currently have %d output ids \n",output);
	//print out list of ids
	fprintf(fp,"%d \n",output); 
 	for(n=0; n<atoms; n++)
	{
		if(disps[n]>=cutoff)
			fprintf(fp,"%d \n",n+1); //print out id 
	}
	fclose(fp); 
	return 0; 
}

//method finds atoms having minimum displacement, and outputs their start and end positions in outfile, dispout method, prints out distribution file of displacements
int displacementOutput(struct entry * rd1,struct entry * d1,struct entry * dd1,int atoms,int * count,double a0,double * dim,int * ids, int * idcount,char * append)
{ 
	int n,n2, ct2;  
	int id,ind; 
	double d; 
	findJacked(rd1,d1,dd1,atoms,count,a0/2/pow(2.0,0.5),dim,0,NULL); 
	FILE * fp;
	FILE *fp2;  
	char mat[50]; 
	int boundi[3]={0,0,0}; 
	join(mat,append,"disp",".stat");
	fp=fopen(mat,"w");
	fp2=fopen("dispdistribution.stat","w");
	fprintf(fp,"%d \n",*count);  
	fprintf(fp2,"%d \n",*count);  
	ct2=0;
	//all items should be sorted 
	ind=0;
	for(n=0; n<(*count); n++)
	{
		id=(int)dd1[n].ent[7];
		while(id>ids[ind] && ind<(*idcount))//increment until equal or greater than current id, all lists are sorted
		{
			ind++;
		} 
		if(id==ids[ind] && ind<(*idcount)) //this means we skip if displacement in previous defect list, so we will only see new displacements
		{
			ind++; 
			continue;
		} 
		//need to interrogate points, find which ones are significant displacements, and wrap around the dimensions for easier plotting
		for(n2=0;n2<3; n2++) //safe to assume atom didn't channel 5/6 of a side dimension, means that wrapped around
		{
			if( (rd1[id-1].ent[n2]-dd1[n].ent[n2])> (dim[n2]*5/6)   )	
			{
				rd1[id-1].ent[n2]=rd1[id-1].ent[n2]-dim[n2]; 	
			}	
			if( (dd1[n].ent[n2]-rd1[id-1].ent[n2])> (dim[n2]*5/6)   )
			{
				dd1[n].ent[n2]=dd1[n].ent[n2]-dim[n2]; 	
			}
		}
		d=dist(&dd1[n], &rd1[id-1],dim,boundi);
		//if(d < (a0/2/pow(2.0,0.5)) )
		//	continue;           //if insignificant skip over
		fprintf(fp2,"%lf \n",d); //print output to displacement distribution file
		fprintf(fp," %f %f %f ",rd1[id-1].ent[0],rd1[id-1].ent[1],rd1[id-1].ent[2]); 
		fprintf(fp," %f %f %f \n",dd1[n].ent[0],dd1[n].ent[1],dd1[n].ent[2]); 
		ct2++; 
	}
	printf("excluded %d displacements \n",ind); 
	ind=0; 
	for(n=0; n<(*count); n++) //fill up list with new ids so next call will see them and exclude the previous displacements
	{
		ids[n]=dd1[n].ent[7]; 	
	}
	(*idcount)=(*count); 
	printf("final count is %d vs. %d",ct2,(*count)); 
	fclose(fp); 
	fclose(fp2); 
}
//takes 15 reference neighbor vectors and determines if vector is within buirrlion zone
int inbrillouinzone(float * vecs, float * neighs)
{
	int n1,n2; 
	float mag2; 
	float prod; 
	
	//printf("neighs %f %f %f \n",neighs[0],neighs[1],neighs[2]); 
	for(n1=0; n1<15; n1++)
	{
		mag2=0; 
		prod=0; 
		//printf("%f %f %f \n",vecs[n1*3+0],vecs[n1*3+1],vecs[n1*3+2]); 
		for(n2=0; n2<3; n2++)
		{
			mag2=pow(vecs[n1*3+n2],2)+mag2;
			prod=prod+vecs[n1*3+n2]*neighs[n2];  	
		}
		//printf("prod %f and mag^2/2 %f \n", prod, mag2/2); 
		if(prod>mag2/2) //has to not satisfy this inequality for all neighbor vectors
			return 0; //outside 1st BZ
	}
	return 1; //inside 1st BZ 
}
//calculates temperature of reference list of atoms
int calculateTemp(struct entry * d1, double kb,char * inlist,FILE * outlist)
{
	double ke=0;
	int len,n,id; 
	FILE *fp; 
	fp=fopen(inlist,"r"); 
	fscanf(fp,"%d \n",&len); 
	for(n=0; n<len; n++)
	{
		fscanf(fp,"%d \n",&id); 
		ke=ke+d1[id-1].ent[6]; 	
		//printf("%d  %f \n ",id,d1[id-1].ent[6]); 
	}
	printf("len %d ke %lf \n",len,ke); 
	fclose(fp); 
	ke=ke*2/3/kb/len; 
	printf("calculated cluster as being %lf K \n",ke); 
	fprintf(outlist,"%lf \n",ke); 
	return 0; 
}
//determines the number of atoms that are melted in the simulation by calculating their effective temperature
int calculateMelt(struct entry * d1, double kb,char * inlist,FILE * outlist,double melttemp)
{
	printf("melt temp cutoff %lf \n",melttemp); 
	double ke=0;
	int len,n,id,meltcount;
	meltcount=0;  
	FILE *fp; 
	fp=fopen(inlist,"r"); 
	fscanf(fp,"%d \n",&len); 
	for(n=0; n<len; n++)
	{
		fscanf(fp,"%d \n",&id); 
		ke=d1[id-1].ent[6]; 	
		if(ke*2/3/kb > melttemp)
			meltcount++; 
	}
	fclose(fp); 
	printf("number of melted atoms %d \n",meltcount); 
	fprintf(outlist,"%d \n",meltcount); 
	return 0; 
}
int calculateTempDev(struct entry * d1,int size, double kb,FILE * outlist)
{ 
	int n; 
	double tdev=0;
	double dev=0; 
	double maxdev=0; 
	double tempavg=0;
	//calculate average   
	for(n=0; n<size; n++)
	{
		tempavg=d1[n].ent[6]*2/3/kb+tempavg;
	}
	tempavg=tempavg/size;
	printf("average temperature %lf \n",tempavg); 
	//calculate temperature deviation
	for(n=0; n<size; n++)
	{
		dev=(d1[n].ent[6]*2/3/kb-tempavg)*(d1[n].ent[6]*2/3/kb-tempavg);
		if(dev>maxdev)
			maxdev=dev; 
		tdev=tdev+dev;   	
	}
	tdev=tdev/size; 
	tdev=pow(tdev,0.5);
	maxdev=pow(maxdev,0.5);  
	printf("maximum deviation %lf \n",maxdev); 
	printf("temperature deviation %lf \n",tdev); 
	fprintf(outlist,"%lf \n",tdev); 
	return 0; 
}

//finds 12 nearest neighbors and excludes those that are already in list
//rescale this so produces quantity analogous to the antisite number
int findLocOrder(struct listlist *mdata,struct entry *rd1,int size,struct entry *d1,struct entry *dd1,int *count,double *dim,int *adim,int scale,double a0, char *inlist,FILE *output,char * process)
{
	int * refids; 
	int id, n,n2,leng,len,bulk,alcount,flag; 
	int pos[3]; 
	double S,nicount,nitotal; 
	struct entry neighs[50]; 
	refids=(int *)calloc(size,sizeof(int)); 
	FILE *fp; 
	fp=fopen(inlist,"r"); 
	fscanf(fp,"%d \n",&len); 
	for(n=0; n<len; n++)
	{
		fscanf(fp,"%d \n",&id); 
		refids[id-1]=1; 	
	}
	S=0;  
	bulk=0; 
	alcount=0; 
	nitotal=0; 
	printf("locating Al atoms \n"); 
	for(n=0; n<size; n++)
	{
		//get 12 nearest neighbors of Al atoms inside system
		if(refids[n]==1 ) //check if in ref id list
		{
			bulk++; 
			if(d1[n].ent[3]==1) //check if Al atom
			{
				alcount++; 
				getmatpos(pos,d1[n],adim,dim); //get position
				leng=0;
				searchNeighbors(mdata,pos,&d1[n],adim,dim,a0,scale,a0,neighs,&leng,50,12); //find neighbor vectors and distances
				qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors
				nicount=0;
				flag=0; 
				//we want to exclude atoms right on the surface because this will bias the calculation
 				for(n2=0; n2<12; n2++) //we assume boundary atoms are properly coordinated 
				{
					if(refids[(int)(neighs[n2].ent[7]-1)]==0)
					{
						//flag++; 
					}
					if(neighs[n2].ent[3]==2)
					{	
						nicount=nicount+1;
						nitotal=nitotal+1; 
					}
				}
				if(flag<=6)
					S=S+(4-nicount/3); //calculate local order parameter
				else
				{
					nitotal=nitotal-nicount; 
					alcount--;
				} 
			}
			//printf(" \n"); 
		}
	}
	//S=S/alcount; 
	printf("We have %d Al atoms out of %d total volume atoms with an average local order parameter of %lf \n",alcount,bulk,S);
	printf("Average number of Ni nearest neighbors %lf ,S calculated using this parameter %lf \n",nitotal/alcount,(nitotal/alcount/3-3));

	FILE * fp3; 
	fp3=fopen("outfile.txt","a"); 
	if(fp3==NULL)
		fp3=fopen("outfile.txt","w"); 
	fprintf(fp3,"%s \n",process); 
	fprintf(fp3,"%d al of %d volume atoms with local order parameter of %lf \n",alcount,bulk,S); 
	fclose(fp3); 

	return 0;
}
//every single atom site has kinetic energy set to average of 12 nearest neighbors and self and maybe next nearest neighbors
int keAverage(struct listlist *mdata,struct entry *d1,struct entry *dd1,int size,int *count,double *dim,int *adim,int scale,double a0, char * filein)
{
	int leng,n,n2,swit; 
	int pos[3]; 
	struct entry neighs[50]; 
	float keavg,totenergy1,totenergy2,inke;
	totenergy1=0; 
	totenergy2=0; 
	FILE * fp; 	
	//determine whether not going to run this time intensive method based on whether outfile already present average ke data
	fp=fopen(filein,"r"); 
	if(fp==NULL)
	{
		fp=fopen(filein,"w");  
	}
	else //scan in data
	{
		printf("file already present reading in \n"); 
		fscanf(fp,"%d \n",&swit); //scan in number of items in list 
		for(n=0; n<size; n++)
		{
			totenergy1=d1[n].ent[6]+totenergy1; 
			fscanf(fp,"%f \n",&inke); 
			d1[n].ent[6]=inke;
			dd1[n]=d1[n];
			totenergy2=totenergy2+inke;  
		}
		printf("energy is hopefully conserved %f %f \n",totenergy1,totenergy2);
		(*count)=0;  
		return 0; //exit function
	}	

	fprintf(fp,"%d \n",size); 
	for(n=0; n<size; n++)
	{
		dd1[n]=d1[n]; 
		totenergy1=d1[n].ent[6]+totenergy1; 
		leng=0; 
		getmatpos(pos,d1[n],adim,dim); //get position
		searchNeighbors(mdata,pos,&d1[n],adim,dim,a0,scale,a0,neighs,&leng,50,18); //find neighbor vectors and distances
		keavg=dd1[n].ent[6]; 
		for(n2=0; n2<18; n2++) //we assume boundary atoms are properly coordinated 
		{
			keavg=keavg+neighs[n2].ent[6]; 
		}
		dd1[n].ent[6]=keavg/19; 
	}
	//read back into d1 for further processing
	for(n=0; n<size; n++)
	{
		totenergy2=totenergy2+d1[n].ent[6]; 
		d1[n].ent[6]=dd1[n].ent[6];
		fprintf(fp,"%f \n",d1[n].ent[6]); 
	}	
	(*count)=size;
	//(*count)=0 otherwise  
	printf("energy hopefully is conserved by process %f %f \n",totenergy1,totenergy2);
	fclose(fp);  
	return 0; 
}
//finds 12 nearest neighbors and excludes those that are already in list
int findSurface(struct listlist *mdata,int size,struct entry *d1,struct entry *dd1,int *count,double *dim,int *adim,int scale,double a0, char *inlist,FILE *output,char * process)
{
	int * refids; 
	int * surfids; 
	int id, n,n2,leng,len,surf; 
	int pos[3]; 
	struct entry neighs[50]; 
	refids=(int *)calloc(size,sizeof(int)); 
	surfids=(int *)calloc(size,sizeof(int)); 
	FILE *fp; 
	fp=fopen(inlist,"r"); 
	fscanf(fp,"%d \n",&len); 
	for(n=0; n<len; n++)
	{
		fscanf(fp,"%d \n",&id); 
		refids[id-1]=1; 	
	}
	(*count)=0; 
	printf("locating surface ids \n"); 
	for(n=0; n<size; n++)
	{
		//now we search 12 nearest neighbors of reference ids and only add them to the surface list if they are not already in the reference list
		if(refids[n]==1)
		{
			dd1[(*count)]=d1[n]; 
			dd1[(*count)].ent[4]=10; //add interior atoms for visualization
			(*count)++; 
			leng=0; 
			getmatpos(pos,d1[n],adim,dim); //get position
			searchNeighbors(mdata,pos,&d1[n],adim,dim,a0,scale,a0,neighs,&leng,50,12); //find neighbor vectors and distances
			qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors
			for(n2=0; n2<12; n2++) //we assume boundary atoms are properly coordinated 
			{
				id=neighs[n2].ent[7]; 
				if(refids[id-1]==0) //i.e. not in reference list already
				{
					surfids[id-1]++; //we have found a surface atom if not already in bulk
				}	
			}
		}
	}
	//count up surface ids
	surf=0; 
	for(n=0; n<size; n++)
	{
		if(surfids[n]<=6 && surfids[n]>=2) //say has to be referenced at least 2 times
		{
			dd1[(*count)]=d1[n]; //add surface atoms to output buffer for visualization
			dd1[(*count)].ent[4]=-10; 
			(*count)++;
			surf++;   	
		}
		if(surfids[n]>6) //say has to be referenced at least 2 times
		{
			dd1[(*count)]=d1[n]; //add surface atoms to output buffer for visualization
			dd1[(*count)].ent[4]=10; 
			(*count)++;
			len++;   	
		}

	}
	//if(output!=NULL)//will have null input when called independently
	//	fprintf(output,"%d %d \n ",(*count)-len,len); 

	FILE * fp3; 
	fp3=fopen("outfile.txt","a"); 
	if(fp3==NULL)
		fp3=fopen("outfile.txt","w"); 
	fprintf(fp3,"%s \n",process); 
	fprintf(fp3,"%d %d \n",surf,len); 
	fclose(fp3); 

	printf("We have %d surface atoms and %d bulk atoms \n", surf,len); 
	return 0;
}
//method will search for interstitials and antisites and classify them with velocity fields
int findDefects2(struct listlist * ref, struct listlist * mdata, struct entry * rd1, struct entry * d1, struct entry* dd1, int size, int *count, double a0, int scale, double *dim, int *adim,FILE * defects, char * append, double width)
{
	int c1,rep11,rep22,antial,antini,vacc,inti,jointal,jointni;   
	struct entry neighs [50]; 
	int n1,n2,n3,leng,incount; 
	int d[3]={0,0,0}; 
	int pos[3];
	float * vecs;  
	int um; 
	float fum [4];
	struct entry *next1; 
	struct entry *next2; 
	double center=251.542; //this is center z coordinate

	FILE * fp; 
	printf("loading reference neighbor vectors \n"); 
	fp=fopen("gb0.list","r");
	vecs=(float*)calloc(size*15*3,sizeof(float)); 
	if(vecs==NULL)
	{
		printf("not enough memory \n"); 
		return;
	}
	for(n1=0; n1<size; n1++)
	{
		fscanf(fp,"%d \n",&um); //scan in id
		for(n2=0; n2<15; n2++)
		{
			fscanf(fp,"%f %f %f %f \n",&fum[0],&fum[1],&fum[2],&fum[3]); //1st is distance, last 3 are vecs
			for(n3=0; n3<3; n3++)
			{
					vecs[n1*15*3+n2*3+n3]=fum[n3+1]; 
			}
		}
	}
	fclose(fp); 
	
	printf("finding defects \n"); 
	//this will return array with defects, and label -20 in field 4 of d1, if not defect and 20 if defect
	findJacked(rd1,d1,dd1,size,count,a0/2/pow(2.0,0.5),dim,0,NULL);

	printf("we have %d defect canidates \n",*count); 	
	printf("min displacement distance %f \n \n",a0/2/pow(2.0,0.5)); 
		
	rep11=0; 
	rep22=0; 
	antial=0;
	antini=0;
	vacc=0;
	inti=0;
	jointal=0;
	jointni=0; 
	(*count)=0; 
	
	//search for vaccancies, search BZ around each jacked up atom, reference lattice has all atoms read into positions, can search neighbors for matches within BZ
	for(n1=1; n1<size; n1++)
	{
		if(d1[n1].ent[4]==20)
		{
			incount=0; 
			leng=0; 
			//we search rd1, we are searching from lattice tesselated by reference atom BZs. 
			getmatpos(pos,rd1[n1],adim,dim); //get position
			searchNeighbors(mdata,pos,&rd1[n1],adim,dim,a0,scale,a0,neighs,&leng,50,3); //find neighbor vectors and distances
			qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors, only care about closest 3.  

			for(n2=0; n2<3; n2++)
			{
				for(n3=0; n3<3; n3++)
					fum[n3]=neighs[n2].ent[9+n3]; 
				if(inbrillouinzone(&vecs[15*3*n1],fum)==1)
				{
					if(incount==0)
						next1=&neighs[n2]; 
					incount++;
				}
			}
			if(incount==0)
			{
				dd1[(*count)]=rd1[n1]; //set location from reference b/c obviously no atom is there 
				vacc++; 	//nothing but neighbor in cell, add atom
				dd1[(*count)].ent[4]=10; //not an antisite
				dd1[(*count)].ent[5]=-1; //vacancy flag  
				(*count)++;  	
			}
			if(incount==1 &&  rd1[n1].ent[3]!= (*next1).ent[3])
			{
				dd1[(*count)]=(*next1); 
				if(rd1[n1].ent[3]==2)
				{
					dd1[(*count)].ent[4]=1; 	
					antini++;
				} 
				else
				{	
					dd1[(*count)].ent[4]=-1; 
					antial++; 
				}
				dd1[(*count)].ent[5]=10; 
				(*count)++; 
			}
		}	
	}

   //method excludes defects within soem center value of the grain boundary excluding antisite defects, vacancies and interstitials can easily arise from 
   //rearrangements of the grain boundary
	
	int subi=0; 
	if(width!=0.0) //even if searched with zero width wouldn't do anything
	{
		printf("removing interstitials and vacancies within +/- %f of the grainboundary at %f \n", width/2,center); 
		for(n1=0; n1<(*count); n1++)
		{
			if(dd1[n1].ent[5]==1)
			{
				if(dd1[n1].ent[2]>(center-width/2) && dd1[n1].ent[2]<(center+width/2) )
				{
					subi++; 
					dd1[n1].ent[4]=10; 
					dd1[n1].ent[5]=10;	
				}	
						
			}
			if(dd1[n1].ent[5]==-1)
			{
				if(dd1[n1].ent[2]>(center-width/2) && dd1[n1].ent[2]<(center+width/2) )
				{
					vacc--; 
					dd1[n1].ent[4]=10; 
					dd1[n1].ent[5]=10;	
				}		
			}	
		}
	}	
	inti=inti-subi/2; //we have 2 interstitials atoms for each interstitial defect
	
	//print out defect information
	fprintf(defects,"%4d   %4d   %4d    %4d    %4d    %4d     %4d      %4d     %4d\n",(antini+rep11+rep22+antial),rep11,rep22,antini,antial,(inti),vacc,(jointni),(jointal));  
	return 0;	
		
}
//add grain boundary atoms to list, enabled if doing grain boundary test
int insertGrainBoundary(struct entry * rd1,struct entry *dd1, int *count, int size)
{
	int n,id,len;
	int * ids;  
	FILE *fp; 
	fp=fopen("grainboundary.list","r");
	if(fp==NULL)
	{
		printf("no grain boundary reference file detected, not reading in \n"); 
		return 0; 
	}
	printf("reading in grainboundary list id's \n"); 
	ids=(int *)calloc(size,sizeof(int)); 
	for(n=0; n<(*count); n++)
	{
		id=dd1[n].ent[7]; 
		ids[id-1]=1; 
	}
	fscanf(fp,"%d \n",&len); 
	for(n=0; n<len; n++)
	{
		fscanf(fp,"%d \n",&id); 
		if(ids[id-1]!=1)
		{
			dd1[(*count)]=rd1[id-1];
			dd1[(*count)].ent[4]=20; //give grain boundary particular flags so can seperate from other defects
			dd1[(*count)].ent[5]=20;  
			(*count)++; 	
		}	
	}	
	fclose(fp); 
	return 0; 
}
//find atoms with energy above cutoff and define defect region based on results
int findKECluster(struct listlist *data,struct entry *d1,int size,struct entry * dd1,int * count,double a0,int scale,double *dim,int *adim, double cutoff,double stepsize,int prevcount, int clustersize)
{
	FILE *fp; 
	struct entry neighs[50];
	int pos[3];  
	int * ids; //use to keep track of which ids are a part of the cluster
	int n, n2, leng, ccount; 
	ids=(int *)calloc(size,sizeof(int)); //zero initialized so can assume
	(*count)=0;
	printf("finding kecluster \n"); 
	int max=clustersize; 
	int min=clustersize-50; 
	int mincount=1; //id has to come up at least mincount times in neighbor lists, use to make regions better connected
	int range=2; 
	int neighstot=18; //search 1st and 2nd nearest neighbors

	for(n=0; n<size; n++)
	{
		if(d1[n].ent[6]>cutoff)
		{
			dd1[(*count)]=d1[n]; 
			(*count)++; 
			ids[n]=1; 
		}  	
	}
	printf("have %d canidate volume atoms \n",(*count));
 
	//after find backbone atoms, search neighbors to get full list of cluster
	//if ke contours sufficiently smooth this shouldn't matter
	/*
	for(n=0; n<(*count); n++)
	{
		leng=0; 
		getmatpos(pos,dd1[n],adim,dim); //get position
		searchNeighbors(data,pos,&dd1[n],adim,dim,a0,scale,range*a0,neighs,&leng,50,neighstot); //find neighbor vectors and distances
		qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors
		for(n2=0; n2<leng; n2++) //add neighbor ids to list
		{
			if((int)dd1[n].ent[7]==292300)
			{ 
				printf("id %d \n",(int)(neighs[n2].ent[7]));
				printf("dist %f \n",neighs[n2].ent[5]);
			} 
			ids[(int)(neighs[n2].ent[7]-1)]++; //add ids to list
		}
	}
	*/
	
	printf("printing out ids \n"); 
	ccount=0; 
	for(n=0; n<size; n++)
	{
		if(ids[n]>=mincount)
		{
			ccount++; 
		}		
	}
	
	(*count)=0; 
	if( ccount<=max && ccount>=min )
	{
		printf("printing out antisite list \n"); 
		fp=fopen("antisite.list","w");  
		fprintf(fp,"%d \n",ccount); 
		for(n=0; n<size; n++)
		{
			if(ids[n]>=mincount)
			{
				fprintf(fp,"%d \n",n+1); //print out idea if part of cluster group
				dd1[(*count)]=d1[n]; 
				(*count)++;
			}		
		}
		printf("atoms in defect buffer %d and atoms which have mincount %d \n",(*count),ccount); 	
		fclose(fp); 	
		//print out located ids
		return 0;
	}
	else //do recursive call and change kenetic energy cutoff up or down to get ideal size
	{
		if( (prevcount>max && ccount<min) || (prevcount<max && ccount>min) )
			stepsize=stepsize/2; 
		printf("count off %d cutoff %lf \n",ccount,cutoff); 
		if(ccount>=max)
			cutoff=cutoff+stepsize; 
		if(ccount<=min)
			cutoff=cutoff-stepsize; 
		findKECluster(data,d1,size,dd1,count,a0,scale,dim,adim,cutoff,stepsize,ccount,clustersize); 
		return 0; 
	} 	
}
//creates reference lattice based on current dimensions of total volume so can account for thermal expansion
//assume 50*50*50 dimensions, won't work for GB system
int createRefLattice(struct entry *rd1, int size, double *dim)
{
	int n1,n2,n3,n4,count;
	float a0; 
	a0=(float)(dim[0]+dim[1]+dim[2])/50/3;
	printf("Dimensions are %lf %lf %lf \n",dim[0],dim[1],dim[2]); 
	printf("lattice constant is %f \n",a0); 
	//define nearest neighbor vectors
	float vec1[3]={0.0,0.0,0.0}; 
	float vec2[3]={0.5*a0,0.5*a0,0.0}; 
	float vec3[3]={0.0,0.5*a0,0.5*a0}; 
	float vec4[3]={0.5*a0,0.0,0.5*a0};
	float * vect[4]; 
	vect[0]=vec1; 
	vect[1]=vec2; 
	vect[2]=vec3; 
	vect[3]=vec4; 
	count=0; 
	for(n1=0; n1<50; n1++)
	{
		for(n2=0; n2<50; n2++)
		{
			for(n3=0; n3<50; n3++)
			{
				for(n4=0; n4<4; n4++)
				{
					rd1[count].ent[0]=n1*a0+*(vect[count%4]+0);  //fill in coordinates of all unit cells using basis vectors 
					rd1[count].ent[1]=n2*a0+*(vect[count%4]+1); 
					rd1[count].ent[2]=n3*a0+*(vect[count%4]+2);
					if(count%4==0)
						rd1[count].ent[3]=1; //Al atom at base
					else
						rd1[count].ent[3]=2;  
					count++;
				}		
			}
		}
	}

	//method for finding reference lattice
	/*
	printf("finding references angles from perfect lattice \n"); 
	//find reference angles
	leng=0; 
	ccount=0;
	getmatpos(pos,rd1[0],adim,dim); //get position
	searchNeighbors(mref,pos,&rd1[0],adim,dim,a0,scale,a0,neighs,&leng,50,12); //find neighbor vectors and distances
	for(n=0; n<12; n++)
	{
		//printf("id %d and seperation %f \n",(int)neighs[n].ent[7],neighs[n].ent[5]); 
		for(n2=(n+1);n2<12;n2++) //go through and create all pairs of nearest neighbor vectors
		{
			sum=0; 
			for(n3=0;n3<3;n3++)
			{
				sum=neighs[n].ent[9+n3]*neighs[n2].ent[9+n3]+sum; //take dot product 
			}	
			sum=sum/neighs[n].ent[5]/neighs[n2].ent[5];
			refangles[ccount]=acos(sum);
			ccount++; 
		}	
	}*/

	return 0; 
}
//locates regions of crystal where there are significant deviations from the reference lattice sites, checks angles
int devAngles(struct listlist *mref,struct listlist *mdata ,struct entry *rd1,struct entry *d1,int size,struct entry * dd1,int * count,double a0,int scale,double *dim,int *adim, double cutoff)
{
	int n,leng,n2,n3,n5,ccount,refcount,rescount; 
	int pos[3]; 
	float sum,deviation,min,max,avg,pi;
	struct entry neighs[50]; 
 	float refangles [12*11/2];
	float datangles[12*11/2];  
	pi=3.14159; 
	min=10000; 
	max=0; 
	avg=0; 
	rescount=0; 
	
	//we know what the reference angles have to be for the perfect lattice
	ccount=0; 
	for(n=0;n<6;n++)
	{
		refangles[ccount]=pi;
		ccount++;  
	}
	for(n=0;n<24;n++)
	{
		refangles[ccount]=pi*1/3;
		ccount++;  
		refangles[ccount]=pi*2/3;
		ccount++;  
	}
	for(n=0;n<12;n++)
	{
		refangles[ccount]=pi*1/2;
		ccount++;  
	}
	printf("total number of ref angles %d \n",ccount); 
	qsort((void*)refangles,12*11/2,sizeof(float),comparefloat);
 
	(*count)=0; 
	findJacked(rd1,d1,dd1,size,count,a0/4/pow(2.0,0.5),dim,0,NULL); //assume atom moved at least 1/2 wigner seitz radius before considering 
	printf("found %d potential defect atoms \n",(*count));        //as possible disordered region
	//4th entry of d1 labeled with 20 if considered defect
	//go through list and check if canidate atoms exceed cutoff parameter
	refcount=(*count); 
	(*count)=0; 
	printf("searching through canidates which exceed maximum deviation \n"); 
	for(n5=0; n5<size; n5++)
	{
		if(d1[n5].ent[4]==20)//canidate melt region
		{
			leng=0; 
			ccount=0;
			getmatpos(pos,d1[n5],adim,dim); //get position
			searchNeighbors(mdata,pos,&d1[n5],adim,dim,a0,scale,a0,neighs,&leng,50,12); //find neighbor vectors and distances
			for(n=0; n<12; n++)
			{
				//printf("id %d and seperation %f \n",(int)neighs[n].ent[7],neighs[n].ent[5]); 
				for(n2=(n+1);n2<12;n2++) //go through and create all pairs of nearest neighbor vectors
				{
					sum=0; 
					for(n3=0;n3<3;n3++)
					{
						sum=neighs[n].ent[9+n3]*neighs[n2].ent[9+n3]+sum; //take dot product 
					}	
					sum=sum/neighs[n].ent[5]/neighs[n2].ent[5];
					datangles[ccount]=acos(sum);
					ccount++; 
				}	
			}
			qsort((void*)datangles,12*11/2,sizeof(float),comparefloat); //sort data so can directly compare to reference 
			deviation=0; 
			for(n=60; n<(12*11/2); n++)
			{			
				deviation=pow(datangles[n]-refangles[n],2.0)+deviation;
				//printf("%f %f \n",datangles[n],refangles[n]);  	
			}
			deviation=deviation/6;
			if(deviation>max)
				max=deviation; 
			if(deviation<min)
				min=deviation; 
			if(deviation>cutoff)
			{
				avg=avg+deviation; 
				dd1[(*count)]=d1[n5];
				dd1[(*count)].ent[4]=-10;  
				(*count)++;
				rescount++; 
			}
			else
			{
				dd1[(*count)]=d1[n5];
				dd1[(*count)].ent[4]=10;
				(*count)++;  
			}
		}
		else
		{
				dd1[(*count)]=d1[n5];
				dd1[(*count)].ent[4]=10;
				(*count)++;  
		}
	}
	
	printf("average deviation from reference (for atoms above threshold) is %f \n",avg/rescount); 
	printf("minimum deviation from reference lattice position %f \n",min); 
	printf("maximum deviation from reference lattice position %f \n",max); 
	printf("%d atoms are considered to be in melt \n",rescount); 
	
	return 0; 
}
int displist(struct listlist *mref,struct entry *rd1,struct entry *d1,int size,struct entry * dd1,int * count,double a0,int scale,double *dim,int *adim)
{
	int n, n2, ccount, orgcount,leng,id; 
	int pos[3]; 
	struct entry neighs[50]; 
	int * ids; //use to keep track of which ids are a part of the cluster
	ids=(int *)calloc(size,sizeof(int)); //zero initialized so can assume
	
	ccount=0; 
	FILE *fp; 
	fp=fopen("disps.list","r"); 
	fscanf(fp,"%d \n",&orgcount); 
	
	printf("%d atoms in disps.list \n",orgcount); 
	for(n=0; n<orgcount; n++)
	{
		fscanf(fp,"%d \n",&id); 
		ids[id-1]=1; 
		getmatpos(pos,d1[id-1],adim,dim); //get position
		leng=0; 
		searchNeighbors(mref,pos,&d1[id-1],adim,dim,a0,scale,a0,neighs,&leng,50,12); //find neighbor vectors and distances
		qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors
		for(n2=0; n2<leng; n2++)
		{
			ids[(int)(neighs[n2].ent[7]-1)]=1; //add ids to list
		}	
	}
	fclose(fp); 
	
	fp=fopen("antisite.list","w"); 
	(*count)=0; 
	printf("printing out ids \n"); 
	ccount=0; 
	for(n=0; n<size; n++)
	{
		if(ids[n]==1)
		{
			ccount++; 
		}		
	}
	printf("found %d volume atoms \n",ccount); 	
	fprintf(fp,"%d \n",ccount); 
	for(n=0; n<size; n++)
	{
		if(ids[n]==1)
		{
			fprintf(fp,"%d \n",n+1); //print out id if part of cluster group
			dd1[(*count)]=d1[n]; 
			(*count)++;
		}		
	}
	free(ids);
	fclose(fp);  
	return 0; 
}
//calculates rms distance of all replacement defects, just prints out, also prints out list, make so wont print over previous lists if there
int calculateRMS(struct listlist *mdata, struct entry *rd1, struct entry *d1,int size, struct entry * dd1, int *count, double a0, int scale, double 
*dim,int *adim)
{
	int n, n2, anticount, ccount;
	double dist2;  
	double mean[]={0.0,0.0,0.0}; 
	int printing,leng;  
	int pos[3]; 
	struct entry neighs[50]; 
	int * ids; //use to keep track of which ids are a part of the cluster
	ids=(int *)calloc(size,sizeof(int)); //zero initialized so can assume
	
	ccount=0; 
	printing=0; 
	FILE *fp;
	printing=1;  
	if(printing==1)
	{
		fp=fopen("antisite.list","w"); 
	}
	anticount=0; 
	for(n=0; n<(*count); n++)
	{
		if(dd1[n].ent[4]==1 || dd1[n].ent[4]==-1)
		{
			for(n2=0; n2<3; n2++)
			{
				mean[n2]=mean[n2]+dd1[n].ent[n2]; 	
			}
			anticount++;	
		}
	}
	for(n2=0; n2<3; n2++)
	{
		mean[n2]=mean[n2]/anticount; 
	}
	for(n=0; n<(*count); n++)
	{
		if( dd1[n].ent[4]==-1 || dd1[n].ent[4]==1 || dd1[n].ent[4]==10 )
		{
			if(printing==1)
			{
				//method searches a0 around each antisite and if finds neighbors adds to list
				leng=0; 
				getmatpos(pos,dd1[n],adim,dim); //get position
				searchNeighbors(mdata,pos,&dd1[n],adim,dim,a0,scale,a0,neighs,&leng,50,10); //find neighbor vectors and distances
				qsort((void*)neighs,leng,sizeof(struct entry),compare3); //sort neighbors
				//printf("leng %d \n",leng); 
				for(n2=0; n2<leng; n2++)
				{
					ids[(int)(neighs[n2].ent[7]-1)]=1; //add ids to list
				}
				ids[(int)(dd1[n].ent[7]-1)]=1; //put in id of antisite itself
			}
			for(n2=0;n2<3; n2++) //safe to assume atom didn't channel 5/6 of a side dimension, means that wrapped around
			{
				if( (mean[n2]-dd1[n].ent[n2])> (dim[n2]*5/6)   )	
				{
					dd1[n].ent[n2]=dd1[n].ent[n2]+dim[n2]; 	
				}	
				if( (dd1[n].ent[n2]-mean[n2])> (dim[n2]*5/6)   )
				{
					dd1[n].ent[n2]=dd1[n].ent[n2]-dim[n2]; 	
				}
				dist2=dist2+pow(dd1[n].ent[n2]-mean[n2],2.0); 
			}
		}
	}
	if(printing)
	{
		printf("printing out ids \n"); 
		ccount=0; 
		for(n=0; n<size; n++)
		{
			if(ids[n]==1)
			{
				ccount++; 
			}		
		}	
		fprintf(fp,"%d \n",ccount); 
		for(n=0; n<size; n++)
		{
			if(ids[n]==1)
			{
				fprintf(fp,"%d \n",n+1); //print out idea if part of cluster group
			}		
		}
		fclose(fp);  
	}
	dist2=dist2/anticount; 
	dist2=pow(dist2,0.5); 
	printf("mean center for antisites is %lf %lf %lf \n",mean[0],mean[1],mean[2]); 
	printf("rms distance for antisite defects is %lf \n",dist2);
	free(ids); 
	return 0; 
}
int findDefects(struct listlist * ref, struct listlist * data,struct entry* rd1,struct entry* d1,struct entry* dd1,int size,int *count, double a0, int scale, double *dim, int *adim,FILE * defects, char * append, double width) 
{			
	double tol=a0/pow(2,0.5)/2; //distance for considered being in given lattice position
	double di,mind; 
	int count1=0; 
	int tempid; 
	int count2,id,index,ind,ind2,len,flag;  
	struct listlist * bob;  
	struct entry * head, * next1, * next2, * next3;
	int slotless=0;
	int c1,rep11,rep22,antial,antini,vacc,inti,jointal,jointni;   
	struct list neighs; 
	double dists[40]; 
	neighs.len=0; 
	int n1,n2,n3,f1,f2,leng; 
	int d[3]={0,0,0}; 
	int pos[3]; 
	double center=251.542; //this is center z coordinate
	int * vacids; 

	/*printf("getting memory for vac id \n"); 
	vacids=(int *)calloc(size,sizeof(int)); 
	if(vacids==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}*/
	//code to read in atoms with particular coordination
	
	printf("finding defects  \n"); 
	//this will return array with defects, and label -20 in field 4 of d1, if not defect and 20 if defect
	findJacked(rd1,d1,dd1,size,count,a0/2/pow(2.0,0.5),dim,0,NULL);

	printf("we have %d defect canidates \n",*count); 	
	printf("min displacement distance %f \n",a0/2/pow(2.0,0.5)); 

	//we fill up every additional lattice spot in ref with 1-3 atoms from defect lattice, hash in entire lattice
	//reinitialize lengths, reinitialize to 1 b/c counting reference atom in eachb sublist, prevents from having to do annoying offsets
	for(n1=0; n1<adim[0]*adim[1]*adim[2];n1++)
	{
		for(n2=0;n2<ref[n1].lent;n2++)
			ref[n1].len[n2]=1;
		for(n2=0;n2<data[n1].lent;n2++)
			data[n1].len[n2]=1; 
		data[n1].lent=0;  
	}
 
	for(n1=0; n1<size; n1++)
	{
		if(d1[n1].ent[4]==20)
		{
			//will rezero count by searching through d1 and loading into lattice
			(*count)--; 
			getmatpos(pos,d1[n1],adim,dim); //get position
			neighs.len=0; 
			searchRadius(ref,pos,&d1[n1],adim,dim,a0,scale,a0,&neighs,dists,0); //search for neighbor canidates
			mind=1000000;
			ind=-1;  
			if(neighs.len==0)
			{
				printf("cannot find any neighbors, something wrong \n"); 	
			}
			//printf("neigh length %d \n",neighs.len); 
			for(n2=0; n2<neighs.len;n2++) //find distance d1[n2] closest too
			{
				if(mind>dists[n2])
				{
					mind=dists[n2]; 
					ind=n2; 	
				}
			}
			if(ind!=-1)  //if found valid index, add atom to sublist 
			{
				//after find pointer to desired cell, need to get listlist so can put this pointer in, from pointer of closest reference can 
				// calculate position in reference listlist array
				getmatpos(pos,*(neighs.add[ind]),adim,dim);
				index=pos[0]+adim[0]*pos[1]+adim[0]*adim[1]*pos[2];
				bob=&ref[index];//get pointer of listlist head for particular cell we are interested in
				ind2=-1;  
				for(n2=0; n2<(*bob).lent; n2++)//figure out proper sublist to add to, list list head points to several reference atoms in cell
				{
					if((*bob).add[n2*4]==neighs.add[ind])
					{
						ind2=n2; 
						break; 	
					}
				}
				if(ind2==-1)
				{	
					printf("couldn't find correct sublist to add to \n"); 	
				}
				len=(*bob).len[ind2]; //get length of sublist
				//printf("length of sublist %d \n",len); 
				(*bob).add[ind2*4+len]=&d1[n1]; //add atom to sublist
				(*bob).len[ind2]++; 
			}
			else
			{
				printf("not able to find closest atom \n"); 	
			}
		}	
	}
	if((*count)!=0)
		printf("did not enter all defects, have count %d \n",(*count)); 
	
	//matrixStatistics(ref,adim,size,append,0);
	//run through system, label sites with defects, count, and add these to output buffer
	printf("loaded now searching \n"); 	

	rep11=0; 
	rep22=0; 
	antial=0;
	antini=0;
	vacc=0;
	inti=0;
	jointal=0;
	jointni=0; 
	
	for(n1=0; n1<adim[0]*adim[1]*adim[2]; n1++) //search through entire system with linked lists
	{
		len=ref[n1].lent;  //get length of sublist
		//printf("length of list %d \n",len); 
		for(n2=0; n2<len; n2++)
		{
			leng=ref[n1].len[n2]; //get length of list
			head=ref[n1].add[n2*4]; 
			next1=ref[n1].add[n2*4+1]; 
			next2=ref[n1].add[n2*4+2]; //should be okay, just garbage, don't access if leng!=3
			next3=ref[n1].add[n2*4+3]; 	
			//check if head in defect list
			
			tempid=(int)((*head).ent[7]); 
			flag=-1; 
			//this checks if atom has been considered defect canidate by findjacked 
			if( (int)(d1[tempid-1].ent[4])==20 )
				flag=1; 

			if(leng==1&& flag==1 ) //checks if head in list, if is, then consider vacancy 
			{
				dd1[(*count)]=(*head);
				head=&dd1[(*count)];
				//vacids[vacc]=(*head).ent[7]; //load up vacancy id 
				vacc++; 	//nothing but neighbor in cell, add atom
				(*head).ent[4]=10; //not an antisite
				(*head).ent[5]=-1; //vacancy flag  
				(*count)++;  
			}
			else if(leng==2&& flag==1) //classify as antisite or healed, means that own atom is already in defect list, so can't also be in same lattice site
			{
				
				if( (*head).ent[3]!=(*next1).ent[3] )//if atom types are different
				{
					dd1[(*count)]=(*next1);
					next1=&dd1[(*count)]; 
					(*next1).ent[5]=10; //no interstitial flag
					if((*head).ent[3]==2)
					{
						(*next1).ent[4]=1;   //Ni antisite 
						antini++; 
					}
					else
					{
						(*next1).ent[4]=-1; //al antisite
						antial++; 
					}
				 	(*count)++;
				}
				else
				{
					 //'healed' portion
					if((*head).ent[3]==1 && ((*head).ent[7]!=(*next1).ent[7]) )
					{
						rep11++;
						dd1[(*count)]=(*next1); 
						next1=&dd1[(*count)]; 
						(*next1).ent[4]=10;   
						(*next1).ent[5]=10; //no interstitial flag
						(*count)++; 
					} 
					if((*head).ent[3]==2 && ((*head).ent[7]!=(*next1).ent[7]) )  //make sure not same id
					{					
						rep22++;
						dd1[(*count)]=(*next1); 
						next1=&dd1[(*count)]; 
						(*next1).ent[4]=10; 
						(*next1).ent[5]=10; //no interstitial flag
						(*count)++; 
					}
						//crystal fine, same id same type, didn't change
				}
				
			}
			else if(leng==3 ||  (leng==2&&(flag==-1)) ) //if have two atoms in spot, or know that original atom at site is still there, 
//then know we have interstitial
			{
				flag=0; 
				if(leng!=3) //we don't have to worry about the case where there is only one defect atom in the list from this section
				{
					//printf("added interstitial atom \n"); 
					next2=&d1[(int)((*head).ent[7]-1)];  //can use this just as before			
				}
				
				dd1[(*count)]=(*next1);
				next1=&dd1[(*count)]; 
				(*count)++;  
				dd1[(*count)]=(*next2);
				next2=&dd1[(*count)]; 
				(*count)++;  
				
				if( ( (*head).ent[3]==(*next1).ent[3] )&&( (*head).ent[3]==(*next2).ent[3] ))//if interstitial atoms same as head atom, plain interstitial
				{
					(*next1).ent[4]=10; 
					(*next2).ent[4]=10;  //no antisite portion to defect 
				}
				else //we have several different cases here for antisite defects, we can have either 1 or 2, and we need to label correctly
				{
					//case where both atoms are different than the head node
					if((*next1).ent[3]!=(*head).ent[3] &&  (*next2).ent[3]!=(*head).ent[3]  )
					{
						if((*head).ent[4]==2) //head node is Al
						{
							jointni+=1; 
						}
						else
						{
							jointal+=1; 
						}
					}
					//case only one atom is different than head node, cannot classify as antisite defect
					else
					{
						(*next1).ent[4]=10; 
						(*next2).ent[4]=10; 
					}
				}
				(*next1).ent[5]=1;//is a interstitial
				(*next2).ent[5]=1; 
				inti++; 
			}
			else
			{
				if(leng>3)
				{
					printf("something strange, have %d atoms in a single ws cell ", leng-1);
					/*dd1[(*count)]=(*next3);
					next3=&dd1[(*count)];
					(*count)++;  
					(*next3).ent[4]=10; 
					(*next3).ent[5]=-2;*/ 
				} 
			}
		}
	}	
	
	/*double db; 
	int boundi []={0,0,0}; 
	//printinfo(706439,rd1,d1,dd1,count,dim,2);//2 means search for 2 defects in buffer 
	//printinfo(749955,rd1,d1,dd1,count,dim,1); 
	db=dist(&d1[868244-1],&d1[867986-1],dim,boundi);
	printf("distance from interstitial to interstitial %lf \n",db); 
	db=dist(&d1[867986-1],&rd1[868112-1],dim,boundi);
	printf("distance from interstitial to reference atom %lf \n",db);*/ 

   //method excludes defects within soem center value of the grain boundary excluding antisite defects, vacancies and interstitials can easily arise from 
   //rearrangements of the grain boundary
	
	/*double min;
	int minident=-1;  
	for(n1=0; n1<vacc; n1++)
	{
		min=1000; 
		 
		for(n2=0; n2<size; n2++)
		{
			db=dist(&rd1[vacids[n1]-1],&d1[n2],dim,boundi);
			if(db<min ) //make sure not accessing own self
			{
				min=db; 
				minident=dd1[n2].ent[7]; 
			}
		}
		printf("min distance between %d and %d is %lf \n",vacids[n1],minident+1,min); 
	}*/


	int subi=0; 
	if(width!=0.0) //even if searched with zero width wouldn't do anything
	{
		printf("removing interstitials and vacancies within +/- %f of the grainboundary at %f \n", width/2,center); 
		for(n1=0; n1<(*count); n1++)
		{
			if(dd1[n1].ent[5]==1)
			{
				if(dd1[n1].ent[2]>(center-width/2) && dd1[n1].ent[2]<(center+width/2) )
				{
					subi++; 
					dd1[n1].ent[4]=30; 
					dd1[n1].ent[5]=30;	
				}	
						
			}
			if(dd1[n1].ent[5]==-1)
			{
				if(dd1[n1].ent[2]>(center-width/2) && dd1[n1].ent[2]<(center+width/2) )
				{
					vacc--; 
					dd1[n1].ent[4]=30; 
					dd1[n1].ent[5]=30;	
				}		
			}	
		}
		insertGrainBoundary(rd1,dd1,count,size);  //inserts atoms with ids in reference list
	}	
	inti=inti-subi/2; //we have 2 interstitials atoms for each interstitial defect

	printf("length of defect buffer %d \n",(*count)); 
	printf("filling up defect buffer \n"); 
	fillLLists(data, dd1, adim, dim, (*count),"jimbob");//load defects into new array
	//matrixStatistics(data,adim,(*count),append,1);  //display so can see clustering and do error checking

	//calculate rms distance of antisites from center of mass
	calculateRMS(data,rd1,d1,size,dd1,count,a0,scale,dim,adim); 
	printf("we have %d defects \n \n",(*count));
	if((*count)!=(antini+antial+inti*2+vacc-jointal-jointni+rep11+rep22))//joint defects in output buffer for two different reasons, ints are in twice
		printf("count off have %d instead of %d \n",(antini+antial+inti*2+vacc-jointal-jointni),(*count)); 
	 
	fprintf(defects,"%4d   %4d   %4d    %4d    %4d    %4d     %4d      %4d     %4d\n",(antini+rep11+rep22+antial),rep11,rep22,antini,antial,(inti),vacc,(jointni),(jointal));  
	return 0;
		
}
//searches for atoms that meet certain threshold and prints them to output buffer
int threshold(struct entry * d1, struct entry * dd1, int size, double kethresh, int * count)
{
	printf("Running threshold test \n"); 
	int n; 
	for(n=0;n<size;n++)
	{
		if((d1[n].ent[6]) > kethresh)
		{ 
    		dd1[*count]=d1[n]; 
    		(*count)++; 
		}	
	}	
	return 0; 
}
int freeData(struct entry ** trash, int trash_size )
{
	int i; 
	for(i=0; i<trash_size; i++)
	{
		free(trash[i]); 
	} 
	printf("data freed \n");
	return 0;  
}
int cordStatistics(int * cordlist, int size, char * app)//print out coordination statistics as calculated by coordination function
{
	int n; 
	FILE *fp; 
	char mat[50]; 
	join(mat,app,"coord",".stat"); 
	printf("coord file %s",mat);  
	fp=fopen(mat,"w"); 
	int count[40];  //assume no coordinations bigger than 20
	for(n=0; n<40; n++)
	{
		count[n]=0; //initialize matrix
	}
	for(n=0; n<size; n++)
	{
		if(cordlist[n]<40)
			count[cordlist[n]]++; //increment coordination of particular number
			//printf("coordination %d out of bounds \n", cordlist[n]); 
	}	
	fprintf(fp,"Coordination, Number of Atoms \n"); 
	int tot; 
	tot=0; 
	for(n=0; n<40; n++)
	{
		fprintf(fp,"%d , %d \n", n, count[n]);
		tot=count[n]+tot;  
	}
	fprintf(fp,"id number, coordination \n"); 
	for(n=0; n<size; n++)
	{
		fprintf(fp,"%d %d \n ",(n+1),cordlist[n]); 
	}
	fprintf(fp,"\n %d atoms of %d atoms accounted for \n", tot, size); 
	fclose(fp); 
	return 0; 
}
int checkCoordination(struct listlist * dat, struct entry * dd1, int * count, int * idim, double * ddim, int size, double a0,int scale, double tol,char * append) 
{
	//dimr is actual lattice dimensions in angstroms
	double nearneigh=a0/pow(2,0.5);//always use relative distance of x coordinate, rescale other distances to x coordinate 
	printf("using %f for the nearest neighbor distance and %f for tolerance \n",(float)nearneigh, (float)tol); 
	int nx1[3];
	int n, index1, len1, c1, coordcount;
	struct entry *one; 
	struct list neighs; 
	neighs.len=0;
	double dists[40];  
	int *coordin;
	int maxcoord=0;  
	coordcount=0; 
	coordin=(int *)calloc(size,sizeof(int)); 
	if(coordin==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	printf("got coordination memory \n"); 


	(*count)=0; 	
	//need to go through and get linked list of cell inspecting and compare given entry to self list 
	for(nx1[0]=0; nx1[0]<idim[0]; nx1[0]++)
	{
		for(nx1[1]=0; nx1[1]<idim[1]; nx1[1]++)
		{
			for(nx1[2]=0; nx1[2]<idim[2]; nx1[2]++)
			{
				index1=nx1[0]+idim[0]*nx1[1]+idim[0]*idim[1]*nx1[2];//doesn't think this creates valid integer 
				len1=(int)dat[index1].lent; 
				for(c1=0; c1<len1; c1++)
				{	
					one=dat[index1].add[c1*4]; //one accesses the data stored at the address in list
					searchRadius(dat,nx1,one,idim,ddim,a0,scale, (nearneigh+tol), &neighs,dists,0);  
					coordin[(int)((*one).ent[7]-1)]=neighs.len; //we get atom id and put cordination count at id spot
					//printf("neighcount %d cordcount %d \n", , coordcount); 
					dd1[(*count)]=(*one); 
					dd1[(*count)].ent[5]=neighs.len;
					if(neighs.len>maxcoord)
						maxcoord=neighs.len;  
					(*count)++;
					neighs.len=0; 
				}
			}	
		}	
	}
	//sort list of atoms by coordination number, so can have list of ids can ignore
	qsort((void*)dd1,size,sizeof(struct entry),compare3);
	printf("sorted coordination list \n");   
	//figure out boundarires
	int counter=1;  
	int bins[maxcoord]; 
	for(n=0; n<(*count); n++)
	{ 
		//printf("%d \n", (int)dd1[n].ent[5]); 
		while(counter< (int)(dd1[n].ent[5]))
		{
			bins[counter]=n; //give boundary
			counter++; 
			//printf("%d, %d \n",counter,n); 
		}	
	}
	bins[counter]=(*count)-1;  //cap off list 
	printf("length of defect buffer %d \n",(*count)); 
	for(n=1; n<(maxcoord+1);n++)
	{
		printf("%d \n",bins[n]); 
	}	

	printf("finished giving boundaries \n"); 	

	//print lists of atoms with different coordination
	char mat[50]; 
	char joe[3]; 
	int start=0; 
	int stop=0;
 
	for(n=1; n<(maxcoord+1); n++)
	{
		sprintf(mat,"coord%d",n); 
		//join(mat,append,joe,""); 
		printf("coord file %s \n",mat);  
		stop=bins[n]; 
		printIDlist(&dd1[start],(stop-start),mat);
		start=bins[n]; //set as end of list so systematically read through 
	} 
	
	printf("printing out grainboundary id list \n"); 
	char *grain="grainboundary";  
	start=bins[1];
	stop=bins[10]; 
	printIDlist(&dd1[start],(stop-start),grain);
	
	printf("finished filling coordination arrray \n"); 
	cordStatistics(coordin,size,append); 
	free(coordin); 
	return 0; 
}
//grf statistics calculates stDev and average and prints them out to a data file
int grfStatistics(int * data, int atoms, int len, int points, double deltar, double a0, char * app, double * dimr)
{
	double rho; 
	rho=((double)atoms)/dimr[0]/dimr[1]/dimr[2]; //get density based on volume of box and number of atom
	printf("starting statistics \n"); 
	float *stat; 
	stat=(float *)calloc(points*2,sizeof(float)); 
	if(stat==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	FILE * file; 
	char mat [50]; 
	join(mat,app,"grf",".stat");
	printf("opening %s",mat);  
	file=fopen(mat,"w"); 
	fprintf(file,"Length %d \n ", points); 
	fprintf(file, "Radius, f(r) \n "); 
	int n1,n2; 
	float avg, stDev;
	avg=0; 
	stDev=0;  
	//printf("calculating average \n");
	int min=0;  
	for(n1=0; n1<points; n1++)
	{
		for(n2=0; n2<len; n2++)
		{
			avg=data[n1+n2*points]+avg; 
		}
		if( (avg>=0.5)&& min==0  )
		{
			printf("number of atoms %f \n",(float)avg); 
			printf("distance is %f \n", (float)deltar*(n1+1)); 
			min=1; 
		}
		avg=avg/len; 
		avg=avg/rho;
		avg=avg/(4*3.14159*deltar*deltar*deltar*(n1+1)*(n1+1)); 
		stat[n1]=avg; 
		fprintf(file, "%f  %f \n", deltar*n1, avg); 
		avg=0;
	}
	fprintf(file,"Radius, stDev \n"); 
	for(n1=0; n1<points; n1++)
	{
		avg=stat[n1]; 
		for(n2=0; n2<len; n2++)
		{
			avg=(data[n1+n2*points]-avg);
			avg=avg*avg; 
			stDev=avg+stDev;  
		}	  
		stDev=stDev/len; 
		stDev=pow(stDev,0.5); 
		fprintf(file, "%f  %f \n", deltar*n1,stDev); 
		stDev=0;
	}	
	fclose(file); 
	printf("finished statistics \n"); 
	free(stat); 
	return 0; 
}
//gets radial distribution function slow way, this method will get the boundaries, expect answer it produces lower than actual, b/c will miss
//periodic boundary conditions
int sgrfunction(struct entry * rd1, int size, int * dims, double * dimr, double a0,int scale, double rmax, double deltar, char * append)
{
	int n, len1; 
	struct entry one, two;
	printf("finding grf function the slow way \n"); 
	int n1,n2,f1; 
	double dis; 
	int b[3]={0,0,0}; 
	
	int *nr; //accumulation of atom number as go from zero to r   
	len1=(int)rmax/deltar;//gives number of bins to be used, will determine run time
	nr=(int *)calloc(len1*(size),sizeof(int)); 
	if(nr==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
		
	for(n1=0; n1<size; n1++)
	{	
		one=rd1[n]; 
		for(n2=0; n2<size; n2++)
		{
			two=rd1[n2]; 
			if((&two)!=(&one))//only apply section if not the same atom 
			{
				dis=dist(&one,&two,dimr,b);  //don't do boundary detection 
				dis=(double)floor(dis/deltar); 
				if(((int)dis)<len1)
					nr[len1*n+(int)dis]++;  
			}
		}
	}
	printf("finished gathering grf data \n");  
	//grfStatistics(nr,size,len1, deltar, a0,append,dimr); 
	free(nr); 
	return 0; 
}
//gets rf function fast wat
//search through block region determined by radius and bin all atom results into dr bins
int searchBlock(int * bins ,struct listlist * dat, int * nx1, struct entry * center, int * dims, double * dimr, double a0, int scale, double deltar, int length)
{
	double dis; 
	int nx2[3]; 
	int dx1[3]; 
	int boundi[3]={0,0,0}; 
	int index1, c1,len1, rng, n; 
	struct entry * neigh; 
	rng=(int)(length*deltar/a0*scale)+1;  //determine range of cells we sweep 
	
	//printf("in block, using range of %d \n",rng); 	
	for(nx2[0]=-rng; nx2[0]<(rng+1); nx2[0]++)
	{
		for(nx2[1]=-rng; nx2[1]<(rng+1); nx2[1]++)
		{
			for(nx2[2]=-rng; nx2[2]<(rng+1); nx2[2]++)
			{
				for(n=0; n<3; n++)//check boundaries, set appropriate flag if overrun
				{
					dx1[n]=nx1[n]+nx2[n];//add coords of checked cell to get search cell 
					if(dx1[n]>(dims[n]-1))
					{
						dx1[n]=(-dims[n]+dx1[n]); //make sure wraps around proper amount, as long as doesn't pass over old cell we're fine 
						boundi[n]=1;
						//printf("reached boundary \n");  
					}
					else if(dx1[n]<0)	
					{
						dx1[n]=dims[n]+dx1[n]; 
						boundi[n]=1; 
						//printf("reached boundary \n"); 
					}	
				}
				index1=dx1[0]+dims[0]*dx1[1]+dims[0]*dims[1]*dx1[2];
				len1=(int)dat[index1].lent;
				for(c1=0; c1<len1; c1++) //run through contents of neighbor list to check coordination
				{ 
					neigh=dat[index1].add[c1*4];
					if((center)!=(neigh)) //i.e. we are not accessing the same address
					{
						dis=dist(center, neigh,dimr,boundi); 
						dis=(double)floor(dis/deltar); 
						if(((int)dis)<length)
							bins[(int)dis]++;   //if not out of bounds increment bin particular distance falls in
						
							//printf("distance far %f  \n", dis); 
					}
				}
				for(n=0; n<3; n++)
					boundi[n]=0; 	
			}		
		}	
	}
	return 0; 
}
//gets rf function fast wat
// find neighbor vectors and ids and distances, 9-11 is the displacement to the neighboring atom
int searchNeighbors(struct listlist * dat, int * nx1, struct entry * center, int * dims, double * dimr, double a0, int scale, double radius, struct entry * neighs, int * lenbuf, int max, int min)
{
	double dis; 
	int nx2[3]; 
	int dx1[3]; 
	int boundi[3]={0,0,0};
	double vecs[3];  
	int index1, c1,len1, rng, n, c2; 
	struct entry * neig; 
	rng=(int)(radius/a0*scale)+1;  //determine range of cells we sweep 
	//printentry(center); 
	//printf("searching neighbors \n"); 	
	for(nx2[0]=-rng; nx2[0]<(rng+1); nx2[0]++)
	{
		for(nx2[1]=-rng; nx2[1]<(rng+1); nx2[1]++)
		{
			for(nx2[2]=-rng; nx2[2]<(rng+1); nx2[2]++)
			{
				for(n=0; n<3; n++)//check boundaries, set appropriate flag if overrun
				{
					dx1[n]=nx1[n]+nx2[n];//add coords of checked cell to get search cell 
					if(dx1[n]>(dims[n]-1))
					{
						dx1[n]=(-dims[n]+dx1[n]); //make sure wraps around proper amount, as long as doesn't pass over old cell we're fine 
						boundi[n]=1;
						//printf("reached boundary \n");  
					}
					else if(dx1[n]<0)	
					{
						dx1[n]=dims[n]+dx1[n]; 
						boundi[n]=1; 
						//printf("reached boundary \n"); 
					}	
				}
				
				index1=dx1[0]+dims[0]*dx1[1]+dims[0]*dims[1]*dx1[2];
				len1=(int)dat[index1].lent;
				for(c1=0; c1<len1; c1++) 
				{ 
					neig=dat[index1].add[c1*4];
					if((center)!=(neig) ) //if searching for vacancies, will use reference data, so address won't be the same, 
                                                              // but can still find atom with the same id 
					{                    
						dis=vec(center,neig,vecs,dimr,boundi); 
						if(dis<radius && (*lenbuf)<max)
						{
							neighs[(*lenbuf)]=(*neig);
							neighs[(*lenbuf)].ent[5]=dis;
							for(c2=0; c2<3; c2++)
							{
								neighs[(*lenbuf)].ent[9+c2]=(float)vecs[c2];
							}
							(*lenbuf)++;
						}
						
					}
				}
				for(n=0; n<3; n++)
					boundi[n]=0; 	
			}		
		}	
	}
	if((*lenbuf)<min)
	{
		//printf("recursive call \n"); 
		(*lenbuf)=0;
		//printf("radius %lf , lenbuf %d \n",radius,*lenbuf);  
		searchNeighbors(dat,nx1,center,dims,dimr,a0,scale,radius*1.5, neighs,lenbuf,max, min);
	}
	//printf("finished searching neighbors \n"); 
	return 0; 
}
int findNeighVecs(struct listlist * dat, struct entry * rd1, int size , int * dims, double * dimr, double a0,int scale, double radius) 
{
	FILE * fp; 
	int nx1[3];
	int n,n2, index1, id, lenbuf,n3; 
	struct entry neighs[50]; 

	printf("starting neighvec list method \n"); 
	printf("radius %lf \n",radius); 
	
	int vals[2]={706439,749955}; 
	
	fp=fopen("vecs.list","w"); 
	for(n=0; n<size; n++)
	{
		//n=vals[n3]-1;
		lenbuf=0; 
		index1=getmatpos(nx1,rd1[n],dims,dimr); 	
		id=rd1[n].ent[7];
		searchNeighbors(dat,nx1,&rd1[n],dims,dimr,a0,scale,radius,neighs,&lenbuf,50,15);
		if(lenbuf<15)
			printf("not able to find enough neighbors \n"); 
		qsort((void*)neighs,lenbuf,sizeof(struct entry),compare3);
		fprintf(fp,"%d \n",id);  
		for(n2=0; n2<15; n2++)
		{		
			fprintf(fp,"%f %f %f %f \n",neighs[n2].ent[5],neighs[n2].ent[9],neighs[n2].ent[10],neighs[n2].ent[11]); 	
		}
		fprintf(fp," \n"); 
	}
	
	fclose(fp);
	printf("finished printing neighbor vectors \n");  
	return 0; 
}

int grfunction(struct listlist * dat, struct entry * data, struct entry * dd1, int * count, int size, int * dims, double * dimr, double a0,int scale, double rmax, double deltar, char* append,char * listfile) 
{
	FILE * fp; 
	int nx1[3];
	int n, index1, len1, len2, c1, c2, accum, id,listlen,ct,atoms,len0,ind,nearneighs; 
	struct entry *one;
	 
	atoms=size; 
	len0=size; 

	int *nr; //accumulation of atom number as go from zero to r   
	len1=(int)rmax/deltar;//gives number of bins to be used, will determine run time
	printf("rmax is %f * a0, deltar is %f * a0 \n",(float)rmax, (float)deltar); 

	if(listfile!=NULL)//open up listfile, get number of entries for memory allocation
	{
		fp=fopen(listfile,"r"); 
		fscanf(fp,"%d \n",&len0); //write list size into size varible 
	}
	nr=(int *)calloc(len1*(len0),sizeof(int)); 
	if(nr==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	ind=(int)(a0/pow(2.0,0.5)/deltar); 
	printf("nearest neighbor distance %f \n",(float)a0/pow(2.0,0.5)); 
	printf("created bins %d long , nearest neighbor bins %d \n", len1,ind); 
	printf("length of list is %d \n",len0);
 
	
	if(listfile==NULL)
	{
	//need to go through and get linked list of cell inspecting and compare given entry to self list 
		for(nx1[0]=0; nx1[0]<dims[0]; nx1[0]++)
		{
			for(nx1[1]=0; nx1[1]<dims[1]; nx1[1]++)
			{
				for(nx1[2]=0; nx1[2]<dims[2]; nx1[2]++)
				{
					index1=nx1[0]+dims[0]*nx1[1]+dims[0]*dims[1]*nx1[2];//doesn't think this creates valid integer
					len2=dat[index1].lent;                               //sweep through neighbor list at a location
					for(c1=0; c1<len2; c1++)
					{	
						one=dat[index1].add[c1*4]; //one accesses the data stored at the address in list
						id=(*one).ent[7];
						searchBlock(&nr[len1*(id-1)],dat,nx1,one,dims,dimr,a0,scale,deltar,len1); //writes what finds in each bin to address
						//we want to label velocity fields based on atom coordination
						nearneighs=0; 
						for(c2=0; c2<(ind+1);c2++) //add up number of neighbors within distance
						{
							nearneighs=nearneighs+nr[len1*(id-1)+c2]; 	
						}
						dd1[(*count)]=data[id-1]; 
						dd1[(*count)].ent[4]=(float)nearneighs; //set fourth entry to be the number of nearest neighbors
						(*count)++;
						//printf("nearneighs are %d",nearneighs);  
					}	
				}	
			}
		}
		listlen=size; 
	}
	else  //read in data from listfile get grf function from these
	{
		int i,id;  
		int ct=0; 
		int ind=-1; 
		for(n=0; n<len0;n++)
		{
			i=fscanf(fp,"%d \n",&id); 
			if(i==EOF)
			{
				printf("miscount \n"); 
				break; //reached end of readin file	
			}
			//printf("id from list %d \n",id); 
			getmatpos(nx1,data[id-1],dims,dimr);
			//printf("position of particle %d, %d, %d \n",nx1[0],nx1[1],nx1[2]); 
			index1=nx1[0]+dims[0]*nx1[1]+dims[0]*dims[1]*nx1[2]; 
			len2=dat[index1].lent;
			if(len2==0)
				printf("Searching list with zero length \n"); 
			ind=-1; 
        		//sweep through neighbor list at a location, look for particle has id we are looking for.  
			for(c1=0; c1<len2; c1++)
			{	
				one=dat[index1].add[c1*4]; //one accesses the data stored at the address in list
				if( (int)((*one).ent[7])==id  )
				{
					ind=1; 
					break; 
				}
			}//with this loop we make sure we can find the correct id, if can't will prevent from going forward
			if(ind==-1)
			{
				printf("Can't find proper id \n"); 
				return 0; 
			}
			searchBlock(&nr[len1*(ct)],dat,nx1,one,dims,dimr,a0,scale,deltar,len1); //writes what finds in each bin to address
			ct++; 
			
			//calculate number of nearest neighbors
			ind=(int)a0/2/pow(2.0,0.5)/deltar; 
			nearneighs=0; 
			for(c1=0; c1<(ind+1);c1++)
			{
				nearneighs=nearneighs+nr[len1*(id-1)+c1]; 	
			}
			dd1[(*count)]=data[id-1]; 
			dd1[(*count)].ent[4]=nearneighs; //set fourth entry to be the number of nearest neighbors
			(*count)++; 
		}
		
	}
	
	
	printf("finished gathering grf data \n");  
	grfStatistics(nr,atoms,len0,len1, deltar, a0,append,dimr); 
	free(nr); 
	return 0; 
}
//read in data from file fp and label atom type 1st velocity field
int readin(FILE *fp,int size, struct entry * buf, double * dim, int atomtype, int readintype )
{
	//if readintype =1 do old readin with 8 fields
	//if readintype =2 do new readin with 12 fields
	
	char * formin; 

	if(readintype==2)
	{
		formin="%f %f %f %f %f %f %f %f %f %f %f %f \n"; 
	}
	else
	{
		formin="%f %f %f %f %f %f %f %f \n"; 
	}
	
	int i,n; 
	float im[12]; 
	for(n=0;n<size;n++)
	{
		if(readintype==2)
		{
			fscanf(fp,formin,&im[0],&im[1],&im[2],&im[3],&im[4],&im[5],&im[6],&im[7],&im[8],&im[9],&im[10],&im[11]); 
		}
		else
		{
			fscanf(fp,formin,&im[0],&im[1],&im[2],&im[3],&im[4],&im[5],&im[6],&im[7]);
			for(i=8;i<12;i++)
				im[i]=0; 
 
		}	
		for(i=0; i<12; i++)
		{
			buf[n].ent[i]=(double)im[i]; 
		}
		for(i=0; i<3; i++)
		{
			buf[n].ent[i]=buf[n].ent[i]*dim[i]; //convert from relative to absolute coordinates
		}   
		buf[n].ent[3]=atomtype; //put in atom type
	}
	return 0; 
}
//method will write out 1st atom type, and if another atom type appears will automatically begin writing second part
//write-out, write-out, write for ruin, and the world's end 
int writeout(FILE *fp, struct entry * d, double * dim,  int count)
{
	int n,n1; 
	int nexttype=0; 
	int flag=0;
	char formout []="%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %d %12.6f %12.6f %12.6f %12.6f \n";  
	for(n=0;n<count;n++)
	{
		if( (((int)(d[n].ent[3]))==2)&& (flag==0) )//if at second atom type print out appropriate lines
		{
			fprintf(fp, "\n 58.69 \n"); 
	    	fprintf(fp,"Ni \n"); //get two middle lines one has mass other has atom type 
	    	flag=1; //do this so won't keep printing out
		}
		fprintf(fp,formout,d[n].ent[0]/dim[0],d[n].ent[1]/dim[1],d[n].ent[2]/dim[2],d[n].ent[3],d[n].ent[4],d[n].ent[5],d[n].ent[6],(int)d[n].ent[7],d[n].ent[8],d[n].ent[9],d[n].ent[10],d[n].ent[11]);
	}
	return 0; 
}

//prints out list of ids from data entries
int printIDlist(struct entry * data,int count,char * append) 
{
	int n; 
	FILE *fp; 
	char mat[50]; 
	join(mat,append,"",".list"); 
	printf("list file %s",mat);  
	fp=fopen(mat,"w"); 
	fprintf(fp, "%d \n",count); //print length of file at start
	for(n=0; n<count; n++)
	{
		fprintf(fp,"%d \n",(int)data[n].ent[7]); //prints out id list
	}
	fclose(fp); 
	return 0; 
}
int main(int argc, char* argv[])
{
	int number; 
	int fillneighlist=0; 
	char jacked_up[]="shift"; 
	char full[] ="full"; 
	char searchfile[]="searchfile"; 
	char search[]="search"; 
	char ethresh[]="ethreshold"; 
	char quantity[]="quantity"; 
	char keatom[]="keatom"; 
	char posatom[]="posatom"; 
	char alldefects[]="alldefects";
	char alldefects2[]="alldefects2"; 
	char coordination[]="coordination";
	char dispout[]="dispout"; 
	char chains[]="chains"; 
	char sgrf[]="sgrf"; 
	char grf[]="grf";   
	char listgrf[]="listgrf"; 
	char tlist[]="tlist";
	char tempcluster[]="tempcluster"; 
	char meltcluster[]="meltcluster"; 
	char findSurf[]="findSurf"; 
	char pedist[]="pedist";  
	char kedist[]="kedist";  
	char stressdist[]="stressdist"; 
	char tempdev[]="tempdev"; 
	char neighvec[]="neighvec"; 
	char findCascades[]="findCascades"; 
	char kecluster[]="kecluster"; 
	char locOrder[]="locOrder"; 
	char latticedev[]="latticedev"; 
	char dispsCount[]="dispsCount"; 
	char readdisp[]="readdisp";
	FILE * keclusterfile; 
	char *defect_type;
	char *processfile;
	char *referencefile; 
	char *listfile; 
	FILE *quantout;  
	FILE *defects;
	FILE *tempcl;  
	int sid;
	int clustersize;  
	int * ids;  
	int idcount;
	int cutoff2;  
	double width; 
	int dimen; 
	double temperature; 
	char *quantity_type; 
	char *filein; 
	int quick=1;
	int trashcount=0; 
	int readstyle=1; 
	struct entry * trash[20]; 
	double kb=8.617*pow(10,-5); 
	double cutoff; 
	double melttemp; 
	struct entry * history; 
	int histcounter; 
	int histlistcounter;
	int maxhistory;  
	double kethresh; 
	double deltaz; 
	double a0; //lattice parameter for the system, assigned based on number of atoms (if 1 Ni, if 2 Ni3Al )
	printf("Arg number %d \n", argc);
	number=(int)atof(argv[1]); //number of atom types in lattice, prepared to handle 1 or 2
	defect_type=argv[2];  
	processfile=argv[3]; 
	referencefile=argv[4]; 
	double range; 
	double deltar; 
	printf("%d %s %s %s \n", number, defect_type, processfile, referencefile); 
	struct entry * quantbuf; 
	
	if(strcmp(defect_type,full)==0)
	{
		readstyle=(int)atof(argv[5]);
	}
	if(strcmp(defect_type,coordination)==0)
	{
		readstyle=(int)atof(argv[5]); 
	}
	if(strcmp(defect_type,neighvec)==0)
	{
		readstyle=(int)atof(argv[5]); 	
	}
	if(strcmp(defect_type,readdisp)==0)
	{
		readstyle=(int)atof(argv[5]); 	
	}
	if(strcmp(defect_type,latticedev)==0)
	{
		readstyle=(int)atof(argv[5]);
		cutoff=(double)atof(argv[6]);  	
	}
	if(strcmp(defect_type,pedist)==0)
	{
		readstyle=2;
		deltaz=(double)atof(argv[5]);
		dimen=(int)atof(argv[6]); 
	}
	if(strcmp(defect_type,chains)==0)
	{
		readstyle=(int)atof(argv[5]); 
	}
	if(strcmp(defect_type,dispout)==0)
	{
		readstyle=(int)atof(argv[5]); 
	}
	if(strcmp(defect_type,dispsCount)==0)
	{
		readstyle=(int)atof(argv[5]);
		cutoff2=(int)atof(argv[6]);  
	}
	if(strcmp(defect_type,stressdist)==0)
	{
		readstyle=2;
		deltaz=(double)atof(argv[5]);
	}
	if(strcmp(defect_type,kedist)==0)
	{
		readstyle=2;
		deltaz=(double)atof(argv[5]);
		dimen=(int)atof(argv[6]); 
	}
	if(strcmp(defect_type,listgrf)==0)
	{
		range=(double)atof(argv[5]);
		deltar=(double)atof(argv[6]); 
		listfile=argv[7]; 
	}
	if(strcmp(defect_type,tempcluster)==0)
	{
		readstyle=(int)atof(argv[5]); 
		listfile=argv[6]; 
		tempcl=fopen("tempcluster.stat","w"); 
	}
	if(strcmp(defect_type,meltcluster)==0)
	{
		readstyle=(int)atof(argv[5]); 
		listfile=argv[6];
		melttemp=(double)atof(argv[7]);  
		tempcl=fopen("meltcluster.stat","w"); 
	}
	if(strcmp(defect_type,tempdev)==0)
	{
		readstyle=(int)atof(argv[5]); 
		tempcl=fopen("tempdev.stat","w"); 
	}
	if(strcmp(defect_type,findSurf)==0)
	{
		readstyle=(int)atof(argv[5]); 
		listfile=argv[6]; 
	}
	if(strcmp(defect_type,locOrder)==0)
	{
		readstyle=(int)atof(argv[5]); 
		listfile=argv[6]; 
	}
	if(strcmp(defect_type,findCascades)==0)
	{
		readstyle=(int)atof(argv[5]); 
		cutoff=(double)atof(argv[6]); 
	}
	if(strcmp(defect_type,kecluster)==0)
	{
		readstyle=(int)atof(argv[5]); 
		cutoff=(double)atof(argv[6]);
		clustersize=(int)atof(argv[7]);
		filein=argv[8];   
		keclusterfile=fopen("svratios.stat","w"); 
	}
	if(strcmp(defect_type,tlist)==0)
	{
		temperature=(double)atof(argv[5]); 
	}
	if(strcmp(defect_type,quantity)==0)
	{
		quantout=fopen("quantityout","w");
 		quantity_type=argv[5];
		fprintf(quantout,"%s \n",quantity_type); 
		if(strcmp(quantity_type,keatom)==0)
		{
			sid=(int)atof(argv[6]); //get id number of atom want to get data from	
			fprintf(quantout,"data from atom # %d \n", sid); 
		}
		if(strcmp(quantity_type,posatom)==0)
		{
			sid=(int)atof(argv[6]); //get id number of atom want to get data from	
			fprintf(quantout,"data from atom # %d \n", sid); 
		}
		//getmemory(&quantbuf,1000,trash,&trashcount);  //assume that not processing more than 1000 points, good assumption
	}
	if(strcmp(defect_type,alldefects)==0)
	{ 
		readstyle=(int)atof(argv[5]);
		width=(double)atof(argv[6]); 
		defects=fopen("defects.stat","w");
		fprintf(defects, "Rept, Rep11, Rep22 ,Ni antis ,Al antis ,Intrs, Vaccs ,Intrs-Ni Antis, Intrs-Al Antis \n" );  
	}
	if(strcmp(defect_type,alldefects2)==0)
	{ 
		readstyle=(int)atof(argv[5]);
		width=(double)atof(argv[6]); 
		defects=fopen("defects2.stat","w");
		fprintf(defects, "Rept, Rep11, Rep22 ,Ni antis ,Al antis ,Intrs, Vaccs ,Intrs-Ni Antis, Intrs-Al Antis \n" );  
	}
	if(strcmp(defect_type,search)==0)
	{
		sid=(int)atof(argv[5]);  
	}      
	if(strcmp(defect_type,ethresh)==0)
	{
		kethresh=(double)atof(argv[5]);
	}
	if(strcmp(defect_type,grf)==0||strcmp(defect_type,sgrf)==0)
	{
		range=(double)atof(argv[5]); 
		deltar=(double)atof(argv[6]);
		readstyle=(int)atof(argv[7]);  
	}	
	FILE *master;
	master=fopen(processfile, "r"); 
	FILE *ref; 
	ref=fopen(referencefile, "r"); 
	if(ref==NULL||master==NULL)
	{
		printf("null file \n"); 
		return 1; 
	}
	
	FILE *bob; 
	FILE *bob2; 

	char *formin;
	char *formout; 
	int len; 
	
	//the format for the data read from cfg files is xs,ys,zs, vx,vy,vz, ke, id
 
	formin="%f %f %f %f %f %f %f %f \n"; 
	
	int nal; 
	int nni;
	int atoms;
	double tol; 
	struct entry **doh;   
	struct entry *d1,*rd1,*dd1;  
	struct listlist *mref, *mdata;
	int n; 
	int i; 

	int buff1=100; 
	char text[100][100]; //generally safe assumption that all lines manipulating are shorter than 100 characters
	
	//get reference data and put into arrays, first we want to extract dimension and atom number information
	
	//this part scans first line to get atom number entry        	
	for(n=0; n<4;n++)
	{
		fscanf(ref,"%s",text[0]);   
	}
	fscanf(ref," %d \n ",&atoms);  //-1 line
	if(number==2)
	{ 
		nal=atoms/4;
		nni=nal*3;
		len=20; 
	} 
	else
	{
		nal=atoms; //all atoms go to a single type
		nni=0;
		len=20;  
	}
	printf("%d atoms in system with %d types \n",atoms, number);
	double dim[3];
	float tdim; 
	int adim[3]; 
	fgets(text[0],buff1,ref); //-1 line
	int n1; 
	for(n1=0; n1<3; n1++)//-12 lines
	{ 
		fscanf(ref, "%s",text[0]); 
		fscanf(ref, "%s",text[0]); //get two strings out of line
		fscanf(ref, "%f \n",&tdim); //read line data into dimension -1
		dim[n1]=(double)tdim; //need to be careful with readins, can't read in doubles, only floats, so have to convert
		for(n=0; n<4; n++)  
		{
			fgets(text[0],buff1,ref); //-3 lines
		}
	}
	printf("The dimensions are %f A, %f A, %f A \n", dim[0],dim[1],dim[2]);

	if(readstyle==2) //read further to remove additional fields
		len=len+4; 
 
	for(n=0; n<(len-14); n++)//take out remaining lines
	{
			fgets(text[0],buff1,ref); 
	}
	
	float im[8]; //need float array to facilitate data read off, can't read into doubles directly with fscanf 	
	getmemory((void**)&rd1,atoms,trash, &trashcount,"entry");   
	getmemory((void**)&d1,atoms,trash, &trashcount,"entry");  
	getmemory((void**)&dd1,atoms,trash, &trashcount,"entry");   

	readin(ref,nal,rd1,dim,1,readstyle); //reads in data starting at rd1 
	fgets(text[0],buff1,ref);                                                         //need * to access pointer address for command
	fgets(text[0],buff1,ref); //get two middle lines one has mass other has atom type 
	readin(ref,nni,&(rd1[nal]),dim,2,readstyle); 
	printf("data read in \n"); 
	qsort((void*)rd1,atoms,sizeof(struct entry),compare1);  
	printf("reference data sorted \n");
	n=checkAtoms(rd1,atoms,number,nal); 
	if(n==1)
		return 1; //exit program if missing atoms

	//logic for assigning lattice spacing
	if(number==1)
		a0=3.52; //assume Ni lattice, problem if really Al lattice
	else
		a0=3.571; 
	printf("Lattice constant for the system is %f \n", a0); 
	int scale=2; //2 gives 2 slots per lattice cell, 1/2 gives 1/2 slot per cell
	printf("scale is %f matrix elements per lattice cell \n", pow(scale,3.0)); 	
	
	//we want to create a matrix which stores atom positions in linked lists and read this in 
	
	if((strcmp(defect_type,coordination)==0)||(strcmp(defect_type,listgrf)==0)||(strcmp(defect_type,readdisp)==0)||(strcmp(defect_type,grf)==0)||(strcmp(defect_type,alldefects2)==0)||(strcmp(defect_type,findSurf)==0)||(strcmp(defect_type,kecluster)==0)||strcmp(defect_type,locOrder)==0||strcmp(defect_type,latticedev)==0)
	{
		fillneighlist=1;
	} 
	if(strcmp(defect_type,latticedev)==0)
	{
		//createRefLattice(rd1,atoms,dim);
	}
	for(n=0;n<3;n++)
	{
		adim[n]=(int)dim[n]/a0; 
		adim[n]=adim[n]*scale; //we want cell size to be half of lattice constant per side
		adim[n]=adim[n]+1; //round up so don't have bunching	
	}
	printf("Dimensions of matrix are %d,  %d,  %d \n", adim[0],adim[1],adim[2]);	
	//use convention that mem[x+dim[1]*y+dim[1]*dim[2]*z] to address all x has range of dim[1] y range of dim[2] and z range of dim[3]
	getmemory((void**)&mref,adim[0]*adim[1]*adim[2],trash, &trashcount,"llist");  
	getmemory((void**)&mdata,adim[0]*adim[1]*adim[2],trash, &trashcount,"llist");
	// xs, ys, zs, vx, vy, vz, ke, id, we will use velocity bits to store information and set flag
	fillLLists(mref, rd1, adim, dim, atoms,text[98]); //populates neighbor lists
	double radius; 
	radius=(float)a0;
	radius=radius*3/2;  
	//printf("radius %f %lf \n",radius,a0*3/2); 
	if(strcmp(defect_type,neighvec)==0) //we want to check new lists agaisnt old opposite lists
	{
		 findNeighVecs(mref,rd1,atoms,adim,dim,a0,scale,radius);  
	}
	if(strcmp(defect_type,dispout)==0 || strcmp(defect_type,dispsCount)==0)
	{
		ids=(int *)calloc(atoms,sizeof(int)); //initialize id list and idcount
		idcount=0;  
	}
	if(strcmp(defect_type,findCascades)==0)
	{
		histcounter=1; 
		histlistcounter=0; 
		maxhistory=30; 
		int buff=(int)10000/cutoff*10; //determine size based on cutoff value
		history=(struct entry *)calloc(buff*maxhistory,sizeof(struct entry));
		int n5; 
		for(n5=0; n5<buff*maxhistory; n5++)
		{
			history[n5].ent[7]=0; //set id for zero so we know when to print out or not
		}
	}
	printf("Entering data file processing \n"); 
	while((fgets(text[99],buff1,master))!=NULL)
	{
		printf("processfile %s \n", processfile);
		n=strlen(text[99]);
		*(&(text[99][0])+n-1)='\0'; //get rid of endline so string properly formatted 	
		join(text[95],text[99],defect_type,""); 
		printf("text %s \n", text[99]); 
		bob=fopen(text[99],"r");  
		if(bob==NULL)
		{
			printf("null readin \n");
			freeData(trash, trashcount);  
			return 1; 
		}
		//modify output file, append modi to end
		*(text[99]+n-1)='m';
		*(text[99]+n)='o'; 
		*(text[99]+n+1)='\0';  
		bob2=fopen(text[95],"w"); 
		//we also want to make string to characterize file
		for(n1=0; n1<(n-6);  n1++)
			*(text[98]+n1)=*(text[99]+n1);
		*(text[98]+n-6)='\0';
		printf("append is %s \n",text[98]); 
			
		for(n=0; n<len; n++)  
		{
			fgets(text[n],buff1,bob); //fgets gets text string
		}

		//read in data entries
		readin(bob,nal,d1,dim,1,readstyle );
		fgets(text[0],buff1,bob);                                                         //need * to access pointer address for command
		fgets(text[0],buff1,bob); //get two middle lines one has mass other has atom type 
		readin(bob,nni,&(d1[nal]),dim,2,readstyle);
		qsort((void*)d1,atoms,sizeof(struct entry),compare1); 
		n=checkAtoms(d1,atoms,number,nal); 
		if(n==1)//display everything is something goes wrong
		{
			writeout(bob2,d1,dim,atoms);
			fclose(bob2); 
			return 1; 
		}
		
		//read into neighbor lists if method requires
		if(fillneighlist==1)
		{
			fillLLists(mdata, d1, adim, dim, atoms,text[98]); //populates neighbor lists
		}
		
		//fig out what kind of defects want to look for
		int n1,n2,f1,f2;  
		int count; 
		count=0;  
	
		if(strcmp(defect_type,alldefects )==0) //we want to check new lists agaisnt old opposite lists
		{
			qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			findDefects(mref,mdata,rd1,d1,dd1,atoms,&count,a0,scale,dim,adim,defects,text[98],width); 
		}
		if(strcmp(defect_type,alldefects2 )==0) //we want to check new lists agaisnt old opposite lists
		{
			qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			findDefects2(mref,mdata,rd1,d1,dd1,atoms,&count,a0, scale,dim,adim,defects,text[98],width); 
		}
		if(strcmp(defect_type,kecluster )==0)
		{
			printf("running kecluster method \n"); 
			keAverage(mdata,d1,dd1,atoms,&count,dim,adim,scale,a0,filein); 
			findKECluster(mdata,d1,atoms,dd1,&count,a0,scale,dim,adim,cutoff,0.1,0,clustersize);
			printf("finding surface area of defect cluster \n"); 
			count=0; //need this so can fill up dd1 completely new 
			findSurface(mdata,atoms,d1,dd1,&count,dim,adim,scale,a0,"antisite.list",keclusterfile,text[98]);  
		}
		if(strcmp(defect_type,findCascades)==0)
		{
			locateCascades(rd1,atoms,d1,cutoff,history,histcounter,maxhistory,&histlistcounter); 
			histcounter++; 
		}
		if(strcmp(defect_type,jacked_up )==0) //we want to check new lists agaisnt old opposite lists
		{
			findJacked(rd1,d1,dd1,atoms,&count,a0/10,dim,0,NULL); 
		}
		if(strcmp(defect_type,pedist)==0)
		{
			findDist(rd1,d1,dd1,atoms,&count,dim,deltaz,text[98],pedist,dimen); 
		}
		if(strcmp(defect_type,kedist)==0)
		{
			findDist(rd1,d1,dd1,atoms,&count,dim,deltaz,text[98],kedist,dimen); 
		}
		if(strcmp(defect_type,stressdist)==0)
		{
			findStressdist(rd1,d1,dd1,atoms,&count,dim,deltaz,text[98]); 
		}
		if(strcmp(defect_type,dispout )==0) //we want to check new lists agaisnt old opposite lists
		{
			displacementOutput(rd1,d1,dd1,atoms,&count,a0,dim,ids,&idcount,text[98]); 
		}
		if(strcmp(defect_type,readdisp)==0)
		{
			printf("reading in disps.list to convert to volume, print out in antisite.list \n"); 
			displist(mref,rd1,d1,atoms,dd1,&count,a0,scale,dim,adim); 
		}
		if(strcmp(defect_type,chains )==0) //we want to identify chains of interstitials to make anaylsis easier
		{
			findChains(mref,mdata,rd1,d1,dd1,atoms,&count,a0,scale,dim,adim,text[98]); 
		}
		if(strcmp(defect_type,tlist )==0) //we want to check new lists agaisnt old opposite lists
		{
			double ke=3/2*8.61733*0.00001*temperature;
			printf("The threshold energy is %f \n",(float)ke);  
			threshold(d1, dd1,atoms,ke, &count); 
			printIDlist(dd1,count,text[98]); 
		}
		if(strcmp(defect_type,findSurf)==0)
		{
			printf("finding surface area of defect cluster \n"); 
			findSurface(mdata,atoms,d1,dd1,&count,dim,adim,scale,a0,listfile,NULL,text[98]); 
		}
		if(strcmp(defect_type,locOrder)==0)
		{
			printf("finding local order parameter in volume region \n"); 
			findLocOrder(mdata,rd1,atoms,d1,dd1,&count,dim,adim,scale,a0,listfile,NULL,text[98]); 
		}
		if(strcmp(defect_type,dispsCount)==0)
		{
			printf("calculating displacement count \n"); 
			displacementCount(rd1,d1,dd1,atoms,&count,a0,dim,text[98],ids,cutoff2); 
		}
		if(strcmp(defect_type,tempcluster)==0)
		{
			printf("Doing cluster temperature calculation \n"); 
			calculateTemp(d1,kb,listfile,tempcl); 
		}
		if(strcmp(defect_type,meltcluster)==0)
		{
			printf("Doing cluster melt volume calculation \n"); 
			calculateMelt(d1,kb,listfile,tempcl,melttemp); 
		}
		if(strcmp(defect_type,tempdev)==0)
		{
			printf("calculating temp deviation in time \n"); 
			calculateTempDev(d1,atoms,kb,tempcl); 
		}	
		if(strcmp(defect_type,listgrf)==0)
		{
			printf("Getting grf potential for function \n"); 
			qsort((void*)d1,atoms,sizeof(struct entry),compare1);//method assumes data sorted by id
			grfunction(mdata,d1,dd1,&count,atoms,adim,dim,a0,scale,range*a0,a0*deltar,text[98],listfile);  
		}
		if(strcmp(defect_type,full)==0) //puts all data in output data buffer
		{
			printf("print out ordered list \n"); 
			//qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			printf("data sorted \n"); 
			//need to be careful with this part because can cause bad behavior potentially if looped over
			writeOver(d1,dd1,atoms); 
			n=checkAtoms(dd1,atoms,number,nal); 
			if(n==1)
				return 1; 
			count=atoms; 			
		}
		if(strcmp(defect_type,latticedev)==0)
		{
			printf("running lattice deviation calculation \n"); 
			devAngles(mref,mdata,rd1,d1,atoms,dd1,&count,a0,scale,dim,adim,cutoff); 
		}
		if(strcmp(defect_type,grf)==0)
		{
			printf("Getting grf potential for function \n"); 
			grfunction(mdata,d1,dd1,&count,atoms,adim,dim,a0,scale,range*a0, a0*deltar,text[98],NULL);  
		}
		if(strcmp(defect_type,sgrf)==0)
		{
			printf("Getting sgrf potential for function \n"); 
			sgrfunction(rd1,atoms,adim,dim,a0,scale,range*a0,a0*deltar,text[98]); 
		}
		if(strcmp(defect_type,searchfile)==0)
		{
			printf("doing search of atom ids \n"); 
			struct entry *find; 
			find=(struct entry *)bsearch(&sid,d1,nal,sizeof(struct entry),compare1); 
			if(find==NULL)
			{
				find=(struct entry *)bsearch(&sid,&d1[nal],nni,sizeof(struct entry),compare1); 
				if(find==NULL)
				{
					printf("can't find atom id \n");
					freeData(trash,trashcount);  
					return 1;
				}
				else
				{
					dd1[count]=*find; 
					count++; 	
				}
			}
			else
			{
				dd1[count]=*find; 
				count++; 	
			}
		}
		
		//these commands run differently, they don't use nearly as much memory, just run through list and print out, not part of code pipeline
		
		//chooses quantity want from 
		if(strcmp(defect_type,quantity)==0)
		{	
			//qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			printf("data sorted \n"); 
			printf("quantity "); 
			if(strcmp(quantity_type,keatom)==0)//will find atom with sid, and take quantity and print to quantout
			{
				printf("ke \n"); 
				int keindex=6; //have KE index, make command flexible for different quantities 
				n=quantityOutput(quantout,keindex,sid,d1,dd1,atoms,&count, 1); //one tells that only getting that entry
				if(n==1)
					return 1;  
			}	
			if(strcmp(quantity_type,posatom)==0)//will find atom with sid, and take quantity and print to quantout
			{
				printf("position \n"); 
				int posindex=0; //have KE index, make command flexible for different quantities 
				n=quantityOutput(quantout,posindex,sid,d1,dd1,atoms,&count, 3); //one tells that only getting that entry
				if(n==1)
					return 1;  
			}	
		}
		if(strcmp(defect_type,search)==0)//search for id sid
		{
			 //qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			 printf("data sorted \n");
			 struct entry * ptr;  
			 n=searchAtoms(sid,d1,dd1,&ptr,atoms,&count); 
			 if(n==1)
			 	return 1; //if can't find atom throw error
		}
		if(strcmp(defect_type,coordination)==0)
		{
			printf("checking coordination of data file \n");
			//printcontents(&mref,adim); //prints out all information address of linked list and atom data 
			//matrixStatistics(mref, adim, atoms,text[98],0); //print out file with visualizations of neighbor list filling
			checkCoordination(mref,dd1,&count,adim, dim, atoms, a0,scale,a0/10,text[98]); //search for atoms within  of nearest neighbor dist in fcc   
		}
		if(strcmp(defect_type,ethresh)==0)//search for particle with at least kethresh
		{
			threshold(d1, dd1,atoms,kethresh, &count); 
		}
		
		printf("defect count %d \n",count); 
		fprintf(bob2,"Number of particles = %d \n",count); 		
		
		for(n=1; n<len; n++)  
		{
			fprintf(bob2,"%s",text[n]);
		}
		qsort((void*)dd1,count,sizeof(struct entry),compare2);
		writeout(bob2,dd1,dim,count); //prints back out desired atoms in relative coordinates
		
		fclose(bob2); 
		fclose(bob);
		printf("wrote data \n");  
	}      //break out of while loop
	
	if(strcmp(defect_type,quantity)==0)
		fclose(quantout); //close outfile for quantity output
	if(strcmp(defect_type,alldefects)==0 ||strcmp(defect_type,alldefects2)==0  )
		fclose(defects); 
	if(strcmp(defect_type,tempcluster)==0||strcmp(defect_type,meltcluster)==0||strcmp(defect_type,tempdev)==0)
		fclose(tempcl); 
	if(strcmp(defect_type,kecluster)==0)
		fclose(keclusterfile); 
	if(strcmp(defect_type,dispout )==0)
		free(ids); 
	if(strcmp(defect_type,findCascades)==0)
		printCascades(history,histcounter,maxhistory,histlistcounter); 
	freeData(trash,trashcount);  
	
	return 0; 
}




