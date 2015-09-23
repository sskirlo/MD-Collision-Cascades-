
clc; 
close all; 
clear all; 

%temp file range

trange1=60000; 
trange2=230000; 
tspacing=10000; 

offset=300; %assume converging towards 300k, true to a few degrees

ende=trange2; %number of steps
inc=10; %increments between each log print
startcount=53500; 
count1=53500; %starts at 0, keeps track of logfile entry  
count2=1; %keeps track of matrix entry
ent=11; %number of entries
time=0; %in the first column include time in ps
timeent=5; %entry number of timestep
joe1=zeros(ent,(ende-count1)/inc); 
form='%f %f %f %f %f %f %f %f %f %f \n'; 
foundentry=0; 
check=ende*1000;
run=0; 

for n2=1:1:5

file='g900k';
num=sprintf('%d',n2); 
    
tite=[file,num,'\log.Ni3Al_10kv_restart']; 
bob=fopen(tite,'r'); 
%bob2=fopen('quantityout.txt','r'); 
bob3=fopen([file,num,'\tempcluster.stat'],'r');

%get passed all lines which will have 0 listed
for y=1:1:20
    fgets(bob); %clear out output line stuff
end

while(count1<=ende)
    while(foundentry==0)
        check=fscanf(bob,'%d',1);
        a=sprintf('hello %d',check); 
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
    res=fscanf(bob,form,10);  %scan in 10 entries
    %fgets(bob); %need this to get newline and move on
    joe1(2:ent,count2)=res; 
    joe1(2,count2)=time; 
    joe1(1,count2)=count1; 
    time=joe1(timeent,count2)*inc+time;
    foundentry=0; 
    count1=count1+inc;
    count2=count2+1; 
    run=0; 
end


counts=(trange2-trange1)/tspacing+1; 
%disp('processing temperature'); 
temps=textscan(bob3,'%f ',counts); 
temps=cell2mat(temps);
s=size(temps); 
s=s(1,1); 
times=zeros(1,s); 

for n=1:1:counts
    tcount=trange1+tspacing*(n-1); 
    entry=(tcount-startcount)/inc; 
    %disp(tcount);
    %disp(entry); 
    times(n)=joe1(2,entry); 
end


temp1=2500; 
temp2=1500; 

temps=temps.';
figure; 
plot(times(1:counts),temps(1:counts),'b');
after1=0; 
after2=0; 
for n=2:1:counts
    if(after1==0 && temps(n)<temp1) %reference temperatures
        after1=n; 
    end
    if(after2==0 && temps(n)<temp2)
        after2=n; 
    end
end
%calculate time reaches 1500
slope=(temps(after1)-temps(after1-1))/(times(after1)-times(after1-1)); 
time1500=(temp1-temps(after1-1))/slope+times(after1-1); 
slope2=(temps(after2)-temps(after2-1))/(times(after2)-times(after2-1)); 
time500=(temp2-temps(after2-1))/slope2+times(after2-1); 

%disp(time1500); 
%disp(time500); 
disp(time500-time1500); 

hold on; 
%plot(xtimes,ytemps,'r'); 

fclose(bob); 
fclose(bob3); 

end