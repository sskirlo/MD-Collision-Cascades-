fp=fopen('ints.txt','w'); 

%program goes through and tests energies of adding different defects to
%representative cell and see if decreases system energy

%fprintf(fp,'atom_style	atomic \n'); 
%fprintf(fp,'echo            log \n'); 
%fprintf(fp,'dimension	3 \n'); 
%fprintf(fp,'boundary        p p p \n'); 
%fprintf(fp,'units           metal \n'); 
%fprintf(fp,'atom_style	atomic \n'); 
%fprintf(fp,'neighbor        2.0 bin \n'); 
%fprintf(fp,'neigh_modify    every 1 delay 0 check yes \n'); 
fprintf(fp,'lattice         fcc 3.571 \n'); 
%fprintf(fp,'read_data       anneal501001.data \n');
%fprintf(fp,'region          box block 0 20.0 0 20.0 0 60.0 \n'); 
fprintf(fp,'read_restart       anneal501001.restart \n'); 
fprintf(fp,'pair_style	eam/alloy \n'); 
fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n'); 

%fprintf(fp,'group blocky id <= 74880  \n'); 
%fprintf(fp,'displace_atoms blocky move 17.497 0.0 0.0  \n \n');

%fprintf(fp,'region tg block 0.0 87.0 0.0 87.0 0.0 156.159 units box \n'); 
%fprintf(fp,'region bg block 0.0 87.0 0.0 87.0 156.160 320.32 units box \n \n');
        
%fprintf(fp,'fix 1 all aveforce 0.0 0.0 0.0 region tg \n'); 
%fprintf(fp,'fix 2 all aveforce 0.0 0.0 0.0 region bg \n'); 
%fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'unfix 1 \n'); 
%fprintf(fp,'unfix 2 \n'); 
%fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'fix bob2 all box/relax x 0.0 y 0.0 z 0.0 \n'); 
%fprintf(fp,'minimize 1.0E-08 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'unfix bob2 \n \n'); 
%fprintf(fp,'fix 1 all aveforce 0.0 0.0 0.0 region tg \n'); 
%fprintf(fp,'fix 2 all aveforce 0.0 0.0 0.0 region bg \n'); 
%fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'unfix 1 \n'); 
%fprintf(fp,'unfix 2 \n '); 
%fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'fix bob2 all box/relax x 0.0 y 0.0 z 0.0 \n'); 
%fprintf(fp,'minimize 1.0E-10 1.0E-04 2000 20000 \n'); 
%fprintf(fp,'unfix bob2 \n \n'); 
%fprintf(fp,'minimize 1.0E-10 1.0E-4 2000 10000 \n \n');

fprintf(fp,'write_restart ints.restart \n');
fprintf(fp,'clear \n'); 

step=10000; 

for n1=1:1:8
   for n2=1:1:2
    
        fprintf(fp,'\n'); 
        fprintf(fp,'lattice fcc 3.571 \n'); 
        fprintf(fp,'units           metal \n');
        fprintf(fp,'region  box block 0 20.0 0 20.0 0 68.0 \n'); 
        fprintf(fp,'read_restart ints.restart \n'); 
        fprintf(fp,'pair_style	eam/alloy \n'); 
        fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n');
        fprintf(fp,'thermo          1000 \n');
        fprintf(fp,'thermo_style    custom step pe ke etotal temp vol press pxx pyy pzz \n'); 
        %fprintf(fp,'group blocky id <= 59820 \n');
        %fprintf(fp,'displace_atoms blocky move %f %f %f \n',x1,x2,x2); 
             
        fprintf(fp,'region tg block 0.0 87.0 0.0 87.0 0.0 136.159 units box \n'); 
        fprintf(fp,'region bg block 0.0 87.0 0.0 87.0 136.160 280.32 units box \n \n');
        
        if(n2==1)
            fprintf(fp,'region int block %f %f 0.0 0.5 135.16 135.66 units box \n',20,21);
            fprintf(fp,'create_atoms 1 region int \n');   %place atoms at 1st lattice site it region
        else
            fprintf(fp,'region int block %f %f 0.0 0.5 135.16 135.66 units box \n',22,23);
            fprintf(fp,'create_atoms 2 region int \n'); 
        end
        fprintf(fp,'set atom 149761 x %f y 0.25 z 135.3 \n',20+3.571*n1); 
        
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
        %fprintf(fp,['reset_timestep ',a,' \n']); 
        
        fprintf(fp,'compute pen all pe/atom \n');
        string=['dump snap all cfg 1 inter*',a,'.dump.gz id type xs ys zs xs ys zs xs id xs ys zs c_pen \n']; 
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