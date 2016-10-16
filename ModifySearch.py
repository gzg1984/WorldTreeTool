#!/usr/bin/env python 
#coding:utf-8 
import os
try: 
 import xml.etree.cElementTree as ET 
except ImportError: 
 import xml.etree.ElementTree as ET 
 import sys 

def SubElementWithText(parent, tag, text):
    attrib = {}
    element = parent.makeelement(tag, attrib)
    parent.append(element)
    element.text = text
    return element

try: 
 tree = ET.parse("CurrentSearch.plist")     #打开xml文档 
#root = ET.fromstring(country_string) #从字符串传递xml 
 root = tree.getroot()         #获得root节点  
except Exception, e: 
 print "Error:cannot parse file:country.xml."
 sys.exit(1) 

for country in root.findall('dict'): #找到root节点下的所有country节点 

    GotTable=0
    for finalkeys in country:
      TableDict=finalkeys
      #print finalkeys.text
      if GotTable== 1:
          break
      if finalkeys.text == "table":
          GotTable=1

    for table_child in  TableDict:
        GotConnect=0
        for finalkeys in country:
          ConnectArray=table_child
          #print finalkeys.text
          if GotConnect== 1:
              break
          if finalkeys.text == "connect":
              GotConnect=1

    for ConnectUnit in  ConnectArray:
        ConnectArray.remove(ConnectUnit)
    #print ConnectUnit.tag
    #print ConnectUnit.text
    for line in open("/tmp/gzgtmpuniq"):
        str=line
        #line.replace("l","ssssss")
        str_raw=str[:-1]
        print str_raw
        SubElementWithText(ConnectArray, 'string', str_raw)
    #temp_f=cat "/tmp/gzgtmpuniq"
    #lines = temp_f.readlines()#读取全部内容  
    #for line in lines :
    #        print line 

tree.write('output.xml') 
