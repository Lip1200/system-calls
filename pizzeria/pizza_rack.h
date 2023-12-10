#ifndef PIZZA_RACK_H
#define PIZZA_RACK_H

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define PIZZA_TOTAL 10

typedef struct P_rack{
    int pizzas;
} P_rack;

#endif //PIZZA_RACK_H