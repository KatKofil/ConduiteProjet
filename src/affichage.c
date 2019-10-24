#include <stdio.h>
#include <stdlib.h>

// Une ligne qui contient le nombre de mines présentes
// le nombre de flags placés
// au milieu de la ligne le smiley windows 95 
// afficher tout le jeu (2 boucles for)
// case non active = case x, si flag = drapeau genre p, si active = affiche contenu (0= espace, sinon chiffre)


////////////////////////////////////////
// FONCTION AFFICHER LA GRILLE DE JEU //
////////////////////////////////////////
void AfficheJeu()
{
    printf("\n\n");
    // Une ligne qui contient le nombre de mines présentes
	printf(" mines : %d	",10);
	// au milieu de la ligne le smiley windows 95
	printf("	:)		");
	// le nombre de flags placés
	printf(" drapeaux placés : %d	\n",0);

    for(int i=0;i<16;i++)
		{
		for(int j=0;j<30;j++)
			{                
				printf("x");
			}
				printf("\n");
		}
}

int main()
{     
       AfficheJeu();
       return 0;
}
