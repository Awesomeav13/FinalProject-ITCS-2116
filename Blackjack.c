#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Instructions for Blackjack Game
void printInstructions() {
    printf("Welcome to Simple Blackjack Game!\n");
    printf("Instructions:\n");
    printf("1. You will be dealt two cards initially.\n");
    printf("2. Your goal is to get as close to 21 as possible without going over.\n");
    printf("3. You can choose to 'hit' to receive another card or 'stand' to keep your current hand.\n");
    printf("4. The dealer will also be dealt two cards, but one card will be face-down.\n");
    printf("5. The dealer must hit until their total is 17 or higher.\n");
    printf("6. If you go over 21, you bust and lose the game.\n");
    printf("7. If the dealer goes over 21 or if your total is higher than the dealer's without going over 21, you win.\n");
    printf("8. If both you and the dealer have the same total, it's a tie.\n");
    printf("Let's start!\n\n");
}

// Define structures
typedef enum {HEARTS, DIAMONDS, CLUBS, SPADES} Suit;
typedef enum {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING} Rank;

typedef struct {
    Suit suit;
    Rank rank;
} Card;

typedef struct {
    Card hand[12]; // Max hand size is 12 (to accommodate for potential multiple Aces)
    int numCards;
} Player;

// Function prototypes
void initializeDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void dealCards(Card deck[], Player* player, int numCards);
void displayHand(Player* player);
int calculateHandValue(Player* player);
void playGame(Card deck[], Player* player, Player* dealer);

int main() {
    Card deck[52];
    Player player, dealer;

    initializeDeck(deck);
    shuffleDeck(deck);

    dealCards(deck, &player, 2);
    dealCards(deck, &dealer, 2);

    printInstructions();
    playGame(deck, &player, &dealer);

    return 0;
}

void initializeDeck(Card deck[]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            deck[i * 13 + j].suit = i;
            deck[i * 13 + j].rank = j + 1;
        }
    }
}

void shuffleDeck(Card deck[]) {
    srand(time(NULL));
    int i, j;
    Card temp;
    for (i = 0; i < 52; i++) {
        j = rand() % 52;
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

void dealCards(Card deck[], Player* player, int numCards) {
    int i;
    for (i = 0; i < numCards; i++) {
        player->hand[player->numCards++] = deck[--numCards];
    }
}

void displayHand(Player* player) {
    int i;
    for (i = 0; i < player->numCards; i++) {
        // Print card representation
    }
}

int calculateHandValue(Player* player) {
    int i, value = 0;
    for (i = 0; i < player->numCards; i++) {
        int rank = player->hand[i].rank;
        if (rank >= JACK && rank <= KING) {
            value += 10;
        } else if (rank == ACE) {
            value += 11;
        } else {
            value += rank;
        }
    }
    // Adjust for Aces if necessary
    for (i = 0; i < player->numCards; i++) {
        if (player->hand[i].rank == ACE && value > 21) {
            value -= 10;
        }
    }
    return value;
}

void playGame(Card deck[], Player* player, Player* dealer) {
    char choice;
    printf("Your hand:\n");
    displayHand(player);
    printf("Your total: %d\n", calculateHandValue(player));

    printf("Dealer's hand:\n");
    printf("Card 1: [Hidden]\n");
    printf("Card 2: [Visible]\n");
    printf("Dealer's total: %d\n", dealer->hand[1].rank); // Display only the visible card of the dealer

    while (1) {
        printf("Hit (h) or Stand (s): ");
        scanf(" %c", &choice);

        if (choice == 'h') {
            dealCards(deck, player, 1);
            printf("Your hand:\n");
            displayHand(player);
            printf("Your total: %d\n", calculateHandValue(player));

            if (calculateHandValue(player) > 21) {
                printf("Bust! You lose.\n");
                return;
            }
        } else if (choice == 's') {
            break;
        } else {
            printf("Invalid choice. Please enter 'h' for Hit or 's' for Stand.\n");
        }
    }

    // Dealer's turn
    while (calculateHandValue(dealer) < 17) {
        dealCards(deck, dealer, 1);
        printf("Dealer hits.\n");
    }

    printf("Dealer's hand:\n");
    displayHand(dealer);
    printf("Dealer's total: %d\n", calculateHandValue(dealer));

    // Determine winner
    int playerTotal = calculateHandValue(player);
    int dealerTotal = calculateHandValue(dealer);

    if (playerTotal > 21 || (dealerTotal <= 21 && dealerTotal > playerTotal)) {
        printf("Dealer wins!\n");
    } else if (dealerTotal > 21 || (playerTotal <= 21 && playerTotal > dealerTotal)) {
        printf("You win!\n");
    } else {
        printf("It's a tie!\n");
    }
}
