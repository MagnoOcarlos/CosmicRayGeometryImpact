#!/bin/bash


home=$(echo $PWD)

cd ../plots_codes
plot=$(echo $PWD)
cd $home
echo $plot
pwd
#Parameters : $1: Cones' angle opening
function fixedAngleNitro(){
	#Angle's loop
for((j=0;j<=80;j=j+20))
do
	#loop of coherence length
	for l in 0.1 1.0 10.0
	do	
		#loop of Magnetic field strength 
		for k in  0.01 1.0 100.0 
		do
		
			#loop from radius 20 Mpc to 80 Mpc
			for((i=20; i<=80; i=i+20)) 
			do
				if [[ "$k" ==  *0.01* &&  "$l" != *10.0* ]]	
				then
					continue 2
				else
					# cp ../../data/dadosNitro_radius_${i}_Mpc_${k}nG_lc_${l}Mpc_one_* aux.txt
					echo opa

				fi
				# removing the header of crpropa's file 
				# sed -i "1s/#//g" aux.txt 
				# sed -i '/^#/d' aux.txt
				
				
				#Creating a directory to each different radius 
				mkdir -p ../results/one_sphere/ang_${j}/cone_angle${1}/nitro/L_B_${l}Mpc/B_${k}nG

				# python  geoJetAngle.py aux.txt $j ../results/one_sphere/ang_${j}/cone_angle${1}/nitro/L_B_${l}Mpc/B_${k}nG/results_R$i.txt $1
			done

			cd ../results/one_sphere/ang_${j}/cone_angle${1}/nitro/L_B_${l}Mpc/B_${k}nG
	
			mkdir -p plot/pdfs_saved


			#Using awk to make operations with file's columns, saving de Distance in a different file,
        		#the arrival energy in another.
			#and calculate the trajectory elongation.

			for R in $(seq 20 20 80)
			do
				#taking energies of all events; index: 0->initial energy; current->arrival energy
				# cat results_R$R.txt | awk '{print $5}'>energy_${R}Mpc.txt
				# cat results_R$R.txt | awk '{print $14}'>energy0_${R}Mpc.txt
				
				

				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id==1000010010) print $5  }'>energy_${R}Mpc_Z_1.txt
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id==1000010010) print $14  }'>energy0_${R}Mpc_Z_1.txt

				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000020040 && id<=1000050110) print $5  }'>energy_${R}Mpc_Z_2_Z_5.txt
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000020040 && id<=1000050110) print $14  }'>energy0_${R}Mpc_Z_2_Z_5.txt
				
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000020040 && id<=1000070140) print $5  }'>energy_${R}Mpc_Z_6_Z_10.txt
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000050110 && id<=1000070140) print $14  }'>energy0_${R}Mpc_Z_6_Z_10.txt

				
				# sed -i -e '1d' energy_*
				

				# paste energy_${R}Mpc.txt  energy0_${R}Mpc.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >delta_${R}Mpc.txt

				# paste energy_${R}Mpc_Z_1.txt  energy0_${R}Mpc_Z_1.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >delta_${R}Mpc_Z_1.txt
				# paste energy_${R}Mpc_Z_2_Z_5.txt  energy0_${R}Mpc_Z_2_Z_5.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >delta_${R}Mpc_Z_2_Z_5.txt
				# paste energy_${R}Mpc_Z_6_Z_10.txt  energy0_${R}Mpc_Z_6_Z_10.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >delta_${R}Mpc_Z_6_Z_10.txt

				# #The distance travelled
				# cat results_R$R.txt | sed "1d" | awk  '{print $1}'>Distance_${R}Mpc.txt

				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id==1000010010) print $1  }'>Distance_${R}Mpc_Z_1.txt
			
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000020040 && id<=1000050110) print $1  }'>Distance_${R}Mpc_Z_2_Z_5.txt
				
				# cat results_R$R.txt | sed "1d" | awk  '{id=$4; if(id>=1000020040 && id<=1000070140) print $1  }'>Distance_${R}Mpc_Z_6_Z_10.txt
				
	
				# sed -i -e '1d' Distance_${R}*

				# #Trajectory elongation calculation
				# #Basically the trajectory length minus the distance between the source and the final positon
				# cat results_R$R.txt | awk '{print $1 "\t" $6 "\t" $7 "\t" $8 "\t" $15 "\t" $16 "\t" $17 "\t" $4}'>Traj_elon_aux.txt

				# sed -i -e '1d' Traj_elon_aux.txt
				
				# cat Traj_elon_aux.txt | awk '{elo=$1 - sqrt(($2-$5) ^ (2.0) + ($3 -$6) ^ (2) + ($4 - $7) ^ (2)); printf"%0.3f\t %d\n", elo,$4 }' >elongation_${R}Mpc.txt
				
				# rm Traj_elon_aux.txt

				echo opa
				# #Separating all elongation by nuclei 
				# cat results_R$R.txt | sed "1d" | awk  '{id=$2; if(id==1000010010) print $1  }'>elongation_${R}Mpc_Z_1.txt
			
				# cat results_R$R.txt | sed "1d" | awk  '{id=$2; if(id>=1000020040 && id<=1000050110) print $1  }'>elongation_${R}Mpc_Z_2_Z_5.txt
				
				# cat results_R$R.txt | sed "1d" | awk  '{id=$2; if(id>=1000020040 && id<=1000070140) print $1  }'>elongation_${R}Mpc_Z_6_Z_10.txt
				# echo $R
			done
			pwd
			cd plot/
			cp $plot/Fixed_angle_energy_spectrum_nitro.cc Fixed_angle_energy_spectrum_20Mpc.cc
	
			#output Name

			sed "s/energy_20Mpc/energy_80Mpc/g"  Fixed_angle_energy_spectrum_20Mpc.cc> Fixed_angle_energy_spectrum_80Mpc.cc


			
			#histogram Title	
			sed -i -e "s/Main Title/ Nitrogen: #theta=${j}#circ, B=${k} nG, L_{B}=${l}Mpc,R=20 Mpc, #phi=${1}#circ /g" Fixed_angle_energy_spectrum_20Mpc.cc
 
			sed -i -e "s/Main Title/ Nitrogen: #theta=${j}#circ B=${k} nG, L_{B}=${l}Mpc,R=80 Mpc, #phi=${1}#circ/g" Fixed_angle_energy_spectrum_80Mpc.cc
 
		
			

			#making the plots

			g++ Fixed_angle_energy_spectrum_20Mpc.cc -o plot.exe `root-config --cflags --glibs`
			./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG_R20Mpc_nitro.pdf
			
			g++ Fixed_angle_energy_spectrum_80Mpc.cc -o plot.exe `root-config --cflags --glibs`
			./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG_R80Mpc_nitro.pdf

			#deleting all unnecessaries files
			rm plot.exe

			#Histogram with weight
			# We need to make the cutoff spectrum here, the file name  is Fixed_angle_energy_spectrum_Rcut. 
			# in this file, the argv[4] is the gamma, the argv[5] the Rcut , argv[6] the atomic number and argv[7] is the bins' directory path 

			# for gamma in 1.0 2.0
			# do
			#  	for Rcut in 18.5 19.5 20.0
			#  	do
			# 		cp $plot/Fixed_angle_energy_spectrum_nitro_Rcut.cc Fixed_angle_energy_spectrum_20Mpc_Rcut.cc
	
			# 		#output Name

			# 		sed "s/energy_20Mpc/energy_80Mpc/g"  Fixed_angle_energy_spectrum_20Mpc_Rcut.cc> Fixed_angle_energy_spectrum_80Mpc_Rcut.cc

			# 		sed -i -e "s/Main Title/Angle ${j}#circ, B=${k} nG, L_{B}=${l}Mpc,R=20 Mpc #phi = ${1}#circ, gamma=$gamma, log(#frac{Rcut}{eV})=$Rcut/g"\
			# 		Fixed_angle_energy_spectrum_20Mpc_Rcut.cc 
					
			# 		sed -i -e "s/Main Title/Angle ${j}#circ, B=${k} nG, L_{B}=${l}Mpc,R=80 Mpc #phi = ${1}#circ, gamma=$gamma, log(#frac{Rcut}{eV})=$Rcut /g"\
			# 		Fixed_angle_energy_spectrum_80Mpc_Rcut.cc
					
			# 		g++ Fixed_angle_energy_spectrum_20Mpc_Rcut.cc -o plot.exe `root-config --cflags --glibs`
			# 		./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG_gamma${gamma}_Rcut_${Rcut}_20Mpc.pdf $gamma $Rcut 7 
					
			# 		g++ Fixed_angle_energy_spectrum_80Mpc_Rcut.cc -o plot.exe `root-config --cflags --glibs`
			# 		./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG_gamma${gamma}_Rcut_${Rcut}_80Mpc.pdf\
			# 		$gamma $Rcut 7 
					
			
			# 		rm Fixed_angle_energy_spectrum_20Mpc_Rcut.cc Fixed_angle_energy_spectrum_80Mpc_Rcut.cc
			# 	done 
			# done
			
			rm pdfs_saved/*gamma*

			mkdir -p /mnt/c/Users/carlo/Desktop/importante/Desktop/imagens_overleaf/nitro_cone${1}/
			cp pdfs_saved/Energy*  /mnt/c/Users/carlo/Desktop/importante/Desktop/imagens_overleaf/nitro_cone${1}/	
			cd $home
			rm aux.txt
	done
		done
done

}


#Parameters : $1: Cones' angle opening
function fixedAngleProton(){

	for((j=20;j<=20;j=j+20))
do
	#loop of coherence legth
	for l in 0.1 1.0 10.0
	do	
		#loop of Magnetic field strength 
		for k in  0.01 1.0 #100.0 
		do
		
			#loop from radius 20 Mpc to 80 Mpc
			for i in 1 5 10 15 20 40 60 80
			do
				if [[ "$k" ==  *0.01* &&  "$l" != *10.0* ]]	
				then
					continue 2
				else
					cp ../../data/dados_radius_${i}_Mpc_${k}nG_lc_${l}Mpc_one_* aux.txt

				fi
				#removing the header of crpropa's file 
				sed -i "1s/#//g" aux.txt 
				sed -i '/^#/d' aux.txt
				
				#Creating a directory to each different radius 
				mkdir -p ../results/one_sphere/ang_${j}/cone_angle${1}/proton/L_B_${l}Mpc/B_${k}nG

				#creating a directory to save only the bins and respective bins' name 
				dir_name=/mnt/c/Users/carlo/Desktop/importante/IC_reformulation/src/bins/results/one_sphere/ang_${j}/cone_angle${1}/proton/L_B_${l}Mpc/B_${k}nG/

				mkdir -p $dir_name

				python  geoJetAngle.py aux.txt $j ../results/one_sphere/ang_${j}/cone_angle${1}/proton/L_B_${l}Mpc/B_${k}nG/results_R$i.txt $1
	
 
			done

			cd ../results/one_sphere/ang_${j}/cone_angle${1}/proton/L_B_${l}Mpc/B_${k}nG
	
			mkdir -p plot/pdfs_saved


			#Using awk to make operations with file's columns, saving de Distance in a different file,
        		#the arrival energy in another.
			#and calculate the trajectory elongation.

			for R in 1 5 10 15 20 40 60 80
			do
				cat results_R$R.txt | awk '{print $5}'>E.txt
				cat results_R$R.txt | awk '{print $14}'>E0.txt
	
				sed -i -e '1d' E*

				cp E.txt energy_${R}Mpc.txt 
				cp E0.txt energy0_${R}Mpc.txt
				paste E0.txt  E.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >delta_${R}Mpc.txt

				rm E*
	
				cat results_R$R.txt | awk '{print $1}'>Distance_${R}Mpc.txt
	
				sed -i -e '1d' Distance_${R}Mpc.txt

				#Trajectory elongation calculation
				#Basically the trajectory length minus the distance between the source and the final positon
				cat results_R$R.txt | awk '{print $1 "\t" $6 "\t" $7 "\t" $8 "\t" $15 "\t" $16 "\t" $17}'>Traj_elon_aux.txt

				sed -i -e '1d' Traj_elon_aux.txt
				
				cat Traj_elon_aux.txt | awk '{elo=$1 - sqrt(($2-$5) ^ (2.0) + ($3 -$6) ^ (2) + ($4 - $7) ^ (2)); printf"%0.3f\n", elo  }' >elongation_${R}Mpc.txt
				
				
				rm Traj_elon_aux.txt

			done
			rm *ang.txt
			cd plot/
			cp $plot/Fixed_angle_*.cc .
		
			
			
			#histogram Title	
			sed -i -e "s/Main Title/ Proton: #theta=${j}#circ, B=${k} nG, L_{B}=${l}Mpc, #phi=${1}#circ/g" Fixed_angle_energy_spectrum.cc
			sed -i -e "s/Main Title/ Proton: #theta=${j}#circ, B=${k} nG, L_{B}=${l}Mpc, #phi=${1}#circ/g" Fixed_angle_distance_hist.cc
			sed -i -e "s/Main Title/ Proton: #theta=${j}#circ, B=${k} nG, L_{B}=${l}Mpc, #phi=${1}#circ/g" Fixed_angle_deltaE_E0.cc
			sed -i -e "s/Main Title/ Proton: #theta=${j}#circ, B=${k} nG, L_{B}=${l}Mpc, #phi=${1}#circ/g" Fixed_angle_elongation.cc
			#making the plots
			g++ Fixed_angle_deltaE_E0.cc -o plot.exe `root-config --cflags --glibs`
			./plot.exe pdfs_saved/deltaE_E0_angle${j}_LB_${l}Mpc_B${k}nG.pdf $dir_name\
			angle${j}_LB_${l}Mpc_B${k}nG #energy loss
	
			g++ Fixed_angle_distance_hist.cc -o plot.exe `root-config --cflags --glibs`
			./plot.exe pdfs_saved/distance_angle${j}_LB_${l}Mpc_B${k}nG.pdf $dir_name\
			angle${j}_LB_${l}Mpc_B${k}nG #Distance travelled

			g++ Fixed_angle_elongation.cc -o plot.exe `root-config --cflags --glibs`
			./plot.exe pdfs_saved/elongation_angle${j}_LB_${l}Mpc_B${k}nG.pdf $dir_name\
			angle${j}_LB_${l}Mpc_B${k}nG #trajectory elongation

			g++ Fixed_angle_energy_spectrum.cc -o plot.exe `root-config --cflags --glibs`
			#l:Coherence length; k: Magnetic field intensity; 3 argument: file's name; dir_name:bins' directory
			./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG.pdf $dir_name\
			angle${j}_LB_${l}Mpc_B${k}nG #arrival energy spectrum

			pwd
			#Histogram with weight
			# We need to make the cutoff spectrum here, the file name  is Fixed_angle_energy_spectrum_Rcut. 
			# in this file, the argv[4] is the gamma, the argv[5] the Rcut , argv[6] the atomic number and argv[7] is the bins' directory path 
			for gamma in 1.0 2.0
			do
			 	for Rcut in 18.5 19.5 20.0
			 	do
					sed -i -e "s/Main Title/ Proton: Angle ${j}#circ, B=${k} nG, L_{B}=${l}Mpc,#phi = ${1}#circ, #gamma=$gamma, Rcut=$Rcut/g"\
					 Fixed_angle_energy_spectrum_Rcut.cc
					
					g++ Fixed_angle_energy_spectrum_Rcut.cc -o plot.exe `root-config --cflags --glibs`
					./plot.exe $l $k pdfs_saved/Energy_spectrum_angle${j}_LB_${l}Mpc_B${k}nG_gamma${gamma}_Rcut_${Rcut}.pdf\
					 $gamma $Rcut 1 $dir_name angle${j}_LB_${l}Mpc_B${k}nG_gamma${gamma}_Rcut_${Rcut}

					 sed -i -e "s/ Proton: Angle ${j}#circ, B=${k} nG, L_{B}=${l}Mpc,#phi = ${1}#circ, #gamma=$gamma, Rcut=$Rcut/Main Title/g"\
					 Fixed_angle_energy_spectrum_Rcut.cc


				done 
			done
			
	
			#deleting all unnecessaries files
			rm plot.exe
			#rm ../*.txt
	        	#rm *.cc

			mkdir -p /mnt/c/Users/carlo/Desktop/importante/Desktop/imagens_overleaf/proton_cone${1}/
			cp pdfs_saved/Energy*  /mnt/c/Users/carlo/Desktop/importante/Desktop/imagens_overleaf/proton_cone${1}	
			cd $home
			rm aux.txt
	done
		done
done


}
