#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "list.h"

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
    printf("================\n");
    printf("    || //    |\n");
    printf("    ||//     |\n");
    printf("    ||/      |\n");
    printf("    ||       %s\n", errors > 0 ? "O" : " ");
    printf("    ||      %s%s%s\n", errors > 2 ? "/" : " ", errors > 1 ? "|" : " ", errors > 3 ? "\\" : " ");
    printf("    ||       %s\n", errors > 4 ? "|" : " ");
    printf("    ||      %s %s\n", errors > 5 ? "/" : " ", errors > 6 ? "\\" : " ");
    printf("    ||\n");
    printf("    ||\n");
    printf("    ||\n");
    printf("==========\n");
}

void printWordState(const char *word, const bool *guessed) {
    printf("Word : ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalpha(word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("%c ", guessed[i] ? word[i] : '*');
        }
    }
    printf("\n");
}

void playGame(const char *word, char *category) {
    int errors = 0;
    bool guessed[strlen(word)];
    memset(guessed, 0, sizeof(guessed));

    while (errors <= 6) {
        printf("Category: %s\n", category);
        printGallows(errors);
        printWordState(word, guessed);

        char guess;
        printf("Enter your guess: ");
        scanf(" %c", &guess);

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
            printf("Congratulations! You've guessed the word '%s'\n", word);
            break;
        }
    }

    if (errors > 6) {
        printGallows(errors);
        printf("Game over! The word was '%s'\n", word);
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
                printf("Erreur d'allocation de mémoire\n");
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
    char replay = 'Y';

    if (argc != 4) {
        printf("Usage: ./hangman <dictionary.txt> <difficulty> <category>\n");
        return 1;
    }

    char *dictionaryFile = argv[1];
    char *difficulty = argv[2];
    char *category = argv[3];

    if (strcmp(difficulty, "facile") != 0 && strcmp(difficulty, "moyen") != 0 && strcmp(difficulty, "difficile") != 0) {
        printf("Invalid difficulty. Choose between 'facile', 'moyen', or 'difficile'.\n");
        return 1;
    }

    for (int i = 0; category[i] != '\0'; i++) {
        if (!isalpha(category[i])) {
            printf("Invalid category. The category must only contain letters.\n");
            return 1;
        }
    }

    srand(time(NULL));
    while (replay == 'Y') {
        CategoryNode *categories = readDictionary(dictionaryFile);
        Node *filteredWords = filterList(categories, category, difficulty);
        Element selectedElement = chooseRandomWord(filteredWords);
        if (selectedElement.name[0] != '\0') {
            playGame(selectedElement.name, category);
        } else {
            printf("No words found for the selected category and difficulty.\n");
            return 1;
        }

        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &replay);

    }

    return 0;
}
