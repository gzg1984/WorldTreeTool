#!/bin/sh
if [ $# -lt 1 ]
then
	echo "need the comments XML file as arg[1]"
	exit 255
fi
XMLcount=`echo $1|grep "\.xml"|wc -l`
if [ $XMLcount -eq 0 ]
then
	echo "need the comments XML file as arg[1]"
	exit 254
fi

python getOtherProject.py $1 > /tmp/gzgtmp

ObjectName=`echo $1|sed -e "s/\(.*\).xml/\1/g"`
sh CreateObjectLinkTreeTable.sh $ObjectName /tmp/gzgtmp
