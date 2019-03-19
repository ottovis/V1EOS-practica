#!/usr/bin/env bash

#setup to reset envi to clean state
#cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

#git fetch origin
#git reset --hard origin/master
#git clean -fdx 

#cd /

#actual script

while [ -z $name ]
do
  read -p "Give name: " name
done

while [ -z $password ]
do
  read -p "Give password: " password
done

hashed=$(echo $password | sha1sum)
found=

while read line
do
  if [ "$line" == "$name" ] && [ -z "$found" ]
  then
    found="$name"
    continue
  fi
  if [ -n "$found" ]
  then
    if [ "$line" == "$hashed" ]
    then
      echo "logged in"
      break
    else
      echo "wrong password"
    fi
  fi
done <passwd.txt

if [ -z "&found" ]
then
  echo "user not found"
fi

hashed=
password=
