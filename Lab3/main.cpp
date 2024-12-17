#include <iostream>
#include "vector.h"
#include <iostream>
#include <vector>
#include <algorithm> // ��� std::min_element � std::max_element
#include <utility>   // ��� std::pair
#include <cmath>    // ��� std::sqrt
#include <thread>
#include <chrono>


// ������� ��� ���������� ������������ � ������������� ��������� � ����� ������ Vector
std::pair<std::pair<int, size_t>, std::pair<int, size_t>> findMinMax(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int min_value = numbers[0];
    int max_value = numbers[0];
    size_t min_index = 0;
    size_t max_index = 0;

    for (size_t i = 1; i < size; ++i) {
        if (numbers[i] < min_value) {
            min_value = numbers[i];
            min_index = i;
        }
        if (numbers[i] > max_value) {
            max_value = numbers[i];
            max_index = i;
        }
    }

    return {{min_value, min_index}, {max_value, max_index}};
}

// ������� ��� ���������� �������� �������� ��������� � �������
double calculateAverage(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += numbers[i]; // ��������� ��� ��������
    }

    return static_cast<double>(sum) / size; // ���������� ������� ��������
}


double SumOfElements(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += numbers[i]; // ��������� ��� ��������
    }

    return sum; // ���������� ������� ��������
}

// ������� ��� ���������� ������������� �����
double calculateManhattanNorm(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    double sum = 0.0; // ����� ���������� ��������
    for (size_t i = 0; i < size; ++i) {
        sum += std::abs(numbers[i]); // ��������� ���������� �������� ���������
    }

    return sum; // ���������� ������������� �����
}

// ������� ��� ���������� ���������� �����
double calculateEuclideanNorm(const Vector<int>& numbers) {
    size_t size = numbers.getSize();
    if (size == 0) {
        throw std::runtime_error("Vector is empty.");
    }

    double sumOfSquares = 0.0; // ����� ��������� ���������
    for (size_t i = 0; i < size; ++i) {
        sumOfSquares += static_cast<double>(numbers[i]) * numbers[i]; // ��������� �������� ���������
    }

    return std::sqrt(sumOfSquares); // ���������� ���������� ������ �� ����� ���������
}

// ������� ��� ���������� ���������� ������������
template <typename T>
T dotProduct(const Vector<T>& vec1, const Vector<T>& vec2) {
    if (vec1.getSize() != vec2.getSize()) {
        throw std::invalid_argument("Vectors must be of the same size for dot product.");
    }

    T result = 0;

    for (size_t i = 0; i < vec1.getSize(); ++i) {
        result += vec1[i] * vec2[i]; // ��������� ������������ ��������������� ���������
    }

    return result;
}





      // ������������ ���������� ������� � �������������� �������
void parallelExecution(Vector<int>& vec1, Vector<int>& vec2) {
   std::vector<std::thread> threads;

   threads.emplace_back([&]() {
        auto [minMaxPair1, minMaxPair2] = findMinMax(vec1);
        auto [minValue, minIndex] = minMaxPair1;
        auto [maxValue, maxIndex] = minMaxPair2;
        std::cout << "Min value: " << minValue << " at index " << minIndex << "\n" << std::endl;;
        std::cout << "Max value: " << maxValue << " at index " << maxIndex << "\n" << std::endl;;
    });

   threads.emplace_back([&]() {
       double avg = calculateAverage(vec1);
       std::cout << "Average value: " << avg << "\n"<< std::endl;;

   });

   threads.emplace_back([&]() {
       double sum = SumOfElements(vec1);
       std::cout << "Sum value: " << sum << "\n"<< std::endl;;

   });

   threads.emplace_back([&]() {
       double manhattanNorm = calculateManhattanNorm(vec1);
       std::cout << "Manhattan Norm: " << manhattanNorm << "\n"<< std::endl;;

   });

   threads.emplace_back([&]() {
       double euclideanNorm = calculateEuclideanNorm(vec1);
       std::cout << "Euclidean Norm: " << euclideanNorm << "\n"<< std::endl;;

   });

   threads.emplace_back([&]() {
       double dotProd = dotProduct(vec1, vec2);
       std::cout << "Dot Product: " << dotProd << "\n"<< std::endl;;

   });

   for (auto& th : threads) {
       th.join(); // ������� ���������� ���� �������
   }
}

int main() {
    Vector<int> vec(10); // ������� ������ ����� ����� � �������� 10
    Vector<int> vec1(100000000); // ������� ������ ����� ����� � �������� 10
    Vector<int> vec2(100000000); // ������� ������ ����� ����� � �������� 10

    try {
        // ��� ������ � ������������ �������
        /*
        //����������� �������� ������� vec
        vec.initializeWithConstant(8); // �������������� ��� �������� ��������� 8

        std::cout << "Size of vector: " << vec.getSize() << std::endl;
        for (size_t i = 0; i < vec.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec[i] << std::endl;
        }*/

        //��������� �������� ������� vec1
         vec1.initializeWithRandomNumbers(-100, 100); // �������������� ���������� ������� �� -10 �� 10
        std::cout << "size of vector1: " << vec1.getSize() << std::endl;
        std::cout << "After inicialization random numbers vector1:" << std::endl;
        /*
        for (size_t i = 0; i < vec1.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec1[i] << std::endl;
        }*/

        //��������� �������� ������� vec2
         vec2.initializeWithRandomNumbers(-100, 101); // �������������� ���������� ������� �� -10 �� 10
        std::cout << "size of vector2: " << vec2.getSize() << std::endl;
        std::cout << "After inicialization random numbers vector2:" << std::endl;
      /*  for (size_t i = 0; i < vec2.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec2[i] << std::endl;
        }

        */

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

        auto result = findMinMax(vec1);
        // ������� ����������
        std::cout <<"\nMin value: " << result.first.first << " at index: " << result.first.second << std::endl;
        std::cout << "Max value: " << result.second.first << " at index: " << result.second.second << std::endl;

        // �������� ������� ��� ���������� �������� ��������
        double average = calculateAverage(vec1);
        std::cout  <<"\nAverage value: " << average <<"\n"<< std::endl;

        // �������� ������� ��� ���������� ����� ��������� �������
         double sum = SumOfElements(vec1);
        std::cout << "Sum value: " << sum <<"\n"<< std::endl;

         // �������� ������� ��� ���������� ���������� �����
        double euclidnorm = calculateEuclideanNorm(vec1);
        std::cout << "Euclidean norm: " << euclidnorm <<"\n"<< std::endl;

        // �������� ������� ��� ���������� ������������� �����
        double manxattannorm = calculateManhattanNorm(vec1);
        std::cout << "Manhattan norm: " << manxattannorm <<"\n"<<  std::endl;

        // ���������� ���������� ������������
        int ScalarComposition = dotProduct(vec1, vec2);
        std::cout << "Dot product of vector1 and vector2: " << ScalarComposition <<"\n"<< std::endl;

    std::cout<< "---------------------------------------------------------"<<"\n" << std::endl;


        parallelExecution(vec1, vec2);




        /*

        // ������� ������ � ����.
        vec1.exportToFile("output.txt");

        //������ ������ �� �����
        // ������� ����� ������ ��� �������.
        Vector<int> importedVec; // ������� ����� ������
        importedVec.initializeWithConstant(0); // �������������� ��� ����� ��������

        importedVec.importFromFile("output.txt");

        // ������� ��������������� ������.
        std::cout << "Imported data:" << std::endl;
        for (size_t i = 0; i < importedVec.getSize(); ++i) {
            std::cout << "Element " << i << ": " << importedVec[i] << std::endl;
        }

        */
    return 0;
}

