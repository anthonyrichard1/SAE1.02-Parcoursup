all : parcoursup informations administrateurs candidats responsable

parcoursup : menus.c testMenus.c informations.c erreur.c administrateurs.c candidats.c
	gcc -Wall $^ -o parcoursup
	
informations : informations.c erreur.c testInformations.c candidats.c
	gcc -Wall $^ -o informations
	
administrateurs : administrateurs.c informations.c erreur.c testAdministrateurs.c candidats.c
	gcc -Wall $^ -o administrateurs

candidats : candidats.c testCandidats.c erreur.c informations.c
	gcc -Wall $^ -o candidats

responsable : responsable.c testResponsable.c
	gcc -Wall $^ -o responsable
	
clean :
	rm -f parcoursup informations administrateurs candidats responsable
