#!/usr/bin/env bash

#setup to reset envi to clean state
cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

git fetch origin
git reset --hard origin/master
git clean -fdx 

cd /

#actual script
if [ $# -lt 1 ]
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

set -x

for img in *.jpg
do
    filename=${img%.*}
    convert "$filename.jpg" -resize 128x128 "$filename.png"
done

exit 0

