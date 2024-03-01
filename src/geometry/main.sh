#!/bin/bash

#importing the function from data_treatment.sh
source data_treatment.sh
source data_treatment_Bmin.sh

#fixedAngleProton 50
#fixedAngleNitro 50
#fixedAngleNitro 90
#fixedAngleProton 360
# fixedAngleNitro 15
# fixedAngleProton 5


# fixedAngleProton 120
# fixedAngleProton 350
# fixedAngleProton 10
# fixedAngleProtonBmin 32
# fixedAngleProtonBmin 34
# fixedAngleProtonBmin 20
# fixedAngleProton 20
# fixedAngleProton 20

for phi in $(seq 20 20 160)
do
    fixedAngleProtonBmin $phi
done

# fixedAngleProton 50
# fixedAngleProton 360
# fixedAngleProton 360