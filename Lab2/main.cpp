#include <iostream>
#include <cstdlib> // Для функции rand()
#include <ctime>   // Для функции time()
#include "Matrix.h"

int main() {
    try {
        // Инициализация генератора случайных чисел
        std::srand(static_cast<unsigned>(std::time(0)));

        // Создаем матрицы 3x3
        MatrixDense<double> matrixA(3, 3);
        MatrixDense<double> matrixB(3, 3);

        // Заполняем матрицу A случайными значениями от 1 до 100
        for (unsigned i = 0; i < matrixA.rows(); ++i) {
            for (unsigned j = 0; j < matrixA.cols(); ++j) {
                matrixA(i, j) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение от 1 до 100
            }
        }

        // Заполняем матрицу B случайными значениями от 1 до 100
        for (unsigned i = 0; i < matrixB.rows(); ++i) {
            for (unsigned j = 0; j < matrixB.cols(); ++j) {
                matrixB(i, j) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение от 1 до 100
            }
        }

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

        // Записываем матрицу A в файл
        outFile << "Matrix A:" << std::endl;
        for (unsigned i = 0; i < matrixA.rows(); ++i) {
            for (unsigned j = 0; j < matrixA.cols(); ++j) {
                outFile << matrixA(i, j);
                if (j < matrixA.cols() - 1) {
                    outFile << " ";
                }
            }
            outFile << std::endl;
        }

        // Записываем матрицу B в файл
        outFile << "\nMatrix B:" << std::endl;
        for (unsigned i = 0; i < matrixB.rows(); ++i) {
            for (unsigned j = 0; j < matrixB.cols(); ++j) {
                outFile << matrixB(i, j);
                if (j < matrixB.cols() - 1) {
                    outFile << " ";
                }
            }
            outFile << std::endl;
        }

        // Умножаем матрицу A на скаляр
        double scalar = 2.5; // Пример скаляра
        MatrixDense<double> scaledMatrix(3, 3);

        for (unsigned i = 0; i < matrixA.rows(); ++i) {
            for (unsigned j = 0; j < matrixA.cols(); ++j) {
                scaledMatrix(i, j) = scalar * matrixA(i, j); // Умножение на скаляр
            }
        }

        // Выводим результирующую матрицу на экран
        std::cout << "Scaled matrix A (multiplied by " << scalar << "):" << std::endl;
        scaledMatrix.print();

        // Записываем результирующую матрицу в файл
        outFile << "\nScaled matrix A (multiplied by " << scalar << "):" << std::endl;
        for (unsigned i = 0; i < scaledMatrix.rows(); ++i) {
            for (unsigned j = 0; j < scaledMatrix.cols(); ++j) {
                outFile << scaledMatrix(i, j);
                if (j < scaledMatrix.cols() - 1) {
                    outFile << " ";
                }
            }
            outFile << std::endl;
        }

        outFile.close(); // Закрытие файла

        std::cout << "All matrices successfully generated in file matrices.txt" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
