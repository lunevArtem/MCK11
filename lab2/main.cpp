#include <iostream>
#include <cstdlib> // Для функции rand()
#include <ctime>   // Для функции time()
#include <fstream> // Для std::ofstream
#include "Matrix.h"
#include "MatrixDiagonal.h" //
#include "DenseMatrix.h"
#include "DenseMatrixArray.h"

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

         // Закрываем файл после записи матриц A и B
        outFile.close();

       // Создаем диагональную матрицу C размером 3
        MatrixDiagonal<double> matrixC(3);

        // Заполняем диагональные элементы случайными значениями
        for (unsigned i = 0; i < matrixC.size(); ++i) {
            matrixC(i, i) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение от 1 до 100
            if (i < matrixC.size() - 1) {
                matrixC(i, i + 1) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение для верхней диагонали
                matrixC(i + 1, i) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение для нижней диагонали
            }
        }

        // Выводим диагональную матрицу C на экран в консоль
        std::cout << "Generated diagonal matrix C:" << std::endl;
        matrixC.print();

        // Создаем диагональную матрицу D размером 3
        MatrixDiagonal<double> matrixD(3);

        // Заполняем диагональные элементы случайными значениями
        for (unsigned i = 0; i < matrixD.size(); ++i) {
            matrixD(i, i) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение от 1 до 100
            if (i < matrixD.size() - 1) {
                matrixD(i, i + 1) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение для верхней диагонали
                matrixD(i + 1, i) = static_cast<double>(std::rand() % 100 + 1); // Случайное значение для нижней диагонали
            }
        }

        // Выводим диагональную матрицу D на экран в консоль
        std::cout << "Generated diagonal matrix D:" << std::endl;
        matrixD.print();

        // Открываем файл для записи обеих диагональных матриц C и D
        std::ofstream diagOutFile("Matrix_Diagonal.txt");
        if (!diagOutFile) {
            throw std::runtime_error("The file could not be opened for writing");
        }

        // Записываем диагональную матрицу C в файл
        matrixC.exportToFile(diagOutFile, "Диагональная матрица C:");

        // Записываем диагональную матрицу D в файл
        matrixD.exportToFile(diagOutFile, "Диагональная матрица D:");


        // Сложение матриц C и D
        MatrixDiagonal<double> matrixSum = matrixC + matrixD;

        // Выводим результат на экран
        std::cout << "Sum of matrices C and D:" << std::endl;
        matrixSum.print();

        // Записываем результат в файл
        matrixSum.exportToFile(diagOutFile, "Сумма матриц C и D:");

       // Вычитание матриц C и D
        MatrixDiagonal<double> matrixDiff = matrixC - matrixD;

        // Выводим результат на экран
        std::cout << "Difference of matrices C and D:" << std::endl;
        matrixDiff.print();

        // Записываем результат в файл
        matrixDiff.exportToFile(diagOutFile, "Разность матриц C и D:");

        // Поэлементное умножение
        MatrixDiagonal<double> matrixProd = matrixC.elementWiseMultiply(matrixD);

        // Выводим результат на экран
        std::cout << "Element-wise product of matrices C and D:" << std::endl;
        matrixProd.print();

        // Записываем результат в файл
        matrixProd.exportToFile(diagOutFile, "Поэлементное произведение матриц C и D:");

        // Матричное умножение
        MatrixDiagonal<double> matrixMatProd = matrixC.matrixMultiply(matrixD);

        // Выводим результат на экран
        std::cout << "Matrix product of matrices C and D:" << std::endl;
        matrixMatProd.print();

        // Записываем результат в файл
        matrixMatProd.exportToFile(diagOutFile, "Матричное произведение матриц C и D:");

        // Транспонирование матриц C и D
        MatrixDiagonal<double> matrixC_T = matrixC.transpose();
        MatrixDiagonal<double> matrixD_T = matrixD.transpose();

        // Выводим результат на экран
        std::cout << "Transposed matrix C:" << std::endl;
        matrixC_T.print();

        std::cout << "Transposed matrix D:" << std::endl;
        matrixD_T.print();

        // Записываем результат в файл
        matrixC_T.exportToFile(diagOutFile, "Транспонированная матрица C:");
        matrixD_T.exportToFile(diagOutFile, "Транспонированная матрица D:");

        // Произведение Кронекера матриц C и D
        MatrixDiagonal<double> matrixKroneckerProd = matrixC.kroneckerProduct(matrixD);

        // Выводим результат на экран
        std::cout << "Kronecker product of matrices C and D:" << std::endl;
        matrixKroneckerProd.print();

        // Записываем результат в файл
        matrixKroneckerProd.exportToFile(diagOutFile, "Произведение Кронекера матриц C и D:");


        DenseMatrixArray matrixArray(5); // Создаем массив из 5 элементов

        // Создаем несколько плотных матриц
        DenseMatrix* mat1 = new DenseMatrix(2, 2);
        mat1->setValue(0, 0, 1);
        mat1->setValue(0, 1, 2);
        mat1->setValue(1, 0, 3);
        mat1->setValue(1, 1, 4);

        DenseMatrix* mat2 = new DenseMatrix(2, 2);
        mat2->setValue(0, 0, 1);
        mat2->setValue(0, 1, 2);
        mat2->setValue(1, 0, 3);
        mat2->setValue(1, 1, 4); // Идентичная матрица

        DenseMatrix* mat3 = new DenseMatrix(3, 3);
        mat3->setValue(0, 0, 5);

        // Устанавливаем матрицы в массив
        matrixArray.setMatrix(0, mat1);
        matrixArray.setMatrix(1, mat2); // Не будет добавлена в массив (идентичная)
        matrixArray.setMatrix(2, mat3);

        // Печатаем массив матриц
        matrixArray.print();

        // Экспортируем массив матриц в файл
        matrixArray.exportToFile("Matrix_Diagonal.txt");

        diagOutFile.close(); // Закрытие файла

   } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
