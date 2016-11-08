#!/bin/sh
#######
#check the args
if [ $# -lt 1 ]
then
	echo "no object name ?"
	exit 255
fi
if [ $# -lt 2 ]
then
	echo "no Connects?  ?"
	exit 254
fi
if [ -f $2 ]
then
	echo "connects file check done"
else
	echo "connects file doesn't exist?"
	exit 253
fi
#check table name exist ?
TABLES=`mysql -u root --password=19841221 user0 <<!
show tables;
!`

object_count=`echo $TABLES|grep -w $1|wc -l`
if [ $object_count -eq 0 ]
then
	echo "new object, create table"
	mysql -u root --password=19841221 user0 <<!
create table $1 ( LinkType varchar (512) not null, LinkTarget varchar (512) not null);
!
else
	echo "have the exist table already..."
fi



##new table should have a "belong"
## and several "connect"
Connects=`cat $2 |uniq`
for connect_object in $Connects
do
	echo "TRY:select * from $1 where LinkTarget = '$connect_object' ; "
	check_exist=`mysql -u root --password=19841221 user0 <<!
select * from $1 where LinkTarget = "$connect_object" ;
!`
if [ -z "$check_exist" ]
then
	echo "New connect to $connect_object "
	mysql -u root --password=19841221 user0 <<!
insert into $1 values ('connect','$connect_object');
!
else
check_exist_count=`echo $check_exist|wc -l`
if [ $check_exist_count -eq 0 ]
then
	echo "New connect to $connect_object "
	mysql -u root --password=19841221 user0 <<!
insert into $1 values ('connect','$connect_object');
!
else
	echo "Connected $connect_object already exists."
fi

fi
done


