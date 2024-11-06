#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(unsigned r, unsigned c) : rows(r), cols(c), data(r, std::vector<double>(c, 0)) {}

void DenseMatrix::setValue(unsigned r, unsigned c, double value) {
    if (r < rows && c < cols) {
        data[r][c] = value;
    }
}

double DenseMatrix::getValue(unsigned r, unsigned c) const {
    if (r < rows && c < cols) {
        return data[r][c];
    }
    return 0; // Возвращаем 0 для несуществующих индексов
}

void DenseMatrix::print(std::ostream& os) const { // Метод для вывода в поток
    for (const auto& row : data) {
        for (double val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
}

bool DenseMatrix::operator==(const DenseMatrix& other) const {
    return rows == other.rows && cols == other.cols && data == other.data;
}
