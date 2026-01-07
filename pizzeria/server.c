#include "pizza_rack.h"
#include <time.h>

int main (int argc, char * argv[]) {
    // Initialize random seed
    srand(time(NULL) ^ getpid());
    
    P_rack* etagere;
    const char* smph_pizza = "sem_pizza"; // Semaphore for available pizzas.
    const char* smph_start = "sem_start"; // Semaphore to indicate service start.

    // Check number of arguments passed to program.
    if (argc != 2) {
        fprintf(stderr, "Usage %s: <shared memory name>\\n", argv[0]);
        return -1;
    }

    // Open shared memory.
    int fd_shm = shm_open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    if (fd_shm == -1) {
        perror("Shared memory open error");
        return -1;
    }

    // Map shared memory.
    etagere = mmap(NULL, sizeof(P_rack), PROT_WRITE | PROT_READ, MAP_SHARED, fd_shm, 0);
    if (etagere == MAP_FAILED) {
        perror("Mapping error");
        return -1;
    }
    printf("\\nShared memory! [%p]\\n", etagere);

    // Open semaphores.
    sem_t* sem_start = sem_open(smph_start, 0);
    if (sem_start == SEM_FAILED) {
        perror("sem_start open error");
        return -1;
    }

    sem_t* sem_pizza = sem_open(smph_pizza, 0);
    if (sem_pizza == SEM_FAILED) {
        perror("sem_pizza semaphore creation error");
        return -1;
    }
    
    printf("Ready for service! Chef!!\\n");
    if (sem_post(sem_start) < 0) {
        perror("sem_post error on sem_start");
        return -1;
    }

    // Pizza serving loop.
    for (int i = 1; i <= PIZZA_TOTAL; i++) {
        sem_wait(sem_pizza); // Wait to access the rack.
        if(etagere->pizzas > 0){
            etagere->pizzas--; // Remove a pizza from the rack.
            sem_post(sem_start); // Inform cook there is space for more pizzas.
            printf("\\nHot stuff coming through! (A pizza leaves the rack to be served)\\n There are %d pizza(s) left on the rack.\\n", etagere->pizzas);
        }
        sem_post(sem_pizza); // Release semaphore after serving a pizza.
        sleep(rand() % 6 + 2); // Service or waiting time.
        printf("The pizza is served!\\n");
    }

    printf("Well done! 10 pizzas served! \n");

    // Cleanup and close resources.
    sem_close(sem_start);
    sem_close(sem_pizza);
    munmap(etagere, sizeof(P_rack));
    shm_unlink(argv[1]);
    return 0;
}
