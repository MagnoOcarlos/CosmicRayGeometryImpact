#!/bin/sh
#PBS -M rma@ifi.unicamp.br
#PBS -m abe
#PBS -N new_B_and_R
#PBS -e esfera.err
#PBS -o esfera.out
#PBS -q serial
#PBS -l nodes=1:ppn=12




. /etc/profile.d/modules.sh

module load compiler/gcc/8.2.0
source /home/sw/intel/bin/compilervars.sh intel64
source /home/sw/intel/composer_xe_2015/mkl/bin/mklvars.sh intel64
. /home/sw/intel/impi/5.1.2.150/bin64/mpivars.sh
export INTEL_LICENSE_FILE=/opt/intel/composerxe-2011.0.084/licenses:/opt/intel/l
icenses:/home/cc/fandri/intel/licenses:/opt/intel/composer_xe_2011_sp1.6.233/lic
enses:/opt/intel/licenses:/home/cc/fandri/intel/licenses
export I_MPI_HYDRA_BOOTSTRAP=rsh
export I_MPI_DEVICE=rdssm

#activing the miniconda 
echo $PWD

source CARLOS/exportconda

conda activate crpropa_magno
export PYTHONPATH=/home/drc01/kemp/rma/CARLOS/CRPropa3/build:$PYTHONPATH
cd CARLOS/CosmicRayGeometryImpact/src/simulations

which python
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
