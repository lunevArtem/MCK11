#include "DenseMatrixArray.h"
#include <fstream> // Для работы с файлами

DenseMatrixArray::DenseMatrixArray(size_t size) : matrices(size, nullptr) {}

DenseMatrixArray::~DenseMatrixArray() {
    for (auto& matrix : matrices) {
        delete matrix; // Освобождаем память
    }
}

void DenseMatrixArray::setMatrix(size_t index, DenseMatrix* matrix) {
    if (index < matrices.size()) {
        if (matrices[index] == nullptr) { // Если еще нет матрицы в этом индексе
            matrices[index] = matrix; // Сохраняем указатель на новую матрицу
        } else if (*matrices[index] == *matrix) { // Если матрицы одинаковые
            delete matrix; // Удаляем новую матрицу, так как она идентична уже сохраненной
        } else {
            delete matrix; // Удаляем новую матрицу, если она не идентична
        }
    }
}

DenseMatrix* DenseMatrixArray::getMatrix(size_t index) const {
    if (index < matrices.size()) {
        return matrices[index];
    }
    return nullptr; // Возвращаем nullptr для несуществующих индексов
}

void DenseMatrixArray::print() const {
    for (size_t i = 0; i < matrices.size(); ++i) {
        std::cout << "Matrix at index " << i << ":\n";
        if (matrices[i]) {
            matrices[i]->print(); // Печатаем матрицу на экран
        } else {
            std::cout << "Empty\n"; // Если матрица пустая
        }
    }
}

void DenseMatrixArray::exportToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app); // Открываем файл в режиме добавления
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < matrices.size(); ++i) {
        outFile << "Matrix at index " << i << ":\n";
        if (matrices[i]) {
            matrices[i]->print(outFile); // Выводим матрицу в файл
        } else {
            outFile << "Empty\n"; // Если матрица пустая
        }
    }

    outFile.close(); // Закрываем файл
}
