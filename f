#!/usr/local/bin/bash


clear=$'\033[2J'
top=$'\033[H'

#trap "setterm --cursor on; stty echo; echo ${clear}; exit; trap -- - SIGINT SIGTERM" SIGTERM SIGINT

echo "${clear}"
while true; do
  echo "${top}"
  stty -echo
  #  setterm --cursor off
  echo -e "$@" | figl | lolcat
  # setterm --cursor off
  sleep 2
done
