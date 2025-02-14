exec_python=python
for lc in 1.0 
do
        for R in 100  200 #300 400 500 600 700 800 900 1000
        do
                for B in 0.1 0.0001
                do
                        $exec_python simulation_paris.py 10000 $lc $R $B

                       	cat sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_one_sphere_seed1-CR.txt >../neutrinos/results/sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc-CR.txt
                       	cat sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_one_sphere_seed1-NU.txt >../neutrinos/results/sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc-NU.txt

                        rm  dados_nitro/dadosNitro_radius_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed1-CR.txt
                        sed -i -e '/^#/d' sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed*-CR*
                        
			rm  dados_nitro/dadosNitro_radius_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed1-NU.txt
                        sed -i -e '/^#/d' sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed*-NU*

                        cat sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_one_sphere_seed*-CR* >>../neutrinos/results/sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc-CR.txt
                        cat sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc_one_sphere_seed*-NU* >>../neutrinos/results/sim-A_55_Z_26_R_${R}_Mpc_${B}nG_lc_${lc}Mpc-NU.txt

                        rm *.txt
                done
        done
done