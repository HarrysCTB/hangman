#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include "list.h"

int isValidLine(char *line) {
    char *copy = strdup(line);
    char *field = strtok(copy, ",");
    int fieldCount = 0;
    while (field != NULL) {
        fieldCount++;
        if (fieldCount == 3) {
            if (strcmp(field, "facile") != 0 && strcmp(field, "moyen") != 0 && strcmp(field, "difficile") != 0) {
                free(copy);
                return 0;
            }
        }
        field = strtok(NULL, ",");
    }
    free(copy);
    return fieldCount == 3;
}

void handleDictionaryErrors(char *dictionaryFile) {
    FILE *file = fopen(dictionaryFile, "r");
    if (file == NULL) {
        printw("Erreur d'ouverture du fichier %s\n", dictionaryFile);
        exit(1);
    }

    char line[256];
    int lineNumber = 1;
    int validWordsCount = 0;

    while (fgets(line, sizeof(line), file)) {
        if (!isValidLine(line)) {
            printw("Erreur à la ligne %d: %s\n", lineNumber, line);
        } else {
            validWordsCount++;
        }
        lineNumber++;
    }

    if (validWordsCount == 0) {
        printw("Erreur: Le dictionnaire ne contient aucun mot valide.\n");
        exit(1);
    }

    fclose(file);
}

Element chooseRandomWord(Node *list) {
    int count = 0;
    Node *current = list;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count == 0) {
        Element empty = {0};
        return empty;
    }

    int chosenIndex = rand() % count;

    current = list;
    for (int i = 0; i < chosenIndex; i++) {
        current = current->next;
    }

    return current->element;
}

void printGallows(int errors) {
    printw("================\n");
    printw("    || //    |\n");
    printw("    ||//     |\n");
    printw("    ||/      |\n");
    printw("    ||       %s\n", errors > 0 ? "O" : " ");
    printw("    ||      %s%s%s\n", errors > 2 ? "/" : " ", errors > 1 ? "|" : " ", errors > 3 ? "\\" : " ");
    printw("    ||       %s\n", errors > 4 ? "|" : " ");
    printw("    ||      %s %s\n", errors > 5 ? "/" : " ", errors > 6 ? "\\" : " ");
    printw("    ||\n");
    printw("    ||\n");
    printw("    ||\n");
    printw("==========\n");
}

void printWordState(const char *word, const bool *guessed) {
    printw("Word : ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalpha(word[i])) {
            printw("%c ", word[i]);
        } else {
            printw("%c ", guessed[i] ? word[i] : '*');
        }
    }
    printw("\n");
}

void playGame(const char *word, char *category) {
    int errors = 0;
    bool guessed[strlen(word)];
    memset(guessed, 0, sizeof(guessed));

    while (errors <= 6) {
        clear(); // Efface l'écran avant de redessiner
        printw("Category: %s\n", category);
        printGallows(errors);
        printWordState(word, guessed);

        char guess;
        printw("Enter your guess: ");
        refresh();
        guess = getch(); // Lit un caractère

        bool found = false;
        for (int i = 0; word[i] != '\0'; i++) {
            if (word[i] == guess) {
                guessed[i] = true;
                found = true;
            }
        }

        if (!found) {
            errors++;
        }

        bool wordComplete = true;
        for (int i = 0; word[i] != '\0'; i++) {
            if (!guessed[i]) {
                wordComplete = false;
                break;
            }
        }

        if (wordComplete) {
            printw("Congratulations! You've guessed the word '%s'\n", word);
            break;
        }
    }

    if (errors > 6) {
        clear();
        printGallows(errors);
        printw("Game over! The word was '%s'\n", word);
    }
}

CategoryNode *addCategoryToList(CategoryNode *list, char *category) {
    CategoryNode *newNode = malloc(sizeof(CategoryNode));
    strcpy(newNode->category, category);
    newNode->list = NULL;
    newNode->next = list;
    return newNode;
}

Node *addToList(Node *list, Element element) {
    Node *newNode = malloc(sizeof(Node));
    newNode->element = element;
    newNode->next = list;
    return newNode;
}

CategoryNode *findCategory(CategoryNode *list, char *category) {
    CategoryNode *node = list;
    while (node != NULL) {
        if (strcmp(node->category, category) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

Node *filterList(CategoryNode *categories, char *category, char *difficulty) {
    CategoryNode *categoryNode = findCategory(categories, category);
    if (categoryNode == NULL) {
        return NULL;
    }

    Node *filtered = NULL;
    Node *current = categoryNode->list;
    while (current != NULL) {
        if (strcmp(current->element.difficulty, difficulty) == 0) {
            Node *newNode = malloc(sizeof(Node));
            if (newNode == NULL) {
                printw("Erreur d'allocation de mémoire\n");
                return NULL;
            }

            newNode->element = current->element;
            newNode->next = NULL;

            if (filtered == NULL) {
                filtered = newNode;
            } else {
                Node *temp = filtered;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        current = current->next;
    }
    return filtered;
}

void trimNewline(char *str) {
    int length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}


CategoryNode *readDictionary(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    CategoryNode *categories = NULL;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#') {
            continue;
        }

        Element element;
        char *token = strtok(line, ",");
        strcpy(element.name, token);

        token = strtok(NULL, ",");
        strcpy(element.category, token);

        token = strtok(NULL, ",\n"); // Ajoutez \n pour éliminer les retours à la ligne
        strcpy(element.difficulty, token);
        trimNewline(element.difficulty); // Nettoyez le saut de ligne

        CategoryNode *category = findCategory(categories, element.category);
        if (category == NULL) {
            categories = addCategoryToList(categories, element.category);
            category = findCategory(categories, element.category);
        }
        if (category == NULL) {
            categories = addCategoryToList(categories, element.category);
            category = categories;
        }

        category->list = addToList(category->list, element);
    }

    fclose(file);
    return categories;
}

int main(int argc, char **argv) {
    initscr(); // Initialise l'écran pour l'utilisation de ncurses
    cbreak();  // Désactive la mise en tampon de ligne
    noecho();  // Désactive l'affichage automatique des touches frappées

    char replay = 'Y';

    if (argc != 4) {
        endwin(); // Restaure les paramètres normaux du terminal
        printf("Usage: ./hangman <dictionary.txt> <difficulty> <category>\n");
        return 1;
    }

    char *dictionaryFile = argv[1];
    char *difficulty = argv[2];
    char *category = argv[3];

    if (strcmp(difficulty, "facile") != 0 && strcmp(difficulty, "moyen") != 0 && strcmp(difficulty, "difficile") != 0) {
        endwin(); // Restaure les paramètres normaux du terminal
        printf("Invalid difficulty. Choose between 'facile', 'moyen', or 'difficile'.\n");
        return 1;
    }

    for (int i = 0; category[i] != '\0'; i++) {
        if (!isalpha(category[i])) {
            endwin(); // Restaure les paramètres normaux du terminal
            printf("Invalid category. The category must only contain letters.\n");
            return 1;
        }
    }
    handleDictionaryErrors(dictionaryFile);
    srand(time(NULL));
    while (replay == 'Y' || replay == 'y') {
        CategoryNode *categories = readDictionary(dictionaryFile);
        Node *filteredWords = filterList(categories, category, difficulty);
        Element selectedElement = chooseRandomWord(filteredWords);
        if (selectedElement.name[0] != '\0') {
            playGame(selectedElement.name, category);
        } else {
            printw("No words found for the selected category and difficulty.\n");
            break;
        }

        printw("Do you want to play again? (Y/N): ");
        refresh();
        replay = getch();
    }
    endwin(); // Restaure les paramètres normaux du terminal
    return 0;
}
