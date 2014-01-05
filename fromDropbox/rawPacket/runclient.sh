#!/bin/bash
#===============================================================================
#
#          FILE:  runclient.sh
# 
#         USAGE:  ./runclient.sh 
# 
#   DESCRIPTION:  run ./msdu up to a number of times specified
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR:   (), 
#       COMPANY:  
#       VERSION:  1.0
#       CREATED:  07/21/2009 03:36:40 PM SGT
#      REVISION:  ---
#===============================================================================

i=0;
while :
do
#./msdu
let i=$i+1
echo $i
#./vlan
./vlansmall
#usleep 100000;
#usleep 800000;
#usleep 500;
#usleep 10;
usleep 500;
done
