
%(1,1,0)=x1
%(1,-1,0)=y1

%(1,0,0)=x2
%(0,1,0)=y2

%program will return the dimensions for the top crystal and bottom crystal
%which will minimize strain energy, done by the number of lattice lengths
%in given direction

x1=[1 0 0];
x2=[1 1 0]; 
y1=[0 1 0]; 
y2=[1 -1 0]; 
%normalize unit vectors
x2=x2/dot(x2,x2)^(1/2); 
y2=y2/dot(y2,y2)^(1/2); 

size=60; %max number of atoms willing to fit in each direction
min1=1000; 
min2=1000; 
mem1=zeros(1,2); 
mem2=zeros(1,2); 
len1=abs(dot(x2,x1)); 
len2=abs(dot(y2,y1)); 

for n1=1:1:size
    for n2=1:1:size
        val1=abs(n1-len1*n2); 
        val2=abs(n1-len2*n2); 
        if(val1<min1)
            min1=val1; 
            mem1(1,1)=n1; 
            mem1(1,2)=n2; 
        end
        if(val2<min2)
            min2=val2; 
            mem2(1,1)=n1; 
            mem2(1,2)=n2; 
        end
    end
end

disp('results for x \n');
disp(mem1);
disp('results for y \n');
disp(mem2); 
