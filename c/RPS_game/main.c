#include "rps_game.h"

int main() {
    int user_score = 0;
    int comp_score = 0;

    initialize_random();

    printf("\n========== Welcome to Rock Paper Scissor Game ==========\n");
    printf("\nThere will be %d rounds in total.\n", NUM_ROUNDS);

    for (int i = 0; i < NUM_ROUNDS; i++) {
        printf("\n*** ROUND %d of %d ***\n", i + 1, NUM_ROUNDS);

        Choice user_choice = get_user_choice();
        Choice comp_choice = get_computer_choice();

        int round_winner = determine_winner(user_choice, comp_choice);

        // Update scores
        if (round_winner == 1) {
            user_score++;
        } else if (round_winner == -1) {
            comp_score++;
        }

        // Print round results
        print_round_result(i + 1, user_choice, comp_choice, round_winner);

        printf("Current Score - You: %d, Computer: %d\n", user_score, comp_score);

        // Pause before the next round (if not the last round)
        if (i < NUM_ROUNDS - 1) {
             pause_execution();
        }
    }

    print_final_result(user_score, comp_score);

    printf("\nTHANK YOU FOR PLAYING!!!\n");

    return 0;
}