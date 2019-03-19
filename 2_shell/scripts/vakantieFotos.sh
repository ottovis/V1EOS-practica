#!/usr/bin/env bash

#setup to reset envi to clean state
#cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

#git fetch origin
#git reset --hard origin/master
#git clean -fdx 

cd /

#actual script
if [ $# == 0 ]
then
  echo "Please give a path to the script"
  exit 1
fi

cd $1

if [ $? != 0 ]
then
  echo "Please give a valid path to the script"
  exit 1
fi

cd Afbeeldingen

if [ $? != 0 ]
then
  echo "First run sorteerAfbeeldingen.sh script"
  exit 1
fi

mkdir Vakantie

readarray -t ARR < <( find . | grep vakantie )
find . | grep vakantie | readarray -t ARR

for VALUE in "${ARR[@]}"
do
  mv "${VALUE}" Vakantie/
done

exit 0

