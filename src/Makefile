all : menus structures parcoursup

parcoursup : structures.h structures.c testStructures.c
	gcc -Wall $^ -o parcoursup

menus : menus.c testMenus.c
	gcc -Wall $^ -o menus

structures : structures.c testStructures.c
	gcc -Wall $^ -o structures
	
clean :
	rm menus
	rm structures
	rm parcoursup
