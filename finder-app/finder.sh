#!/bin/sh

if [ $# != 2 ]
then
	echo "Invalid number of arguments passed, $#"
	exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d $filesdir ]
then
	echo "Invalid directory supplied, $filesdir"
	exit 1	
fi


files_in_dir=$(find -L $1)
files_found=0
total_matches_found=0

for files in $files_in_dir;
do
	if [ -f $files ]
	then
		files_found=$((files_found+1))
		matches_found_per_file=$(grep -c -e $2 $files)
		total_matches_found=$((total_matches_found+$(grep -c -e $2 $files)))
	fi
done

echo "The number of files are $files_found and the number of matching lines are $total_matches_found"
exit 0
