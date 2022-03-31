#!/bin/sh
########################################################################
# 
# 	Scriptname	setup_git.sh
# 
# 	Description:	quick setup of git
# 
########################################################################

echo "Setting up git ..."

git config --global user.name "Ian Stanley"
git config --global user.email "ian@jesusdiedfor.me"
git config --global core.editor vim

# echo "Creating ssh key ..."
# ssh-keygen 
# 
# echo "Now goto https://github.com/settings/keys and add key to GitHub ..."
# 
# cat ~/.ssh/id_rsa.pub
# 
