#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

char board[3][3];
int currentPlayer = 1;
int singlePlayer = 0;

// Function prototypes
void initializeBoard();
void clearScreen();
void printBoard();
void displayLastBoard();
int checkWin();
int makeMove(int row, int col, int symbol);
void aiMove();
void playSinglePlayer();
void playMultiplayer();
char coinToss();

int main() {
    system("cls");  // Clear the screen
    printf(" \033[1;32m  \n");

    int choice;
    int playAgain;

    printf("                            Welcome to Tic-Tac-Toe!\n                      ");

    do {
        printf(" \033[1;32m  \n");

        initializeBoard(); // Reset the board for a new game

        char coinResult = coinToss();
        if (coinResult == 'H') {
            printf("                            Player 1 (Heads) starts first!\n");
            currentPlayer = 1;
        } else {
            printf("                            Player 2 (Tails) starts first!\n");
            currentPlayer = 2;
        }

        int validChoice = 0;
        while (!validChoice) {
            printf("                            Select the mode:\n");
            printf("                            1. Multiplayer\n");
            printf("                            2. Single Player\n");
            printf("                            3. Quit Game\n\t\t\t\t");
            if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2 && choice != 3)) {
                printf("                            Invalid input. Please enter 1 for Single Player, 2 for Multiplayer, or 3 to quit the game.\n");
                while (getchar() != '\n'); // Clear the input buffer
            } else {
                validChoice = 1;
            }
        }

        if (choice == 2) {
            singlePlayer = 1;
        } else if (choice == 1) {
            singlePlayer = 0; // Reset singlePlayer for multiplayer
        } else if (choice == 3) {
            return 0; // Quit the game
        }

        if (singlePlayer) {
            playSinglePlayer();
        } else {
            playMultiplayer();
        }

        printf("                            Do you want to play again? (1 for yes, 0 for no): ");
        scanf("%d", &playAgain);
        displayLastBoard(); // Display the last board and reset it
        system("cls"); // Clear the screen
        printf(" \033[1;32m  \033[1;0m \n");
    } while (playAgain);

    return 0;
}

void initializeBoard() {
    // Initialize the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void clearScreen() {
    // Clear the screen
    system("cls");
}

void printBoard() {
    clearScreen();
    printf("                            \n");
    printf("                               Tic-Tac-Toe\n\n");
    printf("                               1 | 2 | 3\n");
    printf("                              ---|---|---\n");
    printf("                               4 | 5 | 6\n");
    printf("                              ---|---|---\n");
    printf("                               7 | 8 | 9\n");
    printf("                            \n");

    // Display the current state of the board with 'X' and 'O' symbols.
    printf("                               Current Board\n");
    printf("                               %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("                              ---|---|---\n");
    printf("                               %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("                              ---|---|---\n");
    printf("                               %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("                            \n");
}

void displayLastBoard() {
    printBoard();
    // Reset the last board to an empty state
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return 1;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return 1;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return 1;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }

    return -1; // Draw
}

int makeMove(int row, int col, int symbol) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return 0; // Invalid move
    }
    board[row][col] = symbol;
    return 1; // Valid move
}

void aiMove() {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    makeMove(row, col, 'O');
}

void playSinglePlayer() {
    int position;
    int moveCount = 0;

    initializeBoard();

    do {
        printBoard();

        if (currentPlayer == 1) {
            int validPosition = 0;
            while (!validPosition) {
                printf("                            Your turn. Enter a position (1-9): ");
                if (scanf("                            %d", &position) != 1) {
                    printf("                            Invalid input. Please enter a number between 1 and 9.\n");
                    while (getchar() != '\n'); // Clear the input buffer
                } else {
                    int row = (position - 1) / 3;
                    int col = (position - 1) % 3;

                    if (position >= 1 && position <= 9 && makeMove(row, col, 'X')) {
                        moveCount++;
                        validPosition = 1;
                    } else {
                        printf("                            Invalid move. Try again.\n");
                    }
                }
            }
        } else {
            aiMove();
            moveCount++;
        }

        int result = checkWin();
        if (result == 1) {
            printBoard();
            if (currentPlayer == 1) {
                printf("                            You win!\n");
            } else {
                printf("                            AI wins!\n");
            }
            break;
        } else if (result == -1) {
            printBoard();
            printf("                            It's a draw!\n");
            break;
        }

        currentPlayer = 3 - currentPlayer;
    } while (moveCount < 9);
}

void playMultiplayer() {
    char *player1_name = (char *)malloc(20 * sizeof(char));
    char *player2_name = (char *)malloc(20 * sizeof(char));

    printf("                            Enter the name of Player 1: ");
    scanf("                            %s", player1_name);

    printf("                            Enter the name of Player 2: ");
    scanf("                            %s", player2_name);

    int position;
    int moveCount = 0;

    initializeBoard();

    do {
        printBoard();

        printf("                            %s's turn. Enter a position (1-9): ", (currentPlayer == 1) ? player1_name : player2_name);
        int validPosition = 0;
        while (!validPosition) {
            if (scanf("%d", &position) != 1 || position < 1 || position > 9) {
                printf("                            Invalid input. Enter a number between 1 and 9.\n");
                while (getchar() != '\n'); // Clear the input buffer
            } else {
                int row = (position - 1) / 3;
                int col = (position - 1) % 3;

                if (makeMove(row, col, (currentPlayer == 1) ? 'X' : 'O')) {
                    moveCount++;
                    validPosition = 1;
                } else {
                    printf("                            Invalid move. Try again.\n");
                }
            }
        }

        int result = checkWin();
        if (result == 1) {
            printBoard();
            printf("                            %s wins!\n", (currentPlayer == 1) ? player1_name : player2_name);
            break;
        } else if (result == -1) {
            printBoard();
            printf("                            It's a draw!\n");
            break;
        }

        currentPlayer = 3 - currentPlayer;
    } while (moveCount < 9);
}

char coinToss() {
    return rand() % 2 == 0 ? 'H' : 'T';
}

#endif
