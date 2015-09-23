
        clear all; 
        close all; 

        name1={'50100','5050' ,'100100'};
        
        len=[16,16,18]; 

        %purpose of file is to read in restart files, to create files which
        %can be processed further
        
        fp=fopen('restartreader','w'); 
        
        for n1=1:3
            for n2=1:len(n1)
            
                a=sprintf('%d',n2); 
                name=[char(name1(n1)), a];
                fprintf(fp,'\n'); 
                fprintf(fp,'lattice fcc 3.571 \n'); 
                fprintf(fp,'units           metal \n');
                fprintf(fp,['read_restart ',name ,'.restart \n']); 
                fprintf(fp,'pair_style	eam/alloy \n'); 
                fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n');
                fprintf(fp,'thermo          1000 \n');
                fprintf(fp,'thermo_style    custom step pe ke etotal temp vol press pxx pyy pzz \n');
                
                fprintf(fp,'reset_timestep 0 \n'); 
                fprintf(fp,'compute pen all pe/atom \n');
                string=['dump snap all cfg 1 gamma*',name, '.dump.gz id type xs ys zs xs ys zs xs id xs ys zs c_pen \n']; 
                fprintf(fp,string);  
                fprintf(fp,'dump_modify snap element Al Ni \n'); 
                %fprintf(fp,['write_restart ', name,'.restart \n']);
                fprintf(fp,'thermo 1 \n');
               % fprintf(fp,'# %d \n',step);  %use this as marker 
                fprintf(fp,'run 1  \n');
                fprintf(fp,'clear \n');
        
            end
        end
        
        fclose(fp); 