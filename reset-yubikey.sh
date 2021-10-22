#!/bin/sh

[ "$1" != "-f" ] && echo Use -f to reset Yubikey && exit 1

ykman openpgp reset 
ykman oath reset
ykman piv reset

