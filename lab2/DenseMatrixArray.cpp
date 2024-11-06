#include "DenseMatrixArray.h"
#include <fstream> // ��� ������ � �������

DenseMatrixArray::DenseMatrixArray(size_t size) : matrices(size, nullptr) {}

DenseMatrixArray::~DenseMatrixArray() {
    for (auto& matrix : matrices) {
        delete matrix; // ����������� ������
    }
}

void DenseMatrixArray::setMatrix(size_t index, DenseMatrix* matrix) {
    if (index < matrices.size()) {
        if (matrices[index] == nullptr) { // ���� ��� ��� ������� � ���� �������
            matrices[index] = matrix; // ��������� ��������� �� ����� �������
        } else if (*matrices[index] == *matrix) { // ���� ������� ����������
            delete matrix; // ������� ����� �������, ��� ��� ��� ��������� ��� �����������
        } else {
            delete matrix; // ������� ����� �������, ���� ��� �� ���������
        }
    }
}

DenseMatrix* DenseMatrixArray::getMatrix(size_t index) const {
    if (index < matrices.size()) {
        return matrices[index];
    }
    return nullptr; // ���������� nullptr ��� �������������� ��������
}

void DenseMatrixArray::print() const {
    for (size_t i = 0; i < matrices.size(); ++i) {
        std::cout << "Matrix at index " << i << ":\n";
        if (matrices[i]) {
            matrices[i]->print(); // �������� ������� �� �����
        } else {
            std::cout << "Empty\n"; // ���� ������� ������
        }
    }
}

void DenseMatrixArray::exportToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app); // ��������� ���� � ������ ����������
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < matrices.size(); ++i) {
        outFile << "Matrix at index " << i << ":\n";
        if (matrices[i]) {
            matrices[i]->print(outFile); // ������� ������� � ����
        } else {
            outFile << "Empty\n"; // ���� ������� ������
        }
    }

    outFile.close(); // ��������� ����
}
