#!/bin/sh
#PBS -M rma@ifi.unicamp.br
#PBS -m abe
#PBS -N one_Sphere_80
#PBS -e esfera.err
#PBS -o esfera.out
#PBS -q auger
#PBS -l nodes=1:ppn=1




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



#Inicio do script

source /home/drc01/kemp/rma/CRPropa-Rafa/ExportMe

cd  /home/drc01/kemp/rma/CARLOS/git/IC_project/python_code/simulations

exec_python="/home/drc01/kemp/rma/CRPropa-Rafa/Python-3.8.2/build/bin/python3.8"

$exec_python oneSphereEmission.py 100000 1 80  
