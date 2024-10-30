#include "score.h"

int main() {
  Level level;
  Level * p_level;
  p_level = &level;

  // création d une structure qui permet de stocker le temps en seconde à un moment donné depuis le lancement de la machine 
  // convertion de ticks en seconde automatique avec la fonction "clock_gettime"
  struct timespec tp;
  struct timespec * p_tp = &tp;

  int tour_0 = 0; // permet de voir si on est ou pas au premier tour de jeu.

  long temps; // permet de stocker le temps écoulé depuis le début du jeu
  long * p_temps = &temps;

  // clear le terminal
  system("clear");

  // stock la direction dans laquelle le joueur veut se déplacer (ou 'e' si le joueur souhaite mettre fin au jeu)
  char input;

  // Boucle de jeu principale
  while (choose_level(p_level)) {

    input = 'a'; // stock la direction dans laquelle le joueur veut se déplacer (ou 'e' si le joueur souhaite mettre fin au jeu)

    clock_gettime(CLOCK_MONOTONIC, p_tp); // fait une sauvegarde du nombre de secondes écoulées depuis le lancement de la machine
    temps = 0;

    // Boucle secondaire (en jeu)
    while (input != 'e' && check_game_over(p_level) == 0){
      // clear le terminal
      system("clear");

      // Affiche le chrono pour chaque partie lancée, à chaque tour de jeu.

      if (tour_0 == 0){
        printf("Temps écoulé : 0 seconds | (entrez e pour terminer la partie et revenir au menu de selection de niveau)\n");
        tour_0 = 1;
      }

      else{
        chrono(p_tp, p_temps);
        printf("Temps écoulé : %ld seconds\n(entrez e pour terminer la partie et revenir au menu de selection de niveau)\n", temps);
      }

      // Affiche le plateau de jeu
      display_board(p_level);

      // Lit l'entrée de l'utilisateur et déplace le joueur si nécessaire
      
      scanf("%c", &input);
      if (input == 'h' || input == 'b' || input == 'g' || input == 'd') {
        p_level->nb_mouvements += 1;
        move_player(p_level, input);
      }
    }

    // Vérifie si la partie est gagnée par le joueur
    if (check_game_over(p_level)) {
      system("clear");
      display_board(p_level);
      printf("Bravo, vous avez gagné !\n");
      // calcul le temps écoulé depuis le début de la partie
      chrono(p_tp, p_temps);
      score(p_temps, p_level);
      // met fin à la partie
    }

    // Sinon il a décidé d'arrêter de jouer et a perdu
    else {
      system("clear");
      display_board(p_level);
      printf("Dommage, vous avez perdu !\n");
      // calcul le temps écoulé depuis le début de la partie
      chrono(p_tp, p_temps);
      score(p_temps, p_level);
      // met fin à la partie
    }

  }
  return 0;
}
