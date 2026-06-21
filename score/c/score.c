// References:
// - https://www.w3schools.com/c/c_conditions.php
// - https://www.w3schools.com/c/c_data_types.php

#include <stdio.h>

double normalize(int minValue, int maxValue, double value){
    if(value < minValue) return minValue;
    if(value > maxValue) return maxValue;
    return value;
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
    int userPriority, userType;
    double frequencyUse, timeAnticipation, penalty;

    // Variables process
    double frequencyNorm, anticipationNorm, penaltyNorm;
    
    // Variables outputs
    double score, finalScore;

    printf("######################## PRIORITIZATION OF RESERVATIONS ######################## \n");

    printf("Enter user priority (1-5): ");
    scanf("%d", &userPriority);

    printf("Enter number historical reservations: ");
    scanf("%lf", &frequencyUse);

    printf("Enter hours before the reservations: ");
    scanf("%lf", &timeAnticipation);

    printf("Enter user type (1=normal, 2=premium): ");
    scanf("%d", &userType);

    printf("Enter previous cancellations: ");
    scanf("%lf", &penalty);

    // Process------------------------------------------------------------
    // Normalization inputs
    userPriority = normalize(1, 5, userPriority);
    userType = normalize(1, 2, userType);

    // 1- Normalization
    frequencyNorm = frequencyUse / MAX_FREQUENCY;
    anticipationNorm = timeAnticipation / MAX_TIME;
    penaltyNorm = penalty / MAX_PENALTY;

    // 2- Calculate score
    score = (W1 * (userPriority / 5.0)) + (W2 * frequencyNorm) + (W3 * anticipationNorm) + (W4 * (userType / 2.0)) - (W5 * penaltyNorm);

    // 3- Settings
    if(penalty > UMBRAL) score = score * 0.8;

    // 4- Final score
    finalScore = normalize(0, 1, score);

    // Output --------------------------------------------------------------
    printf(">> Score: %lf | Final score [0,1]: %lf\n", score, finalScore);
    printf("######################## END PRIORITIZATION OF RESERVATIONS ########################");
    return 0;
}
