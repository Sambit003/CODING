#include "rps_game.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// --- Function Implementations ---

void initialize_random() {
    srand(time(NULL)); // Seed the random number generator once
}

// Helper function to generate random number in a range [min, max]
static int generate_rand_int(int min, int max) {
     // rand() % (max - min + 1) gives range [0, max-min]
     // Add min to shift range to [min, max]
    return min + (rand() % (max - min + 1));
}

Choice get_computer_choice() {
    // Generate a random number between 1 and 3 (inclusive)
    // and cast it to the Choice enum type.
    return (Choice)generate_rand_int(ROCK, SCISSORS);
}

const char* choice_to_string(Choice choice) {
    switch (choice) {
        case ROCK:     return "Rock";
        case PAPER:    return "Paper";
        case SCISSORS: return "Scissor";
        default:       return "Invalid";
    }
}

// Simple function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Portable pause function
void pause_execution() {
    printf("Press Enter to continue...");
    clear_input_buffer(); // Clear any potential leftover characters first
    getchar(); // Wait for Enter key
}


Choice get_user_choice() {
    int input = 0;
    char buffer[100]; // Buffer to read user input line

    printf("\nSelect the corresponding number: \n");
    printf("%d. Rock\n%d. Paper\n%d. Scissor\n", ROCK, PAPER, SCISSORS);
    printf("Enter your choice (1-3): ");

    while (1) { // Loop until valid input is received
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Try to parse an integer from the buffer
            if (sscanf(buffer, "%d", &input) == 1) {
                 // Check if the integer is within the valid range
                if (input >= ROCK && input <= SCISSORS) {
                    // Input is valid, cast to Choice and return
                    return (Choice)input;
                } else {
                    printf("Invalid choice. Please enter 1, 2, or 3: ");
                }
            } else {
                 // Input was not a valid integer
                 printf("Invalid input type. Please enter a number (1, 2, or 3): ");
            }
        } else {
            // fgets failed (e.g., EOF) - handle error or exit
            fprintf(stderr, "Error reading input.\n");
            return INVALID_CHOICE; // Indicate failure
        }
        // If we reach here, input was invalid, loop continues
    }
}


int determine_winner(Choice user, Choice computer) {
    if (user == computer) {
        return 0; // Tie
    }
    // Winning conditions for the user
    if ((user == ROCK && computer == SCISSORS) ||
        (user == PAPER && computer == ROCK) ||
        (user == SCISSORS && computer == PAPER))
    {
        return 1; // User wins
    }
    // Otherwise, the computer wins
    return -1; // Computer wins
}

void print_round_result(int round_num, Choice user_choice, Choice comp_choice, int winner) {
    printf("\n--- ROUND %d RESULTS ---\n", round_num);
    printf("--> You chose: %s\n", choice_to_string(user_choice));
    printf("--> Computer chose: %s\n", choice_to_string(comp_choice));

    if (winner == 0) {
        printf("\nOutcome: IT'S A TIE!\n");
    } else if (winner == 1) {
        printf("\nOutcome: YOU WIN THIS ROUND!\n");
    } else {
        printf("\nOutcome: COMPUTER WINS THIS ROUND!\n");
    }
    printf("-----------------------\n");
}

void print_final_result(int user_score, int comp_score) {
     printf("\n========== GAME OVER ==========\n");
     printf("Final Score: You = %d | Computer = %d\n", user_score, comp_score);

    if (user_score > comp_score) {
        printf("\nCONGRATULATIONS! YOU WON THE GAME!\n");
    } else if (comp_score > user_score) {
        printf("\nCOMPUTER WON THE GAME! Better luck next time.\n");
    } else {
        printf("\nTHE GAME IS A TIE!\n");
    }
     printf("=============================\n");
}