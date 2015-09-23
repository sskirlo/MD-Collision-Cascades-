close all; 
clear all; 



swit=0; %swit =1 if we want to plot phi instead of phi*r, just so can get a better impression

drho2=0.300*10^-3; 
dr2=0.5954*10^-3; 
r1=0:1:9999; 
r2=r1; 
r1=r1*drho2; 
r2=r2*dr2; 
r2=r2'; 
r1=r1'; 

bob3=fopen('NiAlB2.eam.alloy','r'); 

for y=1:1:6
    fgets(bob3); %copies over first 8 lines
end

F12=fscanf(bob3,'%f',10000);
%figure; 
%plot(r1,F12); 
ph12=fscanf(bob3,'%f ',10000);
%figure; 
%plot(r2,ph12); 
fgets(bob3); %get next formatting line
F22=fscanf(bob3,'%f',10000); 
ph22=fscanf(bob3,'%f',10000); 
%figure; 
%plot(r1,F22);
%figure;
%plot(r2,ph22); 
phi112=fscanf(bob3,'%f',10000); 
phi212=fscanf(bob3,'%f',10000); 
phi222=fscanf(bob3,'%f',10000); 

if(swit==1)
   for n=1:1:10000
      phi112(n)=phi112(n)/r2(n,1);  
      phi212(n)=phi212(n)/r2(n,1);
      phi222(n)=phi222(n)/r2(n,1);
   end
end

fclose(bob3);



bob=fopen('NiAl.eam.alloy.txt','r'); 
bob2=fopen('NiAl_mod.eam.alloy','w'); 

drho=0.69951*10^-3; 
dr=0.672488*10^-3; 
x1=0:1:9999; 
x2=x1; 
x1=x1*drho; 
x2=x2*dr; 
x2=x2'; 
x1=x1'; 

for y=1:1:6
    text=fgets(bob); %copies over first 8 lines
    fprintf(bob2,text); 
end

F1=fscanf(bob,'%f',10000);
figure; 
plot(x1,F1,'r'); 
hold on; 
plot(r1,F12,'b'); 

ph1=fscanf(bob,'%f ',10000);
figure; 
plot(x2,ph1,'r');
hold on; 
plot(r2,ph12,'b'); 

text=fgets(bob); %get next formatting line
fprintf(bob2,'%f \n',F1); 
fprintf(bob2,'%f \n',ph1);

fprintf(bob2,'%s ',text); %need this otherwise won't work

F2=fscanf(bob,'%f',10000); 
ph2=fscanf(bob,'%f',10000); 
fprintf(bob2,'%f \n',F2); 
fprintf(bob2,'%f \n',ph2);
figure; 
plot(x1,F2);
figure;
plot(x2,ph2); 
phi11=fscanf(bob,'%f',10000); 
phi21=fscanf(bob,'%f',10000); 
phi22=fscanf(bob,'%f',10000); 

disp('checking didnt overrun'); 
while(1==1) %use this code to make sure didn't miss anything
    text=fgets(bob); 
    a=sprintf('%s \n',text); 
    disp(a); 
    if(text==-1)
        disp('all data processed'); 
        break; 
    end
end
disp('final checks'); 
a=sprintf('%f last number \n',phi22(10000,1)); 
disp(a); 

disp(size(F1)); 
disp(size(F2)); 
disp(size(ph2)); 
disp(size(ph1)); 
disp(size(phi11)); 
disp(size(phi21)); 
disp(size(phi22)); 

%format of inner potential output is of form phi*r 

%create modified phi11 zbl potential
ctf=1/2*(3*pi/4)^(2/3); 
a0=0.5291772;
zni=28; 
zal=13; 
con=(8.9875518*10^9)*(10^10)*(1.60217646*10^-19); 
phiz11=ones(10000,1); 
for n=0:1:9999
    a=ctf*a0/(zni^(0.23)+zni^(0.23)); 
    r=n*dr; 
    screen=0.1818*exp(-3.2*r/a)+0.5099*exp(-0.9423*r/a)+0.2802*exp(-0.4028*r/a)+0.02817*exp(-0.2016*r/a); 
    phiz11(n+1)=zni*zni*con*screen; 
end
phiz21=ones(10000,1); 
for n=0:1:9999
    a=ctf*a0/(zal^(0.23)+zni^(0.23)); 
    r=n*dr; 
    screen=0.1818*exp(-3.2*r/a)+0.5099*exp(-0.9423*r/a)+0.2802*exp(-0.4028*r/a)+0.02817*exp(-0.2016*r/a); 
    phiz21(n+1)=zal*zni*con*screen; 
end
phiz22=ones(10000,1); 
for n=0:1:9999
    a=ctf*a0/(zal^(0.23)+zal^(0.23)); 
    r=n*dr; 
    screen=0.1818*exp(-3.2*r/a)+0.5099*exp(-0.9423*r/a)+0.2802*exp(-0.4028*r/a)+0.02817*exp(-0.2016*r/a); 
    phiz22(n+1)=zal*zal*con*screen; 
end

%creating spline functions
%need to calculate the derivatives of the functions
dphiz11=diff(phiz11);
dphiz11=dphiz11/dr; 
d2phiz11=diff(dphiz11);
d2phiz11=d2phiz11/dr; 
d3phiz11=diff(d2phiz11);
d3phiz11=d3phiz11/dr; 

dphi112=diff(phi112); 
dphi112=dphi112/dr2; 
d2phi112=diff(dphi112);
d2phi112=d2phi112/dr2; 
d3phi112=diff(d2phi112);
d3phi112=d3phi112/dr2; 
na1=floor(0.5/dr);
na2=floor(1.5/dr2);%3200; %cutoff distances for spline
ra=x2(na1,1); 
rb=r2(na2,1); 
g=sprintf('cuttoffs are %f %f for phi11 \n',ra,rb); 
disp(g); 
%we want to increase from 4 to 6 by 6, for smoother fit
M=[ra 1  1/ra    1/ra^2    1/ra^3    1/ra^4   1/ra^5      1/ra^6;      rb 1 1/rb 1/rb^2 1/rb^3 1/rb^4 1/rb^5 1/rb^6;
   1  0 -1/ra^2  -2/ra^3  -3/ra^4   -4/ra^5   -5/ra^6    -6/ra^7;      1 0 -1/rb^2 -2/rb^3 -3/rb^4 -4/rb^5 -5/rb^6 -6/rb^7; 
   0  0  2/ra^3  6/ra^4   12/ra^5   20/ra^6   30/ra^7    42/ra^8;      0 0 2/rb^3 6/rb^4 12/rb^5 20/rb^6 30/rb^7 42/rb^8; 
   0  0 -6/ra^4  -24/ra^5 -60/ra^6  -120/ra^7 -210/ra^8  -(42*8)/ra^9; 0 0 -6/rb^4 -24/rb^5 -60/rb^6 -120/rb^7 -210/rb^8 -(42*8)/rb^9 ];

%M=[ra^3   ra^2  ra 1  1/ra    1/ra^2    1/ra^3    1/ra^4   ;      rb^3   rb^2  rb 1  1/rb    1/rb^2    1/rb^3    1/rb^4;
% 3*ra^2 2*ra  1  0 -1/ra^2  -2/ra^3  -3/ra^4   -4/ra^5   ;     3*rb^2 2*rb  1  0 -1/rb^2  -2/rb^3  -3/rb^4   -4/rb^5 ; 
% 6*ra   2     0  0   2/ra^3  6/ra^4   12/ra^5   20/ra^6   ;     6*rb   2     0  0   2/rb^3  6/rb^4   12/rb^5   20/rb^6 ; 
% 6      0     0  0 -6/ra^4  -24/ra^5 -60/ra^6  -120/ra^7 ;      6       0    0   0  -6/rb^4  -24/rb^5  -60/rb^6   -120/rb^7 ];

phis=[phiz11(na1);phi112(na2);dphiz11(na1);dphi112(na2);d2phiz11(na1);d2phi112(na2);d3phiz11(na1);d3phi112(na2)]; %get join params 
a=inv(M)*phis; 
%convert NiAl distance to ZBL distance
na2=floor(1.5/dr); 
splice11=ones((na2-na1),1); 
for n=1:1:(na2-na1)  %create splice part of function, based on fitting params
    r=x2(na1+n-1,1); 
    splice11(n,1)=(a(1)*r+a(2)*1+a(3)*1/r+a(4)*1/r^2+a(5)*1/r^3+a(6)*1/r^4+a(7)*1/r^5+a(8)*1/r^6); 
    if(swit==1)
       splice11(n,1)=splice11(n,1)/r; 
    end
end

%splice for joining Mishin NiAl potential to Mishin Ni3Al potential for Ni-Ni 
dphi11=diff(phi11); 
dphi11=dphi11/dr; 
d2phi11=diff(dphi11);
d2phi11=d2phi11/dr; 
d3phi11=diff(d2phi11);
d3phi11=d3phi11/dr; 

na2a=floor(2.2/dr); %based on NiAl potential
na1a=floor(1.8/dr2);  %based on Ni3Al potential
ra=r2(na1a,1); 
rb=x2(na2a,1); 

M=[ra 1  1/ra    1/ra^2    1/ra^3    1/ra^4   1/ra^5      1/ra^6;      rb 1 1/rb 1/rb^2 1/rb^3 1/rb^4 1/rb^5 1/rb^6;
   1  0 -1/ra^2  -2/ra^3  -3/ra^4   -4/ra^5   -5/ra^6    -6/ra^7;      1 0 -1/rb^2 -2/rb^3 -3/rb^4 -4/rb^5 -5/rb^6 -6/rb^7; 
   0  0  2/ra^3  6/ra^4   12/ra^5   20/ra^6   30/ra^7    42/ra^8;      0 0 2/rb^3 6/rb^4 12/rb^5 20/rb^6 30/rb^7 42/rb^8; 
   0  0 -6/ra^4  -24/ra^5 -60/ra^6  -120/ra^7 -210/ra^8  -(42*8)/ra^9; 0 0 -6/rb^4 -24/rb^5 -60/rb^6 -120/rb^7 -210/rb^8 -(42*8)/rb^9 ];
phis=[phi112(na1a);phi11(na2a);dphi112(na1a);dphi11(na2a);d2phi112(na1a);d2phi11(na2a);d3phi112(na1a);d3phi11(na2a)];
a=inv(M)*phis; 
%need to fill in fraction based on Ni3Al lengths
na1a=ceil(1.8/dr); 
splice11a=ones((na2a-na1a),1); 
for n=1:1:(na2a-na1a)  %create splice part of function, based on fitting params
    r=x2(na1a+n-1,1); 
    splice11a(n,1)=(a(1)*r+a(2)*1+a(3)*1/r+a(4)*1/r^2+a(5)*1/r^3+a(6)*1/r^4+a(7)*1/r^5+a(8)*1/r^6); 
    if(swit==1)
       splice11a(n,1)=splice11a(n,1)/r; 
    end
end

%need to extrapolate points from NiAl result into same scale as Ni3Al

%indmax=0; 
%disp('size r2'); 
%disp(size(r2));
%for n=2:10000
 %   ind=ceil(r2(n,1)/dr); 
 %   phi112p(ind,1)=phi112(n,1); %read points into rescaled positions
 %   if(ind>indmax)
 %       indmax=ind; 
 %   end
indmax=floor(10000*dr2/dr); 
phi112p=interp1(r2,phi112,x2(1:indmax)); 
 
%disp(size(r2)); 
figure; 
plot(r2,phi112, 'b', x2(1:indmax),phi112p(1:indmax),'r'); 
title('phill2p and phill2'); 

%construct final potential for Ni-Ni interaction
fphi11=ones(10000,1); 
fphi11(1:na1,1)=phiz11(1:na1,1); 
fphi11(na1:(na2-1),1)=splice11(1:(na2-na1),1);
fphi11(na2:(na1a-1),1)=phi112p(na2:(na1a-1),1); 
fphi11(na1a:na2a-1,1)=splice11a(1:(na2a-na1a),1); 
fphi11(na2a:10000,1)=phi11(na2a:10000,1); 

if(swit==1)
   for n=1:1:10000
      phi11(n)=phi11(n)/x2(n,1);  
      phiz11(n)=phiz11(n)/x2(n,1);
   end
end

dphiz21=diff(phiz21);
dphiz21=dphiz21/dr; 
d2phiz21=diff(dphiz21);
d2phiz21=d2phiz21/dr; 
d3phiz21=diff(d2phiz21);
d3phiz21=d3phiz21/dr; 
dphi21=diff(phi21); 
dphi21=dphi21/dr; 
d2phi21=diff(dphi21);
d2phi21=d2phi21/dr; 
d3phi21=diff(d2phi21);
d3phi21=d3phi21/dr; 
nb1=floor(0.8/dr);
nb2=floor(1.8/dr);%3200; %cutoff distances for spline
ra=x2(nb1,1); 
rb=x2(nb2,1); 
g=sprintf('cuttoffs are %f %f for phi21 \n',ra,rb); 
disp(g); 
M=[ra 1  1/ra    1/ra^2    1/ra^3    1/ra^4   1/ra^5      1/ra^6;      rb 1 1/rb 1/rb^2 1/rb^3 1/rb^4 1/rb^5 1/rb^6;
   1  0 -1/ra^2  -2/ra^3  -3/ra^4   -4/ra^5   -5/ra^6    -6/ra^7;      1 0 -1/rb^2 -2/rb^3 -3/rb^4 -4/rb^5 -5/rb^6 -6/rb^7; 
   0  0  2/ra^3  6/ra^4   12/ra^5   20/ra^6   30/ra^7    42/ra^8;      0 0 2/rb^3 6/rb^4 12/rb^5 20/rb^6 30/rb^7 42/rb^8; 
   0  0 -6/ra^4  -24/ra^5 -60/ra^6  -120/ra^7 -210/ra^8  -(42*8)/ra^9; 0 0 -6/rb^4 -24/rb^5 -60/rb^6 -120/rb^7 -210/rb^8 -(42*8)/rb^9 ];
phis=[phiz21(nb1);phi21(nb2);dphiz21(nb1);dphi21(nb2);d2phiz21(nb1);d2phi21(nb2);d3phiz21(nb1);d3phi21(nb2)]; %get join params 
a=inv(M)*phis; 
splice21=ones((nb2-nb1),1); 
for n=1:1:(nb2-nb1)  %create splice part of function, based on fitting params
    r=x2(nb1+n-1,1); 
    splice21(n,1)=(a(1)*r+a(2)*1+a(3)*1/r+a(4)*1/r^2+a(5)*1/r^3+a(6)*1/r^4+a(7)*1/r^5+a(8)*1/r^6); 
    if(swit==1)
       splice21(n,1)=splice21(n,1)/r; 
    end
end
fphi21=ones(10000,1); 
fphi21(1:nb1,1)=phiz21(1:nb1,1); 
fphi21(nb1:nb2-1,1)=splice21(1:(nb2-nb1),1); 
fphi21(nb2:10000,1)=phi21(nb2:10000,1); 
if(swit==1)
   for n=1:1:10000
      phi21(n)=phi21(n)/x2(n,1);  
      phiz21(n)=phiz21(n)/x2(n,1);
   end
end


dphiz22=diff(phiz22);
dphiz22=dphiz22/dr; 
d2phiz22=diff(dphiz22);
d2phiz22=d2phiz22/dr; 
d3phiz22=diff(d2phiz22);
d3phiz22=d3phiz22/dr; 
dphi22=diff(phi22); 
dphi22=dphi22/dr; 
d2phi22=diff(dphi22);
d2phi22=d2phi22/dr; 
d3phi22=diff(d2phi22);
d3phi22=d3phi22/dr; 
nc1=floor(0.8/dr);
nc2=floor(1.8/dr);%3200; %cutoff distances for spline
ra=x2(nc1,1); 
rb=x2(nc2,1); 
g=sprintf('cuttoffs are %f %f for phi22 \n',ra,rb); 
disp(g); 
M=[ra 1  1/ra    1/ra^2    1/ra^3    1/ra^4   1/ra^5      1/ra^6;      rb 1 1/rb 1/rb^2 1/rb^3 1/rb^4 1/rb^5 1/rb^6;
   1  0 -1/ra^2  -2/ra^3  -3/ra^4   -4/ra^5   -5/ra^6    -6/ra^7;      1 0 -1/rb^2 -2/rb^3 -3/rb^4 -4/rb^5 -5/rb^6 -6/rb^7; 
   0  0  2/ra^3  6/ra^4   12/ra^5   20/ra^6   30/ra^7    42/ra^8;      0 0 2/rb^3 6/rb^4 12/rb^5 20/rb^6 30/rb^7 42/rb^8; 
   0  0 -6/ra^4  -24/ra^5 -60/ra^6  -120/ra^7 -210/ra^8  -(42*8)/ra^9; 0 0 -6/rb^4 -24/rb^5 -60/rb^6 -120/rb^7 -210/rb^8 -(42*8)/rb^9 ];
phis=[phiz22(nc1);phi22(nc2);dphiz22(nc1);dphi22(nc2);d2phiz22(nc1);d2phi22(nc2);d3phiz22(nc1);d3phi22(nc2)]; %get join params 
a=inv(M)*phis; 
splice22=ones((nc2-nc1),1); 
for n=1:1:(nc2-nc1)  %create splice part of function, based on fitting params
    r=x2(nc1+n-1,1); 
    splice22(n,1)=(a(1)*r+a(2)*1+a(3)*1/r+a(4)*1/r^2+a(5)*1/r^3+a(6)*1/r^4+a(7)*1/r^5+a(8)*1/r^6); 
    if(swit==1)
       splice22(n,1)=splice22(n,1)/r; 
    end
end
fphi22=ones(10000,1); 
fphi22(1:nc1,1)=phiz22(1:nc1,1); 
fphi22(nc1:(nc2-1),1)=splice22(1:(nc2-nc1),1); 
fphi22(nc2:10000,1)=phi22(nc2:10000,1); 
if(swit==1)
   for n=1:1:10000
      phi22(n)=phi22(n)/x2(n,1);  
      phiz22(n)=phiz22(n)/x2(n,1);
   end
end

d1=floor(1.5/dr2); 
d2=floor(2.0/dr2); 
figure; 
plot(x2(1:na1),phiz11(1:na1),'b',x2(na1:(na2-1),1),splice11(1:(na2-na1),1),'c',x2(na2:(na1a-1)),phi112p(na2:(na1a-1)),'r'); 
hold on; 
plot(x2(na1a:(na2a-1),1),splice11a(1:(na2a-na1a),1),'c',x2,phi11,'g');
title('Pair Potential for Ni-Ni'); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)*R'); 
%legend('ZBL','Spline1','Mishin (NiAl)', 'Spline2','Mishin (Ni3Al)' );
%ylim([-5,40]); 
xlim([1.6,2.2]); 
set(gcf, 'PaperPositionMode', 'auto');
print(['nini1','.eps'],'-depsc2'); 
ylim([-5,40]); 
xlim([0,4]); 
set(gcf, 'PaperPositionMode', 'auto');
print(['nini2','.eps'],'-depsc2'); 
ylim([0,1300]); 
xlim([0.3,0.7]);
set(gcf, 'PaperPositionMode', 'auto');
print(['nini3','.eps'],'-depsc2'); 

phin11=ones(10000,1); 
for n=1:1:10000
    phin11(n,1)=phiz11(n,1)/x2(n,1); %put into proper potential form
end

figure; 
%plot(x2(r1:r2),phin11(r1:r2),'b'); 
plot(x2,fphi11,'r'); 
title('fphi11'); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)'); 
%ylim([-5,20]);
xlim([1.0,3]);
%xlim([0.3,0.8]); 

figure;
plot(x2(1:nb1),phiz21(1:nb1),'b',x2,phi21,'r',x2(nb1:(nb2-1),1),splice21(1:(nb2-nb1),1),'g');
title('Pair Potential for Ni-Al'); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)');  
legend('ZBL','Mishin', 'Spline');
ylim([-5,100]);

phin21=ones(10000,1); 
for n=1:1:10000
    phin21(n,1)=phiz21(n,1)/x2(n,1); %put into proper potential form
end

figure; 
%plot(x2(r1:r2),phin21(r1:r2),'b'); 
plot(x2,fphi21,'r');
title('fphi21'); 
ylim([-5,100]); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)'); 


figure;
plot(x2(1:nc1),phiz22(1:nc1),'b',x2,phi22,'r',x2(nc1:(nc2-1),1),splice22(1:(nc2-nc1),1),'g');
title('Pair Potential for Al-Al'); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)'); 
legend('ZBL','Mishin', 'Spline');
ylim([-5,15]);

phin22=ones(10000,1); 
for n=1:1:10000
    phin22(n,1)=phiz22(n,1)/x2(n,1); %put into proper potential form
end

figure; 
%plot(x2(r1:r2),phin22(r1:r2),'b'); 
plot(x2,fphi22,'r');
title('fphi22'); 
%ylim([-5,15]); 
xlabel('Distance (Ang)');
ylabel('Energy (eV)'); 
ylim([-5,15]);

%put new potentials in modified document
disp(size(fphi11)); 
disp(size(fphi21)); 
disp(size(fphi22)); 
fprintf(bob2,'%f \n',fphi11); 
fprintf(bob2,'%f \n',fphi21);
fprintf(bob2,'%f \n',fphi22); 

fclose(bob2);
fclose(bob);
