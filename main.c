#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct {
    char* word;
    int frequency;
} WordFrequency;

void convertToLowercase(char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = tolower(text[i]);
    }
}

void countWords(char* text, WordFrequency** frequencies, int* count) {
    const char delimiters[] = " \t\n.,;:!?\"+)(-";
    char* word = strtok(text, delimiters);

    while (word != NULL) {
        // Преобразуем слово к нижнему регистру перед поиском и сохранением
        char* lowerWord = strdup(word);
        convertToLowercase(lowerWord);

        // Ищем слово в массиве frequencies
        int found = 0;
        for (int i = 0; i < *count; i++) {
            // Преобразуем слово из массива к нижнему регистру перед сравнением
            char* freqWord = strdup((*frequencies)[i].word);
            convertToLowercase(freqWord);

            if (strcmp(freqWord, lowerWord) == 0) {
                (*frequencies)[i].frequency++;
                found = 1;
                free(freqWord);
                break;
            }

            free(freqWord);
        }

        // Если слово не найдено, добавляем его в массив frequencies
        if (!found) {
            (*count)++;
            *frequencies = realloc(*frequencies, (*count) * sizeof(WordFrequency));
            (*frequencies)[(*count) - 1].word = strdup(lowerWord);
            (*frequencies)[(*count) - 1].frequency = 1;
        }

        free(lowerWord);
        word = strtok(NULL, delimiters);
    }
}

int compareFrequencies(const void* a, const void* b) {
    const WordFrequency* freqA = (const WordFrequency*)a;
    const WordFrequency* freqB = (const WordFrequency*)b;

    return freqB->frequency - freqA->frequency;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: calcFrequency <input_file> <output_file>\n");
        return 1;
    }

    // Открываем файлы для чтения и записи
    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Failed to open output file.\n");
        fclose(input);
        return 1;
    }

    // Получаем размер файла
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);

    // Выделяем память для текста
    char* text = malloc(size + 1);
    if (text == NULL) {
        printf("Memory allocation failed.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Читаем текст из файла
    fread(text, 1, size, input);
    text[size] = '\0';

    // Преобразуем все слова к нижнему регистру
    convertToLowercase(text);

    // Считаем количество слов и их частоту
    WordFrequency* frequencies = NULL;
    int count = 0;
    countWords(text, &frequencies, &count);

    // Сортируем слова по частоте встречаемости (в порядке убывания)
    qsort(frequencies, count, sizeof(WordFrequency), compareFrequencies);

    // Записываем результаты в файл
    for (int i = 0; i < count; i++) {
        if (frequencies[i].frequency > 1) {
            fprintf(output, "%s - %d\n", frequencies[i].word, frequencies[i].frequency);
        }
    }

    // Освобождаем память и закрываем файлы
    fclose(input);
    fclose(output);
    free(text);

    for (int i = 0; i < count; i++) {
        free(frequencies[i].word);
    }
    free(frequencies);

    printf("The word count was successful.\n");

    return 0;
}