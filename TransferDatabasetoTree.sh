#!/bin/sh
if [ $# -lt 1 ]
then
	echo "need the Core Name"
	exit 255
fi

ConnectecTagets=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "connect"
!`

tempFolder=`date +%d%M%N`
mkdir /tmp/$tempFolder
for Objects in $ConnectecTagets
do
	if [ "$Objects" = "LinkTarget" ]
	then
		continue;
	fi
	echo $Objects >> /tmp/$tempFolder/gzgtmpuniq
done

###### Creat a new current search file 
cat  > /tmp/$tempFolder/CurrentSearch.plist  <<!
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

python ModifySearch.py /tmp/$tempFolder/CurrentSearch.plist 
cat /tmp/$tempFolder/output.xml
rm -rf /tmp/$tempFolder
