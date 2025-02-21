
conda activate crpropa_magno
export PYTHONPATH=../../../CRPropa3/build:$PYTHONPATH
#cd CARLOS/CosmicRayGeometryImpact/src/simulations

exec_python=python
a=1
z=1

for lc in 1.0 
do
        for R in 100 200 250 500 1000
        do
                for B in 0.1  0.01 0.0001
                do
                        $exec_python simulation_paris.py 100000 $lc $R $B 1 1

                        sed -i -e '/^#/d' sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed*-CR*

                        sed -i -e '/^#/d' sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed*-NU*

                       	cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed1-CR.txt > ../../neutrinos/results/sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-CR_2.txt
                       	cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed1-NU.txt > ../../neutrinos/results/sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-NU_2.txt

                        #rm  dados_nitro/dadosNitro_radius_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed1-CR.txt
                        
			#rm  dados_nitro/dadosNitro_radius_${R}_Mpc_${B}nG_lc_${lc}Mpc_seed1-NU.txt

                        cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed*-CR* >>../../neutrinos/results/sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-CR_2.txt
                        cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc_seed*-NU* >>../../neutrinos/results/sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-NU_2.txt

                        rm *.txt
                done
        done
done

