#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FLIGHTS 100

const char *destinations[] = {
    "New York", "London", "Paris", "Tokyo", "Dubai", "Singapore", "Sydney",
    "Toronto", "Los Angeles", "Berlin", "Amsterdam", "Rome", "Madrid",
    "Istanbul", "Seoul", "Bangkok", "Dublin", "Zurich", "Chicago", "Mumbai"
};

const char *statuses[] = {"On Time", "Delayed"};

void generate_flight_data(FILE *file) {
    srand(time(NULL));

    for (int i = 1; i <= NUM_FLIGHTS; i++) {
        const char *destination = destinations[rand() % (sizeof(destinations) / sizeof(destinations[0]))];
        int arrival_hour = rand() % 24;
        int arrival_minute = (rand() % 4) * 15;
        int departure_hour = (arrival_hour + 1 + rand() % 3) % 24;
        int departure_minute = (arrival_minute + 15) % 60;
        int gate = rand() % 20 + 1;
        const char *status = statuses[rand() % (sizeof(statuses) / sizeof(statuses[0]))];

        fprintf(file,
                "Flight ID: %d\n"
                "Destination: %s\n"
                "Arrival: %02d:%02d\n"
                "Departure: %02d:%02d\n"
                "Gate: %d\n"
                "Status: %s\n\n",
                i, destination, arrival_hour, arrival_minute, departure_hour, departure_minute, gate, status);
    }
}

int main() {
    FILE *file = fopen("flights.txt", "w");
    if (file == NULL) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    generate_flight_data(file);
    fclose(file);

    printf("flights.txt has been created with 100 flight entries.\n");
    return EXIT_SUCCESS;
}

