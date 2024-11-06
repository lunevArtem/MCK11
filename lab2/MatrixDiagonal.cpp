#include "MatrixDiagonal.h"

// �����������
template <typename T>
MatrixDiagonal<T>::MatrixDiagonal(unsigned size) : _size(size),
    _mainDiagonal(size),
    _upperDiagonal(size - 1),
    _lowerDiagonal(size - 1) {
    if (size == 0) {
        throw std::invalid_argument("Size must be greater than zero.");
    }
}

// ����������
template <typename T>
MatrixDiagonal<T>::~MatrixDiagonal() {
    // ������� ������������� ����������� ������
}

// ����� ������� � ��������� �������
template <typename T>
T& MatrixDiagonal<T>::operator()(unsigned i, unsigned j) {
    if (i >= _size || j >= _size) {
        throw std::out_of_range("Indexes out of range.");
    }
    if (i == j) {
        return _mainDiagonal[i]; // ������� ���������
    } else if (i + 1 == j) {
        return _upperDiagonal[i]; // ������� ���������
    } else if (i == j + 1) {
        return _lowerDiagonal[j]; // ������ ���������
    } else {
        static T zero = 0; // ������� �������� ��� �� ������������ ���������
        return zero;
    }
}

// ����� ��� ��������� ������� �������
template <typename T>
unsigned MatrixDiagonal<T>::size() const {
    return _size;
}

// ����� ��� ����������� �������
template <typename T>
void MatrixDiagonal<T>::print() const {
    for (unsigned i = 0; i < _size; ++i) {
        for (unsigned j = 0; j < _size; ++j) {
            if (i == j) {
                std::cout << _mainDiagonal[i] << " "; // ������� ���������
            } else if (i + 1 == j) {
                std::cout << _upperDiagonal[i] << " "; // ������� ���������
            } else if (i == j + 1) {
                std::cout << _lowerDiagonal[j] << " "; // ������ ���������
            } else {
                std::cout << "0 "; // ������� �������
            }
        }
        std::cout << std::endl;
    }
}
// ����� � ����
template <typename T>
void MatrixDiagonal<T>::exportToFile(std::ofstream& outFile, const std::string& title) const {
    outFile << title << std::endl;
    for (unsigned i = 0; i < _size; ++i) {
        for (unsigned j = 0; j < _size; ++j) {
            if (i == j) {
                outFile << _mainDiagonal[i]; // ������� ���������
            } else if (i + 1 == j) {
                outFile << _upperDiagonal[i]; // ������� ���������
            } else if (i == j + 1) {
                outFile << _lowerDiagonal[j]; // ������ ���������
            } else {
                outFile << "0"; // ������� �������
            }
            if (j < _size - 1) { // �� ��������� ������ ����� ���������� �������� � ������
                outFile << " ";
            }
        }
        outFile << std::endl; // ������� ������ ����� ������ ������ �������
    }
}

// ����� ��� �������� ���� ������������ ������
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::operator+(const MatrixDiagonal<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix sizes must be the same for addition.");
    }

    MatrixDiagonal<T> result(_size); // ������� ����� ������� ��� ����������

    for (unsigned i = 0; i < _size; ++i) {
        result(i, i) = this->_mainDiagonal[i] + other._mainDiagonal[i]; // �������� ������� ���������

        if (i < _size - 1) {
            result(i, i + 1) = this->_upperDiagonal[i] + other._upperDiagonal[i]; // �������� ������� ���������
            result(i + 1, i) = this->_lowerDiagonal[i] + other._lowerDiagonal[i]; // �������� ������ ���������
        }
    }

    return result;
}

// ����� ��� ��������� ���� ������������ ������
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::operator-(const MatrixDiagonal<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix sizes must be the same for subtraction.");
    }

    MatrixDiagonal<T> result(_size); // ������� ����� ������� ��� ����������

    for (unsigned i = 0; i < _size; ++i) {
        result(i, i) = this->_mainDiagonal[i] - other._mainDiagonal[i]; // ��������� ������� ���������

        if (i < _size - 1) {
            result(i, i + 1) = this->_upperDiagonal[i] - other._upperDiagonal[i]; // ��������� ������� ���������
            result(i + 1, i) = this->_lowerDiagonal[i] - other._lowerDiagonal[i]; // ��������� ������ ���������
        }
    }

    return result;
}
// � ����� ���������� MatrixDiagonal.cpp
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::elementWiseMultiply(const MatrixDiagonal<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix sizes must be the same for multiplication.");
    }

    MatrixDiagonal<T> result(_size); // ������� ����� ������� ��� ����������

    for (unsigned i = 0; i < _size; ++i) {
        result(i, i) = this->_mainDiagonal[i] * other._mainDiagonal[i]; // ��������� ������� ���������

        if (i < _size - 1) {
            result(i, i + 1) = this->_upperDiagonal[i] * other._upperDiagonal[i]; // ��������� ������� ���������
            result(i + 1, i) = this->_lowerDiagonal[i] * other._lowerDiagonal[i]; // ��������� ������ ���������
        }
    }

    return result;
}

template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::matrixMultiply(const MatrixDiagonal<T>& other) const {
    if (_size != other._size) {
        throw std::invalid_argument("Matrix sizes must be the same for multiplication.");
    }

    MatrixDiagonal<T> result(_size); // ������� ����� ������� ��� ����������

    for (unsigned i = 0; i < _size; ++i) {
        // ��������� ������� ���������
        result(i, i) = this->_mainDiagonal[i] * other._mainDiagonal[i];

        // ��������� ������� � ������ ����������
        if (i < _size - 1) {
            result(i, i + 1) = this->_mainDiagonal[i] * other._upperDiagonal[i] +
                               this->_upperDiagonal[i] * other._mainDiagonal[i + 1]; // ��������� ��������������
            result(i + 1, i) = this->_lowerDiagonal[i] * other._mainDiagonal[i] +
                               this->_mainDiagonal[i + 1] * other._lowerDiagonal[i]; // ��������� ��������������
        }
    }

    return result;
}

// ����� ��� ���������������� �������
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::transpose() const {
    MatrixDiagonal<T> transposed(_size); // ������� ����� ������� ��� ����������

    // �������� ������� ���������
    for (unsigned i = 0; i < _size; ++i) {
        transposed(i, i) = this->_mainDiagonal[i];
    }

    // ������ ������� ������� � ������ ���������
    for (unsigned i = 0; i < _size - 1; ++i) {
        transposed(i + 1, i) = this->_upperDiagonal[i]; // ������� ��������� ���������� ������
        transposed(i, i + 1) = this->_lowerDiagonal[i]; // ������ ��������� ���������� �������
    }

    return transposed;
}

// ����� ��� ������������ ��������� ���� ������������ ������
template <typename T>
MatrixDiagonal<T> MatrixDiagonal<T>::kroneckerProduct(const MatrixDiagonal<T>& other) const {
    unsigned newSize = _size * other._size; // ����� ������ �������
    MatrixDiagonal<T> result(newSize); // ������� ����� ������� ��� ����������

    for (unsigned i = 0; i < _size; ++i) {
        for (unsigned j = 0; j < other._size; ++j) {
            // ������������ ��������� ������� ���������
            result(i * other._size + j, i * other._size + j) = this->_mainDiagonal[i] * other._mainDiagonal[j];

            // ���� ���� ������� � ������ ���������, ��������� ��
            if (i < _size - 1) {
                result(i * other._size + j, (i + 1) * other._size + j) = this->_upperDiagonal[i] * other._mainDiagonal[j];
            }
            if (j < other._size - 1) {
                result(i * other._size + j, i * other._size + (j + 1)) = this->_mainDiagonal[i] * other._upperDiagonal[j];
            }
            if (i < _size - 1 && j < other._size - 1) {
                result((i + 1) * other._size + j, i * other._size + j) = this->_lowerDiagonal[i] * other._mainDiagonal[j];
                result(i * other._size + (j + 1), i * other._size + j) = this->_mainDiagonal[i] * other._lowerDiagonal[j];
            }
        }
    }

    return result;
}


// ����� ������������� ��� double (���� �����)
template class MatrixDiagonal<double>;
