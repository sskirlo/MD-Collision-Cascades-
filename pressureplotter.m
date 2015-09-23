
close all; 
clear all; 

%read pressure data in from referenec Ni

P=[0,1.5,2.6,5.1,7.8,8.8,11.4,12.8, 24.7, 37.5, 49.0, 63.2, 72.7, 81.3,89.0,94.1, 101.2,109.7,110,114,121.8, 127.5,134.5,140.4,147.4 ]; 
V=[10.9423,10.8504,10.7841,10.6565,10.5302,10.4821,10.3638,10.289,9.8373,9.4545,9.104,8.8219,8.6623, 8.5267, 8.3894,8.3124,8.1966,8.0621,8.0644,8.0134,7.9236,7.855,7.7731,7.713,7.6279]; 
P=P/10^2; %convert to Mbars
V=V/V(1,1); %normalize volume to start

%all the Ni data in these files, save old one for reference
bob=fopen('log.compressmish','r'); %this is data for unmodified potential
bob2=fopen('log.compressmishmod','r'); 
bob3=fopen('log.mishB2','r'); 
% 1     2    3    4   5     6   7    8      9    10   11
%step, pot, ken, temp,vol, press, pxx, pyy, pzz
form='%f %f %f %f %f %f %f %f %f %f'; 
mish=textscan(bob,form,1000);
mish=cell2mat(mish); 
Pmish=mish(:,6); 
Vmish=mish(:,5); 
Pmish=Pmish/10^6; %go from bars to Mbars
Vmish=Vmish/Vmish(1); %normalize to starting volume for comparision
mish=textscan(bob2,form,1000);
mish=cell2mat(mish); 
Pmodmish=mish(:,6); 
Vmodmish=mish(:,5);
Pmodmish=Pmodmish/10^6; %go from bars to Mbars
Vmodmish=Vmodmish/Vmodmish(1);
mish=textscan(bob3,form,1000);
mish=cell2mat(mish); 
Pnmodmish=mish(:,6); 
Vnmodmish=mish(:,5); 
Pnmodmish=Pnmodmish/10^6; %go from bars to Mbars
Vnmodmish=Vnmodmish/Vnmodmish(1);

%Rose fit to P,V data

Ecoh=4.45*1.602*10^-19; 
B=181*10^9; 
a0=3.52*10^-10; 

V2=0.2:0.001:1;
V0=a0^3*4/3*pi; 
V2=V2*V0; 
P2=V2; 
s=size(V2);
s=s(1,2); 

L=(4*Ecoh/B/a0/(9))^(1/2); 
min=20; 
max=0; 

for n=1:1:s

    a=(3/(4*pi))^(1/3)/L*( (V2(1,n))^(1/3)-V0^(1/3) ); 
    if(n==1)
        disp('min scaled distance')
        disp(a); 
    end
    P2(1,n)=-3*B*((V2(1,n)/V0)^(1/3)-1)/(V2(1,n)/V0)^(2/3)*exp(-a)*(1-0.15*a+0.05*a^2); 
    P2(1,n)=P2(1,n)/10^11; %convert to Mbars
    
end
V2=V2/V0; 

figure;
plot(V2,P2); 
hold on; 
plot(V,P,'ob','MarkerSize', 5);
hold on; 
plot(Vmish,Pmish,'.c', 'MarkerSize', 5); 
hold on; 
plot(Vmodmish,Pmodmish,'.g', 'MarkerSize', 5); 
hold on; 
plot(Vnmodmish,Pnmodmish,'.r', 'MarkerSize', 5); 
legend('Rose Fit','Experiment', 'Mishin (Ni3Al Ni-Ni)', ' Final Mod','Mishin (NiAl Ni-Ni)' ); 
xlabel('Relative Volume (V/V0)'); 
title('Pressure vs. Volume ')
ylabel('Pressure (MBar)'); 
ylim([0 60]); 
xlim([0.30 1]); 

figure;
plot(V2,P2); 
hold on; 
plot(V,P,'ob','MarkerSize', 5);
hold on; 
plot(Vmish,Pmish,'.c', 'MarkerSize', 5); 
hold on; 
plot(Vmodmish,Pmodmish,'.g', 'MarkerSize', 5); 
hold on; 
plot(Vnmodmish,Pnmodmish,'.r', 'MarkerSize', 5); 
legend('Rose Fit','Experiment', 'Mishin (Ni3Al Ni-Ni)', ' Final Mod','Mishin (NiAl Ni-Ni)' ); 
xlabel('Relative Volume (V/V0)'); 
title('Pressure vs. Volume ')
ylabel('Pressure (MBar)'); 
ylim([0 1.5]); 
xlim([0.70 1]); 

fclose(bob); 
fclose(bob2);
%fclose(bob3); 

