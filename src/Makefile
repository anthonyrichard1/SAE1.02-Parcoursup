all : parcoursup informations administrateurs candidats responsable

parcoursup : menus.c testMenus.c informations.c administrateurs.c candidats.c responsable.c erreur.c
	gcc -Wall $^ -o parcoursup
	
informations : informations.c testInformations.c erreur.c
	gcc -Wall $^ -o informations
	
administrateurs : administrateurs.c testAdministrateurs.c erreur.c informations.c
	gcc -Wall $^ -o administrateurs

candidats : candidats.c testCandidats.c erreur.c informations.c
	gcc -Wall $^ -o candidats

responsable : responsable.c testResponsable.c erreur.c
	gcc -Wall $^ -o responsable
	
clean :
	rm -f parcoursup informations administrateurs candidats responsable
