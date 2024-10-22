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
    MatrixDense(unsigned m, unsigned n) : _m(m), _n(n) {
        if (m == 0 || n == 0) {
            throw std::invalid_argument("The dimensions of the matrix must be greater than zero.");
        }
        _data = new T[_m * _n]; // Выделение памяти для матрицы
    }

    // Деструктор
    ~MatrixDense() {
        delete[] _data; // Освобождение памяти
    }

    // Метод для доступа к элементам матрицы (неконстантный)
    T& operator()(unsigned i, unsigned j) {
        if (i >= _m || j >= _n) {
            throw std::out_of_range("The indexes go beyond the matrix.");
        }
        return _data[i * _n + j]; // Возврат элемента матрицы
    }

    // Метод для доступа к элементам матрицы (константный)
    const T& operator()(unsigned i, unsigned j) const {
        if (i >= _m || j >= _n) {
            throw std::out_of_range("The indexes go beyond the matrix.");
        }
        return _data[i * _n + j]; // Возврат элемента матрицы
    }

    // Метод для получения количества строк
    unsigned rows() const {
        return _m;
    }

    // Метод для получения количества столбцов
    unsigned cols() const {
        return _n;
    }

    // Метод для отображения матрицы
    void print() const {
        for (unsigned i = 0; i < _m; ++i) {
            for (unsigned j = 0; j < _n; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Метод для экспорта матрицы в текстовый файл
    void exportToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("The file could not be opened for writing");
        }

        for (unsigned i = 0; i < _m; ++i) {
            for (unsigned j = 0; j < _n; ++j) {
                outFile << (*this)(i, j);
                if (j < _n - 1) { // Не добавлять пробел после последнего элемента в строке
                    outFile << " ";
                }
            }
            outFile << std::endl; // Перевод строки после каждой строки матрицы
        }

        outFile.close(); // Закрытие файла
    }
};

#endif // MATRIX_H
