#include "MatrixBlock.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

template <typename T>
BlockMatrix<T>::BlockMatrix(unsigned blockRows, unsigned blockCols, unsigned numBlocksRows, unsigned numBlocksCols)
    : blockRows_(blockRows), blockCols_(blockCols), numBlocksRows_(numBlocksRows), numBlocksCols_(numBlocksCols) {
    blocks_.resize(numBlocksRows_, std::vector<std::vector<T>>(numBlocksCols_, std::vector<T>(blockRows_ * blockCols_)));
}

template <typename T>
BlockMatrix<T>::~BlockMatrix() {
    // Вектор автоматически очищает память
}

template <typename T>
void BlockMatrix<T>::fillRandom() {
    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    blocks_[i][j][k * blockCols_ + l] = static_cast<T>(std::rand() % 100 + 1);
                }
            }
        }
    }
}

template <typename T>
void BlockMatrix<T>::print() const {
    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            std::cout << "Block (" << i << ", " << j << "):" << std::endl;
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    std::cout << blocks_[i][j][k * blockCols_ + l] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

template <typename T>
void BlockMatrix<T>::exportToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    outFile << "BlockMatrix" << std::endl; // Название класса
    outFile << blockRows_ << " " << blockCols_ << " " << numBlocksRows_ << " " << numBlocksCols_ << std::endl; // Размеры матрицы и блоков

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    outFile << blocks_[i][j][k * blockCols_ + l] << " ";
                }
                outFile << std::endl;
            }
        }
    }

    outFile.close();
}

template <typename T>
bool BlockMatrix<T>::importFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

    std::string className;
    inFile >> className;
    if (className != "BlockMatrix") {
        std::cerr << "Class name does not match!" << std::endl;
        return false;
    }

    inFile >> blockRows_ >> blockCols_ >> numBlocksRows_ >> numBlocksCols_;
    blocks_.resize(numBlocksRows_, std::vector<std::vector<T>>(numBlocksCols_, std::vector<T>(blockRows_ * blockCols_)));

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    inFile >> blocks_[i][j][k * blockCols_ + l];
                }
            }
        }
    }

    inFile.close();
    return true;
}

template <typename T>
void BlockMatrix<T>::scalarMultiply(T scalar) {
    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    blocks_[i][j][k * blockCols_ + l] *= scalar;
                }
            }
        }
    }
}

template <typename T>
BlockMatrix<T> BlockMatrix<T>::elementWiseMultiply(const BlockMatrix<T>& other) const {
    if (numBlocksRows_ != other.numBlocksRows_ || numBlocksCols_ != other.numBlocksCols_ ||
        blockRows_ != other.blockRows_ || blockCols_ != other.blockCols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for element-wise multiplication.");
    }

    BlockMatrix<T> result(blockRows_, blockCols_, numBlocksRows_, numBlocksCols_);

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    result.blocks_[i][j][k * blockCols_ + l] = blocks_[i][j][k * blockCols_ + l] * other.blocks_[i][j][k * blockCols_ + l];
                }
            }
        }
    }

    return result;
}

template <typename T>
BlockMatrix<T> BlockMatrix<T>::operator*(const BlockMatrix<T>& other) const {
    if (numBlocksCols_ != other.numBlocksRows_ || blockCols_ != other.blockRows_) {
        throw std::invalid_argument("Matrix dimensions do not allow multiplication.");
    }

    BlockMatrix<T> result(blockRows_, other.blockCols_, numBlocksRows_, other.numBlocksCols_);

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < other.numBlocksCols_; ++j) {
            for (unsigned k = 0; k < numBlocksCols_; ++k) {
                for (unsigned m = 0; m < blockRows_; ++m) {
                    for (unsigned n = 0; n < other.blockCols_; ++n) {
                        result.blocks_[i][j][m * other.blockCols_ + n] += blocks_[i][k][m * blockCols_ + n] * other.blocks_[k][j][n];
                    }
                }
            }
        }
    }

    return result;
}

template <typename T>
BlockMatrix<T> BlockMatrix<T>::operator+(const BlockMatrix<T>& other) const {
    if (numBlocksRows_ != other.numBlocksRows_ || numBlocksCols_ != other.numBlocksCols_ ||
        blockRows_ != other.blockRows_ || blockCols_ != other.blockCols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    BlockMatrix<T> result(blockRows_, blockCols_, numBlocksRows_, numBlocksCols_);

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    result.blocks_[i][j][k * blockCols_ + l] = blocks_[i][j][k * blockCols_ + l] + other.blocks_[i][j][k * blockCols_ + l];
                }
            }
        }
    }

    return result;
}

template <typename T>
BlockMatrix<T> BlockMatrix<T>::operator-(const BlockMatrix<T>& other) const {
    if (numBlocksRows_ != other.numBlocksRows_ || numBlocksCols_ != other.numBlocksCols_ ||
        blockRows_ != other.blockRows_ || blockCols_ != other.blockCols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    BlockMatrix<T> result(blockRows_, blockCols_, numBlocksRows_, numBlocksCols_);

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    result.blocks_[i][j][k * blockCols_ + l] = blocks_[i][j][k * blockCols_ + l] - other.blocks_[i][j][k * blockCols_ + l];
                }
            }
        }
    }

    return result;
}

template <typename T>
BlockMatrix<T> BlockMatrix<T>::transpose() const {
    BlockMatrix<T> result(blockCols_, blockRows_, numBlocksCols_, numBlocksRows_);

    for (unsigned i = 0; i < numBlocksRows_; ++i) {
        for (unsigned j = 0; j < numBlocksCols_; ++j) {
            for (unsigned k = 0; k < blockRows_; ++k) {
                for (unsigned l = 0; l < blockCols_; ++l) {
                    result.blocks_[j][i][l * blockRows_ + k] = blocks_[i][j][k * blockCols_ + l];
                }
            }
        }
    }

    return result;
}


template class BlockMatrix<int>;
template class BlockMatrix<double>;
