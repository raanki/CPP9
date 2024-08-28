#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <ctime>

#define GREEN "\033[32m"
#define WHITE_ON_GREEN "\033[37;42m"
#define RESET "\033[0m"

std::vector<int> parseInput(int argc, char* argv[]);
void displayVector(const std::vector<int>& data, const std::string& label);
void displayDeque(const std::deque<int>& data, const std::string& label);
double measureTimeVector(PmergeMe& sorter);
double measureTimeDeque(PmergeMe& sorter);
void displaySortedData(const std::vector<int>& sortedVector, const std::deque<int>& sortedDeque);
void displayTimes(double vectorTime, double dequeTime, std::size_t dataSize);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <integers...>" << std::endl;
        return 1;
    }

    try {
        std::vector<int> data = parseInput(argc, argv);
        displayVector(data, "Before");

        PmergeMe sorter(data);

        double vectorTime = measureTimeVector(sorter);
        double dequeTime = measureTimeDeque(sorter);

        const std::vector<int>& sortedVector = sorter.getSortedVector();
        const std::deque<int>& sortedDeque = sorter.getSortedDeque();

        displaySortedData(sortedVector, sortedDeque);
        displayTimes(vectorTime, dequeTime, data.size());

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

std::vector<int> parseInput(int argc, char* argv[]) {
    std::vector<int> data;
    for (int i = 1; i < argc; ++i) {
        int number;
        std::istringstream iss(argv[i]);
        if (!(iss >> number) || number < 0) {
            throw std::runtime_error("Error: invalid input");
        }
        data.push_back(number);
    }
    return data;
}

void displayVector(const std::vector<int>& data, const std::string& label) {
    std::cout << WHITE_ON_GREEN << label << ": " << RESET;
    for (std::size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << (i + 1 < data.size() ? " " : "\n");
    }
}

void displayDeque(const std::deque<int>& data, const std::string& label) {
    std::cout << WHITE_ON_GREEN << label << ": " << RESET;
    for (std::size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << (i + 1 < data.size() ? " " : "\n");
    }
}

double measureTimeVector(PmergeMe& sorter) {
    clock_t startVector = clock();
    sorter.sortWithVector();
    clock_t endVector = clock();
    return static_cast<double>(endVector - startVector) / CLOCKS_PER_SEC * 1000000;
}

double measureTimeDeque(PmergeMe& sorter) {
    clock_t startDeque = clock();
    sorter.sortWithDeque();
    clock_t endDeque = clock();
    return static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC * 1000000;
}

void displaySortedData(const std::vector<int>& sortedVector, const std::deque<int>& sortedDeque) {
    displayVector(sortedVector, "After (vector)");
    displayDeque(sortedDeque, "After (deque)");
}

void displayTimes(double vectorTime, double dequeTime, std::size_t dataSize) {
    std::cout << GREEN << "Time to process a range of " << RESET << dataSize
              << GREEN << " elements with std::vector: " << RESET << vectorTime << GREEN << " us" << RESET << std::endl;

    std::cout << GREEN << "Time to process a range of " << RESET << dataSize
              << GREEN << " elements with std::deque: " << RESET << dequeTime << GREEN << " us" << RESET << std::endl;
}
