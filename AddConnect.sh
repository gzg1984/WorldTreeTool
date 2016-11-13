#!/bin/sh
if [ $# -lt 2 ]
then
        echo "First: CoreName  seceond: Connected Object"
        exit 254
fi
### $1 is table
### $2 is the connect "string"


mysql -u root --password=19841221 user0<<!
delete from $1 where LinkType = 'connectl' and LinkTarget = '$2';
!

######
##Insert new
mysql -u root --password=19841221 user0<<!
insert into $1 values ('connect','$2');
!

CheckExistTable=`mysql -u root --password=19841221 user0<<!
show tables;
!`
CheckExistTableCount=`echo $CheckExistTable|grep $2|wc -l`
if [ $CheckExistTableCount -eq "0" ]
then
mysql -u root --password=19841221 user0<<!
create table $2 ( LinkType varchar (512) not null, LinkTarget varchar (512) not null);
!
fi

