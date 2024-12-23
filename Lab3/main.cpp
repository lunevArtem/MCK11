#include "vector.h"
#include "functions.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <omp.h>


void ExecutionOneThread(Vector<int>& vec1, Vector<int>& vec2) {
    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени

    auto [minMaxPair1, minMaxPair2] = findMinMax(vec1);
    auto [minValue, minIndex] = minMaxPair1;
    auto [maxValue, maxIndex] = minMaxPair2;

    double avg = calculateAverage(vec1);
    double sum = SumOfElements(vec1);
    double manhattanNorm = calculateManhattanNorm(vec1);
    double euclideanNorm = calculateEuclideanNorm(vec1);

    double dotProd = dotProduct(vec1, vec2);

    // Вывод результатов
    std::cout << "Min: " << minValue << " at index " << minIndex << "\n";
    std::cout << "Max: " << maxValue << " at index " << maxIndex << "\n";
    std::cout << "Average: " << avg << "\n";
    std::cout << "Sum: " << sum << "\n";
    std::cout << "Manhattan Norm: " << manhattanNorm << "\n";
    std::cout << "Euclidean Norm: " << euclideanNorm << "\n";
    std::cout << "Dot Product: " << dotProd << "\n";
    auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
    std::chrono::duration<double> duration = end - start; // Вычисляем продолжительность
    std::cout << "Execution time (One Thread): " << duration.count() << " seconds\n";
}




      // Параллельное выполнение функций с использованием потоков
void parallelExecutionThread(Vector<int>& vec1, Vector<int>& vec2) {

    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени

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
       th.join(); // Ожидаем завершения всех потоков
   }

    auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
    std::chrono::duration<double> duration = end - start; // Вычисляем продолжительность
    std::cout << "Execution time (parallelExecutionThread): " << duration.count() << " seconds\n";
}



void parallelExecutionOMP(Vector<int>& vec1, Vector<int>& vec2) {
    auto start = std::chrono::high_resolution_clock::now(); // Начало замера времени

    #pragma omp parallel num_threads(6)
    {
        #pragma omp single // Обеспечиваем, что только один поток выполняет этот блок
        {
            // Параллельное выполнение функций
            #pragma omp task
            {
                auto [minMaxPair1, minMaxPair2] = findMinMax(vec1);
                auto [minValue, minIndex] = minMaxPair1;
                auto [maxValue, maxIndex] = minMaxPair2;
                std::cout << "\nMin: " << minValue << " at index " << minIndex << "\n";
                std::cout << "Max: " << maxValue << " at index " << maxIndex << "\n";
            }

            #pragma omp task
            {
                double avg = calculateAverage(vec1);
                std::cout << "\nAverage: " << avg << "\n";
            }

            #pragma omp task
            {
                double sum = SumOfElements(vec1);
                std::cout << "\nSum: " << sum << "\n";
            }

            #pragma omp task
            {
                double manhattanNorm = calculateManhattanNorm(vec1);
                std::cout << "\nManhattan Norm: " << manhattanNorm << "\n";
            }

            #pragma omp task
            {
                double euclideanNorm = calculateEuclideanNorm(vec1);
                std::cout << "\nEuclidean Norm: " << euclideanNorm << "\n";
            }

            #pragma omp task
            {
                double dotProd = dotProduct(vec1, vec2);
                std::cout << "\nDot Product: " << dotProd << "\n";
            }
        } // Конец блока single
    } // Конец параллельного региона
    auto end = std::chrono::high_resolution_clock::now(); // Конец замера времени
    std::chrono::duration<double> duration = end - start; // Вычисляем продолжительность
    std::cout << "Execution time (parallelExecutionOMP): " << duration.count() << " seconds\n";
}


int main() {
  //  Vector<int> vec(10); // Создаем вектор целых чисел с размером 10
    Vector<int> vec1(100000000); // Создаем вектор целых чисел с размером 10
    Vector<int> vec2(100000000); // Создаем вектор целых чисел с размером 10

    try {
        // тут веткор с константными данными
        /*
        //Константные значения вектора vec
        vec.initializeWithConstant(8); // Инициализируем все элементы значением 8

        std::cout << "Size of vector: " << vec.getSize() << std::endl;
        for (size_t i = 0; i < vec.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec[i] << std::endl;
        }*/

        //Рандомные значения вектора vec1
         vec1.initializeWithRandomNumbers(-10, 10); // Инициализируем случайными числами от -10 до 10
        std::cout << "size of vector1: " << vec1.getSize() << std::endl;
        std::cout << "After inicialization random numbers vector1:" << std::endl;
        /*
        for (size_t i = 0; i < vec1.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec1[i] << std::endl;
        }*/

        //Рандомные значения вектора vec2
         vec2.initializeWithRandomNumbers(-10, 11); // Инициализируем случайными числами от -10 до 10
        std::cout << "size of vector2: " << vec2.getSize() << std::endl;
        std::cout << "After inicialization random numbers vector2:" << std::endl;
      /*  for (size_t i = 0; i < vec2.getSize(); ++i) {
            std::cout << "Element " << i << ": " << vec2[i] << std::endl;
        }

        */

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    std::cout<< "--------------------OneThread-------------------------------------"<<"\n" << std::endl;

        ExecutionOneThread(vec1,vec2);

    std::cout<< "--------------------std::thread-------------------------------------"<<"\n" << std::endl;

        parallelExecutionThread(vec1, vec2);

    std::cout<< "-------------------------OpenMP--------------------------------------"<<"\n" << std::endl;

        parallelExecutionOMP(vec1, vec2);



        /*

        // Экспорт данных в файл.
        vec1.exportToFile("output.txt");

        //Импорт данных из файла
        // Создаем новый объект для импорта.
        Vector<int> importedVec; // Создаем новый вектор
        importedVec.initializeWithConstant(0); // Инициализируем его перед импортом

        importedVec.importFromFile("output.txt");

        // Выводим импортированные данные.
        std::cout << "Imported data:" << std::endl;
        for (size_t i = 0; i < importedVec.getSize(); ++i) {
            std::cout << "Element " << i << ": " << importedVec[i] << std::endl;
        }

        */
    return 0;
}

