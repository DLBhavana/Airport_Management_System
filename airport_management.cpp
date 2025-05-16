#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FLIGHTS 100
#define MAX_PASSENGERS 200

// ---------------------- Structures --------------------------
typedef struct {
    int id;
    char destination[50];
    char arrivalTime[10];
    char departureTime[10];
    int gateNumber;
    int delayed; // 1 if delayed
} Flight;

typedef struct {
    int id;
    char name[50];
    char passport[20];
    int checkedIn; // 1 if checked in
} Passenger;

// ---------------------- Global Data --------------------------
Flight flights[MAX_FLIGHTS];
Passenger passengers[MAX_PASSENGERS];
int flightCount = 0;
int passengerCount = 0;

// ---------------------- Function Declarations ----------------
void loadFlightsFromFile();
void displayFlights();
void checkInPassenger();
void displayPassengers();
void handleDelay();
void manageBaggage();
void securityScreening();
void announceMessage();
int login();  // Declare the login function

// ---------------------- Main Menu ---------------------------
int main() {
    int choice;
    
    // Call login function
    if (!login()) {
        printf("Invalid login! Exiting...\n");
        return 0;
    }

    loadFlightsFromFile();  // Load flights on startup

    do {
        printf("\n--- Airport Management System ---\n");
        printf("1. Display Flights\n");
        printf("2. Check-in Passenger\n");
        printf("3. Display Passengers\n");
        printf("4. Delay a Flight\n");
        printf("5. Baggage Handling\n");
        printf("6. Security Screening\n");
        printf("7. Public Announcement\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: displayFlights(); break;
            case 2: checkInPassenger(); break;
            case 3: displayPassengers(); break;
            case 4: handleDelay(); break;
            case 5: manageBaggage(); break;
            case 6: securityScreening(); break;
            case 7: announceMessage(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid option!\n");
        }
    } while (choice != 0);

    return 0;
}

// ---------------------- Function Definitions ----------------

int login() {
    char username[20], password[20];

    // Predefined credentials (you can change these)
    const char correctUsername[] = "admin";
    const char correctPassword[] = "admin123";

    // Ask for username and password
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    strtok(username, "\n");  // Remove trailing newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    strtok(password, "\n");  // Remove trailing newline

    // Check if credentials are correct
    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        printf("Login successful!\n");
        return 1;  // Return 1 for successful login
    } else {
        printf("Invalid credentials!\n");
        return 0;  // Return 0 for failed login
    }
}

void loadFlightsFromFile() {
    FILE *file = fopen("flights.txt", "r");
    if (!file) {
        printf("Error: Could not open flights.txt\n");
        return;
    }

    while (flightCount < MAX_FLIGHTS && !feof(file)) {
        char status[20];

        fscanf(file, "Flight ID: %d\n", &flights[flightCount].id);
        fscanf(file, "Destination: %[^\n]\n", flights[flightCount].destination);
        fscanf(file, "Arrival: %s\n", flights[flightCount].arrivalTime);
        fscanf(file, "Departure: %s\n", flights[flightCount].departureTime);
        fscanf(file, "Gate: %d\n", &flights[flightCount].gateNumber);
        fscanf(file, "Status: %[^\n]\n\n", status);

        flights[flightCount].delayed = strcmp(status, "Delayed") == 0 ? 1 : 0;
        flightCount++;
    }

    fclose(file);
}

void displayFlights() {
    if (flightCount == 0) {
        printf("No flights available.\n");
        return;
    }

    for (int i = 0; i < flightCount; i++) {
        printf("\nFlight ID: %d\nDestination: %s\nArrival: %s\nDeparture: %s\nGate: %d\nStatus: %s\n",
            flights[i].id,
            flights[i].destination,
            flights[i].arrivalTime,
            flights[i].departureTime,
            flights[i].gateNumber,
            flights[i].delayed ? "Delayed" : "On Time");
    }
}

void checkInPassenger() {
    if (passengerCount >= MAX_PASSENGERS) {
        printf("Passenger limit reached!\n");
        return;
    }

    printf("Enter passenger name: ");
    fgets(passengers[passengerCount].name, 50, stdin);
    strtok(passengers[passengerCount].name, "\n");

    printf("Enter passport number: ");
    scanf("%s", passengers[passengerCount].passport);

    passengers[passengerCount].id = passengerCount + 1;
    passengers[passengerCount].checkedIn = 1;

    printf("Passenger checked in with ID: %d\n", passengers[passengerCount].id);
    passengerCount++;
}

void displayPassengers() {
    for (int i = 0; i < passengerCount; i++) {
        printf("\nID: %d\nName: %s\nPassport: %s\nStatus: %s\n",
            passengers[i].id,
            passengers[i].name,
            passengers[i].passport,
            passengers[i].checkedIn ? "Checked-In" : "Not Checked-In");
    }
}

void handleDelay() {
    int id;
    printf("Enter Flight ID to delay: ");
    scanf("%d", &id);
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].id == id) {
            flights[i].delayed = 1;
            printf("Flight %d marked as delayed.\n", id);
            return;
        }
    }
    printf("Flight ID not found.\n");
}

void manageBaggage() {
    int pid;
    printf("Enter Passenger ID for baggage check: ");
    scanf("%d", &pid);
    if (pid <= passengerCount && pid > 0) {
        printf("Baggage for passenger ID %d has been tagged and sorted.\n", pid);
    } else {
        printf("Invalid Passenger ID.\n");
    }
}

void securityScreening() {
    int pid;
    printf("Enter Passenger ID for security check: ");
    scanf("%d", &pid);
    if (pid <= passengerCount && pid > 0) {
        printf("Passenger ID %d cleared through security.\n", pid);
    } else {
        printf("Invalid Passenger ID.\n");
    }
}

void announceMessage() {
    char msg[100];
    printf("Enter announcement message: ");
    fgets(msg, 100, stdin);
    strtok(msg, "\n");
    printf("\n[Announcement]: %s\n", msg);
}

