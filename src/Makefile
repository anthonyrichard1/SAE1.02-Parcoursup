all : administrateurs #parcoursup menus structures

parcoursup : structures.c testStructures.c
	gcc -Wall $^ -o parcoursup

menus : menus.c testMenus.c
	gcc -Wall $^ -o menus

structures : structures.c testStructures.c
	gcc -Wall $^ -o structures
	
administrateurs : administrateurs.c testAdministrateurs.c structures.c
	gcc -Wall $^ -o administrateurs
	
clean :
	rm administrateurs #menus structures parcoursup
