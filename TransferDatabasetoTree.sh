#!/bin/sh
if [ $# -lt 1 ]
then
	echo "need the Core Name"
	exit 255
fi

ConnectecTagets=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "connect"
!`
BelongTarget=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "belong"
!`

tempFolder=`date +%d%M%N`
mkdir /tmp/$tempFolder
ConnectecTagets=`echo $ConnectecTagets|sed -e "s/$1//g"`
touch  /tmp/$tempFolder/gzgtmpuniq
for Objects in $ConnectecTagets
do
	if [ "$Objects" = "LinkTarget" ]
	then
		continue;
	elif [ "$Objects" = "$1" ]
	then
		continue;
	fi
	echo $Objects >> /tmp/$tempFolder/gzgtmpuniq
done

###### Creat a new current search file 
if [ -z "$ConnectecTagets" ]
then
if [ -z $BelongTarget ]
then
cat  > /tmp/$tempFolder/CurrentSearch.plist  <<!
<plist version="1.0">
<dict>
        <key>CoreName</key>
        <string>$1</string>
</dict>
</plist>
!
else
ReadBelongTarget=Unknown
for Objects in $BelongTarget
do
	if [ "$Objects" = "LinkTarget" ]
	then
		continue;
	elif [ "$Objects" = "$1" ]
	then
		continue;
	else
		ReadBelongTarget=$Objects
		break;
	fi
done
cat  > /tmp/$tempFolder/CurrentSearch.plist  <<!
<plist version="1.0">
<dict>
        <key>CoreName</key>
        <string>$1</string>
        <key>table</key>
        <dict>
		<key>belong</key>
		<string>$ReadBelongTarget</string>
        </dict>
</dict>
</plist>
!
fi

cat /tmp/$tempFolder/CurrentSearch.plist
rm -rf /tmp/$tempFolder





else
if [ -z "$BelongTarget" ]
then
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
else
ReadBelongTarget=Unknown
for Objects in $BelongTarget
do
	if [ "$Objects" = "LinkTarget" ]
	then
		continue;
	elif [ "$Objects" = "$1" ]
	then
		continue;
	else
		ReadBelongTarget=$Objects
		break;
	fi
done
cat  > /tmp/$tempFolder/CurrentSearch.plist  <<!
<plist version="1.0">
<dict>
        <key>CoreName</key>
        <string>$1</string>
        <key>table</key>
        <dict>
		<key>belong</key>
		<string>$ReadBelongTarget</string>
                <key>connect</key>
                <array>
                        <string>Unknown</string>
                </array>
        </dict>
</dict>
</plist>
!
fi

python ModifySearch.py /tmp/$tempFolder/CurrentSearch.plist 
cat /tmp/$tempFolder/output.xml
rm -rf /tmp/$tempFolder
fi
