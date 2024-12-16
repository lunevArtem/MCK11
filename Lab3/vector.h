#ifndef VECTOR_H
#define VECTOR_H

#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdlib> // ��� rand() � srand()
#include <ctime>   // ��� time()
#include <iostream>

template <typename T>
class Vector {
private:
    T* data;             // ��������� �� ������������ ������
    size_t n;            // ������� ������ ������� (���������� ���������)
    size_t capacity;     // ����������� �������
    bool is_initialized; // ��������� �������������

public:
    Vector(size_t initial_size = 1000); // �����������
    ~Vector(); // ����������

    void initializeWithConstant(const T& value);// ������������� ����������
    void initializeWithRandomNumbers(T min, T max);// ������������� ���������� �������
    void push_back(const T& value); // ����� ��� ���������� ��������
    T& operator[](size_t index); // �������� ������� �� �������
    size_t getSize() const; // ����� ��� ��������� �������� �������

    void exportToFile(const std::string& filename) const; // ������� ������ � ����
    void importFromFile(const std::string& filename); // ������ ������ �� �����
    const T& operator[](size_t index) const; // ����������� ������ ���������

private:
    void checkInitialization() const; // ����� ��� �������� ��������� �������������
};

// ���������� ������� ������ Vector

template <typename T>
Vector<T>::Vector(size_t initial_size) : data(nullptr), n(0), capacity(initial_size), is_initialized(false) {
    // ������ �� ���������� � ������������
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data; // ����������� ������ ��� ����������� �������
}

template <typename T>
void Vector<T>::initializeWithConstant(const T& value) {
    if (is_initialized) {
        throw std::runtime_error("Vector is already initialized."); // ����������, ���� ������ ��� ���������������
    }

    data = new T[capacity]; // �������� ������ ��� ������
    for (size_t i = 0; i < capacity; ++i) {
        data[i] = value; // �������������� ��� �������� ����������
    }

    n = capacity; // ������������� ������� ������
    is_initialized = true; // ������������� ��������� ������������� � true
}

template <typename T>
void Vector<T>::initializeWithRandomNumbers(T min, T max) {
    if (is_initialized) {
        throw std::runtime_error("Vector is already initialized."); // ����������, ���� ������ ��� ���������������
    }

    data = new T[capacity]; // �������� ������ ��� ������

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // �������������� ��������� ��������� �����
    for (size_t i = 0; i < capacity; ++i) {
        data[i] = min + (std::rand() % (max - min + 1)); // �������������� ���������� ������� � �������� ���������
    }

    n = capacity; // ������������� ������� ������
    is_initialized = true; // ������������� ��������� ������������� � true
}

template <typename T>
void Vector<T>::checkInitialization() const {
    if (!is_initialized) {
        throw std::runtime_error("Vector is not initialized."); // ����������, ���� ������ �� ���������������
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    checkInitialization(); // ��������� ��������� ������������� ����� ����������� ������

    if (n >= capacity) {
        size_t new_capacity = capacity * 2; // ����������� �������
        T* new_data = new T[new_capacity]; // ������� ����� ������

        for (size_t i = 0; i < n; ++i) {
            new_data[i] = data[i]; // �������� ������ �������� � ����� ������
        }

        delete[] data; // ����������� ������ ������
        data = new_data; // �������������� ��������� �� ����� ������
        capacity = new_capacity; // ��������� �������
    }

    data[n++] = value; // ��������� ����� ������� � ����������� ������
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    checkInitialization(); // ��������� ��������� ������������� ����� ����������� ������
    if (index >= n) {
        throw std::out_of_range("Index out of range"); // �������� �� ����� �� �������
    }

    return data[index]; // ���������� ������� �� �������
}

template <typename T>
size_t Vector<T>::getSize() const {
    checkInitialization(); // ��������� ��������� ������������� ����� ����������� ������
    return n; // ���������� ����������� �������
}

template <typename T>
void Vector<T>::exportToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for record!" << std::endl;
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        outFile << data[i] << std::endl; // ���������� ������ ������� � ����
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
    is_initialized = true; // ������������� ��������� ������������� � true

    // ����������� ������ �� �����, ���� ���� ��� ������.
    while (inFile >> value) {
        push_back(value);  // ��������� ��������� �������� � ������.
    }

    inFile.close();
    std::cout << "Data successfully imported from " << filename << std::endl;
}

// ���������� ����������� ������ ��������� []
template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    checkInitialization(); // ��������� ��������� ������������� ����� ����������� ������
    if (index >= n) {
        throw std::out_of_range("Index out of range"); // �������� �� ����� �� �������
    }

    return data[index]; // ���������� ������� �� �������
}


#endif // VECTOR_H
