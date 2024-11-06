#ifndef DENSEMATRIXARRAY_H
#define DENSEMATRIXARRAY_H

#include "DenseMatrix.h"
#include <vector>
#include <string> // ��� ������������� std::string

class DenseMatrixArray {
private:
    std::vector<DenseMatrix*> matrices; // ������ ���������� �� ������� �������

public:
    DenseMatrixArray(size_t size);
    ~DenseMatrixArray();

    void setMatrix(size_t index, DenseMatrix* matrix);
    DenseMatrix* getMatrix(size_t index) const;

    void print() const; // ������ ������ �� �����
    void exportToFile(const std::string& filename) const; // ������� ������ � ����
};

#endif // DENSEMATRIXARRAY_H
