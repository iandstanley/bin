#!/bin/sh
## refernce http://www.dict.org/rfc2229.txt
word="$1"
if [ -z "$word" ]; then
	echo "syntax: ./dict <word>"
	exit 1
fi

curl "dict://dict.org/d:$word"
