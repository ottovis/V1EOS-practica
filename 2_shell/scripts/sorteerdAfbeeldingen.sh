#!/usr/bin/env bash

#setup to reset envi to clean state
cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

git fetch origin
git reset --hard origin/master
git clean -fdx 

cd /

#actual script
if [ $# == 0 ]
then
  echo "Please give a path to the script"
  exit
fi

cd $1

if [ $? != 0 ]
then
  echo "Please give a valid path to the script"
  exit
fi

mkdir Afbeeldingen


find . -name "*.jpg" -exec cp '{}' Afbeeldingen/ \; -prune # -o(r) werkt niet, dus maar op twee regels.
find . -name "*.png" -exec cp '{}' Afbeeldingen/ \; -prune # ook -prune werkt niet dus cp geeft foutmeldingen.


