! References:
! - https://www.famaf.unc.edu.ar/~vmarconi/numerico1/FortranTutorial.pdf

program run_score
    implicit none

    ! Constants
    real, parameter :: w1 = 0.30
    real, parameter :: w2 = 0.20
    real, parameter :: w3 = 0.25
    real, parameter :: w4 = 0.15
    real, parameter :: w5 = 0.10
    real, parameter :: max_frequency = 100.0
    real, parameter :: max_time = 72.0
    real, parameter :: max_penalty = 10.0
    real, parameter :: umbral = 4.0

    ! Variables inputs
    integer :: user_priority
    integer :: user_type
    real :: frequency_use
    real :: time_anticipation
    real :: penalty

    ! Variables process
    real :: frequency_norm
    real :: anticipation_norm
    real :: penalty_norm

    ! Variables output
    real :: score
    real :: final_score

    print *, "######################## PRIORITIZATION OF RESERVATIONS ########################"

    ! Inputs
    print *, "Enter user priority (1-5):"
    read *, user_priority

    print *, "Enter number historical reservations:"
    read *, frequency_use

    print *, "Enter hours before the reservation:"
    read *, time_anticipation

    print *, "Enter user type (1=normal, 2=premium):"
    read *, user_type

    print *, "Enter previous cancellations:"
    read *, penalty

    ! Process------------------------------------------------------------
    ! Normalization inputs
    user_priority = max(1, min(user_priority, 5))
    user_type = max(1, min(user_type, 2)) 

    ! 1- Normalization
    frequency_norm = frequency_use / max_frequency
    anticipation_norm = time_anticipation / max_time
    penalty_norm = penalty / max_penalty

    ! 2- Calculate score
    score = (w1 * (user_priority / 5.0)) + (w2 * frequency_norm) + (w3 * anticipation_norm) + (w4 * (user_type / 2.0)) - (w5 * penalty_norm)

    ! 3- Settings
    if(penalty > umbral) score = score * 0.8

    ! 4- Final score
    final_score = max(0.0, min(score, 1.0))
    
    ! Output --------------------------------------------------------------
    print *, ">> Score:", score, "| Final score [0,1]:", final_score

    print *, "######################## END PRIORITIZATION OF RESERVATIONS ########################"

end program run_score