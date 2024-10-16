#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Класс для описания характеристик процессора
class CpuSpec {
public:
    std::string model;          // Модель процессора
    int cores;                  // Количество ядер
    float frequency;            // Частота в ГГц
    int threads;                // Количество потоков
    int cacheSize;              // Размер кэша в МБ
    std::string architecture;   // Архитектура процессора

    void print() const;         // Вывод информации о процессоре
    void exportData(std::ofstream& file) const;  // Экспорт данных в файл
    void importData(std::ifstream& file);        // Импорт данных из файла
};

// Класс для описания характеристик графического процессора
class GpuSpec {
public:
    std::string model;          // Модель графического процессора
    int memorySize;             // Объем памяти в ГБ
    float coreClock;            // Тактовая частота в ГГц
    std::string memoryType;     // Тип памяти (например, GDDR6)
    int shaderCores;            // Количество шейдерных ядер
    float tdp;                  // Тепловая мощность (TDP) в ваттах

    void print() const;         // Вывод информации о графическом процессоре
    void exportData(std::ofstream& file) const;  // Экспорт данных в файл
    void importData(std::ifstream& file);        // Импорт данных из файла
};

// Класс для описания характеристик оперативной памяти
class RamSpec {
public:
    int capacity;               // Объем памяти в ГБ
    double speed;               // Скорость памяти в МГц

    void print() const;         // Вывод информации о RAM
    void exportData(std::ofstream& file) const;  // Экспорт данных в файл
    void importData(std::ifstream& file);        // Импорт данных из файла
};

// Класс для описания характеристик сетевого интерфейса
class LanSpec {
public:
    int bandwidth;              // Пропускная способность сети в Мбит/с

    void print() const;         // Вывод информации о LAN
    void exportData(std::ofstream& file) const;  // Экспорт данных в файл
    void importData(std::ifstream& file);        // Импорт данных из файла
};

// Класс для узла кластера, который включает спецификации CPU, GPU, RAM и LAN
class ClusterNode : public CpuSpec, public GpuSpec, public RamSpec, public LanSpec {
public:
    int id_node;                // Идентификатор узла

    void print() const;         // Вывод информации о узле кластера
    void exportData(std::ofstream& file) const;  // Экспорт данных узла в файл
    void importData(std::ifstream& file);        // Импорт данных узла из файла
};

// Класс для управления кластером узлов
class Cluster {
public:
    std::string name; // Имя кластера
    std::string status; // Статус кластера
    std::vector<ClusterNode> nodes;

    void addNode(const ClusterNode &node);
    void removeNode(int id);
    size_t nodeCount() const;
    void print() const;
};

#endif // CLUSTER_H
