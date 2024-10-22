#include <iostream>
#include <cstdlib> // ��� ������� rand()
#include <ctime>   // ��� ������� time()
#include "Matrix.h"

int main() {
    try {
        // ������������� ���������� ��������� �����
        std::srand(static_cast<unsigned>(std::time(0)));

        // ������� ������� 3x3
        MatrixDense<double> matrixA(3, 3);
        MatrixDense<double> matrixB(3, 3);

        // ��������� ������� A ���������� ���������� �� 1 �� 100
        for (unsigned i = 0; i < matrixA.rows(); ++i) {
            for (unsigned j = 0; j < matrixA.cols(); ++j) {
                matrixA(i, j) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� �� 1 �� 100
            }
        }

        // ��������� ������� B ���������� ���������� �� 1 �� 100
        for (unsigned i = 0; i < matrixB.rows(); ++i) {
            for (unsigned j = 0; j < matrixB.cols(); ++j) {
                matrixB(i, j) = static_cast<double>(std::rand() % 100 + 1); // ��������� �������� �� 1 �� 100
            }
        }

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

        // ���������� ������� A � ����
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

        // ���������� ������� B � ����
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

        // �������� ������� A �� ������
        double scalar = 2.5; // ������ �������
        MatrixDense<double> scaledMatrix(3, 3);

        for (unsigned i = 0; i < matrixA.rows(); ++i) {
            for (unsigned j = 0; j < matrixA.cols(); ++j) {
                scaledMatrix(i, j) = scalar * matrixA(i, j); // ��������� �� ������
            }
        }

        // ������� �������������� ������� �� �����
        std::cout << "Scaled matrix A (multiplied by " << scalar << "):" << std::endl;
        scaledMatrix.print();

        // ���������� �������������� ������� � ����
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

        outFile.close(); // �������� �����

        std::cout << "All matrices successfully generated in file matrices.txt" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
