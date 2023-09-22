
#include <stdlib.h>
#include <stdio.h>

// "constantes"
#define TAILLE 12
#define NB_COLORS 6
#define NB_ESSAIS 23

#define FG_SHIFT 30
#define BG_SHIFT 40

// type de donnees
typedef enum {BLACK = 0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, MAX_COLORS} ColorCode;

// prototypes
ColorCode ** creeGrille (int);                                          // A FAIRE
void detruitGrille (ColorCode ***, int);                                // A FAIRE
void afficheCouleur (int, int, char);
void afficheGrille (ColorCode **, int);                                 // A FAIRE
void randomGrille (ColorCode **, int, int);                             // A FAIRE
int isFlooded (ColorCode **, int);                                      // A FAIRE
void propagate (ColorCode **, int, ColorCode);                          // A FAIRE
void propagate_rec (ColorCode **, int, ColorCode, ColorCode, int, int); // A FAIRE
void play (int, int, int);                                              // A TERMINER

/* **************************************** */
ColorCode ** creeGrille (int taille)
{
    ColorCode **M;
    M = malloc (taille * sizeof(ColorCode*));
    for(int i=0; i< taille; ++i)
    {
      M[i]= malloc (taille * sizeof(ColorCode));
    }
    return M;
}

//Desallocation
void detruitGrille (ColorCode ***tmp, int taille)
{
  ColorCode **M = *tmp;
  for(int i=0; i< taille; ++i)
  {
    free(M[i]);
  }
  free(M);
  (*tmp) = NULL;

}

//AFFICHAGE
void afficheGrille (ColorCode **M, int taille)
{
  for(int i = 0; i< taille; ++i)
  {
    for(int j=0; j< taille; j++)
    {
      afficheCouleur(BLACK, M[i][j], '0'+ M[i][j]);
    }
    printf("\n");
  }
}

int alea(int a, int b){
  return (a + rand()%(b - a +1));
}

void randomGrille (ColorCode **M, int l, int nbCouleur)
{
  for (int i = 0; i < l; ++i)
  {
    for (int j = 0; j < l; ++j)
    {
      M[i][j] = alea(1, nbCouleur);
    }
  }
}

int isFlooded (ColorCode **M, int taille)
{
  for (int i = 0; i < taille; ++i)
  {
    for(int j=0; j< taille; ++j){
      if(M[0][0] != M[i][j])
        return 0;
    }
  }
  return 1;
}

void propagate_rec (ColorCode **M, int taille, ColorCode ancienneCouleur, ColorCode newCouleur, int i, int j)
{

  if(M[i][j] != ancienneCouleur ){
    return;
  }
  M[i][j] = newCouleur;

  if(i> 0)
  {
    propagate_rec(M, taille, ancienneCouleur, newCouleur, i-1, j);
  }

  if(i < taille -1)
  {

    propagate_rec(M, taille, ancienneCouleur, newCouleur, i+1, j);
  }
  if(j> 0){

    propagate_rec(M, taille, ancienneCouleur, newCouleur, i, j-1);

  }
    if(j < taille - 1)
    {
      propagate_rec(M, taille, ancienneCouleur, newCouleur, i, j+1);
    }
}

// implementations
void afficheCouleur (int fg, int bg, char c)
{
  printf("\033[%d;%dm %c\033[m", FG_SHIFT + fg, BG_SHIFT + bg, c);
}


void play (int t, int nb_col, int n)
{
  ColorCode ** G;
  int res = -1;

  // initialisation
  G = creeGrille (t);
  randomGrille (G, t, nb_col);
  afficheGrille (G, t);
  int comp = 0;
  // boucle principale
  for (int i = 0; i < n; ++i)
  {
    // A FAIRE
    printf("Donner la couleur : ");
    scanf("%d", &nb_col);
    comp++;

    if(G[0][0] != nb_col){ //Si les couleurs ne sont identiques PROPAGER

        propagate_rec(G, t, G[0][0], nb_col, 0, 0);
      }
        afficheGrille (G, t);
        printf("TENTATIVES RESTANTES : %d\n", (NB_ESSAIS - comp -1));

  }


  // resultats
  if (res == -1)
    printf("Bye!\n");
   if (isFlooded(G,t))
    printf("GAGNE!\n");
  else
    printf("YOU LOSE !\n");

  // desallocation memoire
  detruitGrille(&G, t);
}



int main ()
{
  srand(time(NULL)); //reinitialiser la grille avec alea
  play(TAILLE, NB_COLORS, NB_ESSAIS);

  return EXIT_SUCCESS;
}
