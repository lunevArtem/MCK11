#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

template <typename T = double>
class MatrixDense {
private:
    unsigned _m; // Количество строк
    unsigned _n; // Количество столбцов
    T* _data;    // Указатель на данные матрицы

public:
    // Конструктор
    MatrixDense(unsigned m, unsigned n);

    // Деструктор
    ~MatrixDense();

    // Метод для доступа к элементам матрицы (неконстантный)
    T& operator()(unsigned i, unsigned j);

    // Метод для доступа к элементам матрицы (константный)
    const T& operator()(unsigned i, unsigned j) const;

    // Метод для получения количества строк
    unsigned rows() const;

    // Метод для получения количества столбцов
    unsigned cols() const;

    // Метод для отображения матрицы
    void print() const;

    // Метод для экспорта матрицы в текстовый файл
    void exportToFile(std::ofstream& outFile, const std::string& title) const;

    // Умножение матрицы на скаляр
    MatrixDense<T> scalarMultiply(T scalar) const;

    // Поэлементное умножение
    MatrixDense<T> elementWiseMultiply(const MatrixDense<T>& other) const;

    // Матричное умножение
    MatrixDense<T> matrixMultiply(const MatrixDense<T>& other) const;

    // Перегрузка оператора * для матричного умножения
    MatrixDense<T> operator*(const MatrixDense<T>& other) const;

    // Сложение матриц
    MatrixDense<T> operator+(const MatrixDense<T>& other) const;

    // Вычитание матриц
    MatrixDense<T> operator-(const MatrixDense<T>& other) const;

    // Транспонирование матрицы
    MatrixDense<T> transpose() const;

};

#endif // MATRIX_H
