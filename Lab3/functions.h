#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm> // Для std::min_element и std::max_element
#include <utility>   // Для std::pair
#include <cmath>    // Для std::sqrt

// Функция для нахождения минимального и максимального элементов в вашем классе Vector
std::pair<std::pair<int, size_t>, std::pair<int, size_t>> findMinMax(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int min_value = numbers[0];
    int max_value = numbers[0];
    size_t min_index = 0;
    size_t max_index = 0;

    for (size_t i = 1; i < size; ++i) {
        if (numbers[i] < min_value) {
            min_value = numbers[i];
            min_index = i;
        }
        if (numbers[i] > max_value) {
            max_value = numbers[i];
            max_index = i;
        }
    }

    return {{min_value, min_index}, {max_value, max_index}};
}

// Функция для нахождения среднего значения элементов в векторе
double calculateAverage(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += numbers[i]; // Суммируем все элементы
    }

    return static_cast<double>(sum) / size; // Возвращаем среднее значение
}


double SumOfElements(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += numbers[i]; // Суммируем все элементы
    }

    return sum; // Возвращаем среднее значение
}

// Функция для вычисления манхэттенской нормы
double calculateManhattanNorm(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    double sum = 0.0; // Сумма абсолютных значений
    for (size_t i = 0; i < size; ++i) {
        sum += std::abs(numbers[i]); // Суммируем абсолютные значения элементов
    }

    return sum; // Возвращаем манхэттенскую норму
}

// Функция для вычисления евклидовой нормы
double calculateEuclideanNorm(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    double sumOfSquares = 0.0; // Сумма квадратов элементов
    for (size_t i = 0; i < size; ++i) {
        sumOfSquares += static_cast<double>(numbers[i]) * numbers[i]; // Суммируем квадраты элементов
    }

    return std::sqrt(sumOfSquares); // Возвращаем квадратный корень из суммы квадратов
}

// Функция для вычисления скалярного произведения
template <typename T>
T dotProduct(const Vector<T>& vec1, const Vector<T>& vec2) {
    if (vec1.getSize() != vec2.getSize()) {
        throw std::invalid_argument("Vectors must be of the same size for dot product.");
    }

    T result = 0;

    for (size_t i = 0; i < vec1.getSize(); ++i) {
        result += vec1[i] * vec2[i]; // Суммируем произведения соответствующих элементов
    }

    return result;
}

#endif // FUNCTIONS_H_INCLUDED
