all : menus informations administrateurs

menus : menus.c testMenus.c
	gcc -Wall $^ -o menus
	
informations : informations.c erreur.c testInformations.c
	gcc -Wall $^ -o informations
	
administrateurs : administrateurs.c informations.c erreur.c testAdministrateurs.c
	gcc -Wall $^ -o administrateurs
	
clean :
	rm menus informations administrateurs
