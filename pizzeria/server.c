#include "pizza_rack.h"

int main (int argc, char * argv[]) {
    P_rack* etagere;
    const char* smph_pizza = "sem_pizza"; // Sémaphore pour les pizzas disponibles.
    const char* smph_start = "sem_start"; // Sémaphore pour indiquer le début du service.

    // Vérification du nombre d'arguments passés au programme.
    if (argc != 2) {
        fprintf(stderr, "Usage %s: <shared memory name>\n", argv[0]);
        return -1;
    }

    // Ouverture de la mémoire partagée.
    int fd_shm = shm_open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    if (fd_shm == -1) {
        perror("Erreur d'ouverture de memoire partagée");
        return -1;
    }

    // Mapping de la mémoire partagée.
    etagere = mmap(NULL, sizeof(P_rack), PROT_WRITE | PROT_READ, MAP_SHARED, fd_shm, 0);
    if (etagere == MAP_FAILED) {
        perror("Erreur de mapping");
        return -1;
    }
    printf("\nMémoire partagée ! [%p]\n", etagere);

    // Ouverture des sémaphores.
    sem_t* sem_start = sem_open(smph_start, 0);
    if (sem_start == SEM_FAILED) {
        perror("Erreur d'ouverture de sem_start");
        return -1;
    }

    sem_t* sem_pizza = sem_open(smph_pizza, 0);
    if (sem_pizza == SEM_FAILED) {
        perror("Erreur de création du semaphore sem_pizza");
        return -1;
    }
    
    printf("Prêt pour le service! Chef!!.\n");
    if (sem_post(sem_start) < 0) {
        perror("Erreur sem_post sur sem_start");
        return -1;
    }

    // Boucle de service des pizzas.
    for (int i = 1; i <= PIZZA_TOTAL; i++) {
        sem_wait(sem_pizza); // Attente pour accéder à l'étagère.
        if(etagere->pizzas > 0){
            etagere->pizzas--; // Retrait d'une pizza de l'étagère.
            sem_post(sem_start); // Informer le cuisinier qu'il y a de l'espace pour plus de pizzas.
            printf("\nChaud devant! (Une pizza sort du rack pour être servie)\n Il reste %d pizza(s) sur le rack.\n", etagere->pizzas);
        }
        sem_post(sem_pizza); // Libération du sémaphore après avoir servi une pizza.
        sleep(rand() % 6 + 2); // Temps de service ou d'attente.
        printf("La pizza est servie !\n");
    }

    printf("Well done! 10 pizzas servies! \n");

    // Nettoyage et fermeture des ressources.
    sem_close(sem_start);
    sem_close(sem_pizza);
    munmap(etagere, sizeof(P_rack));
    return 0;
}
