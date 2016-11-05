#!/usr/bin/evn python 
#coding:utf-8 
try: 
 import xml.etree.cElementTree as ET 
except ImportError: 
 import xml.etree.ElementTree as ET 
 import sys 
try: 
 tree = ET.parse("comments_template.xml")     #打开xml文档 
#root = ET.fromstring(country_string) #从字符串传递xml 
 root = tree.getroot()         #获得root节点  
except Exception, e: 
 print "Error:cannot parse file:comments_template.xml."
 sys.exit(1) 
#print root.tag, "-", root.attrib  
#
#print "*"*10
#
#print child_tree[0][0].text   #通过下标访问 
#print child_tree[0][1].text   #通过下标访问 
#print child_tree[0][2].text   #通过下标访问 
#print child_tree[0].tag, child_tree[0].text 
#
#print "*"*10
 
for country in root.findall('dict'): #找到root节点下的所有country节点 
    #for keys in country.findall('key'):
    #  rank = keys.text   #子节点下节点rank的值 
    #  print rank 
    #for Strings in country.findall('string'):
    #  name = Strings.text      #子节点下属性name的值 
    #  #name = country.get('string')      #子节点下属性name的值 
    #  print name

    get=0
    
    for keys_loop in country:
      CommentsFileArray=keys_loop
      if get == 1:
            break
      if keys_loop.text == "comments_file_array":
          get=1

    for ArrayUnitDict in CommentsFileArray:
      #for child in ArrayUnitDict: 
          #print child.tag, "-", child.attrib 
          #print child.text
      getContent=0
      for content_loop in ArrayUnitDict:
              CommentsContentDict=content_loop
              if getContent == 1:
                    break
              if content_loop.text == "comments_file_content": 
                  getContent=1

      #print "*"*40
      getLineContent=0
      for Content in CommentsContentDict:
          ###Get line Comments
          comments_file_content_line_dict=Content
          if getLineContent== 1:
                break
          if Content.text == "LineComments": 
              getLineContent=1


      #for OneLine in comments_file_content_line_dict:
              #print "ssssssssssssss*******" + OneLine.tag + "xxxx" + OneLine.text
      #from here , we have every key and every dict
      for OneLineCommentWithoutLineNumber in comments_file_content_line_dict.findall('dict'): 
          #print OneLineCommentWithoutLineNumber.tag , "test", OneLineCommentWithoutLineNumber.attrib
          GotOtherProjectLink=0
          for InterLineCommentsContent in OneLineCommentWithoutLineNumber:
              OtherProjectLinkUnit=InterLineCommentsContent
              #print OtherProjectLinkUnit.tag , "test", OtherProjectLinkUnit.attrib
              #print OtherProjectLinkUnit.tag + "test" + OtherProjectLinkUnit.text
              if GotOtherProjectLink == 1:
                  #print OtherProjectLinkUnit.tag, "test", OtherProjectLinkUnit.text
                  break
              if InterLineCommentsContent.text == "OtherProjectLink":
                  GotOtherProjectLink=1

          #for finalkeys in  OtherProjectLinkUnit:
          #  print finalkeys.tag
          for finalDicts in  OtherProjectLinkUnit.findall('dict'):
              GotOtherProjectLink_finalName=0
              for finalkeys in finalDicts:
                  OtherProjectLinkfinalName=finalkeys
                  #print finalkeys.text
                  if GotOtherProjectLink_finalName == 1:
                      break
                  if finalkeys.text == "project":
                      GotOtherProjectLink_finalName=1
              
              print OtherProjectLinkfinalName.text
          
          #print OtherProjectLinkUnit.tag, "test", OtherProjectLinkUnit.text
#                  print "tag - " + InterLineCommentsContent.tag 
#                  break

#  rank = int(country.find('rank').text) 
#  if rank > 50: 
#   root.remove(country) 

          #for lineCommentOneLine in comments_file_content_dict:
          #  print lineCommentOneLine.tag + "-" + lineCommentOneLine.text


          #if child.tag == "dict":
          #    child_tree=child.getroot()
          #    break
    
 
#修改xml文件 
#for country in root.findall('country'): 
#  rank = int(country.find('rank').text) 
#  if rank > 50: 
#   root.remove(country) 
 
#tree.write('output.xml') 
