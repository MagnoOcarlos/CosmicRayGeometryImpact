#!/bin/bash

home=/home/magnum/Desktop/IC/python_code/geometry
run=/home/magnum/Desktop/IC/python_code/results/shell
plot=/home/magnum/Desktop/IC/python_code/results/100k/plots

#loop from radius 20 Mpc to 80 Mpc
for((i=20; i<=80; i=i+20)) 
do
	#Create a directory to each different radius 
	mkdir -p ../results/one_sphere/${i}_Mpc/initAngle
	
	#loop for the angles and to run the geometry code to each one
	for((j=0; j<=20; j=j+5))
	do
		cp *radius_${i}_Mpc_one_* aux.txt

		sed -i "1s/#//g" aux.txt 
		sed -i '/^#/d' aux.txt


		python  geometry.py aux.txt $j ../results/one_sphere/${i}_Mpc/initAngle/results_ang$j.txt
	done
	
	cd ../results/one_sphere/${i}_Mpc/initAngle
	
	mkdir -p plot/pdfs_saved

	dir=$(echo $PWD)

	sed -i "12 a path=$dir" $run/test.sh

	bash $run/test.sh
	cd plot/
	cp $plot/initAngle_*.cc .

#	sed -i "47s/103/$(($i+100))/g" Distance_hist.cc
#	sed -i "47s/3/$i/g" Distance_hist.cc 
	

	sed -i "189s/Energy_spectrum.pdf/Energy_spectrum_R$i.pdf/g" initAngle_Energy_spectrum.cc
	sed -i "189s/Distance.pdf/Distance_R$i.pdf/g" initAngle_Distance_hist.cc
	sed -i "189s/DeltaE_E0.pdf/DeltaE_E0_R$i.pdf/g" initAngle_DeltaE_E0.cc
	

	g++ initAngle_DeltaE_E0.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe
	
	g++ initAngle_Distance_hist.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe

	g++ initAngle_Energy_spectrum.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe

	rm plot.exe
	rm ../*.txt
	rm *.cc

	sed -i "/^path=/d" $run/test.sh
	cd $home
	rm aux.txt 
done
