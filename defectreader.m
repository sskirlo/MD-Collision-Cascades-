close all; 
clear all; 

bob=fopen('log.Ni3Al_defects','r');


ende=10063; 

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
        %a=sprintf('found %s %d',check2,check); 
        %disp(a);
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
    
    for n1=1:1:9
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

ni=[76123,76125,76127,76128,77880,77884,77888,77892,76120,76122,76124,76126,74304,74302,74300,74298,74296,74292,74288,74284,74295,74291,74287,74283];
sa=size(ni); 
sni=sa(1,2); 
al=[77883,77887,77891,77895,74303,74301,74299,74297];
sa=size(al); 
sal=sa(1,2);
t=[ni al]; 
sa=size(t); 


EcohNi=-4.6278; 
EcohAl=-4.6175; 
minVac=10000; 
minAnti=10000; 
maxVac=-10; 
maxAnti=-10; 


for n=1:1:(((ende-10000)/inc)+1)
    disp('id of atom changed'); 
    disp(t(ceil(n/2))); 
    E0=joe1(2,n);
    E0=E0+690459.07; 
    if(mod(n,2)==1) %vacancy type
        if(n/2<=sni)
            E0=E0+EcohNi; 
        else
            E0=E0+EcohAl;  
        end
        
        if(E0<minVac)
            minVac=E0; 
        end
        if(E0>maxVac)
            maxVac=E0; 
        end
        
    else   %antisite type
        if(n/2<=sni)
            E0=E0+EcohNi-EcohAl;
        else
            E0=E0+EcohAl-EcohNi;
        end
        
        if(E0<minAnti)
            minAnti=E0; 
        end
        if(E0>maxAnti)
            maxAnti=E0; 
        end
    end
    disp('defect energy'); 
    disp(E0); 
end    

disp('minAnti'); 
disp(minAnti); 
disp('minVac'); 
disp(minVac); 
disp('maxAnti'); 
disp(maxAnti); 
disp('maxVac'); 
disp(maxVac); 

