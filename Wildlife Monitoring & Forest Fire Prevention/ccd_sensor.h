#include <stdlib.h>

#ifndef CCD_SENSOR_H
#define CCD_SENSOR_H

#define FIRE_THRESHOLD 60.0 // Fire detected above 60°C

// Simulates temperature readings (random for now)
static inline float get_temperature(int x, int y) {
    return 30.0 + (rand() % 40); // Random temp between 30-70°C
}

// Checks if temperature exceeds fire threshold
static inline int detect_fire(float temperature) {
    return (temperature >= FIRE_THRESHOLD);
}

#endif
