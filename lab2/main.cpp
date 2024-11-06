#include <iostream>
#include <cstdlib> // ��� ������� rand()
#include <ctime>   // ��� ������� time()
#include <fstream> // ��� std::ofstream
#include "Matrix.h"
#include "MatrixDiagonal.h" //
#include "DenseMatrix.h"
#include "DenseMatrixArray.h"

// ������� ��� ���������� ������� ���������� ����������
template <typename T>
void fillMatrix(MatrixDense<T>& matrix) {
    for (unsigned i = 0; i < matrix.rows(); ++i) {
        for (unsigned j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = static_cast<T>(std::rand() % 100 + 1); // ��������� �������� �� 1 �� 100
        }
    }
}

int main() {
    try {
        // ������������� ���������� ��������� �����
        std::srand(static_cast<unsigned>(std::time(0)));

        // ������� ������� 3x3
        MatrixDense<double> matrixA(3, 3);
        MatrixDense<double> matrixB(3, 3);

        // ��������� ������� ���������� ����������
        fillMatrix(matrixA);
        fillMatrix(matrixB);

        // ������� ������� A � B � �������
        std::cout << "Generated matrix A:" << std::endl;
        matrixA.print();

        std::cout << "Generated matrix B:" << std::endl;
        matrixB.print();

        // ��������� ���� ��� ������
        std::ofstream outFile("matrices.txt");
        if (!outFile) {
            throw std::runtime_error("The file could not be opened for writing");
        }

        // ���������� ������� � ���� � �������������� ������ exportToFile
        matrixA.exportToFile(outFile, "������� A:");
        matrixB.exportToFile(outFile, "\n������� B:");

        // �������� ������� A �� ������
        double scalar = 2.5; // ������ �������
        MatrixDense<double> scaledMatrix = matrixA.scalarMultiply(scalar);

        // ������� �������������� ������� �� �����
        std::cout << "Scaled matrix A (multiplied by " << scalar << "):" << std::endl;
        scaledMatrix.print();

        // ���������� �������������� ������� � ����
        scaledMatrix.exportToFile(outFile, "\n�������������� ������� A (���������� ��  " + std::to_string(scalar) + "):");

        // ������������ ��������� ������ A � B
        MatrixDense<double> elementWiseResult = matrixA.elementWiseMultiply(matrixB);
        std::cout << "Element-wise multiplication of A and B:" << std::endl;
        elementWiseResult.print();
        elementWiseResult.exportToFile(outFile, "\n������������ ��������� ������ A � B:");

        // ��������� ��������� ������ A � B
        MatrixDense<double> matrixResult = matrixA * matrixB;
        std::cout << "Matrix multiplication of A and B:" << std::endl;
        matrixResult.print();
        matrixResult.exportToFile(outFile, "\n��������� ��������� ������ A � B:");

        // ��������� ��������
        MatrixDense<double> additionResult = matrixA + matrixB;
        std::cout << "Matrix addition of A and B:" << std::endl;
        additionResult.print();
        additionResult.exportToFile(outFile, "\n��������� ��������:");

        // ��������� ���������
        MatrixDense<double> subtractionResult = matrixA - matrixB;
        std::cout << "Matrix subtraction of A and B:" << std::endl;
        subtractionResult.print();
        subtractionResult.exportToFile(outFile, "\n��������� ���������:");

        // ���������������� ������� A
        MatrixDense<double> transposeResult = matrixA.transpose();
        std::cout << "Transpose of matrix A:" << std::endl;
        transposeResult.print();
        transposeResult.exportToFile(outFile, "\n���������������� ������� A:");

         // ��������� ���� ����� ������ ������ A � B
        outFile.close();

       // ������� ������������ ������� C �������� 3
        MatrixDiagonal<double> matrixC(3);

        // ��������� ������������ �������� ���������� ����������
        for (unsigned i = 0; i < matrixC.size(); ++i) {
            matrixC(i, i) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� �� 1 �� 100
            if (i < matrixC.size() - 1) {
                matrixC(i, i + 1) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� ��� ������� ���������
                matrixC(i + 1, i) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� ��� ������ ���������
            }
        }

        // ������� ������������ ������� C �� ����� � �������
        std::cout << "Generated diagonal matrix C:" << std::endl;
        matrixC.print();

        // ������� ������������ ������� D �������� 3
        MatrixDiagonal<double> matrixD(3);

        // ��������� ������������ �������� ���������� ����������
        for (unsigned i = 0; i < matrixD.size(); ++i) {
            matrixD(i, i) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� �� 1 �� 100
            if (i < matrixD.size() - 1) {
                matrixD(i, i + 1) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� ��� ������� ���������
                matrixD(i + 1, i) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� ��� ������ ���������
            }
        }

        // ������� ������������ ������� D �� ����� � �������
        std::cout << "Generated diagonal matrix D:" << std::endl;
        matrixD.print();

        // ��������� ���� ��� ������ ����� ������������ ������ C � D
        std::ofstream diagOutFile("Matrix_Diagonal.txt");
        if (!diagOutFile) {
            throw std::runtime_error("The file could not be opened for writing");
        }

        // ���������� ������������ ������� C � ����
        matrixC.exportToFile(diagOutFile, "������������ ������� C:");

        // ���������� ������������ ������� D � ����
        matrixD.exportToFile(diagOutFile, "������������ ������� D:");


        // �������� ������ C � D
        MatrixDiagonal<double> matrixSum = matrixC + matrixD;

        // ������� ��������� �� �����
        std::cout << "Sum of matrices C and D:" << std::endl;
        matrixSum.print();

        // ���������� ��������� � ����
        matrixSum.exportToFile(diagOutFile, "����� ������ C � D:");

       // ��������� ������ C � D
        MatrixDiagonal<double> matrixDiff = matrixC - matrixD;

        // ������� ��������� �� �����
        std::cout << "Difference of matrices C and D:" << std::endl;
        matrixDiff.print();

        // ���������� ��������� � ����
        matrixDiff.exportToFile(diagOutFile, "�������� ������ C � D:");

        // ������������ ���������
        MatrixDiagonal<double> matrixProd = matrixC.elementWiseMultiply(matrixD);

        // ������� ��������� �� �����
        std::cout << "Element-wise product of matrices C and D:" << std::endl;
        matrixProd.print();

        // ���������� ��������� � ����
        matrixProd.exportToFile(diagOutFile, "������������ ������������ ������ C � D:");

        // ��������� ���������
        MatrixDiagonal<double> matrixMatProd = matrixC.matrixMultiply(matrixD);

        // ������� ��������� �� �����
        std::cout << "Matrix product of matrices C and D:" << std::endl;
        matrixMatProd.print();

        // ���������� ��������� � ����
        matrixMatProd.exportToFile(diagOutFile, "��������� ������������ ������ C � D:");

        // ���������������� ������ C � D
        MatrixDiagonal<double> matrixC_T = matrixC.transpose();
        MatrixDiagonal<double> matrixD_T = matrixD.transpose();

        // ������� ��������� �� �����
        std::cout << "Transposed matrix C:" << std::endl;
        matrixC_T.print();

        std::cout << "Transposed matrix D:" << std::endl;
        matrixD_T.print();

        // ���������� ��������� � ����
        matrixC_T.exportToFile(diagOutFile, "����������������� ������� C:");
        matrixD_T.exportToFile(diagOutFile, "����������������� ������� D:");

        // ������������ ��������� ������ C � D
        MatrixDiagonal<double> matrixKroneckerProd = matrixC.kroneckerProduct(matrixD);

        // ������� ��������� �� �����
        std::cout << "Kronecker product of matrices C and D:" << std::endl;
        matrixKroneckerProd.print();

        // ���������� ��������� � ����
        matrixKroneckerProd.exportToFile(diagOutFile, "������������ ��������� ������ C � D:");


        DenseMatrixArray matrixArray(5); // ������� ������ �� 5 ���������

        // ������� ��������� ������� ������
        DenseMatrix* mat1 = new DenseMatrix(2, 2);
        mat1->setValue(0, 0, 1);
        mat1->setValue(0, 1, 2);
        mat1->setValue(1, 0, 3);
        mat1->setValue(1, 1, 4);

        DenseMatrix* mat2 = new DenseMatrix(2, 2);
        mat2->setValue(0, 0, 1);
        mat2->setValue(0, 1, 2);
        mat2->setValue(1, 0, 3);
        mat2->setValue(1, 1, 4); // ���������� �������

        DenseMatrix* mat3 = new DenseMatrix(3, 3);
        mat3->setValue(0, 0, 5);

        // ������������� ������� � ������
        matrixArray.setMatrix(0, mat1);
        matrixArray.setMatrix(1, mat2); // �� ����� ��������� � ������ (����������)
        matrixArray.setMatrix(2, mat3);

        // �������� ������ ������
        matrixArray.print();

        // ������������ ������ ������ � ����
        matrixArray.exportToFile("Matrix_Diagonal.txt");

        diagOutFile.close(); // �������� �����

   } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
