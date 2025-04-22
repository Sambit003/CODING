/*
srand() ka full form hota hai: seed random.
rand() function pseudo-random numbers deta hai, but agar seed fix ho toh wo same sequence dega.
time(NULL) current time in seconds return karta hai since January 1, 1970 (Epoch time).
srand(time(NULL)) har second mein seed change karta hai so that rand() har baar different output de.

srand() se hum rand() ko ek starting point dete hain jisko seed bolte hain.
Taaki har baar rand() ka output alag ho, srand() ko alag seed chahiye hoti hai.
srand() sets a global/internal seed used by rand() globally
srand() ka effect global hota hai, function boundary matter nahi karti.
Ek baar srand() call karne ke baad, rand() kahin bhi use kar lo — same sequence follow karega.

rand() ek random integer deta hai (0 se RAND_MAX tak). On most systems (especially Windows or GCC-based compilers),
RAND_MAX = 32767 (i.e., 2¹⁵ - 1)
% x ka matlab hai, us random number ko x ke range mein lana (0 se x-1 tak).
So agar x = 10, toh function 0 se 9 tak random number dega.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_rand_num(int x)
{
    return (rand() % x) + 1;
}

int main()
{
// Random seed — ek hi baar set karna hai, baar baar nahi
    srand(time(NULL)); // Call srand(time(NULL)); once at the beginning of main() instead of in the generate_rand_num() function.
    int comp_score = 0, user_score = 0, user_choice, prog_choice, play_again;
    printf("\n========== Welcome to Rock Paper Scissor Game ==========\n");
    printf("\nThere will be Three rounds in total.\n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("\n***ROUND %d***\n", i + 1);
        printf("\nSelect the corresponding number: \n1. Rock\n2. Paper\n3. Scissor\nEnter your choice: ");
        scanf("%d", &user_choice);
        if (user_choice >= 1 && user_choice <= 3)
        {
            if (user_choice == 1)
            {
                printf("\n--> You choosed Rock\n");
            }
            else if (user_choice == 2)
            {
                printf("\n--> You choosed Paper\n");
            }
            else if (user_choice == 3)
            {
                printf("\n--> You choosed Scissor\n");
            }
            prog_choice = generate_rand_num(3);

            if (prog_choice == 1)
            {
                printf("--> Computer choosed Rock\n");
            }
            else if (prog_choice == 2)
            {
                printf("--> Computer choosed Paper\n");
            }
            else if (prog_choice == 3)
            {
                printf("--> Computer choosed Scissor\n");
            }

            if (user_choice == prog_choice)
            {
                printf("\n\nTHE MATCH IS A TIE!!!\n\n", i + 1);
            }
            else if ((user_choice == 1 && prog_choice == 2) || (user_choice == 3 && prog_choice == 1) || (user_choice == 2 && prog_choice == 3))
            {
                printf("\nComputer wins!!!\n\n");
                comp_score++;
            }
            else
            {
                printf("\nYou win!!!\n\n");
                user_score++;
            }
        }
        else
        {
            int valid = 0;
            while (!valid) // Keep asking until the input is valid.
            {
                printf("\nInvalid input! Please enter 1, 2, or 3 only.\n");
                printf("\nDo you want to continue playing?\n1. YES\n2. NO\nEnter your choice: ");
                scanf("%d", &play_again);

                if (play_again == 1 || play_again == 2)
                {
                    valid = 1;
                }
                else
                {
                    printf("Please enter a valid option (1 or 2)!\n");
                }
            }

            if (play_again == 2)
            {
                printf("\nThanks for playing!\n");
                return 0;
            }
            else
            {
                // Restart this round (by reducing i)
                i--;
                system("pause");
                system("cls");
                continue;
            }
        }
        system("pause");
        system("cls");
    }
    if ((user_choice >= 1 && user_choice <= 3))
    {
        if (user_score > comp_score)
        {
            printf("\nYOU WON THE GAME! (USER = %d - COMP = %d)\n", user_score, comp_score);
        }
        else if (comp_score > user_score)
        {
            printf("\nCOMPUTER WON THE GAME! (USER = %d - COMP = %d)\n", user_score, comp_score);
        }
        else
        {
            printf("\nTHE GAME IS A TIE! (USER = %d - COMP = %d)\n", user_score, comp_score);
        }
    }
    printf("\nTHANK YOU FOR PLAYING!!!\n");
    return 0;
}