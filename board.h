#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct level Level;
struct level
{
  char ** board;

  int taille;
  int largeur;
  int longueur;

  int nb_niveau;
  int nb_points_interets;
  int nb_points_recouverts;
  int nb_mouvements;
};

void initialize_board(Level * p_level, char * filename) {
  FILE *fp;
  fp = fopen(filename, "r"); // on ouvre le fichier qui correspond au nom entré en argument

  // Initialisation des différents champs de la structure
  p_level->board = NULL;

  p_level->taille = 0;
  p_level->largeur = 0;
  p_level->longueur = 0;

  p_level->nb_niveau = 0;
  p_level->nb_points_interets = 0;
  p_level->nb_points_recouverts = 0;
  p_level->nb_mouvements = 0;

  if (fp == NULL) {
    printf("Erreur: Impossible d'ouvrir le fichier.\n");
    exit(1);
  }

  // Calcul de longueur, largeur, taille du plateau ainsi que le nombre de points d' interets recouverts et non recouverts du plateau
  char c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == 'I') {
      p_level->nb_points_interets +=1;
    }
    if (c == '.') { // cas : caisse + point d'intéret sur la même case
      p_level->nb_points_recouverts +=1;
      p_level->nb_points_interets +=1;
    }
    if (c != '\n') {
      p_level->taille += 1;
    }
  }

  fseek(fp, 0, SEEK_SET);
  while ((c = fgetc(fp)) != '\n') {
    p_level->largeur += 1;
  }

  p_level->longueur = p_level->taille / p_level->largeur; // la longueur est calculé en fonction de la taille totale et de la largeur

  // Allocation de mémoire pour p_level->board

  p_level->board = malloc(p_level->longueur * sizeof(char *));
  if (p_level->board == NULL) { // test d'allocation de la mémoire pour le tableau
    printf("Erreur: Allocation de la mémoire impossible.\n");
    exit(1);
  }
  for (int i = 0; i < p_level->longueur; i++){
    p_level->board[i] = NULL;
    p_level->board[i] = malloc(p_level->largeur * sizeof(char));

    if (p_level->board[i] == NULL) { // test d'allocation de la mémoire pour les sous tableaux (lignes)
      printf("Erreur: Allocation de la mémoire impossible.\n");
      exit(1);
    }
  }

  int x, y, num;
  x = 0;
  y = 0;
  num = 0; // num est le numéro de la case dans l'ordre de lecture

  // Lis chaque caractère du fichier et le place dans le tableau board
  fseek(fp, 0, SEEK_SET);
  while ((c = fgetc(fp)) != EOF) {
    if (c != '\n') {
      p_level->board[x][y] = c;
      num += 1;
      x = num / p_level->largeur;
      y = num % p_level->largeur;
    }
  }

  fclose(fp);
}

// Permet l'affichage du plateau de jeu
void display_board(Level * p_level) {
  int x, y;
  for (x = 0; x < p_level->longueur; x++) {
    for (y = 0; y < p_level->largeur; y++) {
        printf("%c", p_level->board[x][y]);
    }
    printf("\n");
  }
}

// permet au joueur de choisir le level grâce a un entier pris en entrée utilisateur
int choose_level(Level * p_level){
  int niv_diff;
  char board_name[20];

  strcpy(board_name, "levels/board_00.txt");
  printf("Choississez un niveau de difficulté entre 1 et 10 (0 pour quitter le jeu) : ");
  scanf("%d",&niv_diff);

  // si le joueur entre 0 la fonction renvoie 0 et le jeu s'arrête
  if (niv_diff == 0){
    return 0;
  }

  // le joueur doit saisir un entier entre 1 et 10 compris sinon sortie erreur
  else if (niv_diff > 10 || niv_diff < 1){
    printf("Erreur: Veuillez renseigner un niveau de difficulté valide (entre 1 et 10).\n");
    exit(1);
  }

  else {
    p_level->nb_niveau = niv_diff; // met a jour le niveau de difficulté dans la structure

    // met a jour le nom du fichier utilisé
    board_name[13] =  '0' + (niv_diff / 10);
    board_name[14] = '0' + (niv_diff % 10);
    
    initialize_board(p_level, board_name);
  }
  return 1;
}
