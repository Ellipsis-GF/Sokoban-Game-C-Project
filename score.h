#include <time.h>
#include "move.h"

int calcul_difficulte(int level){

  if (level < 6){
    return 4;
  }
  else if (level < 10){
    return 8;
  }
  else{
    return 10;
  }

}

void score(long * temps, Level * p_level){

  printf("Vos résultats :\n");
  printf("Vous avez mis %ld secondes.\n", *temps);
  printf("Vous avez effectué %d deplacements.\n", p_level->nb_mouvements);
  printf("Au total, vous avez déplacé %d caisses sur les %d qu'il y avait à recouvrir.\n", p_level->nb_points_recouverts, p_level->nb_points_interets);

  /* On calcule le score total selon les critères suivants :
  
  * Le joueur gagne [niveau de difficulté] x 20 - [temps en secondes] points, si le nombre obtenu est positif (sinon 0).
  * Le joueur gagne ([niveau de difficulté] x 20 - [nombre de déplacements], si le nombre obtenu est positif (sinon 0)).
  * Le joueur gagne [nombre de caisses qui recouvrent un point d'intérêt] * 30 points.
  * Le joueur gagne un bonus de 500 points s'il a recouvert toutes les caisses
  On fait alors le total de ces points.

  */

  int score_temps, score_deplacements, score_points, score_total, difficulte;
  difficulte = calcul_difficulte(p_level->nb_niveau);
  score_temps = difficulte * 20 - *temps;
  score_deplacements = difficulte * 20 - p_level->nb_mouvements;
  score_points = p_level->nb_points_recouverts * 30;

  if ((p_level->nb_points_interets - p_level->nb_points_recouverts) == 0){
    score_points = score_points + 500;
  }
  if (score_temps < 0){
    score_temps = 0;
  }
  if (score_deplacements < 0){
    score_deplacements = 0;
  }

  score_total = score_temps + score_deplacements + score_points;

  printf("Votre score total est de : %d\n", score_total);

}

// Calcule le temps en passé depuis le début de la partie
void chrono(struct timespec * time, long  * p_temps){
  long start = time->tv_sec;
  clock_gettime(CLOCK_MONOTONIC, time);
  long end = time->tv_sec; // on récupère le temps en secondes
  *p_temps += end - start; // on stock le temps écoulé depuis la dernière fois ou le temps a été sauvegardé
}