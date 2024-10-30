#include "Matrix.h"

// Конструктор
template <typename T>
MatrixDense<T>::MatrixDense(unsigned m, unsigned n) : _m(m), _n(n) {
    if (m == 0 || n == 0) {
        throw std::invalid_argument("The dimensions of the matrix must be greater than zero.");
    }
    _data = new T[_m * _n]; // Выделение памяти для матрицы
    if (!_data) {
        throw std::runtime_error("Memory allocation failed for matrix.");
    }
}

// Деструктор
template <typename T>
MatrixDense<T>::~MatrixDense() {
    delete[] _data; // Освобождение памяти
}

// Метод для доступа к элементам матрицы (неконстантный)
template <typename T>
T& MatrixDense<T>::operator()(unsigned i, unsigned j) {
    if (i >= _m || j >= _n) {
        throw std::out_of_range("The indexes go beyond the matrix.");
    }
    return _data[i * _n + j]; // Возврат элемента матрицы
}

// Метод для доступа к элементам матрицы (константный)
template <typename T>
const T& MatrixDense<T>::operator()(unsigned i, unsigned j) const {
    if (i >= _m || j >= _n) {
        throw std::out_of_range("The indexes go beyond the matrix.");
    }
    return _data[i * _n + j]; // Возврат элемента матрицы
}

// Метод для получения количества строк
template <typename T>
unsigned MatrixDense<T>::rows() const {
    return _m;
}

// Метод для получения количества столбцов
template <typename T>
unsigned MatrixDense<T>::cols() const {
    return _n;
}

// Метод для отображения матрицы
template <typename T>
void MatrixDense<T>::print() const {
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

// Метод для экспорта матрицы в текстовый файл
template <typename T>
void MatrixDense<T>::exportToFile(std::ofstream& outFile, const std::string& title) const {
    outFile << title << std::endl;
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            outFile << (*this)(i, j);
            if (j < _n - 1) { // Не добавлять пробел после последнего элемента в строке
                outFile << " ";
            }
        }
        outFile << std::endl; // Перевод строки после каждой строки матрицы
    }
}

// Умножение матрицы на скаляр
template <typename T>
MatrixDense<T> MatrixDense<T>::scalarMultiply(T scalar) const {
    MatrixDense<T> result(_m, _n);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            result(i, j) = scalar * (*this)(i, j);
        }
    }
    return result;
}

// Поэлементное умножение
template <typename T>
MatrixDense<T> MatrixDense<T>::elementWiseMultiply(const MatrixDense<T>& other) const {
    if (_m != other._m || _n != other._n) {
        throw std::invalid_argument("Matrices must have the same dimensions for element-wise multiplication.");
    }
    MatrixDense<T> result(_m, _n);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            result(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return result;
}

// Матричное умножение
template <typename T>
MatrixDense<T> MatrixDense<T>::matrixMultiply(const MatrixDense<T>& other) const {
    if (_n != other._m) {
        throw std::invalid_argument("Number of columns in the first matrix must equal the number of rows in the second matrix.");
    }
    MatrixDense<T> result(_m, other._n);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < other._n; ++j) {
            for (unsigned k = 0; k < _n; ++k) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}

// Перегрузка оператора * для матричного умножения
template <typename T>
MatrixDense<T> MatrixDense<T>::operator*(const MatrixDense<T>& other) const {
    return matrixMultiply(other);
}

// Сложение матриц
template <typename T>
MatrixDense<T> MatrixDense<T>::operator+(const MatrixDense<T>& other) const {
    if (_m != other._m || _n != other._n) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }
    MatrixDense<T> result(_m, _n);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

// Вычитание матриц
template <typename T>
MatrixDense<T> MatrixDense<T>::operator-(const MatrixDense<T>& other) const {
    if (_m != other._m || _n != other._n) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }
    MatrixDense<T> result(_m, _n);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

// Транспонирование матрицы
template <typename T>
MatrixDense<T> MatrixDense<T>::transpose() const {
    MatrixDense<T> result(_n, _m);
    for (unsigned i = 0; i < _m; ++i) {
        for (unsigned j = 0; j < _n; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}


// Явная специализация для double
template class MatrixDense<double>;
