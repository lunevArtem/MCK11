#ifndef VECTOR_H
#define VECTOR_H

#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib> // Для rand() и srand()
#include <ctime>   // Для time()
#include <iostream>

template <typename T>
class Vector {
private:
    T* data;             // Указатель на динамический массив
    size_t n;            // Текущий размер вектора (количество элементов)
    size_t capacity;     // Вместимость вектора
    bool is_initialized; // Состояние инициализации

public:
    Vector(size_t initial_size = 1000); // Конструктор
    ~Vector(); // Деструктор

    void initializeWithConstant(const T& value);// Инициализация константой
    void initializeWithRandomNumbers(T min, T max);// Инициализация случайными числами
    void push_back(const T& value); // Метод для добавления элемента
    T& operator[](size_t index); // Оператор доступа по индексу
    size_t getSize() const; // Метод для получения текущего размера

    void exportToFile(const std::string& filename) const; // Экспорт данных в файл
    void importFromFile(const std::string& filename); // Импорт данных из файла
    const T& operator[](size_t index) const; // Константная версия оператора

private:
    void checkInitialization() const; // Метод для проверки состояния инициализации
};

// Реализация методов класса Vector

template <typename T>
Vector<T>::Vector(size_t initial_size) : data(nullptr), n(0), capacity(initial_size), is_initialized(false) {
    // Массив не выделяется в конструкторе
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data; // Освобождаем память при уничтожении объекта
}

template <typename T>
void Vector<T>::initializeWithConstant(const T& value) {
    if (is_initialized) {
        throw std::runtime_error("Vector is already initialized."); // Исключение, если вектор уже инициализирован
    }

    data = new T[capacity]; // Выделяем память под массив
    for (size_t i = 0; i < capacity; ++i) {
        data[i] = value; // Инициализируем все элементы константой
    }

    n = capacity; // Устанавливаем текущий размер
    is_initialized = true; // Устанавливаем состояние инициализации в true
}

template <typename T>
void Vector<T>::initializeWithRandomNumbers(T min, T max) {
    if (is_initialized) {
        throw std::runtime_error("Vector is already initialized."); // Исключение, если вектор уже инициализирован
    }

    data = new T[capacity]; // Выделяем память под массив

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализируем генератор случайных чисел
    for (size_t i = 0; i < capacity; ++i) {
        data[i] = min + (std::rand() % (max - min + 1)); // Инициализируем случайными числами в заданном диапазоне
    }

    n = capacity; // Устанавливаем текущий размер
    is_initialized = true; // Устанавливаем состояние инициализации в true
}

template <typename T>
void Vector<T>::checkInitialization() const {
    if (!is_initialized) {
        throw std::runtime_error("Vector is not initialized."); // Исключение, если вектор не инициализирован
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    checkInitialization(); // Проверяем состояние инициализации перед выполнением метода

    if (n >= capacity) {
        size_t new_capacity = capacity * 2; // Увеличиваем емкость
        T* new_data = new T[new_capacity]; // Создаем новый массив

        for (size_t i = 0; i < n; ++i) {
            new_data[i] = data[i]; // Копируем старые элементы в новый массив
        }

        delete[] data; // Освобождаем старый массив
        data = new_data; // Перенаправляем указатель на новый массив
        capacity = new_capacity; // Обновляем емкость
    }

    data[n++] = value; // Добавляем новый элемент и увеличиваем размер
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    checkInitialization(); // Проверяем состояние инициализации перед выполнением метода
    if (index >= n) {
        throw std::out_of_range("Index out of range"); // Проверка на выход за пределы
    }

    return data[index]; // Возвращаем элемент по индексу
}

template <typename T>
size_t Vector<T>::getSize() const {
    checkInitialization(); // Проверяем состояние инициализации перед выполнением метода
    return n; // Возвращаем размерность вектора
}

template <typename T>
void Vector<T>::exportToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for record!" << std::endl;
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        outFile << data[i] << std::endl; // Записываем каждый элемент в файл
    }

    outFile.close();
    std::cout << "Data successfully exported to " << filename << std::endl;
}

template <typename T>
void Vector<T>::importFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    T value;

    n = 0;
    is_initialized = true; // Устанавливаем состояние инициализации в true

    // Импортируем данные из файла, пока есть что читать.
    while (inFile >> value) {
        push_back(value);  // Добавляем считанное значение в вектор.
    }

    inFile.close();
    std::cout << "Data successfully imported from " << filename << std::endl;
}

// Реализация константной версии оператора []
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    checkInitialization(); // Проверяем состояние инициализации перед выполнением метода
    if (index >= n) {
        throw std::out_of_range("Index out of range"); // Проверка на выход за пределы
    }

    return data[index]; // Возвращаем элемент по индексу
}


#endif // VECTOR_H
