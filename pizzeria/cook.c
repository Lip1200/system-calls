#include "pizza_rack.h"

int main (int argc, char * argv[]) {
    // Initialisation des variables.
    P_rack* etagere;  // Pointeur pour l'étagère des pizzas.
    const char* smph_pizza = "sem_pizza"; // Sémaphore pour les pizzas disponibles.
    const char* smph_start = "sem_start"; // Sémaphore pour indiquer le début du service.

    // Vérification du nombre d'arguments passés au programme.
    if (argc != 2) {
        fprintf(stderr, "Usage %s: <shared memory name>\n", argv[0]);
        return -1;
    }

    // Création et ouverture de la mémoire partagée.
    int fd_shm = shm_open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_shm < 0) {
        perror("Erreur d'ouverture de memoire partagée");
        return -1;
    }

    // Attribution d'une taille à la mémoire partagée.
    if (ftruncate(fd_shm, sizeof(P_rack)) < 0) {
        perror("Erreur d'attribution de taille");
        return -1;
    }

    // Mapping de la mémoire partagée dans l'espace d'adressage du processus.
    etagere = mmap(NULL, sizeof(P_rack), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (etagere == MAP_FAILED) {
        perror("Erreur de mapping");
        return -1;
    }
    printf("\nMémoire partagée ! [%p]\n", etagere);
    etagere->pizzas = 0; // Initialisation du compteur de pizzas.

    // Création des sémaphores.
    sem_t* sem_start = sem_open(smph_start, O_CREAT, 0666, 0);
    if (sem_start == SEM_FAILED) {
        perror("Erreur de création du semaphore sem_start");
        return -1;
    }

    sem_t* sem_pizza = sem_open(smph_pizza, O_CREAT, 0666, 1);
    if (sem_pizza == SEM_FAILED) {
        perror("Erreur de création du semaphore dispo");
        return -1;
    }

    // Attente du signal du serveur pour commencer.
    printf("\nGarçon !!!\n");
    if (sem_wait(sem_start) < 0) {
        perror("Erreur sem_wait sur sem_start");
        return -1;
    }

    // Boucle de préparation des pizzas.
    for (int i = 1; i <= PIZZA_TOTAL; i++) {
        sem_wait(sem_pizza); // semaphore pour accéder à l'étagère.
        if(etagere->pizzas < 3) {
            etagere->pizzas++; // Ajout d'une pizza à l'étagère.
            printf("Une pizza est prête ! Il y a maintenant %d pizza(s) sur le rack.\n", etagere->pizzas);
            printf("Il reste %d pizza(s) à préparer.\n", PIZZA_TOTAL - i);
            sem_post(sem_pizza); // Signalement au serveur qu'une pizza est prête.
        } else {
            printf("Le rack est plein !! Le cuisto se repose...\n");
            sem_post(sem_pizza); 
            sem_wait(sem_start); 
            i--;
        }

        printf("Le cuisinier prépare une pizza...\n");
        sleep(rand() % 3 + 2); // Simulation de la préparation d'une pizza.
    }

    printf("Well done! 10 pizzas préparées !\n");

    // Nettoyage et fermeture des ressources.
    sem_unlink(smph_pizza);
    sem_unlink(smph_start);
    sem_close(sem_start);
    sem_close(sem_pizza);
    munmap(etagere, sizeof(P_rack));
    return 0;
}
