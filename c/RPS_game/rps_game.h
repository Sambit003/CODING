#ifndef RPS_GAME_H
#define RPS_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
#define NUM_ROUNDS 3

// Enum for game choices for better readability
typedef enum {
    ROCK = 1,       // Start from 1 to match user input easily
    PAPER = 2,
    SCISSORS = 3,
    INVALID_CHOICE = 0 // Represents an invalid selection
} Choice;

// --- Function Prototypes ---

/**
 * @brief Seeds the random number generator. Should be called once at the start.
 */
void initialize_random();

/**
 * @brief Prompts the user for their choice and validates the input.
 * @return The user's valid choice (ROCK, PAPER, or SCISSORS) or INVALID_CHOICE if input fails repeatedly.
 */
Choice get_user_choice();

/**
 * @brief Generates the computer's random choice.
 * @return The computer's choice (ROCK, PAPER, or SCISSORS).
 */
Choice get_computer_choice();

/**
 * @brief Converts a Choice enum value to its string representation.
 * @param choice The Choice enum value.
 * @return A constant string representation ("Rock", "Paper", "Scissor", "Invalid").
 */
const char* choice_to_string(Choice choice);

/**
 * @brief Determines the winner of a single round.
 * @param user The user's choice.
 * @param computer The computer's choice.
 * @return 1 if the user wins, -1 if the computer wins, 0 for a tie.
 */
int determine_winner(Choice user, Choice computer);

/**
 * @brief Prints the results of a single round.
 * @param round_num The current round number.
 * @param user_choice The user's choice.
 * @param comp_choice The computer's choice.
 * @param winner The result of the round (1=user, -1=comp, 0=tie).
 */
void print_round_result(int round_num, Choice user_choice, Choice comp_choice, int winner);

/**
 * @brief Prints the final game score and declares the overall winner.
 * @param user_score The final score of the user.
 * @param comp_score The final score of the computer.
 */
void print_final_result(int user_score, int comp_score);

/**
 * @brief Clears the input buffer after reading input.
 * Useful after scanf or similar functions to prevent leftover newlines.
 */
void clear_input_buffer();

/**
 * @brief Pauses execution until the user presses Enter.
 * A portable alternative to system("pause").
 */
void pause_execution();


#endif // RPS_GAME_H