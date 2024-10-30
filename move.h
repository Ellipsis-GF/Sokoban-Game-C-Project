#include "board.h"


int check_game_over(Level * p_level) {
  // Vérifie si toutes les boîtes sont placées sur des objectifs
  for (int x = 0; x < p_level->longueur; x++) {
    for (int y = 0; y < p_level->largeur; y++) {
      if (p_level->board[x][y] == 'C') {
        return 0;
      }
    }
  }
  return 1;
}

void move_player(Level * p_level, char direction) {
  int y, x;

  // Trouve la position actuelle du joueur sur le plateau (On note P un joueur sur une case vide et @ quand il se trouve sur un objectif)
  for (x = 0; x < p_level->longueur; x++) {
    for (y = 0; y < p_level->largeur; y++) {
      if (p_level->board[x][y] == 'P' || p_level->board[x][y] == '@') {
        break;
      }
    }
    if (p_level->board[x][y] == 'P' || p_level->board[x][y] == '@') {
        break;
      }
  }

  int x_1, y_1; // (x_1,y_1) : coordonnées de la case vers laquelle le joueur se déplace
  int y_2, x_2; // (x_2,y_2) : coordonnées de la case vers laquelle le joueur essait de pousser une caisse

  // on affecte les bonnes valeur a x_1, x_2, y_1 et y_2 selon la direction dans laquelle se déplace le joueur
  switch(direction){

      case 'h':
          x_1 = x - 1;
          y_1 = y;

          x_2 = x - 2;
          y_2 = y;
      break;

      case 'b':
          x_1 = x + 1;
          y_1 = y;

          x_2 = x + 2;
          y_2 = y;
      break;

      case 'g':
          x_1 = x;
          y_1 = y - 1;

          x_2 = x;
          y_2 = y - 2;
      break;

      case 'd':
          x_1 = x;
          y_1 = y + 1;

          x_2 = x;
          y_2 = y + 2;
      break;
  }
  // déplace le joueur et une potentielle caisse selon la position du joueur, sa direction, et la position des boites

    // test si le joueur deplace une caisse et si il peut le faire (si il n y a pas de mur derriere la caisse)
    if ( p_level->board[x_1][y_1] == 'C' && p_level->board[x_2][y_2] == ' ') {

      // On cherche a savoir si le joueur était sur un objectif ou pas pour savoir si on doit afficher le symbole "I" sur l'ancienne position du joueur
      if(p_level->board[x][y] == 'P'){
        // Déplace le joueur dans la direction spécifiée
        p_level->board[x][y] = ' ';
        p_level->board[x_1][y_1] = 'P';
      }
      else if(p_level->board[x][y] == '@'){
        p_level->board[x][y] = 'I';
        p_level->board[x_1][y_1] = 'P';
      }
      // Déplace la caisse dans la direction spécifiée
      p_level->board[x_2][y_2] = 'C';
    }

    // test si le joueur deplace une caisse qui se situe déja sur un objectif vers une case vide
    else if (p_level->board[x_1][y_1] == '.' && p_level->board[x_2][y_2] == ' '){
      
      // mise a jour du nombre de point d'interets recouverts
      p_level->nb_points_recouverts -= 1;

      if(p_level->board[x][y] == 'P'){
        p_level->board[x][y] = ' ';
        p_level->board[x_1][y_1] = '@';
      }

      else if(p_level->board[x][y] == '@'){
        p_level->board[x][y] = 'I';
        p_level->board[x_1][y_1] = '@';
      }

      p_level->board[x_2][y_2] = 'C';
    }

    // test si le joueur deplace une caisse qui se situe déja sur un objectif vers un objectif
    else if (p_level->board[x_1][y_1] == '.' && p_level->board[x_2][y_2] == 'I'){

        if(p_level->board[x][y] == 'P'){
          p_level->board[x][y] = ' ';
          p_level->board[x_1][y_1] = '@';
        }

        else if(p_level->board[x][y] == '@'){
          p_level->board[x][y] = 'I';
          p_level->board[x_1][y_1] = '@';
        }
      p_level->board[x_2][y_2] = '.';
    }

    // test si le joueur déplace une caisse sur un objectif
    else if (p_level->board[x_1][y_1] == 'C' && p_level->board[x_2][y_2] == 'I') {

      // mise a jour du nombre de point d'interets recouverts
      p_level->nb_points_recouverts += 1;

      if(p_level->board[x][y] == 'P'){
        p_level->board[x][y] = ' ';
        p_level->board[x_1][y_1] = 'P';
      }

      else if(p_level->board[x][y] == '@'){
        p_level->board[x][y] = 'I';
        p_level->board[x_1][y_1] = 'P';
      }
      p_level->board[x_2][y_2] = '.';
    }

    // test si le joueur se déplace sur une case vide
    else if (p_level->board[x_1][y_1] == ' ') {
      if(p_level->board[x][y] == 'P'){
        p_level->board[x][y] = ' ';
        p_level->board[x_1][y_1] = 'P';
      }

      else if(p_level->board[x][y] == '@'){
        p_level->board[x][y] = 'I';
        p_level->board[x_1][y_1] = 'P';
      }
      
    }

    // test si le joueur se déplace sur un objectif
    else if (p_level->board[x_1][y_1] == 'I') {
      if(p_level->board[x][y] == 'P'){
        p_level->board[x][y] = ' ';
        p_level->board[x_1][y_1] = '@';
      }

      else if(p_level->board[x][y] == '@'){
        p_level->board[x][y] = 'I';
        p_level->board[x_1][y_1] = '@';
      }
    }
}