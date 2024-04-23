#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINNING_SPACE 100 // Winning space
#define PURPLE_SPACE_BACK 3 // Number of spaces to move back for purple special space
#define BLUE_SPACE_FORWARD 4 // Number of spaces to move forward for blue special space
#define MIN_DISTANCE_TO_SPECIAL_SPACES 10 // Minimum distance from the winning space to place special spaces

// Function to roll a six-sided die
int rollDie() {
    return rand() % 6 + 1;
}

// Function to move a player's piece
int movePiece(int currentPosition, int spacesToMove) {
    int newPosition = currentPosition + spacesToMove;
    if (newPosition <= WINNING_SPACE) {
        return newPosition;
    } else {
        printf("Invalid move! You cannot go past space %d.\n", WINNING_SPACE);
        return currentPosition;
    }
}

// Function to perform a special event
void specialEvent(int playerNumber, int specialSpaceType) {
    if (specialSpaceType == 1) {
        printf("Player %d landed on a purple special space! Moving back by %d.\n", playerNumber, PURPLE_SPACE_BACK);
    } else if (specialSpaceType == 2) {
        printf("Player %d landed on a blue special space! Moving forward by %d.\n", playerNumber, BLUE_SPACE_FORWARD);
    }
}

// Function to draw the board with player positions and space numbers
void drawBoard(int player1Position, int player2Position) {
    printf("\n");
    for (int i = 1; i <= WINNING_SPACE; i++) {
        if (i == player1Position && i == player2Position) {
            printf("\033[1;33m██\033[0m"); // Yellow color for both players
        } else if (i == player1Position) {
            printf("\033[1;31m██\033[0m"); // Red color for Player 1
        } else if (i == player2Position) {
            printf("\033[1;32m██\033[0m"); // Green color for Player 2
        } else if ((i % 5 == 0 && i <= WINNING_SPACE - MIN_DISTANCE_TO_SPECIAL_SPACES) && i != WINNING_SPACE) { // Every 5th space (excluding the winning space)
            if (i % 10 == 0) {
                printf("\033[1;35mSS\033[0m"); // Purple special space
            } else {
                printf("\033[1;34mSS\033[0m"); // Blue special space
            }
        } else {
            if (i < 10)
                printf("0%d", i); // Add leading zero for single-digit numbers
            else
                printf("%d", i);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    int playAgain = 1; // Variable to track if the user wants to play again

    while (playAgain) {
        int player1Position = 0; // Starting position for player 1
        int player2Position = 0; // Starting position for player 2

        // Instructions for the game
        printf("Welcome to the Sorry! board game!\n");
        printf("Instructions:\n");
        printf("1. Each player starts at position 0.\n");
        printf("2. Players take turns rolling a six-sided die.\n");
        printf("3. Press enter to roll the die.\n");
        printf("4. Move your piece forward by the number of spaces shown on the die.\n");
        printf("5. Land on a purple special space (SS) to move back by %d.\n", PURPLE_SPACE_BACK);
        printf("6. Land on a blue special space (SS) to move forward by %d.\n", BLUE_SPACE_FORWARD);
        printf("7. The first player to reach or exceed space %d wins the game.\n", WINNING_SPACE);
        printf("8. Players are represented by colored rectangles: Red for Player 1, Green for Player 2.\n");
        printf("9. Enjoy playing with your friends or family!\n");

        // Game loop
        while (player1Position < WINNING_SPACE && player2Position < WINNING_SPACE) {
            // Draw the board with player positions
            drawBoard(player1Position, player2Position);

            // Player 1's turn
            printf("\nPlayer 1, press enter to roll the die.\n");
            getchar(); // Wait for player to press enter
            int roll1 = rollDie();
            printf("You rolled: %d\n", roll1);
            player1Position = movePiece(player1Position, roll1);
            printf("Player 1, your new position is: %d\n", player1Position);
            // Check if Player 1 won
            if (player1Position >= WINNING_SPACE) {
                printf("Player 1 wins!\n");
                break; // Exit the game loop
            }

            // Check if Player 1 landed on a special space
            if (player1Position % 5 == 0 && player1Position != WINNING_SPACE && player1Position <= WINNING_SPACE - MIN_DISTANCE_TO_SPECIAL_SPACES) {
                if (player1Position % 10 == 0) {
                    specialEvent(1, 1); // Purple special space
                    player1Position -= PURPLE_SPACE_BACK; // Move back by PURPLE_SPACE_BACK
                } else {
                    specialEvent(1, 2); // Blue special space
                    player1Position += BLUE_SPACE_FORWARD; // Move forward by BLUE_SPACE_FORWARD
                }
            }

            // Draw the board with updated player positions
            drawBoard(player1Position, player2Position);

            // Player 2's turn
            printf("\nPlayer 2, press enter to roll the die.\n");
            getchar(); // Wait for player to press enter
            int roll2 = rollDie();
            printf("You rolled: %d\n", roll2);
            player2Position = movePiece(player2Position, roll2);
            printf("Player 2, your new position is: %d\n", player2Position);
            // Check if Player 2 won
            if (player2Position >= WINNING_SPACE) {
                printf("Player 2 wins!\n");
                break; // Exit the game loop
            }

            // Check if Player 2 landed on a special space
            if (player2Position % 5 == 0 && player2Position != WINNING_SPACE && player2Position <= WINNING_SPACE - MIN_DISTANCE_TO_SPECIAL_SPACES) {
                if (player2Position % 10 == 0) {
                    specialEvent(2, 1); // Purple special space
                    player2Position -= PURPLE_SPACE_BACK; // Move back by PURPLE_SPACE_BACK
                } else {
                    specialEvent(2, 2); // Blue special space
                    player2Position += BLUE_SPACE_FORWARD; // Move forward by BLUE_SPACE_FORWARD
                }
            }
        }

        printf("\nDo you want to play again?\n");
        printf("Press '5' to play again or '2' to exit: ");
        scanf("%d", &playAgain);

        if (playAgain != 5) {
            printf("\nThanks for playing!\n");
            break;
        }
    }

    return 0;
}
