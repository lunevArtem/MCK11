#include "cluster.h"
#include <iostream>
#include <fstream>

int main() {
    // Создание экземпляров классов спецификаций
    CpuSpec cpu;
    cpu.model = "AMD Ryzen 9 5900X";
    cpu.cores = 12;
    cpu.frequency = 3.8;
    cpu.threads = 24;
    cpu.cacheSize = 32;
    cpu.architecture = "Zen 3";

    GpuSpec gpu;
    gpu.model = "AMD Radeon RX 6800 XT";
    gpu.memorySize = 16; // В ГБ
    gpu.coreClock = 2.0;
    gpu.memoryType = "GDDR6";
    gpu.shaderCores = 4608;
    gpu.tdp = 300;

    RamSpec ram;
    ram.capacity = 64; // В ГБ
    ram.speed = 3600; // В МГц

    LanSpec lan;
    lan.bandwidth = 2500; // В Мбит/с

    // Создание узла кластера
    ClusterNode node;
    node.id_node = 1; // Изменен идентификатор узла

    // Заполнение полей узла напрямую
    node.CpuSpec::model = cpu.model;
    node.CpuSpec::cores = cpu.cores;
    node.CpuSpec::frequency = cpu.frequency;
    node.CpuSpec::threads = cpu.threads;
    node.CpuSpec::cacheSize = cpu.cacheSize;
    node.CpuSpec::architecture = cpu.architecture;

    node.GpuSpec::model = gpu.model;
    node.GpuSpec::memorySize = gpu.memorySize;
    node.GpuSpec::coreClock = gpu.coreClock;
    node.GpuSpec::memoryType = gpu.memoryType;
    node.GpuSpec::shaderCores = gpu.shaderCores;
    node.GpuSpec::tdp = gpu.tdp;

    node.RamSpec::capacity = ram.capacity;
    node.RamSpec::speed = ram.speed;

    node.LanSpec::bandwidth = lan.bandwidth;

    // Печать информации о узле
    std::cout << "Cluster Node Information:\n";
    node.print();

    // Экспорт данных узла в файл
    std::ofstream outFile("test1.txt"); // Изменен имя файла
    node.exportData(outFile);
    outFile.close();

    // Создание кластера и добавление узла
Cluster cluster;
cluster.name = "MyCluster"; // Установка имени кластера
cluster.status = "Active"; // Установка статуса кластера
cluster.addNode(node);

// Печать информации о кластере
std::cout << "\nCluster Information:\n";
cluster.print();

    // Импорт данных из файла
    ClusterNode importedNode;
    std::ifstream inFile("test1.txt"); // Изменен имя файла
    importedNode.importData(inFile);
    inFile.close();

    // Печать информации о импортированном узле
    std::cout << "\nImported Node Information:\n";
    importedNode.print();

    return 0;
}
