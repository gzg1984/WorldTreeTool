#EXES=CreateNewWorldTree ExportLeaves ImportLeaves Search
EXES=Search
all:${EXES}
ExportLeaves:ExportLeaves.c
	gcc $^ -o $@ `xml2-config --libs --cflags` `mysql_config --libs`

Search:Search.c
	gcc $^ -o $@ `xml2-config --libs --cflags` `mysql_config --libs`

CreateNewWorldTree:CreateNewWorldTree.c
	gcc $^ -o $@ `xml2-config --libs --cflags` 

ImportLeaves:ImportLeaves.c
	gcc $^ -o $@ `xml2-config --libs --cflags` `mysql_config --libs`


clean:
	rm ${EXES}
	#gcc -o test test.c -lmysqlclient && ./test
	#gcc -I /usr/include/libxml2 -lxml2 test2.c -o test2 && ./teset2
	#gcc test3.c -I/usr/include/libxml2 -lxml2 -o test2 && ./test2
	#gcc test3.c `xml2-config --libs --cflags` -o test2 && ./test2
