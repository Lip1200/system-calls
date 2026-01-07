#include "pizza_rack.h"
#include <time.h>

int main (int argc, char * argv[]) {
    // Initialize random seed
    srand(time(NULL) ^ getpid());
    
    // Variable initialization.
    P_rack* etagere;  // Pointer for pizza rack.
    const char* smph_pizza = "sem_pizza"; // Semaphore for available pizzas.
    const char* smph_start = "sem_start"; // Semaphore to indicate service start.

    // Check number of arguments passed to program.
    if (argc != 2) {
        fprintf(stderr, "Usage %s: <shared memory name>\\n", argv[0]);
        return -1;
    }

    // Create and open shared memory.
    int fd_shm = shm_open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_shm < 0) {
        perror("Shared memory open error");
        return -1;
    }

    // Allocate size to shared memory.
    if (ftruncate(fd_shm, sizeof(P_rack)) < 0) {
        perror("Size allocation error");
        return -1;
    }

    // Map shared memory into process address space.
    etagere = mmap(NULL, sizeof(P_rack), PROT_READ | PROT_WRITE, MAP_SHARED, fd_shm, 0);
    if (etagere == MAP_FAILED) {
        perror("Mapping error");
        return -1;
    }
    printf("\\nShared memory! [%p]\\n", etagere);
    etagere->pizzas = 0; // Initialize pizza counter.

    // Create semaphores.
    sem_t* sem_start = sem_open(smph_start, O_CREAT, 0666, 0);
    if (sem_start == SEM_FAILED) {
        perror("sem_start semaphore creation error");
        return -1;
    }

    sem_t* sem_pizza = sem_open(smph_pizza, O_CREAT, 0666, 1);
    if (sem_pizza == SEM_FAILED) {
        perror("dispo semaphore creation error");
        return -1;
    }

    // Wait for server signal to start.
    printf("\\nWaiter!!!\\n");
    if (sem_wait(sem_start) < 0) {
        perror("sem_wait error on sem_start");
        return -1;
    }

    // Pizza preparation loop.
    for (int i = 1; i <= PIZZA_TOTAL; i++) {
        sem_wait(sem_pizza); // Semaphore to access the rack.
        if(etagere->pizzas < 3) {
            etagere->pizzas++; // Add a pizza to the rack.
            printf("A pizza is ready! There are now %d pizza(s) on the rack.\\n", etagere->pizzas);
            printf("There are %d pizza(s) left to prepare.\\n", PIZZA_TOTAL - i);
            sem_post(sem_pizza); // Signal to server that a pizza is ready.
        } else {
            printf("The rack is full!! The cook is resting...\\n");
            sem_post(sem_pizza); 
            sem_wait(sem_start); 
            i--;
        }

        printf("The cook is preparing a pizza...\\n");
        sleep(rand() % 3 + 2); // Simulate pizza preparation.
    }

    printf("Well done! 10 pizzas prepared!\\n");

    // Cleanup and close resources.
    sem_unlink(smph_pizza);
    sem_unlink(smph_start);
    sem_close(sem_start);
    sem_close(sem_pizza);
    munmap(etagere, sizeof(P_rack));
    return 0;
}
