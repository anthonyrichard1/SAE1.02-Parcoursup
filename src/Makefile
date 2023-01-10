all : menus informations administrateurs candidats

menus : menus.c testMenus.c informations.c erreur.c administrateurs.c candidats.c
	gcc -Wall $^ -o menus
	
informations : informations.c erreur.c testInformations.c
	gcc -Wall $^ -o informations
	
administrateurs : administrateurs.c informations.c erreur.c testAdministrateurs.c
	gcc -Wall $^ -o administrateurs

candidats : candidats.c testCandidats.c erreur.c informations.c
	gcc -Wall $^ -o candidats
	
clean :
	rm -f menus informations administrateurs candidats
