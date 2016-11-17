#!/bin/sh
if [ $# -lt 1 ]
then
	echo "need the Core Name"
	exit 255
fi

ConnectecTagets=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "connect" and LinkTarget != '$1'
!`
BelongTarget=`mysql -u root --password=19841221 user0 <<!
select LinkTarget from $1 where LinkType = "belong"
!`

tempFolder=`date +%d%M%N`
mkdir /tmp/$tempFolder
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

#################Check And Get Bundle Info from objects ###############
AliasNameToURL=`mysql -u root --password=19841221 user0 <<!
select URL from objects where ObjectName = '$1'
!`

BUNDLE_XML=
if [ -z "$AliasNameToURL" ]
then
	##Need do nothing
BUNDLE_XML=
else
###############################
THE_URL=`echo $AliasNameToURL|sed -e "s/URL //g"`
BundleAllInfo=`mysql -u root --password=19841221 WorldTree <<!
select * from bundles where URL = '$THE_URL'
!`
AliasNameToDetail=`mysql -u root --password=19841221 user0 <<!
select detail from objects where ObjectName = '$1'
!`
THE_detail=`echo $AliasNameToDetail|sed -e "s/detail //g"`
###############################
if [ -z "$BundleAllInfo" ]
then
BUNDLE_XML=
else
#ProjectNodeName	URL	detail	file_name	show_name
#linux 1.0	https://www.kernel.org/pub/linux/kernel/v1.0/linux-1.0.tar.gz	linux 1.0	linux	linux-1.0
result_ProjectNodeName=`mysql -u root --password=19841221 WorldTree <<!
select ProjectNodeName from bundles where URL = '$THE_URL'
!`
result_ProjectNodeName=`echo $result_ProjectNodeName|grep -v ProjectNodeName`

result_detail=`mysql -u root --password=19841221 WorldTree <<!
select detail from bundles where URL = '$THE_URL'
!`
result_detail=`echo $result_detail|sed -e "s/detail //g"`

result_file_name=`mysql -u root --password=19841221 WorldTree <<!
select file_name from bundles where URL = '$THE_URL'
!`
result_file_name=`echo $result_file_name|sed -e "s/file_name //g"`

result_show_name=`mysql -u root --password=19841221 WorldTree <<!
select show_name from bundles where URL = '$THE_URL'
!`
result_show_name=`echo $result_show_name|sed -e "s/show_name //g"`
fi
cat  > /tmp/$tempFolder/leaves.list  <<!
	<key>$1</key>
	<dict>
		<key>detail</key>
		<string>$THE_detail</string>
		<key>URL</key>
		<string>http://www.google.com</string>
		<key>bundle</key>
		<dict>
			<key>URL</key>
			<string>$THE_URL</string>
			<key>detail</key>
			<string>$result_detail</string>
			<key>file_name</key>
			<string>$result_file_name</string>
			<key>name</key>
			<string>$result_show_name</string>
		</dict>
	</dict>
	<key>version</key>
	<string>Local</string>
!
BUNDLE_XML=`cat /tmp/$tempFolder/leaves.list`

fi

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
	$BUNDLE_XML
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
	$BUNDLE_XML
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
	$BUNDLE_XML
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
	<key>DataStructAndAlgorithm</key>
	<dict>
		<key>detail</key>
		<string>Data Struct And Algorithm</string>
		<key>URL</key>
		<string>http://users.cis.fiu.edu/~weiss/dsaa_c2e/files.html</string>
		<key>bundle</key>
		<dict>
			<key>URL</key>
			<string>http://users.cis.fiu.edu/~weiss/dsaa_c2e/DSAAC2eCode.tar</string>
			<key>detail</key>
			<string>DataStructAndAlgorithm</string>
			<key>file_name</key>
			<string>DataStructAndAlgorithm</string>
			<key>name</key>
			<string>DataStructAndAlgorithm</string>
		</dict>
	</dict>
	<key>version</key>
	<string>Local</string>
</dict>
</plist>
!
fi

python ModifySearch.py /tmp/$tempFolder/CurrentSearch.plist 
cat /tmp/$tempFolder/output.xml
rm -rf /tmp/$tempFolder
fi
