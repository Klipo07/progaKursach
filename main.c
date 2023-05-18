#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

typedef struct WordFrequency {
    char word[MAX_WORD_LENGTH];
    int frequency;
} WordFrequency;

int isWordSeparator(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

void processTextFile(const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        printf("Failed to open input file.\n");
        return;
    }

    // Count characters and words
    int characterCount = 0;
    int wordCount = 0;

    char ch;
    while ((ch = fgetc(input)) != EOF) {
        characterCount++;

        if (isWordSeparator(ch)) {
            wordCount++;
        }
    }

    // Rewind the file pointer to read words
    rewind(input);

    // Allocate memory for storing words and their frequencies
    WordFrequency* wordFrequencies = malloc(wordCount * sizeof(WordFrequency));
    int numWords = 0;

    // Process each word in the input file
    char word[MAX_WORD_LENGTH];
    while (fscanf(input, "%s", word) == 1) {
        // Check if the word is already recorded
        int i;
        for (i = 0; i < numWords; i++) {
            if (strcmp(wordFrequencies[i].word, word) == 0) {
                wordFrequencies[i].frequency++;
                break;
            }
        }

        // If the word is not recorded, add it to the array
        if (i == numWords) {
            strncpy(wordFrequencies[numWords].word, word, MAX_WORD_LENGTH);
            wordFrequencies[numWords].frequency = 1;
            numWords++;
        }
    }

    // Close the input file
    fclose(input);

    // Open the output file
    FILE* output = fopen(outputFile, "w");
    if (output == NULL) {
        printf("Failed to open output file.\n");
        free(wordFrequencies);
        return;
    }

    // Sort the word frequencies in descending order
    for (int i = 0; i < numWords - 1; i++) {
        for (int j = 0; j < numWords - i - 1; j++) {
            if (wordFrequencies[j].frequency < wordFrequencies[j + 1].frequency) {
                WordFrequency temp = wordFrequencies[j];
                wordFrequencies[j] = wordFrequencies[j + 1];
                wordFrequencies[j + 1] = temp;
            }
        }
    }

    // Write the word frequencies to the output file
    for (int i = 0; i < numWords; i++) {
        if (wordFrequencies[i].frequency > 1) {
            fprintf(output, "%s - %d\n", wordFrequencies[i].word, wordFrequencies[i].frequency);
        }
    }

    // Close the output file
    fclose(output);

    // Free the memory
    free(wordFrequencies);

    printf("Character count: %d\n", characterCount);
    printf("Word count: %d\n", wordCount);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    processTextFile(inputFile, outputFile);

    return 0;
}