close all; 
clear all; 

bob=fopen('log.Ni_1kv_restart','r'); 

ende=150000; %number of steps
inc=10; %increments between each log print
count1=50050; %starts at 0, keeps track of logfile entry  
count2=1; %keeps track of matrix entry
ent=11; %number of entries
time=0; %in the first column include time in ps
timeent=5; %entry number of timestep

%strategy is to can in single int at start of line and see if its count, if
%not go to next line and repeat, if satisfied, then scan in entire line and
%increment count

joe1=ones(ent,(ende-count1)/inc); 

%this is for 11 entry log output, only includes '10' entries, b/c step
%searched for
% 1     2    3    4   5     6   7    8      9    10   11
%step, pot, ken, tot, dt, temp,vol, press, pxx, pyy, pzz
form='%f %f %f %f %f %f %f %f %f %f \n'; 

foundentry=0; 
check=ende*1000;
run=0; 

%get passed all lines which will have 0 listed
for y=1:1:20
    fgets(bob); %clear out output line stuff
end

while(count1<=ende)
    while(foundentry==0)
        check=fscanf(bob,'%d',1);
        a=sprintf('hello %d',check); 
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
    res=fscanf(bob,form,10);  %scan in 10 entries
    %fgets(bob); %need this to get newline and move on
    joe1(2:ent,count2)=res; 
    joe1(1,count2)=time; 
    time=joe1(timeent,count2)*inc+time;
    foundentry=0; 
    count1=count1+inc;
    count2=count2+1; 
    run=0; 
end

%joe=textscan(bob,form); %need to scan 1st thousand lines
%joem=cell2mat(joe); 
%joel(1:1000,:)=joem(1:1000,:);
%for y=1:1:22
%fgets(bob); %clear out output line stuff
%end

%count=997; 
%for x=1:1:99000/26
%joe=textscan(bob,form);
%disp(x); 
%for y=1:1:22
%fgets(bob); %clear out output line stuff
%end
%joem=cell2mat(joe); 
%s=size(joem); %use adaptive sizing for readin
%s=s(1,1); 
%joe1( (count+1):(count+s),:)=joem(1:s,:); 
%count=count+s; 
%end 
%joe2=joe1(1100:count,:); 

figure; 
plot(joe1(1,:), joe1(2,:)); % time vs. pot energy
xlabel('Time (ps)'); 
ylabel('PE(eV)')
title('Potential Energy vs. Time'); 

figure; 
plot(joe1(1,:), joe1(6,:)); %time vs. temp
xlabel('Time (ps)'); 
ylabel('Temp(K)')
title('Temperature vs. Time'); 

figure; 
plot(joe1(1,:), joe1(7,:)); %time vs. vol
xlabel('Time (ps)'); 
ylabel('Volume (Ang^3)')
title('Volume vs. Time'); 

figure; 
plot(joe1(1,:), joe1(4,:)); %time vs. vol
xlabel('Time (ps)'); 
ylabel('TE(eV)')
title('Total Energy vs. Time'); 

figure; 
plot(joe1(1,:), joe1(8,:)); %time vs. pressure
xlabel('Time (ps)'); 
ylabel('Press(Bars)')
title('Pressure vs. Time'); 

fclose(bob);
