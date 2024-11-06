#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <iostream>
#include <vector>

class DenseMatrix {
private:
    unsigned rows;
    unsigned cols;
    std::vector<std::vector<double>> data; // Данные матрицы

public:
    DenseMatrix(unsigned r, unsigned c);
    void setValue(unsigned r, unsigned c, double value);
    double getValue(unsigned r, unsigned c) const;
    void print(std::ostream& os = std::cout) const;

    bool operator==(const DenseMatrix& other) const;
};

#endif // DENSEMATRIX_H
