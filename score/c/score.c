// References:
// - https://www.w3schools.com/c/c_conditions.php
// - https://www.w3schools.com/c/c_data_types.php

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char teamName[30];
    int userPriority;
    int userType;
    double frequencyUse;
    double timeAnticipation;
    double penalty;
    double score;
    double finalScore;
} Reservation;

double normalize(int minValue, int maxValue, double value){
    if(value < minValue) return minValue;
    if(value > maxValue) return maxValue;
    return value;
}

void sortByScore(Reservation reservations[], int teamCount) {
    Reservation temp;

    for(int i = 0; i < teamCount - 1; i++) {
        for(int j = i + 1; j < teamCount; j++) {
            if(reservations[j].finalScore > reservations[i].finalScore) {
                temp = reservations[i];
                reservations[i] = reservations[j];
                reservations[j] = temp;
            }
        }
    }
}

int main()
{
    // Constants
    const double W1 = 0.30, W2 = 0.20, W3 = 0.25, W4 = 0.15, W5 = 0.10;
    const double MAX_FREQUENCY = 100.0;
    const double MAX_TIME = 72.0;
    const double MAX_PENALTY = 10.0;
    const double UMBRAL = 4.0;

    // Variables inputs
    int teamCount;

    // Variables process
    double frequencyNorm, anticipationNorm, penaltyNorm;

    // Variables outputs
    double score, finalScore;

    printf("Enter number of teams: ");
    scanf("%d", &teamCount);

    Reservation *reservations = malloc(teamCount * sizeof(Reservation));

    printf("######################## PRIORITIZATION OF RESERVATIONS ######################## \n");

    for(int i = 0; i < teamCount; i++) {
        printf("------------------------------------ DATA FOR TEAM %d ------------------------------------\n", i + 1);

        printf("Enter the team name: ");
        scanf("%s", reservations[i].teamName);

        printf("Enter user priority (1-5): ");
        scanf("%d", &reservations[i].userPriority);

        printf("Enter number historical reservations: ");
        scanf("%lf", &reservations[i].frequencyUse);

        printf("Enter hours before the reservations: ");
        scanf("%lf", &reservations[i].timeAnticipation);

        printf("Enter user type (1=normal, 2=premium): ");
        scanf("%d", &reservations[i].userType);

        printf("Enter previous cancellations: ");
        scanf("%lf", &reservations[i].penalty);

        // Process------------------------------------------------------------
        // Normalization inputs
        reservations[i].userPriority = normalize(1, 5, reservations[i].userPriority);
        reservations[i].userType = normalize(1, 2, reservations[i].userType);

        // 1- Normalization
        frequencyNorm = reservations[i].frequencyUse / MAX_FREQUENCY;
        anticipationNorm = reservations[i].timeAnticipation / MAX_TIME;
        penaltyNorm = reservations[i].penalty / MAX_PENALTY;

        // 2- Calculate score
        score = (W1 * (reservations[i].userPriority / 5.0)) + (W2 * frequencyNorm) + (W3 * anticipationNorm) + (W4 * (reservations[i].userType / 2.0)) - (W5 * penaltyNorm);

        // 3- Settings
        if(reservations[i].penalty > UMBRAL) score = score * 0.8;

        // 4- Final score
        finalScore = normalize(0, 1, score);

        reservations[i].score = score;
        reservations[i].finalScore = finalScore;
    }

    sortByScore(reservations, teamCount);

    // Output --------------------------------------------------------------
    printf("######################## SCORES ########################\n");
    printf("%-12s %-20s %-12s %-20s\n", "Reservation", "Team", "Score", "Final Score [0,1]");
    printf("%-12s %-20s %-12s %-20s\n", "-----------", "----", "-----", "-----------------");

    for(int i = 0; i < teamCount; i++) {
        printf("%-12d %-20s %-12.4lf %-20.4lf\n",
               i + 1,
               reservations[i].teamName,
               reservations[i].score,
               reservations[i].finalScore);
    }

    printf("######################## END PRIORITIZATION OF RESERVATIONS ########################\n");

    free(reservations);

    return 0;
}