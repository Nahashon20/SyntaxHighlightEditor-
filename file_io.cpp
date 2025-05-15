#include "file_io.h"
#include <fstream>
#include <iostream>
#include <filesystem>



bool loadFromFile(const std::string& filename, TextBuffer& buffer) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return false;
    }

    buffer.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        buffer.addLine(line);
    }

    std::cout << "File loaded successfully from " << filename << ".\n";
    return true;
}

bool saveToFile(const std::string& filename, const TextBuffer& buffer) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to open file for writing.\n";
        return false;
    }

    for (const auto& line : buffer.getLines()) {
        outFile << line << "\n";
    }

    std::cout << "File saved successfully to " << filename << ".\n";
    return true;
}