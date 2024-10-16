#include "cluster.h"
#include <algorithm>  // Для std::remove_if
#include <iostream>
#include <fstream>

// Реализация методов CpuSpec
void CpuSpec::print() const {
    std::cout << "CPU Model: " << model << "\n"
              << "Cores: " << cores << "\n"
              << "Frequency: " << frequency << " GHz\n"
              << "Threads: " << threads << "\n"
              << "Cache Size: " << cacheSize << " MB\n"
              << "Architecture: " << architecture << std::endl;
}

void CpuSpec::exportData(std::ofstream& file) const {
    if (!file.is_open()) {
        std::cerr << "Error: file is not open!" << std::endl;
        return;
    }
    file << "CpuSpec\n"
         << model << "\n"
         << cores << "\n"
         << frequency << "\n"
         << threads << "\n"
         << cacheSize << "\n"
         << architecture << "\n";
}

void CpuSpec::importData(std::ifstream& file) {
    std::string className;
    getline(file, className);
    if (className != "CpuSpec") {
        std::cout << "Class name mismatch!" << std::endl;
        return;
    }
    getline(file, model);

    if (!(file >> cores >> frequency >> threads >> cacheSize)) {
        std::cerr << "Error reading CPU specifications!" << std::endl;
        return;
    }
    file.ignore(); // Игнорируем символ новой строки после чтения целых чисел
    getline(file, architecture);
}

// Реализация методов GpuSpec
void GpuSpec::print() const {
    std::cout << "GPU Model: " << model << "\n"
              << "Memory: " << memorySize << " GB\n"
              << "Core Clock: " << coreClock << " GHz\n"
              << "Memory Type: " << memoryType << "\n"
              << "Shader Cores: " << shaderCores << "\n"
              << "TDP: " << tdp << " W" << std::endl;
}

void GpuSpec::exportData(std::ofstream& file) const {
    if (!file.is_open()) {
        std::cerr << "Error: file is not open!" << std::endl;
        return;
    }
    file << "GpuSpec\n";
    file << model << "\n"
         << memorySize << "\n"  // В GB
         << coreClock << "\n"
         << memoryType << "\n"
         << shaderCores << "\n"
         << tdp << "\n";
}

void GpuSpec::importData(std::ifstream& file) {
    std::string className;
    getline(file, className);
    if (className != "GpuSpec") {
        std::cout << "Class name mismatch!" << std::endl;
        return;
    }
    getline(file, model);

    if (!(file >> memorySize >> coreClock >> memoryType >> shaderCores >> tdp)) {
        std::cerr << "Error reading GPU specifications!" << std::endl;
        return;
    }

    file.ignore(); // Игнорируем символ новой строки после memoryType
}

// Реализация методов RamSpec
void RamSpec::print() const {
    std::cout << "RAM Capacity: " << capacity << " GB\n"
              << "Speed: " << speed << " MHz"  // Скорость остается без изменений
              << std::endl;
}

void RamSpec::exportData(std::ofstream& file) const {
    if (!file.is_open()) {
        std::cerr << "Error: file is not open!"<<std::endl;
        return;
    }
    file<< "RamSpec\n";
    file<< capacity<< "\n"
        <<" "<< speed<< "\n";
}

void RamSpec::importData(std::ifstream& file) {
    std::string className;
    getline(file, className);
    if (className != "RamSpec") {
        std::cout << "Class name mismatch!" << std::endl;
        return;
    }

    if (!(file >> capacity)) {
        std::cerr << "Error reading RAM capacity!" << std::endl;
        return;
    }
    file.ignore(); // Игнорируем символ новой строки после capacity

    if (!(file >> speed)) {
        std::cerr << "Error reading RAM speed!" << std::endl;
        return;
    }
    file.ignore(); // Игнорируем символ новой строки после speed

    // Вывод для проверки
    std::cout << "Imported RAM Capacity: " << capacity << " GB\n";
    std::cout << "Imported RAM Speed: " << speed << " MHz\n";
}


// Реализация методов LanSpec
void LanSpec::print() const {
    std::cout<<"LAN Bandwidth: "<< bandwidth<<" Mbps"<<std::endl;
}

void LanSpec::exportData(std::ofstream& file) const {
   if (!file.is_open()) {
       std::cerr<< ("Error: file is not open!")<<std::endl;
       return;
   }
   file<<"LanSpec\n";
   file<< bandwidth<<"\n";
}

void LanSpec::importData(std::ifstream& file) {
   std::string className;
   getline(file,className);
   if(className!=("LanSpec")) {
       std::cout<<("Class name mismatch!")<<std::endl;
       return;
   }
   file>>bandwidth;
   file.ignore(); // Игнорируем символ новой строки после bandwidth
}

// Реализация методов ClusterNode
void ClusterNode::print() const {
    std::cout<<"Node ID: "<< id_node<<std::endl;
    CpuSpec :: print();
    GpuSpec :: print();
    RamSpec :: print();
    LanSpec :: print();
}

// Реализация методов ClusterNode
void ClusterNode :: exportData(std :: ofstream &file) const {
     if (!file.is_open()) {
         std :: cerr<<"Error :file is not open !"<<std :: endl;
         return ;
     }
     file<<"ClusterNode\n"; // Имя класса
     file<< id_node<<"\n"; // ID узла
     CpuSpec :: exportData(file); // Экспорт данных CPU
     GpuSpec :: exportData(file); // Экспорт данных GPU
     RamSpec :: exportData(file); // Экспорт данных RAM
     LanSpec :: exportData(file); // Экспорт данных LAN
}

void ClusterNode :: importData(std :: ifstream &file) {
     std :: string className;
     getline(file,className);
     if(className!=("ClusterNode")) {
         std :: cout<<"Class name mismatch !"<<std :: endl;
         return ;
     }
     file>> id_node ;
     file.ignore(); // Игнорируем символ новой строки после id_node
     CpuSpec :: importData(file); // Импорт данных CPU
     GpuSpec :: importData(file); // Импорт данных GPU
     RamSpec :: importData(file); // Импорт данных RAM
     LanSpec :: importData(file); // Импорт данных LAN
}

// Реализация методов Cluster
void Cluster :: addNode(const ClusterNode &node) {
     nodes.push_back(node);
}

void Cluster :: removeNode(int id) {
     nodes.erase(std :: remove_if(nodes.begin(), nodes.end(), [id](const ClusterNode &node) { return node.id_node == id; }), nodes.end());
}

size_t Cluster :: nodeCount() const {
     return nodes.size();
}

void Cluster :: print() const {
     std :: cout<<"Cluster Name : "<< name<<"\nStatus : "<< status<<"\nNumber of Nodes : "<< nodeCount()<<std :: endl;
     for(const auto &node : nodes) {
         node.print();
     }
}
