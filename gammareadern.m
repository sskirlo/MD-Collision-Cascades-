close all; 
clear all; 

bob=fopen('log.Ni3Al_5050','r');
a='5050'; 


%50,50, 100,100
%50,100

%ende=23243;
%resol=0.025; 
%ende=10892; 
ende=10892; 
resol=0.1; 

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
    
    for n1=1:1:4
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

y=1.0; 
x=(1+8^2)^(1/2); 
%make matrix of z entries
xpoints=0:1:x/resol; 
xpoints=xpoints*resol; 
ypoints=0:1:y/resol; 
ypoints=ypoints*resol; 
z=ones(y/resol+1,x/resol+1); 

count=1; 
n2=1; 
n1a=0; 

%Ecoh=149616*(3.46333*10^5)/74880; %for 100100
Ecoh=149616*(3.46333*10^5)/74880; %for 5050
%Ecoh=149760*(3.46333*10^5)/74880; %for 50100, subtract away surface energies and rescale
for n1=1:1:(y/resol+1)
    for n2=1:1:(x/resol+1)  %6.91794*10^5
        z(n1,n2)=joe1(2,count); %add in cohesive energy, so just get energy of grain boundary 
        z(n1,n2)=(z(n1,n2)+Ecoh-1641)/(86.371*10^-10)/(85.704*10^-10)*1.602*10^-19*1000;  %1622, was unrelaxed energy 
        if(z(n1,n2)>3700)
            if(n2-1>0)
                z(n1,n2)=z(n1,n2-1); %set to neighbor
            else
                z(n1,n2)=z(n1-1,n2); %set to neighbor
            end
        end    
        count=count+1; 
    end
end

min=1000; 
disp('mins'); 
for n2=1:1:(x/resol+1)
    if(z(5,n2)<min)
        min=z(5,n2); 
    end
end
disp(min); 
for n2=1:1:(x/resol+1)
    if(z(1,n2)<min)
        min=z(1,n2);  
    end
end
disp(min); 

figure;
plot(xpoints,z(6,:));
tit=['Cross section at y=0.5 for ',a]; 
title(tit); 
xlabel('x displacement (*a0)'); 
ylabel('Grain Boundary Energy(mJ/m^2)'); 
h=gcf; 
name=[a ,'cross1', '.jpg']; 
saveas(h,name); 

figure;
plot(xpoints,z(1,:)); 
tit=['Cross section at y=0.0 for ',a]; 
title(tit);
xlabel('x displacement (*a0)'); 
ylabel('Grain Boundary Energy(mJ/m^2)'); 
h=gcf; 
name=[a ,'cross2', '.jpg']; 
saveas(h,name); 
set(gcf, 'PaperPositionMode', 'auto');
print([a,'cross2','.eps'],'-depsc2'); 

figure; 
contour(xpoints,ypoints,z); 
tit=['Gamma Surface for ',a]; 
title(tit);
xlabel('x displacement (*a0)'); 
ylabel('y displacement (*a0)'); 
h=gcf; 
name=[a ,'gamma', '.jpg']; 
blah=colorbar; 
xlabel(blah,'mJ/m^2')
saveas(h,name); 
set(gcf, 'PaperPositionMode', 'auto');
print([a,'gamma','.eps'],'-depsc2'); 

disp('before we had'); 
disp(ende); 
disp('now we have'); 
disp(count+10000-1); 





