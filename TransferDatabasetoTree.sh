#!/bin/sh
if [ $# -lt 1 ]
then
	echo "need the Core Name"
	exit 255
fi

ConnectecTagets=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "connect"
!`

rm /tmp/gzgtmpuniq
for Objects in $ConnectecTagets
do
	if [ "$Objects" = "LinkTarget" ]
	then
		continue;
	fi
	echo $Objects >> /tmp/gzgtmpuniq
done

###### Creat a new current search file 

cat  > CurrentSearch.plist  <<!
<plist version="1.0">
<dict>
        <key>CoreName</key>
        <string>$1</string>
        <key>table</key>
        <dict>
                <key>connect</key>
                <array>
                        <string>Unknown</string>
                </array>
        </dict>
</dict>
</plist>
!

python ModifySearch.py
