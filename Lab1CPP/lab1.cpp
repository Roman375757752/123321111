#define _CRT_SECURE_NO_WARNINGS

#include "array.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Функция для заполнения массива случайными числами
void fill_array_random(Array* arr) {
    srand(static_cast<unsigned int>(time(0)));  // Инициализация генератора случайных чисел
    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr, i, rand() % 100);  // Заполнение случайными числами от 0 до 99
    }
}

// Задача 1: Определить большее количество осадков в первой или второй половине июня
void task1(Array* arr) {
    size_t half_size = array_size(arr) / 2;  // Делим массив пополам
    int sum_first_half = 0, sum_second_half = 0;

    // Подсчет суммы осадков для первой и второй половины
    for (size_t i = 0; i < half_size; ++i) {
        sum_first_half += array_get(arr, i); // Первая половина
        sum_second_half += array_get(arr, i + half_size); // Вторая половина
    }

    std::cout << "Task 1: Rainfall comparison between first and second half of June:\n";
    if (sum_first_half > sum_second_half) {
        std::cout << "More rainfall in the first half of June.\n";
    } else if (sum_second_half > sum_first_half) {
        std::cout << "More rainfall in the second half of June.\n";
    } else {
        std::cout << "Equal rainfall in both halves of June.\n";
    }

    // Определение декады с наибольшим количеством осадков
    int sum_first_decade = 0, sum_second_decade = 0, sum_third_decade = 0;
    size_t one_third = array_size(arr) / 3;
    for (size_t i = 0; i < one_third; ++i) {
        sum_first_decade += array_get(arr, i); // Первая декада
        sum_second_decade += array_get(arr, i + one_third); // Вторая декада
        sum_third_decade += array_get(arr, i + 2 * one_third); // Третья декада
    }

    std::cout << "Task 1: Decade with the most rainfall:\n";
    if (sum_first_decade > sum_second_decade && sum_first_decade > sum_third_decade) {
        std::cout << "First decade had the most rainfall.\n";
    } else if (sum_second_decade > sum_first_decade && sum_second_decade > sum_third_decade) {
        std::cout << "Second decade had the most rainfall.\n";
    } else {
        std::cout << "Third decade had the most rainfall.\n";
    }
}

// Задача 2: Сдвиг элементов массива
void task2(Array* arr, int direction) {
    std::cout << "Task 2: Array shift:\n";

    size_t shift = 1;  // Шаг сдвига можно задать в input.txt
    Array* temp = array_create(array_size(arr));  // Создаем временный массив
    if (temp == nullptr) {
        std::cerr << "Failed to create temporary array.\n";
        return; // Завершение, если временный массив не создан
    }

    if (direction == 1) {  // Сдвиг влево
        for (size_t i = 0; i < array_size(arr) - shift; ++i) {
            array_set(temp, i, array_get(arr, i + shift));
        }
        for (size_t i = array_size(arr) - shift; i < array_size(arr); ++i) {
            array_set(temp, i, 0);  // Заполнение нулями
        }
    } else if (direction == 2) {  // Сдвиг вправо
        for (size_t i = shift; i < array_size(arr); ++i) {
            array_set(temp, i, array_get(arr, i - shift));
        }
        for (size_t i = 0; i < shift; ++i) {
            array_set(temp, i, 0);  // Заполнение нулями
        }
    }

    // Вывод массива после сдвига
    for (size_t i = 0; i < array_size(temp); ++i) {
        std::cout << array_get(temp, i) << " ";
    }
    std::cout << "\n";
    array_delete(temp);
}

int main() {
    std::ifstream input("index.txt");
    if (!input.is_open()) {
        std::cerr << "Failed to open input file\n";
        return 1;  // Завершение, если файл не открыт
    }

    int size1 = 10;  
    int size2 = 20; 
    int direction = 1; // Задаем направление сдвига (1 - влево, 2 - вправо)

    // Создание и заполнение массивов
    Array* arr1 = array_create(size1);  // Создаем массив для задачи 1
    if (arr1 == nullptr) {
        std::cerr << "Failed to create array 1.\n";
        return 1; // Завершение, если массив не создан
    }
    fill_array_random(arr1);  // Заполняем случайными числами

    Array* arr2 = array_create(size2);  // Создаем массив для задачи 2
    if (arr2 == nullptr) {
        std::cerr << "Failed to create array 2.\n";
        array_delete(arr1); // Удаляем первый массив, если второй не создан
        return 1; // Завершение, если массив не создан
    }
    fill_array_random(arr2);  // Заполняем случайными числами

    // Выполнение задачи 1
    task1(arr1);
    array_delete(arr1);  // Удаление массива после использования

    // Выполнение задачи 2
    task2(arr2, direction);  // Передаем массив и направление сдвига
    array_delete(arr2);  // Удаление массива после использования

    input.close();  // Закрываем файл
    return 0;  // Успешное завершение
}
