#include <stdlib.h>

#ifndef AFIR_SENSOR_H
#define AFIR_SENSOR_H

// Structure to represent an animal
typedef struct {
    int id;
    float x, y;
    float heat_signature;
} Animal;

// Simulates animal movement
static inline void track_animal(Animal *animal) {
    animal->x += (rand() % 3) - 1; // Move randomly in X
    animal->y += (rand() % 3) - 1; // Move randomly in Y
    animal->heat_signature = 35.0 + (rand() % 5); // 35-40°C
}

#endif
