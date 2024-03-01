#!/bin/sh


for i in $(seq 20 20 80)
do
	sed -i -e "35s/$/$i/" oneSphere.sh
	sed -i -e "4s/$/$i/"   oneSphere.sh

	qsub oneSphere.sh

	sed -i -e "4s/$i//g" oneSphere.sh
	sed -i -e "35s/$i//g" oneSphere.sh

done

