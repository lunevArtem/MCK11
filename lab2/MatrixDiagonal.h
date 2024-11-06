#ifndef MATRIX_DIAGONAL_H
#define MATRIX_DIAGONAL_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream> // Для std::ofstream

template <typename T = double>
class MatrixDiagonal {
private:
    unsigned _size; // Размер матрицы (количество строк и столбцов)
    std::vector<T> _mainDiagonal; // Вектор для главной диагонали
    std::vector<T> _upperDiagonal; // Вектор для верхней диагонали
    std::vector<T> _lowerDiagonal; // Вектор для нижней диагонали

public:
    // Конструктор
    MatrixDiagonal(unsigned size);

    // Деструктор
    ~MatrixDiagonal();

    // Метод доступа к элементам матрицы
    T& operator()(unsigned i, unsigned j);

    // Метод для получения размера матрицы
    unsigned size() const;

    // Метод для отображения матрицы
    void print() const;

    // Метод для экспорта матрицы в текстовый файл
    void exportToFile(std::ofstream& outFile, const std::string& title) const;

    // Метод для сложения двух диагональных матриц
    MatrixDiagonal<T> operator+(const MatrixDiagonal<T>& other) const;

    // Метод для вычитания двух диагональных матриц
    MatrixDiagonal<T> operator-(const MatrixDiagonal<T>& other) const;

   // Поэлементное и матричное умножение
    MatrixDiagonal<T> elementWiseMultiply(const MatrixDiagonal<T>& other) const;
    MatrixDiagonal<T> matrixMultiply(const MatrixDiagonal<T>& other) const;

    // Метод для транспонирования матрицы
    MatrixDiagonal<T> transpose() const;

    // Метод для произведения Кронекера двух диагональных матриц
    MatrixDiagonal<T> kroneckerProduct(const MatrixDiagonal<T>& other) const;
};

#endif // MATRIX_DIAGONAL_H
