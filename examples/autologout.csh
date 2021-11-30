#!/bin/tcsh
exit

# You can setup your terminal to automatically logout after a period
# of inactivity. This is done by setting the tcsh shell variable
# 'autologout' giving it a value in minutes. If this is the login
# shell the user is logged off. If it is a sub-shell  then the process
# exists to the parent shell which isn't much help.

The following is a transcriptof a autologout session

arpan@tintin# rsh herge
arpan@herge# set autologout=1
arpan@herge# date
Sat Jun 28 18:13:07 IST 2008

<After 1 min of inactivity>

arpan@herge# auto-logout
Connection to herge closed.
arpan@tintin# date
Sat Jun 28 18:14:10 IST 2008

