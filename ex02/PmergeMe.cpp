#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


PmergeMe::PmergeMe(const std::vector<int>& data)
    : vectorData(data), dequeData(data.begin(), data.end()) {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : vectorData(other.vectorData), dequeData(other.dequeData) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        vectorData = other.vectorData;
        dequeData = other.dequeData;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sortWithVector() {
    fordJohnsonSortVector();
}

void PmergeMe::sortWithDeque() {
    fordJohnsonSortDeque();
}

const std::vector<int>& PmergeMe::getSortedVector() const {
    return vectorData;
}

const std::deque<int>& PmergeMe::getSortedDeque() const {
    return dequeData;
}

// Ford-Johnson sort pour std::vector
void PmergeMe::fordJohnsonSortVector() {
    int n = vectorData.size();
    if (n <= 1) return;

    std::vector<int> sortedData;

    // Étape 1 : Trier les paires et insérer dans la liste triée
    for (int i = 0; i + 1 < n; i += 2) {
        if (vectorData[i] > vectorData[i + 1]) {
            std::swap(vectorData[i], vectorData[i + 1]);
        }
        // Insérer le plus petit élément de la paire
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), vectorData[i]), 
            vectorData[i]
        );
        // Insérer le plus grand élément de la paire
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), vectorData[i + 1]), 
            vectorData[i + 1]
        );
    }

    // Si le nombre d'éléments est impair, on insère le dernier élément
    if (n % 2 != 0) {
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), vectorData.back()), 
            vectorData.back()
        );
    }

    vectorData = sortedData;
}

// Ford-Johnson sort pour std::deque
void PmergeMe::fordJohnsonSortDeque() {
    int n = dequeData.size();
    if (n <= 1) return;

    std::deque<int> sortedData;

    // Étape 1 : Trier les paires et insérer dans la liste triée
    for (int i = 0; i + 1 < n; i += 2) {
        if (dequeData[i] > dequeData[i + 1]) {
            std::swap(dequeData[i], dequeData[i + 1]);
        }
        // Insérer le plus petit élément de la paire
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), dequeData[i]), 
            dequeData[i]
        );
        // Insérer le plus grand élément de la paire
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), dequeData[i + 1]), 
            dequeData[i + 1]
        );
    }

    // Si le nombre d'éléments est impair, on insère le dernier élément
    if (n % 2 != 0) {
        sortedData.insert(
            std::upper_bound(sortedData.begin(), sortedData.end(), dequeData.back()), 
            dequeData.back()
        );
    }

    dequeData = sortedData;
}
