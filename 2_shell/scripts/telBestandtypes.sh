#!/usr/bin/env bash

#setup to reset envi to clean state
cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

git fetch origin
git reset --hard origin/master
git clean -fdx 

cd /

#actual script
if [ $# -lt 2 ]
then
  echo "Please give a path to the script, and atleast one file extention"
  exit 1
fi

cd $1

if [ $? != 0 ]
then
  echo "Please give a valid path to the script"
  exit 1
fi

count=0

for value in $*
do
  count=`expr $count + 1`
  if [ $count -lt 2 ]
  then
    continue
  fi
  found=$(find . -name '*.'$value | wc -l)
  echo "found" $found "files with" $value
done

exit 0

