#include <iostream>
#include <cstdlib> // Для функции rand()
#include <ctime>   // Для функции time()
#include <fstream> // Для std::ofstream
#include "Matrix.h"

// Функция для заполнения матрицы случайными значениями
template <typename T>
void fillMatrix(MatrixDense<T>& matrix) {
    for (unsigned i = 0; i < matrix.rows(); ++i) {
        for (unsigned j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = static_cast<T>(std::rand() % 100 + 1); // Случайное значение от 1 до 100
        }
    }
}

int main() {
    try {
        // Инициализация генератора случайных чисел
        std::srand(static_cast<unsigned>(std::time(0)));

        // Создаем матрицы 3x3
        MatrixDense<double> matrixA(3, 3);
        MatrixDense<double> matrixB(3, 3);

        // Заполняем матрицы случайными значениями
        fillMatrix(matrixA);
        fillMatrix(matrixB);

        // Выводим матрицы A и B в консоль
        std::cout << "Generated matrix A:" << std::endl;
        matrixA.print();

        std::cout << "Generated matrix B:" << std::endl;
        matrixB.print();

        // Открываем файл для записи
        std::ofstream outFile("matrices.txt");
        if (!outFile) {
            throw std::runtime_error("The file could not be opened for writing");
        }

        // Записываем матрицы в файл с использованием метода exportToFile
        matrixA.exportToFile(outFile, "Матрица A:");
        matrixB.exportToFile(outFile, "\nМатрица B:");

        // Умножаем матрицу A на скаляр
        double scalar = 2.5; // Пример скаляра
        MatrixDense<double> scaledMatrix = matrixA.scalarMultiply(scalar);

        // Выводим результирующую матрицу на экран
        std::cout << "Scaled matrix A (multiplied by " << scalar << "):" << std::endl;
        scaledMatrix.print();

        // Записываем результирующую матрицу в файл
        scaledMatrix.exportToFile(outFile, "\nРезультирующая матрица A (умноженная на  " + std::to_string(scalar) + "):");

        // Поэлементное умножение матриц A и B
        MatrixDense<double> elementWiseResult = matrixA.elementWiseMultiply(matrixB);
        std::cout << "Element-wise multiplication of A and B:" << std::endl;
        elementWiseResult.print();
        elementWiseResult.exportToFile(outFile, "\nПоэлементное умножение матриц A и B:");

        // Матричное умножение матриц A и B
        MatrixDense<double> matrixResult = matrixA * matrixB;
        std::cout << "Matrix multiplication of A and B:" << std::endl;
        matrixResult.print();
        matrixResult.exportToFile(outFile, "\nМатричное умножение матриц A и B:");

        // Матричное сложение
        MatrixDense<double> additionResult = matrixA + matrixB;
        std::cout << "Matrix addition of A and B:" << std::endl;
        additionResult.print();
        additionResult.exportToFile(outFile, "\nМатричное сложение:");

        // Матричное вычитание
        MatrixDense<double> subtractionResult = matrixA - matrixB;
        std::cout << "Matrix subtraction of A and B:" << std::endl;
        subtractionResult.print();
        subtractionResult.exportToFile(outFile, "\nМатричное вычитание:");

        // Транспонирование матрицы A
        MatrixDense<double> transposeResult = matrixA.transpose();
        std::cout << "Transpose of matrix A:" << std::endl;
        transposeResult.print();
        transposeResult.exportToFile(outFile, "\nТранспонирование матрицы A:");

        outFile.close(); // Закрытие файла

        std::cout << "All matrices successfully generated in file matrices.txt" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
//
