#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>


void remove_duplicates(int* array, int* size) {
    int* unique = (int*)malloc(*size * sizeof(int));
    int unique_index = 0;

    for (int i = 0; i < *size; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < unique_index; j++) {
            if (array[i] == unique[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique[unique_index] = array[i];
            unique_index++;
        }
    }

    for (int i = 0; i < unique_index; i++) {
        array[i] = unique[i];
    }
    *size = unique_index;

    free(unique);
}


void remove_negatives(int** array, int rows, int* sizes) {
    for (int i = 0; i < rows; i++) {
        int new_size = 0;
        for (int j = 0; j < sizes[i]; j++) {
            if (array[i][j] >= 0) {
                array[i][new_size++] = array[i][j];
            }
        }
        sizes[i] = new_size;
        array[i][new_size] = 100;
    }
}


void left_rotate(int* row, int size, int k) {
    int* temp = (int*)malloc(size * sizeof(int));


    for (int i = 0; i < size; i++) {
        temp[i] = row[(i + k) % size];
    }


    for (int i = 0; i < size; i++) {
        row[i] = temp[i];
    }

    free(temp);
}


void left_rotate_2d_array(int** array, int rows, int* sizes, int k) {
    for (int i = 0; i < rows; i++) {
        left_rotate(array[i], sizes[i], k);
    }
}


void print_2d_array(int** array, int rows, int* sizes) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", array[i][j]);
        }
        printf("100\n");
    }
}


void auto_fill_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 200 - 100;
    }
}


void manual_fill_array(int* array, int size) {
    char input_buffer[100];
    int value;
    char* end;
    for (int i = 0; i < size; i++) {
        do {
            printf("Введите %d элемент массива: ", i);
            scanf("%s", input_buffer);
            value = strtol(input_buffer, &end, 10);

            if (*end != '\0') {
                printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                while (getchar() != '\n');
            }
            else {
                array[i] = value;
            }
        } while (*end != '\0');
    }
}


void auto_fill_2d_array(int** array, int rows, int* sizes) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            array[i][j] = rand() % 200 - 100;
        }
        array[i][sizes[i]] = 100;
    }
}

void manual_fill_2d_array(int** array, int rows, int* sizes) {
    char input_buffer[100];
    int value;
    char* end;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            do {
                printf("Введите элемент [%d][%d]: ", i, j);
                scanf("%s", input_buffer);
                value = strtol(input_buffer, &end, 10);

                if (*end != '\0') {
                    printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                    while (getchar() != '\n');
                }
                else {
                    array[i][j] = value;
                }
            } while (*end != '\0');
        }
        array[i][sizes[i]] = 100;
    }
}

void printarray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n;
    char input[100];
    int numbertask, array_size;
    char* end;
    int continue_program = 1;

    while (continue_program) {
        do {
            printf("Выберите номер задания (всего 3):\n");
            scanf("%s", input);
            numbertask = strtol(input, &end, 10);
            if (*end != '\0' || numbertask > 3 || numbertask < 1) {
                printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                while (getchar() != '\n');
            }
        } while (*end != '\0' || numbertask > 3 || numbertask < 1);

        if (numbertask == 1) {
            do {
                printf("Введите размер массива (если размер больше 10000000, то будет использовано более 1 ГБ ОЗУ):\n");
                scanf("%s", input);
                array_size = strtol(input, &end, 10);
                if (*end != '\0' || array_size <= 0) {
                    printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                    while (getchar() != '\n');
                }
                else {
                    int* array = (int*)malloc(array_size * sizeof(int));
                    if (array == NULL) {
                        printf("Ошибка выделения памяти!\n");
                        return 1;
                    }
                    int fill_option;
                    do {
                        printf("Выберите способ заполнения массива (1 - Автоматически, 2 - Вручную): ");
                        scanf("%s", input);
                        fill_option = strtol(input, &end, 10);
                        if (*end != '\0' || (fill_option != 1 && fill_option != 2)) {
                            printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                            while (getchar() != '\n');
                        }
                    } while (*end != '\0' || (fill_option != 1 && fill_option != 2));

                    if (fill_option == 1) {
                        auto_fill_array(array, array_size);
                    }
                    else {
                        manual_fill_array(array, array_size);
                    }

                    printf("Массив до удаления дубликатов:\n");
                    printarray(array, array_size);
                    remove_duplicates(array, &array_size);
                    printf("Массив после удаления дубликатов:\n");
                    printarray(array, array_size);

                    free(array);
                }
            } while (*end != '\0' || array_size <= 0);
        }
        else if (numbertask == 2) {
            int rows;
            printf("Введите количество строк в двумерном массиве: ");
            scanf("%d", &rows);

            int** array2d = (int**)malloc(rows * sizeof(int*));
            int* sizes = (int*)malloc(rows * sizeof(int));

            for (int i = 0; i < rows; i++) {
                printf("Введите количество элементов в строке %d (последний элемент 100): ", i);
                scanf("%d", &sizes[i]);

                array2d[i] = (int*)malloc((sizes[i] + 1) * sizeof(int));
            }

            int fill_option;
            do {
                printf("Выберите способ  заполняния массива(1 - Автоматически, 2 - Вручную) : ");
                scanf("%s", input);
                fill_option = strtol(input, &end, 10);
                if (*end != '\0' || (fill_option != 1 && fill_option != 2)) {
                    printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                    while (getchar() != '\n');
                }
            } while (*end != '\0' || (fill_option != 1 && fill_option != 2));

            if (fill_option == 1) {
                auto_fill_2d_array(array2d, rows, sizes);
            }
            else {
                manual_fill_2d_array(array2d, rows, sizes);
            }

            printf("Двумерный массив до удаления отрицательных элементов:\n");
            print_2d_array(array2d, rows, sizes);

            remove_negatives(array2d, rows, sizes);

            printf("Двумерный массив после удаления отрицательных элементов:\n");
            print_2d_array(array2d, rows, sizes);

            for (int i = 0; i < rows; i++) {
                free(array2d[i]);
            }
            free(array2d);
            free(sizes);
        }
        else if (numbertask == 3) {
            int rows;
            printf("Введите количество строк в двумерном массиве: ");
            scanf("%d", &rows);

            int** array2d = (int**)malloc(rows * sizeof(int*));
            int* sizes = (int*)malloc(rows * sizeof(int));

            for (int i = 0; i < rows; i++) {
                printf("Введите количество элементов в строке %d: ", i);
                scanf("%d", &sizes[i]);

                array2d[i] = (int*)malloc(sizes[i] * sizeof(int));
            }

            int fill_option;
            do {
                printf("Выберите способ заполнения массива (1 - Автоматически, 2 - Вручную): ");
                scanf("%s", input);
                fill_option = strtol(input, &end, 10);
                if (*end != '\0' || (fill_option != 1 && fill_option != 2)) {
                    printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                    while (getchar() != '\n');
                }
            } while (*end != '\0' || (fill_option != 1 && fill_option != 2));

            if (fill_option == 1) {
                auto_fill_2d_array(array2d, rows, sizes);
            }
            else {
                manual_fill_2d_array(array2d, rows, sizes);
            }

            printf("Двумерный массив до циклического сдвига:\n");
            print_2d_array(array2d, rows, sizes);

            printf("Введите количество позиций для циклического сдвига влево: ");
            int k;
            scanf("%d", &k);

            left_rotate_2d_array(array2d, rows, sizes, k);

            printf("Двумерный массив после циклического сдвига на %d позиций:\n", k);
            print_2d_array(array2d, rows, sizes);

            for (int i = 0; i < rows; i++) {
                free(array2d[i]);
            }
            free(array2d);
            free(sizes);
        }
        do {
            printf("Хотите начать заново? (1 - Да, 0 - Нет): ");
            scanf("%s", input);
            continue_program = strtol(input, &end, 10);
            if (*end != '\0' || (continue_program != 1 && continue_program != 0))
            {
                printf("Некорректный ввод, пожалуйста, попробуйте снова.\n");
                while (getchar() != '\n');
            }
        } while (*end != '\0' ||
            (continue_program != 1 && continue_program != 0));
    } printf("Программа завершена.\n");
    return 0;
}