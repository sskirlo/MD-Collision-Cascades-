
fp=fopen('gamman','w'); 

%we want to search x y grid of unique displacements and map gamma surface
a0=3.571; 
y=1; 
x=(1+8^2)^(1/2); 
%we want equal resolution in x,y directions
res=0.1; 

name='50100';

fprintf(fp,'atom_style	atomic \n'); 
fprintf(fp,'echo            log \n'); 
fprintf(fp,'dimension	3 \n'); 
fprintf(fp,'boundary        p p p \n'); 
fprintf(fp,'units           metal \n'); 
fprintf(fp,'atom_style	atomic \n'); 
fprintf(fp,'neighbor        2.0 bin \n'); 
fprintf(fp,'neigh_modify    every 1 delay 0 check yes \n'); 
fprintf(fp,'lattice         fcc 3.571 \n'); 
fprintf(fp,['read_data ',name,'.data \n']); 
fprintf(fp,'pair_style	eam/alloy \n'); 
fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n'); 
fprintf(fp,['write_restart ', name,'.restart \n']);

 

%test to make sure deleting proper regions
%fprintf(fp,'dump snap all cfg 1 gamma*.dump id type xs ys zs xs ys zs xs id \n');  
%fprintf(fp,'dump_modify snap element Al Ni \n'); 
%fprintf(fp,'run 1  \n');
%fprintf(fp,'region t block 0.0 25.0 0.0 25.0 64.0 68.0 \n'); 
%fprintf(fp,'region b block 0.0 25.0 0.0 25.0 0.0 3.0 \n'); 
%fprintf(fp,'group top region t \n'); 
%fprintf(fp,'group bottom region b \n');
%fprintf(fp,'group bottom delete \n'); 
%fprintf(fp,'group top delete \n'); 
%fprintf(fp,'run 1  \n');
fprintf(fp,'clear \n');

%100100
if(strcmp(name,'100100')==1)
    dispxs=[0.5,1.5,1.9,2.9,3.9,4.9,5.8,6.3,7.2,1.0,2.0,2.4,3.4,4.4,5.4,5.8,6.8,7.8]; 
    dispys=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5]; 
end    
    
if(strcmp(name,'5050')==1)
    dispxs=[0.4,1.5,2.4,2.9,3.8,4.8,5.8,6.8,7.2,1.0,2.0,3.4,4.3,5.3,6.3,7.7]; 
    dispys=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5,0.5,0.5,0.5,0.5,0.5]; 
end

if(strcmp(name,'50100')==1)
    dispxs=[4.9,0.5,1.5,2.9,3.8,5.8,7.2,1.0,2.0,2.4,3.4,4.4,5.4,6.3,6.8,7.7]; 
    dispys=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5]; 
end

%for n1=1:1:4 
s=size(dispxs);
s=s(1,2); 
step=1; 
for n1=1:1:s
    %for n2=0:1:x/res
        fprintf(fp,'\n'); 
        fprintf(fp,'lattice fcc 3.571 \n'); 
        fprintf(fp,'units           metal \n');
        fprintf(fp,['read_restart ',name ,'.restart \n']); 
        fprintf(fp,'pair_style	eam/alloy \n'); 
        fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n');
        fprintf(fp,'thermo          1000 \n');
        fprintf(fp,'thermo_style    custom step pe ke etotal temp vol press pxx pyy pzz \n');
      
        % 74736, 5050  74880, 50100   74880, 100100
        if(strcmp('5050',name)==1)
            fprintf(fp,'group blocky id <= 74736 \n');
        else
            fprintf(fp,'group blocky id <= 74880 \n');
        end
        %fprintf(fp,'run 1  \n');
        fprintf(fp,'displace_atoms blocky move %f %f 0.0 \n \n',dispxs(n1)*a0,dispys(n1)*a0); %dispxs(n1)*a0,dispys(n1)*a0); %res*a0*n2,res*a0*n1);
        disp(dispxs(n1));
        disp(dispys(n1)); 
        %fprintf(fp,'fix fp all setforce 0.0 0.0 NULL \n');  %if commented
        %out allows full minimization, with ends constrained
        %fprintf(fp,'region t block 0.0 87.0 0.0 87.0 220.0 235.0 units box \n'); 
        %fprintf(fp,'region b block 0.0 87.0 0.0 87.0 0.0 15.0 units box \n'); 
        %fprintf(fp,'group top region t \n'); 
        %fprintf(fp,'group bottom region b \n'); 
        %fprintf(fp,'fix fp1 top setforce 0.0 0.0 0.0 \n'); 
        %fprintf(fp,'fix fp2 bottom setforce 0.0 0.0 0.0 \n'); 
        %fprintf(fp,'fix bob2 all box/relax x 0.0 y 0.0 \n'); 
        %fprintf(fp,'delete_atoms group bottom \n'); 
        %fprintf(fp,'delete_atoms group top \n');  
        
        fprintf(fp,'region tg block 0.0 87.0 0.0 87.0 0.0 136.159 units box \n'); 
        fprintf(fp,'region bg block 0.0 87.0 0.0 87.0 136.160 280.32 units box \n \n');
        
        fprintf(fp,'fix 1 all aveforce 0.0 0.0 0.0 region tg \n'); 
        fprintf(fp,'fix 2 all aveforce 0.0 0.0 0.0 region bg \n'); 
        fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'unfix 1 \n'); 
        fprintf(fp,'unfix 2 \n'); 
        fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'fix bob2 all box/relax x 0.0 y 0.0 z 0.0 \n'); 
        fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'unfix bob2 \n \n'); 
        fprintf(fp,'fix 1 all aveforce 0.0 0.0 0.0 region tg \n'); 
        fprintf(fp,'fix 2 all aveforce 0.0 0.0 0.0 region bg \n'); 
        fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'unfix 1 \n'); 
        fprintf(fp,'unfix 2 \n '); 
        fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'fix bob2 all box/relax x 0.0 y 0.0 z 0.0 \n'); 
        fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
        fprintf(fp,'unfix bob2 \n \n'); 
        fprintf(fp,'minimize 1.0E-10 1.0E-4 2000 10000 \n \n');
        
        a=sprintf('%d',step); 
        %fprintf(fp,'compute pen all pe/atom \n');
        %string=['dump snap all cfg 1 gamma*',name,a, '.dump id type xs ys zs xs ys zs xs id xs ys zs c_pen \n']; 
        %fprintf(fp,string);  
        %fprintf(fp,'dump_modify snap element Al Ni \n'); 
        fprintf(fp,['write_restart ', name,a,'.restart \n']);
        fprintf(fp,'thermo 1 \n');
        fprintf(fp,'# %d \n',step);  %use this as marker 
        fprintf(fp,'run 1  \n');
        fprintf(fp,'clear \n');
        step=step+1; 
    %end
end

disp('steps'); 
disp(step); 

fclose(fp); 