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
    type :: Reservation
        character(len=30) :: team_name
        integer :: user_priority
        integer :: user_type
        real :: frequency_use
        real :: time_anticipation
        real :: penalty
        real :: score
        real :: final_score
    end type Reservation

    type(Reservation), allocatable :: reservations(:)
    integer :: team_count
    integer :: i

    ! Variables output
    real :: score
    real :: final_score

    print *, "Enter number of teams: "
    read *, team_count

    allocate(reservations(team_count))

    print *, "######################## PRIORITIZATION OF RESERVATIONS ########################"

    ! Inputs
    do i = 1, team_count 
        print *, "------------------------------------ DATA FOR TEAM ", i, " ------------------------------------"

        print *, "Enter the team name:"
        read *, reservations(i)%team_name

        print *, "Enter user priority (1-5):"
        read *, reservations(i)%user_priority

        print *, "Enter number historical reservations:"
        read *, reservations(i)%frequency_use

        print *, "Enter hours before the reservation:"
        read *, reservations(i)%time_anticipation

        print *, "Enter user type (1=normal, 2=premium):"
        read *, reservations(i)%user_type

        print *, "Enter previous cancellations:"
        read *, reservations(i)%penalty

        call calculate_score(reservations(i), score, final_score)

        reservations(i)%score = score
        reservations(i)%final_score = final_score
    end do

    call sort_by_score(reservations, team_count)

    ! Output --------------------------------------------------------------
    print *, "######################## SCORES ########################"
    write(*,'(A12,A20,A12,A25)') "Reservation", "Team", "Score", "Final Score [0, 1]"
    write(*,'(A12,A20,A12,A25)') "-----------", "----", "-----", "------------------"

    do i = 1, team_count
        write(*,'(I12,A20,F12.4,F25.4)') i, trim(reservations(i)%team_name), &
            reservations(i)%score, reservations(i)%final_score
    end do

    print *, "######################## END PRIORITIZATION OF RESERVATIONS ########################"
    
contains

    subroutine calculate_score(item, score, final_score)
        type(Reservation), intent(in) :: item
        real, intent(out) :: score
        real, intent(out) :: final_score

        real :: frequency_norm  ! Variable process
        real :: anticipation_norm ! Variable process
        real :: penalty_norm ! Variable process
        integer :: user_priority
        integer :: user_type

        ! Process------------------------------------------------------------
        ! Normalization inputs
        user_priority = max(1, min(item%user_priority, 5))
        user_type = max(1, min(item%user_type, 2)) 

        ! 1- Normalization
        frequency_norm = item%frequency_use / max_frequency
        anticipation_norm = item%time_anticipation / max_time
        penalty_norm = item%penalty / max_penalty

        ! 2- Calculate score
        score = (w1 * (user_priority / 5.0)) + (w2 * frequency_norm) + (w3 * anticipation_norm) + (w4 * (user_type / 2.0)) - (w5 * penalty_norm)

        ! 3- Settings
        if(item%penalty > umbral) score = score * 0.8

        ! 4- Final score
        final_score = max(0.0, min(score, 1.0))

    end subroutine calculate_score

    subroutine sort_by_score(reservations, n)
        type(Reservation), intent(inout) :: reservations(:)
        integer, intent(in) :: n
        integer :: i
        integer :: j
        type(Reservation) :: temp

        do i = 1, n - 1
            do j = i + 1, n
                if (reservations(j)%score > reservations(i)%score) then
                    temp = reservations(i)
                    reservations(i) = reservations(j)
                    reservations(j) = temp
                end if
            end do
        end do
    end subroutine sort_by_score

end program run_score