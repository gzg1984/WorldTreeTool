#!/bin/sh
mysql -u root --password=19841221 user0<<!
select * from $1 ;
!
