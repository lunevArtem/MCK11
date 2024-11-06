#ifndef DENSEMATRIXARRAY_H
#define DENSEMATRIXARRAY_H

#include "DenseMatrix.h"
#include <vector>
#include <string> // Для использования std::string

class DenseMatrixArray {
private:
    std::vector<DenseMatrix*> matrices; // Вектор указателей на плотные матрицы

public:
    DenseMatrixArray(size_t size);
    ~DenseMatrixArray();

    void setMatrix(size_t index, DenseMatrix* matrix);
    DenseMatrix* getMatrix(size_t index) const;

    void print() const; // Печать матриц на экран
    void exportToFile(const std::string& filename) const; // Экспорт матриц в файл
};

#endif // DENSEMATRIXARRAY_H
