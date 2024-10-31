#include "MatrixDiagonal.h"

// Конструктор
template <typename T>
MatrixDiagonal<T>::MatrixDiagonal(unsigned size) : _size(size),
    _mainDiagonal(size),
    _upperDiagonal(size - 1),
    _lowerDiagonal(size - 1) {
    if (size == 0) {
        throw std::invalid_argument("Size must be greater than zero.");
    }
}

// Деструктор
template <typename T>
MatrixDiagonal<T>::~MatrixDiagonal() {
    // Векторы автоматически освобождают память
}

// Метод доступа к элементам матрицы
template <typename T>
T& MatrixDiagonal<T>::operator()(unsigned i, unsigned j) {
    if (i >= _size || j >= _size) {
        throw std::out_of_range("Indexes out of range.");
    }
    if (i == j) {
        return _mainDiagonal[i]; // Главная диагональ
    } else if (i + 1 == j) {
        return _upperDiagonal[i]; // Верхняя диагональ
    } else if (i == j + 1) {
        return _lowerDiagonal[j]; // Нижняя диагональ
    } else {
        static T zero = 0; // Нулевое значение для не диагональных элементов
        return zero;
    }
}

// Метод для получения размера матрицы
template <typename T>
unsigned MatrixDiagonal<T>::size() const {
    return _size;
}

// Метод для отображения матрицы
template <typename T>
void MatrixDiagonal<T>::print() const {
    for (unsigned i = 0; i < _size; ++i) {
        for (unsigned j = 0; j < _size; ++j) {
            if (i == j) {
                std::cout << _mainDiagonal[i] << " "; // Главная диагональ
            } else if (i + 1 == j) {
                std::cout << _upperDiagonal[i] << " "; // Верхняя диагональ
            } else if (i == j + 1) {
                std::cout << _lowerDiagonal[j] << " "; // Нижняя диагональ
            } else {
                std::cout << "0 "; // Нулевой элемент
            }
        }
        std::cout << std::endl;
    }
}
// Вывод в файл
template <typename T>
void MatrixDiagonal<T>::exportToFile(std::ofstream& outFile, const std::string& title) const {
    outFile << title << std::endl;
    for (unsigned i = 0; i < _size; ++i) {
        for (unsigned j = 0; j < _size; ++j) {
            if (i == j) {
                outFile << _mainDiagonal[i]; // Главная диагональ
            } else if (i + 1 == j) {
                outFile << _upperDiagonal[i]; // Верхняя диагональ
            } else if (i == j + 1) {
                outFile << _lowerDiagonal[j]; // Нижняя диагональ
            } else {
                outFile << "0"; // Нулевой элемент
            }
            if (j < _size - 1) { // Не добавлять пробел после последнего элемента в строке
                outFile << " ";
            }
        }
        outFile << std::endl; // Перевод строки после каждой строки матрицы
    }
}

// Метод для сложения двух диагональных матриц
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::operator+(const MatrixDiagonal<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix sizes must be the same for addition.");
    }

    MatrixDiagonal<T> result(_size); // Создаем новую матрицу для результата

    for (unsigned i = 0; i < _size; ++i) {
        result(i, i) = this->_mainDiagonal[i] + other._mainDiagonal[i]; // Сложение главной диагонали

        if (i < _size - 1) {
            result(i, i + 1) = this->_upperDiagonal[i] + other._upperDiagonal[i]; // Сложение верхней диагонали
            result(i + 1, i) = this->_lowerDiagonal[i] + other._lowerDiagonal[i]; // Сложение нижней диагонали
        }
    }

    return result;
}

// Явная специализация для double (если нужно)
template class MatrixDiagonal<double>;
