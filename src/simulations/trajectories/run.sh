#!/bin/bash

#
for l in 0.1 1.0 10 
	do	
		#loop of Magnetic field strength 
		for k in  0.01 1.0 100
		do
		
			#loop from radius 20 Mpc to 80 Mpc
			for((i=80; i<=80; i=i+20)) 
			do
				if [[ "$k" ==  *0.01* &&  "$l" != *10.0* ]]	
				then
					continue 2

				fi
				#removing the header of crpropa's file 
				#sed -i "1s/#//g" aux.txt 
				#sed -i '/^#/d' aux.txt
				#sed -i '/1000010010/d' aux.txt
				
                d=0
                while [ $d  -eq 0 ] 
                do
                    python oneSphereEmission.py 1 $l $i $k

                     d=$(wc -l trajectory.txt | awk '{print $1}')

                     if [ $d -eq 0 ]
                     then
                        rm trajectory*
                     fi
                     
                     #d=$(($d-1))
                     #echo $d
                done			
	
                rm trajectory.txt 

                mv trajectory* ../../time_series/data/

			done
        done
    done