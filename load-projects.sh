#!/bin/sh  -x 

#	Load git projects in ~/Projects 

PROJDIR=~/Projects
PROJLIST=~/.etc/project-list
MYETCDIR=~/.etc
ETCREPO=git@github.com:iandstanley/.etc.git


clone_etc_repo() {
	git clone $ETCREPO 
}

check_etc_exists() {
	[ ! -d  $MYETCDIR ]	&& clone_etc_repo
}

create_project_dir() {
	mkdir -p $PROJDIR
}

# test if $MYETCDIR exists and clone from github if not

cd $HOME

check_etc_exists 

create_project_dir 

cd $PROJDIR

xargs -n 1 echo "git clone " < $PROJLIST | sh -

