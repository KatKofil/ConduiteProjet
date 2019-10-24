#include <stdio.h>
#include <stdlib.h>

char JEU[16][30];//grille de jeu 
char MINES[16][30];//la grille avec les mines

// Une ligne qui contient le nombre de mines présentes
// le nombre de flags placés
// au milieu de la ligne le smiley windows 95 
// afficher tout le jeu (2 boucles for)
// case non active = case x, si flag = drapeau genre p, si active = affiche contenu (0= espace, sinon chiffre)


//////////////////////////////
// FONCTION INITIALISATION ///
//////////////////////////////
void Init()
{
	for(int i=0;i<16;i++)
		{
			for(int j=0;j<30;j++)
				{
					JEU[i][j]='x';//' 'implique case cachée
					MINES[i][j]='0';                            
				}           
		}
}

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
				printf("%c",JEU[i][j]);
			}
				printf("\n");
		}
}

int main()
{     
       Init();
       AfficheJeu();
       return 0;
}
