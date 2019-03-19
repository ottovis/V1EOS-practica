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
  echo "Please give a path to the script and a command to test"
  exit 1
fi

cd $1

if [ $? != 0 ]
then
  echo "Please give a valid path to the script"
  exit 1
fi

echo "Run of checkStatus.sh with command: $2" > output.log

for file in *
do
  ($2 $file)> /dev/null
  echo "exit status of command $2 against $file was: $?" >> output.log
done

exit 0
