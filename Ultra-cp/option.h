#ifndef OPTION_H
#define OPTION_H

/**
 * Analyse les options de la ligne de commande.
 * @param argc Le nombre d'arguments de la ligne de commande.
 * @param argv Les arguments de la ligne de commande.
 * @param isA Un pointeur vers un indicateur pour l'option -a.
 * @param isF Un pointeur vers un indicateur pour l'option -f.
 * @param nbOpt Un pointeur vers un compteur d'options.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int parseOptions(int argc, char* argv[], int* isA, int* isF, int* nbOpt);

#endif //OPTION_H
