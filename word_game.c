#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char *get_player(void);
int get_points(char *word);
void print_results(char *player1, char *player2, int pts1, int pts2);
int processDictionary(const char *filename, const char *word);
char random_letters();

int main(void)
{
    srand(time(NULL));

    char letters[10];

    for (int i = 0; i < 10; i++)
    {
        letters[i] = random_letters();
    }

    printf("Your letters are:\n");
    printf("%s\n\n", letters);

    printf("WELCOME TO A SCRABBLE GAME - PLEASE FOLLOW THE INSTRUCTIONS TO PLAYER\n");

    printf("\nNo PLURALS accepted...\n");
    printf("Player 1 enter word: ");
    char *player1 = get_player();

    if (player1 == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("\nNo PLURALS accepted...\n");
    printf("Player 2 enter word: ");
    char *player2 = get_player();

    if (player1 == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Call the function to process the dictionary file and search for a word
    int check1 = processDictionary("dictionary.txt", player1);
    int check2 = processDictionary("dictionary.txt", player2);

    int pts1 = get_points(player1);
    int pts2 = get_points(player2);

    print_results(player1, player2, pts1, pts2);

    free(player1);
    free(player2);

    return 0;
}

char *get_player(void)
{
    char *word = malloc(MAX_WORD_LENGTH * sizeof(char));

    if (word == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fgets(word, MAX_WORD_LENGTH, stdin);
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == '\n')
    {
        word[len - 1] = '\0';
    }

    return word;
}

int get_points(char *word)
{
    int points = 0;

    if (word == NULL)
    {
        fprintf(stderr, "Word is not initialized\n");
        return 1;
    }

    size_t length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        points += POINTS[toupper(word[i]) - 65];
    }

    return points;
}

void print_results(char *player1, char *player2, int pts1, int pts2)
{
    printf("\nPlayer 1: %s  --  %d points", player1, pts1);
    printf("        ");
    printf("Player 2: %s  --  %d points\n", player2, pts2);

    if (pts1 < pts2)
    {
        printf("\nPlayer 2 WINS !\n");
    }
    else if (pts1 > pts2)
    {
        printf("\nPlayer 1 WINS !\n");
    }
    else if (pts1 == pts2)
    {
        printf("\nTIE !\n");
    }
}

int processDictionary(const char *filename, const char *word)
{

    char line[100]; // Assuming maximum line length is 100 characters

    // Open the dictionary file
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening dictionary file.\n");
        return 1;
    }

    // Search for the word in the dictionary
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Remove newline character from the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Compare the current line with the target word
        if (strcmp(line, word) == 0)
        {
            found = 1;
            break;
        }
    }

    // Close the dictionary file
    fclose(file);

    // Output the result
    if (found)
    {
        printf("The word \"%s\" is FOUND in the dictionary.\n", word);
    }
    else
    {
        printf("The word \"%s\" is NOT FOUND in the dictionary.\n", word);
    }

    return found;
}

char random_letters()
{
    char x = (rand() % 26) + 65;
    return x;
}
