#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "ccd_sensor.h"
#include "afir_sensor.h"

#define GRID_SIZE 10
#define NUM_ANIMALS 5
#define SIMULATION_DURATION 60

int main() {
    srand(time(NULL));
    Animal animals[NUM_ANIMALS];
    for (int i = 0; i < NUM_ANIMALS; i++) {
        animals[i] = (Animal){i + 1, rand() % GRID_SIZE, rand() % GRID_SIZE, 36.0};
    }

    FILE *file;
    printf("\nWildlife & Fire Monitoring System\n");
    time_t start_time = time(NULL);
    time_t current_time;

    while ((current_time = time(NULL)) - start_time < SIMULATION_DURATION) {
        file = fopen("sensor_data.txt", "w");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }

        fprintf(file, "Step: %ld\n", current_time - start_time + 1);

        for (int x = 0; x < GRID_SIZE; x++) {
            for (int y = 0; y < GRID_SIZE; y++) {
                float temp = get_temperature(x, y);
                if (detect_fire(temp)) {
                    fprintf(file, "FIRE %d %d %.2f\n", x, y, temp);
                    printf("Fire at (%d, %d): %.2f°C\n", x, y, temp);
                }
            }
        }

        for (int i = 0; i < NUM_ANIMALS; i++) {
            track_animal(&animals[i]);
            fprintf(file, "ANIMAL %d %.1f %.1f %.1f\n", animals[i].id, animals[i].x, animals[i].y, animals[i].heat_signature);
            printf("Animal %d: (%.1f, %.1f) %.1f°C\n", animals[i].id, animals[i].x, animals[i].y, animals[i].heat_signature);
        }

        fclose(file);
        sleep(1);
    }

    printf("Simulation completed after %d seconds.\n", SIMULATION_DURATION);
    return 0;
}
