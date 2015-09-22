
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//purpose of code is to sort through files and remove those with energy below threshold value
//not most effecient with memory, reads in memory into dynamically sized arrays

struct entry
{
	double ent[8];
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
	form="%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %d \n"; 
 	printf(form,bob[0].ent[0],bob[0].ent[1],bob[0].ent[2],bob[0].ent[3],bob[0].ent[4],bob[0].ent[5],bob[0].ent[6],(int)bob[0].ent[7]);
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
	mas[pos]='\0'; 
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
//this command assumes that this lists have been sorted, zips together, if number zero, will return 1, 
//otherwise switch to spot at second start and keep searching
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
	printf("initializing lengths \n"); 
	for(n=0; n<(adim[0]*adim[1]*adim[2]); n++)
	{
		neighlist[n].lent=0; 
		for(n1=0; n1<10; n1++)
			neighlist[n].len[n1]=0; //initialize length to 0
	}
	printf("populating neighbor lists \n"); 
	for(n=0;n<size;n++)
	{
		ind=getmatpos(pos,data[n],adim,dim); 
		ny=neighlist[ind].lent; //get length of current list
		neighlist[ind].add[ny*4]=&data[n]; //put address at matrix coordinate 
		neighlist[ind].lent++; //increment position counter
		neighlist[ind].len[ny]++; 
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
//look through vaccinity of a given entry in a given cell, and return number of neighbors within radius, return number of neighbors
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
int findJacked(struct entry* rd1,struct entry* d1,struct entry* dd1,int size, int *count,double tol, double * dmir)
{
	printf("searching for jacked_up crystal \n"); 
	int n1,f1; 
	int b[3]={0,0,0}; 
	for(n1=0; n1<size; n1++)
	{
		f1=isclose(&rd1[n1],&d1[n1],tol,dmir,b);
		if(f1==0)//command returns 0 when not close to old position
		{
			dd1[*count]=d1[n1];
			(*count)++; 	
		}
	}
	//printf("found %d possible defects \n ", (*count)); 
}
//method will search for interstitials and antisites and classify them with velocity fields
int findDefects(struct listlist * ref, struct listlist * data,struct entry* rd1,struct entry* d1,struct entry* dd1,int size,int *count, double a0, int scale, double *dim, int *adim,FILE * defects, char * append) 
{			
	double tol=a0/pow(2,0.5)/2; //distance for considered being in given lattice position
	double di,mind; 
	int count1=0; 
	int count2,id,index,ind,ind2,len;  
	struct listlist * bob;  
	struct entry * head, * next1, * next2;
	int slotless=0;
	int c1,rep11,rep22,antial,antini,vacc,inti,jointal,jointni;   
	struct list neighs; 
	double dists[40]; 
	neighs.len=0; 
	int n1,n2,n3,f1,f2,leng; 
	int d[3]={0,0,0}; 
	int pos[3]; 
	
	printf("finding defects \n"); 
	//we fill up every additional lattice spot in ref with 1-3 atoms from defect lattice, hash in entire lattice
	//reinitialize lengths
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
		if(mind>(a0/2/pow(2.0,0.5)))
			printf("paired with atom outside wigner seitz radius \n"); 
		if(ind!=-1)  //if found valid index, add atom to sublist 
		{
			//after find pointer to desired cell, need to get listlist so can put this pointer in
			//printf("ids of atoms %d, %d \n",(int) (*(neighs.add[ind])).ent[7],(int)d1[n1].ent[7]); 
			getmatpos(pos,*(neighs.add[ind]),adim,dim);
			index=pos[0]+adim[0]*pos[1]+adim[0]*adim[1]*pos[2];
			bob=&ref[index];
			ind2=-1;  
			for(n2=0; n2<(*bob).lent; n2++)//figure out proper sublist to add to
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
	matrixStatistics(ref,adim,size,append,0);
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
	
	for(n1=0; n1<adim[0]*adim[1]*adim[2]; n1++) //search through entire system
	{
		len=ref[n1].lent;  //get length of sublist
		//printf("length of list %d \n",len); 
		for(n2=0; n2<len; n2++)
		{
			leng=ref[n1].len[n2]; //get length of list
			head=ref[n1].add[n2*4]; 
			next1=ref[n1].add[n2*4+1]; 
			next2=ref[n1].add[n2*4+2]; //should be okay, just garbage, don't access if leng!=3	
			if(leng==1)
			{
				vacc++; 	//nothing but neighbor in cell, add atom
				(*head).ent[4]=10; //not an antisite
				(*head).ent[5]=-1; //vacancy flag  
				dd1[(*count)]=(*head);
				(*count)++;  
				//calculate and display distance between original atom and current atom
				int boundi[]={0,0,0};
				double d=dist(head,&d1[(int)((*head).ent[7]-1)],dim,boundi);
				printf("vacancy distance %f id# %d \n",(float)d,(int)((*head).ent[7])); 
				printentry(&d1[(int)((*head).ent[7]-1)]);  
				printentry(&rd1[(int)((*head).ent[7]-1)]);  
				if(head==&d1[(int)((*head).ent[7]-1)] )
					printf("head points to defect data, should point to reference, wrong! \n"); 
			}
			else if(leng==2) //classify as antisite or healed
			{
				(*next1).ent[5]=10; //no interstitial flag
				if( (*head).ent[3]!=(*next1).ent[3] )//if atom types are different
				{
					if((*next1).ent[3]==2)
					{
						(*next1).ent[4]=1;   //Al antisite 
						antial++; 
					}
					else
					{
						(*next1).ent[4]=-1; //Ni antisite
						antini++; 
					}
					dd1[(*count)]=(*next1);
				 	(*count)++;  
				}
				else
				{
					(*next1).ent[4]=10;    //'healed' portion
					if((*head).ent[3]==1 && ((*head).ent[7]!=(*next1).ent[7]) )
					{
						rep11++;
						dd1[(*count)]=(*next1); 
						(*count)++; 
					} 
					if((*head).ent[3]==2 && ((*head).ent[7]!=(*next1).ent[7]) )  //make sure not same id
					{					
						rep22++;
						dd1[(*count)]=(*next1); 
						(*count)++; 
					}
						//crystal fine, same id same type, didn't change
				}
			}
			else if(leng==3)
			{
				if( ( (*head).ent[3]==(*next1).ent[3] )||( (*head).ent[3]==(*next2).ent[3] ))//if interstitial atoms same as head atom, plain interstitial
				{
					(*next1).ent[4]=10; 
					(*next2).ent[4]=10;  //no antisite portion to defect 
				}
				else
				{
					if((*next1).ent[3]==2)
					{
						(*next1).ent[4]=1;   //Ni antisite 
						(*next2).ent[4]=10;  //if don't do this makes accounting annoying later
						antini++; 
						jointni++; 
					}
					else
					{
						(*next1).ent[4]=-1; //Al antisite
						(*next2).ent[4]=10;
						antial++; 
						jointal++; 
					}
				}
				(*next1).ent[5]=1;//is a interstitial
				(*next2).ent[5]=1; 
				dd1[(*count)]=(*next1);
				(*count)++;  
				dd1[(*count)]=(*next2);
				(*count)++;  
				inti++; 
			}
			else
			{
				printf("something strange, have %d atoms in a single ws cell", leng); 
			}
		}
	}	
	

	printf("length of defect buffer %d \n",(*count)); 
	printf("filling up defect buffer \n"); 
	fillLLists(data, dd1, adim, dim, (*count),"jimbob");//load defects into new array
	matrixStatistics(data,adim,(*count),append,1);  //display so can see clustering and do error checking

	printf("we have %d defects \n",(*count));
	if((*count)!=(antini+antial+inti*2+vacc-jointal-jointni+rep11+rep22))//joint defects in output buffer for two different reasons, ints are in twice
		printf("count off have %d instead of %d \n",(antini+antial+inti*2+vacc-jointal-jointni),(*count)); 
	 
	fprintf(defects,"%4d   %4d   %4d    %4d    %4d    %4d     %4d      %4d     %4d\n",(antini+rep11+rep22+antial),rep11,rep22,antini,antial,(inti),vacc,(jointni),(jointal));  
	return 0;
		
}
/*int findAntisite(struct list * ref, struct listlist * data ,struct entry* rd1,struct entry* d1,struct entry* dd1,int size,int *count, double a0, double *dim, int *adim) 
{			
	printf("searching for antisite defects \n"); 
	findJacked(rd1,d1,dd1,size,count,a0/10,dim);  //all these locations will be canidates for anti-site defects
	double tol=a0/pow(2,0.5)/2; //distance for considered being in given lattice position
	int count1=0; 
	struct entry latticesite; 
	struct entry * td1;  
	struct list neighs; 
	neighs.len=0; 
	int n1,n2,f1; 
	int d[3]={0,0,0}; 
	int pos[3]; 
	getTempMemory(&td1,(*count)); //get new buffers for antisite defects coordinates 
	//we check every atom in reference lattice to see if close to our atom
	for(n1=0; n1<(*count); n1++)
	{
		getmatpos(pos,dd1[n1],adim,dim); //get position of current atom 
		//printf("got position \n");
		//printentry(&dd1[n1]);
		//printf("position %d,  %d,  %d \n", pos[0],pos[1],pos[2]);  
		searchRadius(ref,pos,&(dd1[n1]),adim,dim,a0,tol,&neighs,0); //get neighbors within nnd/2, and fill neighs
		for(n2=0; n2<(neighs.len); n2++)
		{
			//printf("number of neighbors %d \n",neighs.len); 
			latticesite=*(neighs.add[n2]);
			//printentry(&latticesite); 	
			if( (latticesite.ent[3])!=(dd1[n1].ent[3]) )//i.e. have different atom types
			{ 
				//printf("added antisite \n"); 
				td1[count1]=latticesite; 
				count1++; 	
			}
		}
		neighs.len=0; 
	}
	 
	writeOver(td1,dd1,count1); //write over dd1 old list with new antisite list
	free(td1); 
	(*count)=count1;
	return 0; 		
}*/

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
//method works by looking at each atom and getting number of atoms within a0/(2)^(1/2)+tol
int checkCoordination(struct listlist * dat, int * idim, double * ddim, int size, double a0,int scale, double tol, char * append) 
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
	coordcount=0; 
	coordin=(int *)calloc(size,sizeof(int)); 
	if(coordin==NULL)
	{ 
		printf("null pointer returned \n"); 
		return 1;
	}
	printf("got coordination memory \n"); 
	
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
					neighs.len=0; 
				}
			}	
		}	
	}
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
	for(n1=0; n1<points; n1++)
	{
		for(n2=0; n2<len; n2++)
		{
			avg=data[n1+n2*points]+avg; 
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
int grfunction(struct listlist * dat, struct entry * data, int size, int * dims, double * dimr, double a0,int scale, double rmax, double deltar, char* append,char * listfile) 
{
	FILE * fp; 
	int nx1[3];
	int n, index1, len1, len2, c1, c2, accum, id,listlen,ct,atoms,len0; 
	struct entry *one;
	 
	atoms=size; 
	len0=size; 

	int *nr; //accumulation of atom number as go from zero to r   
	len1=(int)rmax/deltar;//gives number of bins to be used, will determine run time
	
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
	printf("created bins %d long \n", len1); 
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
				//printf("id of cell invesigating %d \n",(int)(*one).ent[7]); 
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
			//if worker right, one pointer will point to entry with proper id. 
			searchBlock(&nr[len1*(ct)],dat,nx1,one,dims,dimr,a0,scale,deltar,len1); //writes what finds in each bin to address
			ct++; 
		}
		
	}
	printf("finished gathering grf data \n");  
	grfStatistics(nr,atoms,len0,len1, deltar, a0,append,dimr); 
	free(nr); 
	return 0; 
}
//read in data from file fp and label atom type 1st velocity field
int readin(FILE *fp,int size,char * formin, struct entry * buf, double * dim, int atomtype )
{
	int i,n; 
	float im[8]; 
	for(n=0;n<size;n++)
	{
		fscanf(fp,formin,&im[0],&im[1],&im[2],&im[3],&im[4],&im[5],&im[6],&im[7]); 
		for(i=0; i<8; i++)
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
int writeout(FILE *fp, struct entry * d, char * formout, double * dim,  int count)
{
	int n; 
	int nexttype=0; 
	int flag=0; 
	for(n=0;n<count;n++)
	{
		if( (((int)(d[n].ent[3]))==2)&& (flag==0) )//if at second atom type print out appropriate lines
		{
			fprintf(fp, "\n 58.69 \n"); 
	    	fprintf(fp,"Ni \n"); //get two middle lines one has mass other has atom type 
	    	flag=1; //do this so won't keep printing out
		}
		fprintf(fp,formout,d[n].ent[0]/dim[0],d[n].ent[1]/dim[1],d[n].ent[2]/dim[2],d[n].ent[3],d[n].ent[4],d[n].ent[5],d[n].ent[6],(int)d[n].ent[7]);
	}
	return 0; 
}
//function compares based on id number, sorted this way after entering
int compare1(const void *ptr1, const void *ptr2) //compare function to be passed to qsort
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
	char antisite[]="antisite"; 
	char jacked_up[]="shift"; 
	char full[] ="full"; 
	char searchfile[]="searchfile"; 
	char search[]="search"; 
	char ethresh[]="ethreshold"; 
	char quantity[]="quantity"; 
	char keatom[]="keatom"; 
	char posatom[]="posatom"; 
	char alldefects[]="alldefects";
	char coordination[]="coordination";
	char sgrf[]="sgrf"; 
	char grf[]="grf";   
	char listgrf[]="listgrf"; 
	char tlist[]="tlist"; 
	char *defect_type;
	char *processfile;
	char *referencefile; 
	char *listfile; 
	FILE *quantout;  
	FILE *defects; 
	int sid; 
	double temperature; 
	char *quantity_type; 
	int quick=1;
	int trashcount=0; 
	struct entry * trash[20]; 
	double kethresh; 
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
	
	if(strcmp(defect_type,listgrf)==0)
	{
		range=(double)atof(argv[5]);
		deltar=(double)atof(argv[6]); 
		listfile=argv[7]; 
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
		defects=fopen("defects.stat","w");
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
	formout="%12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %12.6f %d \n"; 
	
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
	char text[30][100]; //generally safe assumption that all lines manipulating are shorter than 100 characters
	
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
	for(n=0; n<(len-14); n++)//take out remaining lines
	{
			fgets(text[0],buff1,ref); 
	}
	
	float im[8]; //need float array to facilitate data read off, can't read into doubles directly with fscanf 	
	getmemory((void**)&rd1,atoms,trash, &trashcount,"entry");   
	getmemory((void**)&d1,atoms,trash, &trashcount,"entry");  
	getmemory((void**)&dd1,atoms,trash, &trashcount,"entry");   

	readin(ref,nal,formin,rd1,dim,1); //reads in data starting at rd1 
	fgets(text[0],buff1,ref);                                                         //need * to access pointer address for command
	fgets(text[0],buff1,ref); //get two middle lines one has mass other has atom type 
	readin(ref,nni,formin,&(rd1[nal]),dim,2); 
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
if((strcmp(defect_type,coordination)==0)||(strcmp(defect_type,listgrf)==0)||(strcmp(defect_type,grf)==0)||(strcmp(defect_type,antisite)==0) )
	{
	//need to decide on dimensions of array, use lattice constant based on number of atoms, assume 3.52 for Ni and 3.56 for Ni3Al
		fillneighlist=1;
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
		readin(bob,nal,formin,d1,dim,1 );
		fgets(text[0],buff1,bob);                                                         //need * to access pointer address for command
		fgets(text[0],buff1,bob); //get two middle lines one has mass other has atom type 
		readin(bob,nni,formin,&(d1[nal]),dim,2);
		qsort((void*)d1,atoms,sizeof(struct entry),compare1); 
		n=checkAtoms(d1,atoms,number,nal); 
		if(n==1)//display everything is something goes wrong
		{
			writeout(bob2,d1,formout,dim,atoms);
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
		
		if(strcmp(defect_type,antisite )==0) //we want to check new lists agaisnt old opposite lists
		{
			//qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			//findAntisite(mref,mdata,rd1,d1,dd1,atoms,&count,a0,dim,adim); 
		}
		if(strcmp(defect_type,alldefects )==0) //we want to check new lists agaisnt old opposite lists
		{
			qsort((void*)d1,atoms,sizeof(struct entry),compare1);
			findDefects(mref,mdata,rd1,d1,dd1,atoms,&count,a0,scale,dim,adim,defects,text[98]); 
		}
		if(strcmp(defect_type,jacked_up )==0) //we want to check new lists agaisnt old opposite lists
		{
			findJacked(rd1,d1,dd1,atoms,&count,a0/10,dim); 
		}
		if(strcmp(defect_type,tlist )==0) //we want to check new lists agaisnt old opposite lists
		{
			double ke=3/2*8.61733*0.00001*temperature;
			printf("The threshold energy is %f \n",(float)ke);  
			threshold(d1, dd1,atoms,ke, &count); 
			printIDlist(dd1,count,text[98]); 
		}
		if(strcmp(defect_type,listgrf)==0)
		{
			printf("Getting grf potential for function \n"); 
			qsort((void*)d1,atoms,sizeof(struct entry),compare1);//method assumes data sorted by id
			grfunction(mdata,d1,atoms,adim,dim,a0,scale,range*a0,a0*deltar,text[98],listfile);  
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
		if(strcmp(defect_type,grf)==0)
		{
			printf("Getting grf potential for function \n"); 
			grfunction(mdata,d1,atoms,adim,dim,a0,scale,range*a0, a0*deltar,text[98],NULL);  
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
			matrixStatistics(mref, adim, atoms,text[98],0); //print out file with visualizations of neighbor list filling
			checkCoordination(mref,adim, dim, atoms, a0,scale,a0/10,text[98]); //search for atoms within  of nearest neighbor dist in fcc   
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
		writeout(bob2,dd1,formout,dim,count); //prints back out desired atoms in relative coordinates
		
		fclose(bob2); 
		fclose(bob);
		printf("wrote data \n");  
	}      //break out of while loop
	
	if(strcmp(defect_type,quantity)==0)
		fclose(quantout); //close outfile for quantity output
	if(strcmp(defect_type,alldefects)==0)
		fclose(defects); 
	freeData(trash,trashcount);  
	
	return 0; 
}




