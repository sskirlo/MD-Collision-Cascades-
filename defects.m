fp=fopen('defects.txt','w'); 

%program goes through and tests energies of adding different defects to
%representative cell and see if decreases system energy

%we want to search x y grid of unique displacements and map gamma surface
a0=3.571; 
y=1; 
x=(1+8^2)^(1/2); 
%we want equal resolution in x,y directions
res=0.1; 



%fprintf(fp,'atom_style	atomic \n'); 
%fprintf(fp,'echo            log \n'); 
%fprintf(fp,'dimension	3 \n'); 
%fprintf(fp,'boundary        p p p \n'); 
%fprintf(fp,'units           metal \n'); 
%fprintf(fp,'atom_style	atomic \n'); 
%fprintf(fp,'neighbor        2.0 bin \n'); 
%fprintf(fp,'neigh_modify    every 1 delay 0 check yes \n'); 
fprintf(fp,'lattice         fcc 3.571 \n'); 
fprintf(fp,'read_restart       anneal501001.restart \n');
%fprintf(fp,'region          box block 0 20.0 0 20.0 0 60.0 \n'); 
%fprintf(fp,'read_data       50100.data \n'); 
fprintf(fp,'pair_style	eam/alloy \n'); 
fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n'); 

fprintf(fp,'run 1 \n'); 

%fprintf(fp,'group blocky id <= 74880  \n'); 
%fprintf(fp,'displace_atoms blocky move 17.497 0.0 0.0  \n \n');

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

fprintf(fp,'write_restart defect.restart \n');
fprintf(fp,'clear \n'); 

step=10000; 
ni=[76123,76125,76127,76128,77880,77884,77888,77892,76120,76122,76124,76126,74304,74302,74300,74298,74296,74292,74288,74284,74295,74291,74287,74283];
s=size(ni); 
sni=s(1,2); 
al=[77883,77887,77891,77895,74303,74301,74299,74297];
s=size(al); 
sal=s(1,2);
disp('size of id arrays'); 
disp(size(ni)); 
disp(size(al)); 
x1=0; 
x2=0; %choose gamma surface minimum
x3=0; 
t=[ni al]; 
s=size(t); 
s=s(1,2); 
type=50; 

for n1=1:1:s
   for n2=1:1:2
    
        fprintf(fp,'\n'); 
        fprintf(fp,'lattice fcc 3.571 \n'); 
        fprintf(fp,'units           metal \n');
        fprintf(fp,'region  box block 0 20.0 0 20.0 0 68.0 \n'); 
        fprintf(fp,'read_restart defect.restart \n'); 
        fprintf(fp,'pair_style	eam/alloy \n'); 
        fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n');
        fprintf(fp,'thermo          1000 \n');
        fprintf(fp,'thermo_style    custom step pe ke etotal temp vol press pxx pyy pzz \n'); 
        %fprintf(fp,'group blocky id <= 59820 \n');
        %fprintf(fp,'displace_atoms blocky move %f %f %f \n',x1,x2,x2); 
        
        id=t(1,n1); 
        disp('id of atom'); 
        disp(id);  
        fprintf(fp,'\n'); 
        fprintf(fp,'group at id == %d \n',id);
        if(n2==1)
            fprintf(fp,'delete_atoms group at \n'); 
        else
            if(n1<=sni)
                type=1; 
            else
                type=2; 
            end
            fprintf(fp,'set atom %d type %d \n',id,type); 
        end
       
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
        fprintf(fp,['reset_timestep ',a,' \n']); 
        
        fprintf(fp,'compute pen all pe/atom \n');
        string=['dump snap all cfg 1 gamma',a,'*.dump.gz id type xs ys zs xs ys zs xs id xs ys zs c_pen \n']; 
        fprintf(fp,string);  
        fprintf(fp,'dump_modify snap element Al Ni \n');
        
        fprintf(fp,'thermo 1 \n');
        fprintf(fp,'# %d \n',step);  %use this as marker 
        fprintf(fp,'run 1  \n');
        fprintf(fp,'clear \n');
        step=step+1; 

    end
end

disp('steps'); 
disp(step); 

fclose(fp); 