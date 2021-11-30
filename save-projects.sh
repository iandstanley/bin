#!/bin/sh 

#	Save git projects in ~/Projects 

PROJDIR=~/Projects
PROJLIST=~/.etc/project-list
LOADPROJ=~/bin/load-projects.sh
MYETCDIR=~/.etc
ETCREPO=git@github.com:iandstanley/.etc.git


clone_etc_repo() {
	git clone $ETCREPO 
}

check_etc_exists() {
	[ ! -d  $MYETCDIR ]	&& clone_etc_repo
}

get_git_url() {
	echo Processing = $(pwd)
	grep url config | cut -w -f 4 >> $PROJLIST
}

save_etc_changes() {
	cd $MYETCDIR
	git add .
	git commit -m "updated $PROJLIST"
	git push 
}

get_project_dirs() {
	find $PROJDIR -type d 
}

process_dir() {
	cd $dir/.git
	get_git_url	
}

# test if $MYETCDIR exists and clone from github if not

check_etc_exists 

# remove previous load script

rm -f $PROJLIST

# Loop through $PROJDIR finding projects on github and creating:
# 	- the list of github urls (from the .git/config file)
#	- the script ~/bin/load-projects to recreate the Projects dir

for dir in $(get_project_dirs)
do
	[ -d $dir/.git ] && process_dir	
done
