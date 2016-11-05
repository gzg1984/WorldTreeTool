#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
void run_insert_string(char* sql_string);
static int parse_bundle_dic(char* TargetTable,xmlDocPtr doc,xmlNodePtr leaf)
{
	xmlChar *key;
	xmlNodePtr cur;
	xmlNodePtr leaf_dic;
	char buf[1024];
	sprintf(buf,"insert into bundles values ('%s',",TargetTable);
	/*
	   +-----------------+---------------------------------------------------------+-------------------------+---------------+-----------+
	   | ProjectNodeName | URL                                                     | detail                  | file_name     | show_name |
	   +-----------------+---------------------------------------------------------+-------------------------+---------------+-----------+
	   | xinetd          | https://github.com/xinetd-org/xinetd/archive/master.zip | include telnet and echo | xinetd-master | xinetd    |
	   +-----------------+---------------------------------------------------------+-------------------------+---------------+-----------+
	 */
/*
		bundle dic key: URL			bundle dic string: https://github.com/xinetd-org/xinetd/archive/master.zip
		bundle dic key: detail			bundle dic string: telnet
		bundle dic key: file_name			bundle dic string: xinetd-master
		bundle dic key: name			bundle dic string: xinetd-master
*/

	cur = leaf->xmlChildrenNode;
	while (cur != NULL) 
	{
		//获取key
		//printf("\t\tbundle dict->cur->name:%s\n",cur->name);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"key"))) 
		{
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(!(xmlStrcmp(key, (const xmlChar *)"URL")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取URL string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					sprintf(buf,"%s '%s',",buf,key);
				}
			}
			else if(!(xmlStrcmp(key, (const xmlChar *)"detail")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取detail string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					sprintf(buf,"%s '%s',",buf,key);
				}
			}
			else if(!(xmlStrcmp(key, (const xmlChar *)"file_name")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取file_name string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					sprintf(buf,"%s '%s',",buf,key);
				}
			}
			else if(!(xmlStrcmp(key, (const xmlChar *)"name")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取file_name string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					sprintf(buf,"%s '%s')",buf,key);
				}
			}
			else
			{	printf("\t\tbundle dic key: %s\t", key);
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					printf("\t\tbundle dic string: %s\n", key);
					xmlFree(key);
				}
				else
				{
					printf("not followed by <string> but <%s>\n",cur->name);
					if ((!xmlStrcmp(cur->name, (const xmlChar *)"dict"))) {
						leaf_dic = cur->xmlChildrenNode;
						/** should be bundle here **/
					}
					xmlFree(key);
				}
			}
		}
		cur = cur->next;
	}
	printf("tent to run [%s]\n",buf);
	run_insert_string(buf);
	return 0;
}
static int parse_leaf_dic(char* TargetTable,xmlDocPtr doc,xmlNodePtr leaf)
{
	xmlChar *key;
	xmlNodePtr cur;
	char buf[1024];
	char URL_buf[1024];
	char first_detail_to_end[1024];
	sprintf(buf,"insert into objects values ('%s',",TargetTable);
/*
insert into objects values ('Source Code for Data Structures and Algorithm Analysis in C (Second Edition)','http://users.cis.fiu.edu/~weiss/dsaa_c2e/DSAAC2eCode.tar.Z','Algorithm');
*/
/*
key: xinetd	
	leaf_dic key: detail		leaf_dic string: xinetd is a secure replacement for inetd
	leaf_dic key: URL		leaf_dic string: https://github.com/xinetd-org/xinetd
	leaf_dic key: bundle	
		bundle dic key: URL			bundle dic string: https://github.com/xinetd-org/xinetd/archive/master.zip
		bundle dic key: detail			bundle dic string: telnet
		bundle dic key: file_name			bundle dic string: xinetd-master
		bundle dic key: name			bundle dic string: xinetd-master
*/
/*
mysql> select * from objects where ObjectName = 'Algorithm';
+------------+-----------------------------------------+-----------+--------+
| ObjectName | URL                                     | TableName | detail |
+------------+-----------------------------------------+-----------+--------+
| Algorithm  | https://en.wikipedia.org/wiki/Algorithm | Algorithm |        |
+------------+-----------------------------------------+-----------+--------+
*/


	cur = leaf->xmlChildrenNode;
	strcpy (URL_buf,"");
	while (cur != NULL) {
		//获取key
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"key"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if(!(xmlStrcmp(key, (const xmlChar *)"detail")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取detail string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					strcpy(first_detail_to_end,key);;
				}
			}
			else if(!(xmlStrcmp(key, (const xmlChar *)"URL")))
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取detail string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					strcpy (URL_buf,key);
				}
			}
			else
			{
				cur = cur->next;
				while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
					cur = cur->next;
				}
				//获取string
				if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
					key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
					printf("\tleaf_dic string: %s\n", key);
				}
				else if ((!xmlStrcmp(cur->name, (const xmlChar *)"dict"))) {
					printf("\n");
					parse_bundle_dic(TargetTable, doc,cur);
					/** should be bundle here **/
				}
				else
				{
					printf("not followed by <string> but <%s>\n",cur->name);
				}
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	sprintf(buf,"%s '%s','%s','%s')",buf,URL_buf,TargetTable,first_detail_to_end);
	run_insert_string(buf);
	return 0;
}
static int parse_leaf(xmlDocPtr doc,xmlNodePtr leaf)
{
	xmlChar *key;
	xmlNodePtr cur;
	cur = leaf->xmlChildrenNode;
	char buf[1024];
	while (cur != NULL) {
		//获取key
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"key"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			sprintf(buf,"%s", key);
			cur = cur->next;
			while (!(xmlStrcmp(cur->name, (const xmlChar *)"text"))) {
				cur = cur->next;
			}
			//获取string
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"string"))) {
				key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				printf("string: %s\n", key);
			}
			else if ((!xmlStrcmp(cur->name, (const xmlChar *)"dict"))) {
					printf("\n");
					parse_leaf_dic(buf,doc,cur);
			}
			else
			{
				printf("not followed by <string> but <%s>\n",cur->name);
			}
			
			xmlFree(key);
		}
		cur = cur->next;
	}
	return 0;
}
void run_insert_string(char* sql_string)
{
	/*init sql**/
	MYSQL *conn;
	MYSQL_RES *res;
	unsigned long objcount=0;
	int tempcount=0;
	char** objarray;
	MYSQL_RES *bundle_select;
	MYSQL_ROW row;
	MYSQL_ROW row_of_bundle;
	char server[] = "localhost";
	char user[] = "root";
	char password[] = "19841221";
	char database[] = "WorldTree";
	char query_string[1024]={0};
	/*init sql end**/
	/*init sql**/
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	if (mysql_query(conn, sql_string)) 
	{
		fprintf(stderr, "[%s]%s\n",sql_string,mysql_error(conn));
		exit(1);
	}
	res = mysql_store_result(conn);
FAILED:
	mysql_free_result(res);
	mysql_close(conn);
}
int main(int ac,char** av)
{

	/*init xml**/
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL;
	xmlNodePtr root_dict_node = NULL;
	xmlNodePtr node = NULL;
	xmlNodePtr leaf_dict_node = NULL;
	xmlNodePtr bundle_dict_node = NULL;
	/*
	   doc = xmlNewDoc(BAD_CAST "1.0");
	   root_node = xmlNewNode(NULL, BAD_CAST "root");
	 */

	doc = xmlParseFile("leaves.plist");
	if (doc == NULL) {
		fprintf(stderr, "Failed to parser xml file:temp.xml\n");
		return -1;
	}
	root_node = xmlDocGetRootElement(doc);
	if (root_node == NULL) {
		fprintf(stderr, "Failed to get root node.\n");
		goto FAILED;
	}
	xmlDocSetRootElement(doc, root_node);
	{
		xmlNodePtr cur;
	}

	root_dict_node = root_node->xmlChildrenNode;
	while (!(xmlStrcmp(root_dict_node->name, (const xmlChar *)"text"))) {
		root_dict_node = root_dict_node->next;
	}

	parse_leaf(doc,root_dict_node);
FAILED:
	return 0;
	/*init xml end**/

}
/*
int main222(int argc, char **argv)
{

	xmlNewChild(root_node, NULL, BAD_CAST "node1",BAD_CAST "content of node1");

	node=xmlNewChild(root_node, NULL, BAD_CAST "node3",BAD_CAST"node has attributes");

	xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");

	node = xmlNewNode(NULL, BAD_CAST "node4");

	node1 = xmlNewText(BAD_CAST"other way to create content");

	xmlAddChild(node, node1);

	xmlAddChild(root_node, node);

	return(0);

}
*/
