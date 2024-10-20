#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SCORE_WRONG -10
#define SCORE_RIGHT 100
#define TOTAL_WORDS 100
#define TOTAL_WORD_CHALLANGE 3

bool show[50]; ///used for which character to hide
char arr[TOTAL_WORDS][50]; ///word database. copy file words to local
bool displayed[TOTAL_WORDS]; ///tracking which word displayed, to prevent same word displaying more than once
int total_words = 0; ///total word displayed for playing
int dificulty_level = 1; ///player difficulty level

void generate_show(int len)
{
    for (int i = 0; i < len; ++i)
        show[i] = true;

    int shown = 0;
    int index = 0;
    while (shown < dificulty_level) {
        index = rand() % len;
        if (show[index]) {
            show[index] = false;
            ++shown;
        }
    }
}

void init_local_database(FILE* fp)
{
    total_words = 0;
    ///building local database
    while (fscanf(fp, "%s", arr[total_words]) == 1) {
        displayed[total_words] = false;
        ++total_words;
        if (total_words >= TOTAL_WORDS)
            break;
    }
}

int main()
{
    FILE* fp = fopen("words.txt", "r");
    if (fp == NULL) {
        printf( "unable to open file...");
        return -1;
    }

    init_local_database(fp);

    system("COLOR 03");

    printf("                                            Welcome to Word Puzzle Game!\n");
    printf("Which difficulty level you want to play?\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    scanf("%d", &dificulty_level);
    if (dificulty_level > 3 || dificulty_level < 1)
        dificulty_level = 3;
    printf("Difficulty level %d selected. Lets play.....\n\n", dificulty_level);

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    int index = rand() % TOTAL_WORDS;
    int count = 0;
    char inp[50];
    int score = 0;

    int word_displayed = 0;
    while (word_displayed < TOTAL_WORD_CHALLANGE) {
       printf("\nWord %d\n", word_displayed + 1);
       index = rand() % total_words;

        if (displayed[index] == false) {
            displayed[index] = true;
            word_displayed++;
            generate_show(strlen(arr[index]));

            int k = 0;
            while(arr[index][k]) {
                if (show[k]) {
                    printf("%c", arr[index][k]);
                }
                else
                    {
                    printf("_");
                }
                ++k;
            }

            printf("\n");
            printf("Enter your guess:\n");
            int try_count = 0;
            while (try_count < 3){
                scanf("%s", inp);

                if (strcmp(inp, arr[index]) == 0) {
                    printf("Congratulation!!!\n");
                    score += SCORE_RIGHT;
                    break;
                }
                else {
                    printf("Sorry! Try again...\n");
                    ++try_count;
                    score += SCORE_WRONG;
                }
            }
            if (try_count == 3) {
                printf("Correct word is: %s\n", arr[index]);
            }
        }
        ///printf("Your score is %d", score);
    }
    printf("Your total score is %d", score);

    fclose(fp);
    return 0;
}
