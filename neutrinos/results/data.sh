a=1
z=1

for lc in 1.0 
do
        for R in 100 200 250 500 #1000
        do
                for B in 0.1  0.01 0.0001
                do
                       	cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-CR_2.txt >> sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-CR.txt
                       	cat sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-NU_2.txt >> sim-A_${a}_Z_${z}_R_${R}_Mpc_B_${B}nG_lc_${lc}Mpc-NU.txt
                done
        done
done