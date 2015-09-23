
        clear all; 
        close all; 

        name1={'50100','100100','5050'};
        
        %len=[16,16,18]; 
        %len=[3,3,5]; 
        %len1=[13,4,5]; 
        %len2=[5,6,13]; 
        %len3=[1,5,11,12,13]; 
        len=[1,1,1]; 
        len1=1; 
        len2=13; 
        len3=13; 
        
        %purpose of file is to read in restart files, to create files which
        %can be processed further
        
        fp=fopen('batchanneal','w'); 
        
        %for n1=1:3
         %   for n2=1:len(n1)
          %      if(n1==1)
          %          a=sprintf('%d',len1(n2));
          %      end
          %      if(n1==2)
          %          a=sprintf('%d',len2(n2));
          %      end
          %      if(n1==3)
          %          a=sprintf('%d',len3(n2));
          %      end
                
                %name=[char(name1(n1)), a];
                fprintf(fp,'\n'); 
                fprintf(fp,'lattice fcc 3.571 \n'); 
                fprintf(fp,'units           metal \n');
                fprintf(fp,['read_restart ','final' ,'.restart \n']); 
                fprintf(fp,'pair_style	eam/alloy \n'); 
                fprintf(fp,'pair_coeff	* * /home/sskirlo/potentials/NiAl_mod.eam.alloy Al Ni \n');
                fprintf(fp,'thermo          1000 \n');
                fprintf(fp,'thermo_style    custom step pe ke etotal temp vol press pxx pyy pzz \n');
                
                fprintf(fp,'reset_timestep 0 \n'); 
           
                fprintf(fp,'velocity all create 0.0 3052 dist gaussian \n'); 
                fprintf(fp,'velocity all zero linear \n'); 
                fprintf(fp,'fix joe all dt/reset 10 0.000001 0.001 0.005 units lattice #can assume 1 fs timestep \n'); 

                fprintf(fp,'fix bob all nph aniso 0.0 0.0 0.1 couple xy drag 2.5 \n'); %allow boundaries to relax

                T=0; 
                Tstep=40;
                fprintf(fp,'\n'); 
                for n=1:1:(800)/Tstep
                     fprintf(fp,'run 2000 pre no post no every 25 "velocity all scale %f" \n ',n*Tstep+T);
                end
                
                fprintf(fp,'thermo       10000 \n'); %print out 100 lines during anneal, can moniter
                fprintf(fp,'run 10000 pre no post no every 50 "velocity all scale 800" #anneal for 1 ps \n '); %anneal material for 1 ps
                
                Tstep=5; 
                for n=1:1:(800)/Tstep
                     fprintf(fp,'run 2000 pre no post no every 25 "velocity all scale %f" \n ',800-n*Tstep); 
                end
                fprintf(fp,'run 2000 pre no post no every 25 "velocity all scale %f" \n ',0); %stop at 0 K, so know what temperature its at

                fprintf(fp,['write_restart finalanneal','.restart \n']);
                fprintf(fp,'unfix bob \n'); 
                
                fprintf(fp,'compute pen all pe/atom \n');
                string=['dump snap all cfg 1 finalanneal*', '.dump.gz id type xs ys zs xs ys zs xs id xs ys zs c_pen \n']; 
                fprintf(fp,string);  
                fprintf(fp,'dump_modify snap element Al Ni \n');
                fprintf(fp,'thermo 1 \n');
                 %fprintf(fp,'# %d \n',step);  %use this as marker 
                fprintf(fp,'run 1  \n');
                fprintf(fp,'clear \n');
        
                
            %end
        %end
        
        fclose(fp); 