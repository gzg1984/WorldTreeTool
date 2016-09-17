#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int main(int ac,char** av)
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

	doc = xmlParseFile("temp.xml");
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
	/*init xml**/

	/*init sql**/
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	/** in future, you should input my search and generate a new result to customer **/
	/** after we can upload the connects **/
	if (mysql_query(conn, "select * from Linux_1_0")) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	//res = mysql_use_result(conn);
	res = mysql_store_result(conn);
	/*init sql end**/

/*
	objcount=mysql_num_rows(res);
	
	objarray=malloc(sizeof(char*) * objcount);
	memset(objarray,0,sizeof(sizeof(char*) * objcount));
	printf("res count = %d objarray size is %d\n",objcount,sizeof(char*) * objcount);
*/

	root_dict_node = xmlNewNode(NULL, BAD_CAST "dict");
	xmlNewChild(root_dict_node, NULL, BAD_CAST "key",BAD_CAST "CoreName");
	xmlNewChild(root_dict_node, NULL, BAD_CAST "string",BAD_CAST "Linux 1.0");
	xmlNewChild(root_dict_node, NULL, BAD_CAST "key",BAD_CAST "table");
	leaf_dict_node = xmlNewNode(NULL, BAD_CAST "dict");
	bundle_dict_node = xmlNewNode(NULL, BAD_CAST "array");
	
	tempcount=0;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		if (!strcmp(row[0],"belong"))
		{
			xmlNewChild(leaf_dict_node, NULL, BAD_CAST "key",BAD_CAST "belong");
			xmlNewChild(leaf_dict_node, NULL, BAD_CAST "string",BAD_CAST row[1]);
		}
		else
		{
			xmlNewChild(bundle_dict_node, NULL, BAD_CAST "string",row[1]);
		}
		/******here , handle bundle xml and inter to leaf dict end**/

	}
	xmlNewChild(leaf_dict_node, NULL, BAD_CAST "key",BAD_CAST "connect");
	xmlAddChild(leaf_dict_node, bundle_dict_node);
	xmlAddChild(root_dict_node, leaf_dict_node);

/*
	tempcount=0;
	while (objarray[tempcount]!= NULL)
	{
		printf("has objarray[%d]%s\n",tempcount,objarray[tempcount]);
		tempcount+=1;
	}
*/

	xmlAddChild(root_node, root_dict_node);
	/******here , handle xml **/
	xmlSaveFormatFileEnc("CurrentSearch.plist", doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	//xmlMemoryDump();   

	/******here , handle xml end **/

FAILED:
	/* close sql**/
	mysql_free_result(res);
	mysql_close(conn);
	/* close sql end**/

	return 0;
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
