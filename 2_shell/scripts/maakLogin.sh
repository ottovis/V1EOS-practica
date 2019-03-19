#!/usr/bin/env bash

#setup to reset envi to clean state
#cd /home/otto/Documents/Git/EOS/V1EOS-practica/2_shell/bestanden/

#git fetch origin
#git reset --hard origin/master
#git clean -fdx 

#cd /

#actual script

echo "Please give your name (empty for Default):"
read name

if [ -z $name ]
then
  name=$(whoami)
fi

while [ -z "$password" ]; do
    read -p "Give a password: " password
    if ! [[ "$password" =~ (.*[0-9].*) ]] || ! [[ "$password" =~ (.*[a-z].*) ]] || ! [[ "$password" =~ (.*[A-Z].*) ]] || [ ${#password} -lt 8 ]
    then
      echo "bad password!"
      password=
    fi
done

echo $name >> passwd.txt
echo $password | sha1sum >> passwd.txt

 

