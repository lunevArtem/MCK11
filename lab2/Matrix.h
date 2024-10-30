#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>

template <typename T = double>
class MatrixDense {
private:
    unsigned _m; // ���������� �����
    unsigned _n; // ���������� ��������
    T* _data;    // ��������� �� ������ �������

public:
    // �����������
    MatrixDense(unsigned m, unsigned n);

    // ����������
    ~MatrixDense();

    // ����� ��� ������� � ��������� ������� (�������������)
    T& operator()(unsigned i, unsigned j);

    // ����� ��� ������� � ��������� ������� (�����������)
    const T& operator()(unsigned i, unsigned j) const;

    // ����� ��� ��������� ���������� �����
    unsigned rows() const;

    // ����� ��� ��������� ���������� ��������
    unsigned cols() const;

    // ����� ��� ����������� �������
    void print() const;

    // ����� ��� �������� ������� � ��������� ����
    void exportToFile(std::ofstream& outFile, const std::string& title) const;

    // ��������� ������� �� ������
    MatrixDense<T> scalarMultiply(T scalar) const;

    // ������������ ���������
    MatrixDense<T> elementWiseMultiply(const MatrixDense<T>& other) const;

    // ��������� ���������
    MatrixDense<T> matrixMultiply(const MatrixDense<T>& other) const;

    // ���������� ��������� * ��� ���������� ���������
    MatrixDense<T> operator*(const MatrixDense<T>& other) const;

    // �������� ������
    MatrixDense<T> operator+(const MatrixDense<T>& other) const;

    // ��������� ������
    MatrixDense<T> operator-(const MatrixDense<T>& other) const;

    // ���������������� �������
    MatrixDense<T> transpose() const;

};

#endif // MATRIX_H
