#ifndef MATRIX_DIAGONAL_H
#define MATRIX_DIAGONAL_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream> // ��� std::ofstream

template <typename T = double>
class MatrixDiagonal {
private:
    unsigned _size; // ������ ������� (���������� ����� � ��������)
    std::vector<T> _mainDiagonal; // ������ ��� ������� ���������
    std::vector<T> _upperDiagonal; // ������ ��� ������� ���������
    std::vector<T> _lowerDiagonal; // ������ ��� ������ ���������

public:
    // �����������
    MatrixDiagonal(unsigned size);

    // ����������
    ~MatrixDiagonal();

    // ����� ������� � ��������� �������
    T& operator()(unsigned i, unsigned j);

    // ����� ��� ��������� ������� �������
    unsigned size() const;

    // ����� ��� ����������� �������
    void print() const;

    // ����� ��� �������� ������� � ��������� ����
    void exportToFile(std::ofstream& outFile, const std::string& title) const;

    // ����� ��� �������� ���� ������������ ������
    MatrixDiagonal<T> operator+(const MatrixDiagonal<T>& other) const;

    // ����� ��� ��������� ���� ������������ ������
    MatrixDiagonal<T> operator-(const MatrixDiagonal<T>& other) const;

   // ������������ � ��������� ���������
    MatrixDiagonal<T> elementWiseMultiply(const MatrixDiagonal<T>& other) const;
    MatrixDiagonal<T> matrixMultiply(const MatrixDiagonal<T>& other) const;

    // ����� ��� ���������������� �������
    MatrixDiagonal<T> transpose() const;

    // ����� ��� ������������ ��������� ���� ������������ ������
    MatrixDiagonal<T> kroneckerProduct(const MatrixDiagonal<T>& other) const;
};

#endif // MATRIX_DIAGONAL_H
