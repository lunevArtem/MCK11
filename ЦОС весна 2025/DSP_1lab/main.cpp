#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

// ��������� ��� �������� ���������� ���������
struct Harmonic {
    double amplitude; // ��������� ���������
    double frequency;  // ������� ��������� (������� �������)
};

struct Sample {
    double time;
    double value; // ���������� double ������ uint32_t
};

int main() {
    // ��� ����� ��� ������ ����������
    std::string filename = "parameters.txt";

    // ������ ���������� �� �����
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File opening error " << filename << std::endl;
        return 1;
    }

    int numHarmonics; // ���������� ��������
    double baseFrequency; // ������� �������
    double samplingFrequency; // ������� �������������
    double initialPhase; // ��������� ����� ����
    double imax; // ���������� ���������

    file >> numHarmonics;
    file >> baseFrequency;
    file >> samplingFrequency;
    file >> initialPhase;
    file >> imax;

    // ������ ��� �������� ��������
    std::vector<Harmonic> harmonics(numHarmonics);

    // ������������� ��������
    for (int i = 0; i < numHarmonics; ++i) {
        file >> harmonics[i].amplitude; // ������ ��������� �� �����
        harmonics[i].frequency = baseFrequency * (i + 1); // ������� ���������
    }

    file.close();

    // ��������� �������������
    int numSamples = static_cast<int>(samplingFrequency); // ���������� �������� �� ������
    double period = 1.0 / baseFrequency; // ������ ������� �������
    double dt = period / numSamples; // ��� ������������� �� �������

    // ��������� �������
    std::vector<double> signal(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        double t = i * dt; // ������� �����
        double signalValue = 0.0; // �������� ������� � ������� ������ �������

        for (const auto& harmonic : harmonics) {
            signalValue += harmonic.amplitude * std::sin(2 * M_PI * harmonic.frequency * t + initialPhase);
        }

        signal[i] = signalValue;
    }

    // ���������� ������� � ����
    std::ofstream signalOutFile("signal.txt");
    if (!signalOutFile.is_open()) {
        std::cerr << "Error opening the file for recording the signal." << std::endl;
        return 1;
    }

    for (int i = 0; i < numSamples; ++i) {
        double t = i * dt; // ������� �����
        signalOutFile << t << " " << signal[i] << std::endl;
    }

    signalOutFile.close();

    std::cout << "The signal is recorded in a file signal.txt" << std::endl;
    std::cout << "Maximum amplitude (imax): " << imax << std::endl;

    // ��� ����� ��� ������ �������
    std::string inputFilename = "signal.txt";

    // ��� ����� ��� ������ ������������� �������
    std::string outputFilename = "quantized_signal.txt";

    // ������ ������� �� �����
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "File opening error " << inputFilename << std::endl;
        return 1;
    }

    // ������ ��� �������� �������� �������
    std::vector<Sample> signalSamples;

    double time, value;
    while (inputFile >> time >> value) {
        signalSamples.push_back({time, value});
    }

    inputFile.close();

    if (signalSamples.empty()) {
        std::cerr << "file " << inputFilename << " empty." << std::endl;
        return 1;
    }

   // ��������� �����������
int numLevels = 16; // ���������� ������� �����������

// ������� ����������� � ������������ �������� �������
double minSignal = signalSamples[0].value;
double maxSignal = signalSamples[0].value;

for (const auto& sample : signalSamples) {
    if (sample.value < minSignal) {
        minSignal = sample.value;
    }
    if (sample.value > maxSignal) {
        maxSignal = sample.value;
    }
}

// ������ ������������� ������� � ����
std::ofstream outputFile(outputFilename);
if (!outputFile.is_open()) {
    std::cerr << "File opening error " << outputFilename << std::endl;
    return 1;
}

for (const auto& sample : signalSamples) {
    // ������������ ������� � �������� [-1, 1]
    double normalizedValue = (sample.value - (maxSignal + minSignal) / 2.0) / ((maxSignal - minSignal) / 2.0);


double quantizedNormalized = std::round(normalizedValue * (numLevels - 1)) / (numLevels - 1);
double quantizedValue = quantizedNormalized * ((maxSignal - minSignal) / 2.0) + (maxSignal + minSignal) / 2.0;


    // ������ ������������� �������� � ����
    outputFile << sample.time << " " << quantizedValue << std::endl;
}

outputFile.close();


    std::cout << "The quantized signal is recorded in a file " << outputFilename << std::endl;


 // ����� ������
std::string inputFilename1 = "signal.txt";
std::string inputFilename2 = "quantized_signal.txt";
std::string outputFilename3 = "overlapped_signal.txt";

// ������� ��� �������� ��������
std::vector<Sample> originalSignal;
std::vector<Sample> quantizedSignal;

// ������ �������� �� ������
std::ifstream inputFile1(inputFilename1);
if (!inputFile1.is_open()) {
    std::cerr << "File opening error " << inputFilename1 << std::endl;
    return 1;
}

std::ifstream inputFile2(inputFilename2);
if (!inputFile2.is_open()) {
    std::cerr << "File opening error " << inputFilename2 << std::endl;
    return 1;
}


while (inputFile1 >> time >> value) {
    originalSignal.push_back({time, value});
}

while (inputFile2 >> time >> value) {
    quantizedSignal.push_back({time, value});
}

inputFile1.close();
inputFile2.close();

// ��������, ��� ������� ����� ���������� �����
if (originalSignal.size() != quantizedSignal.size()) {
    std::cerr << "The signals have different lengths." << std::endl;
    return 1;
}

// ������ ����� �������� � ���� ����
std::ofstream outputFile3(outputFilename3);
if (!outputFile3.is_open()) {
    std::cerr << "File opening error " << outputFilename3 << std::endl;
    return 1;
}

for (size_t i = 0; i < originalSignal.size(); ++i) {
    outputFile3 << originalSignal[i].time << " " << originalSignal[i].value << " " << quantizedSignal[i].value << std::endl;
}

outputFile3.close();

std::cout << "Both signals are recorded in a file " << outputFilename3 << std::endl;


// ������ ������� �������������� ������ (���) ����� �������� � ������������ ���������
double mse = 0.0;
for (size_t i = 0; i < originalSignal.size(); ++i) {
    double error = originalSignal[i].value - quantizedSignal[i].value;
    mse += error * error;
}

mse /= originalSignal.size();

std::cout << "Average square error (SQR): " << mse << std::endl;
// ������ ������������������� �������� ��������� �������
double signalPower = 0.0;
for (const auto& sample : originalSignal) {
    signalPower += sample.value * sample.value;
}
signalPower /= originalSignal.size();

// ������ �������� ���� �����������
double noisePower = mse; // mse ��� ���������� ����

// ������ ��������� ������/��� � ���������
double snr = 10 * log10(signalPower / noisePower);

std::cout << "Signal-to-noise ratio (SNR) in decibels: " << snr << std::endl;

return 0;
}
