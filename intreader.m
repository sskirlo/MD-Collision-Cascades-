close all; 
clear all; 

bob=fopen('log.Ni3Al_inters','r');


ende=10015; 

inc=1; %increments between each log print
count1=10000; %starts at 0, keeps track of logfile entry  
count2=1; %keeps track of matrix entry
ent=10; %number of entries

%strategy is to can in single int at start of line and see if its count, if
%not go to next line and repeat, if satisfied, then scan in entire line and
%increment count

joe1=ones(ent,(ende-count1)/inc); 

%this is for 11 entry log output, only includes '10' entries, b/c step
%searched for
% 1     2    3    4   5     6     7    8    9    10  
%step, pot, ken, tot, temp,vol, press, pxx, pyy, pzz
form='%f %f %f %f %f %f %f %f %f %f \n'; 

foundentry=0; 
check=ende*1000;
run=0; 

while(count1<=ende)
    while(foundentry==0)
        check2=fscanf(bob,'%s',1); %need to get # sign in front of comment
        check=fscanf(bob,'%d',1);
        a=sprintf('found %s %d',check2,check); 
        disp(a);
        if(check==count1)
            foundentry=1; 
            disp(count1); 
        else
            fgets(bob); %go to next line, fscan doesn't read line 
        end
        run=run+1; 
        if(run>1000)
            break;    %use this code to prevent matlab from locking up 
        end
    end
    if(run>1000)
        disp('breaking out'); 
        break; 
    end
    
    for n1=1:1:5
        fgets(bob); %get to minimized energy
    end
    jj=fgets(bob);
    disp(jj);
    
    res=fscanf(bob,form,10);  %scan in 10 entries
    foundentry=0;
    joe1(1:ent,count2)=res; 
    joe1(1,count2)=count1; 
    count1=count1+inc;
    count2=count2+1; 
    run=0; 
    
    for n1=1:1:70
        fgets(bob); 
    end  
end

%alternates between vacancy and antisites, need to calculate based on
%atomtype and point defect

EcohNi=-4.6278; 
EcohAl=-4.6175; 
minInt=10000; 
maxInt=-1; 


for n=1:1:(((ende-10000)/inc)+1)
    disp(n); 
    E0=joe1(2,n);
    disp(E0); 
    E0=E0+690459.07; 
    disp(E0); 
    
    if(mod(n,2)==0)
        disp('Ni inter'); 
        E0=E0-EcohNi; 
    else
        disp('Al inter'); 
        E0=E0-EcohAl;  
    end
        
    if(E0<minInt)
        minInt=E0; 
    end
    if(E0>maxInt)
        maxInt=E0; 
    end
        
 
    disp('defect energy'); 
    disp(E0); 
end    

disp('minVac'); 
disp(minInt); 
disp('maxVac'); 
disp(maxInt); 

