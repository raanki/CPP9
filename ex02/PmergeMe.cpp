#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

// la suite de Jacobsthal jusqu'à n
std::vector<int> generateJacobsthalSequence(int n) {
    std::vector<int> jacobsthal;
    jacobsthal.push_back(0); // J_0 = 0
    jacobsthal.push_back(1); // J_1 = 1
    int index = 1;
    while (true) {
        int next = jacobsthal[index] + 2 * jacobsthal[index - 1];
        if (next >= n)
            break;
        jacobsthal.push_back(next);
        index++;
    }
    return jacobsthal;
}

// binarySearch
template <typename Iterator, typename T>
Iterator binarySearchInsertPosition(Iterator begin, Iterator end, const T& value) {
    while (begin < end) {
        Iterator mid = begin + (end - begin) / 2;
        if (value < *mid)
            end = mid;
        else
            begin = mid + 1;
    }
    return begin;
}

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
    vectorData = mergeInsertionSort(vectorData);
}

void PmergeMe::sortWithDeque() {
    dequeData = mergeInsertionSort(dequeData);
}

const std::vector<int>& PmergeMe::getSortedVector() const {
    return vectorData;
}

const std::deque<int>& PmergeMe::getSortedDeque() const {
    return dequeData;
}

// ford-johson sort
std::vector<int> PmergeMe::mergeInsertionSort(const std::vector<int>& data) {
    int n = data.size();
    if (n <= 1)
        return data;

    // Étape 1 : Groupement en paires
    std::vector<std::pair<int, int> > pairs;
    std::vector<int> unpairedElements;
    for (int i = 0; i + 1 < n; i += 2) {
        pairs.push_back(std::make_pair(data[i], data[i + 1]));
    }
    if (n % 2 != 0) {
        unpairedElements.push_back(data.back());
    }

    // Étape 2 : Comparaison des paires
    std::vector<int> largerElements;
    std::vector<int> smallerElements;
    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first > pairs[i].second) {
            largerElements.push_back(pairs[i].first);
            smallerElements.push_back(pairs[i].second);
        } else {
            largerElements.push_back(pairs[i].second);
            smallerElements.push_back(pairs[i].first);
        }
    }

    // Étape 3 : Tri récursif des plus grands éléments
    std::vector<int> S = mergeInsertionSort(largerElements);

    // Étape 4 : Insertion de l'élément apparié avec le premier élément de S
    std::vector<int> result;
    int indexOfFirstInS = -1;
    if (!smallerElements.empty()) {
        // Trouver l'indice de l'élément apparié avec le premier élément de S
        for (std::size_t i = 0; i < largerElements.size(); ++i) {
            if (largerElements[i] == S[0]) {
                indexOfFirstInS = static_cast<int>(i);
                break;
            }
        }
        if (indexOfFirstInS != -1) {
            // Insérer l'élément apparié au début de S
            result.push_back(smallerElements[indexOfFirstInS]);
        }
    }

    // Ajouter le reste de S
    result.insert(result.end(), S.begin(), S.end());

    // Étape 5 : Insertion des éléments restants selon la suite de Jacobsthal
    std::vector<int> pendingIndices;
    for (std::size_t i = 0; i < smallerElements.size(); ++i) {
        if (static_cast<int>(i) != indexOfFirstInS)
            pendingIndices.push_back(static_cast<int>(i));
    }

    // Générer la suite de Jacobsthal
    std::vector<int> jacobsthalSeq = generateJacobsthalSequence(pendingIndices.size());
    // 0 1 1 3 5 11 21 43 85 171 341 683 1365 2731 5461

    // Insertion des éléments selon la suite de Jacobsthal
    std::vector<bool> inserted(pendingIndices.size(), false);
    for (std::size_t seqIndex = 1; seqIndex < jacobsthalSeq.size(); ++seqIndex) {
        int idx = jacobsthalSeq[seqIndex] - 1;
        if (idx < 0 || idx >= static_cast<int>(pendingIndices.size()))
            continue;
        if (inserted[idx])
            continue;
        int valueToInsert = smallerElements[pendingIndices[idx]];
        std::vector<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
        result.insert(insertPos, valueToInsert);
        inserted[idx] = true;
    }
    // Insérer les éléments restants
    for (std::size_t i = 0; i < pendingIndices.size(); ++i) {
        if (!inserted[i]) {
            int valueToInsert = smallerElements[pendingIndices[i]];
            std::vector<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
            result.insert(insertPos, valueToInsert);
        }
    }

    // Insertion des éléments non appariés
    for (std::size_t i = 0; i < unpairedElements.size(); ++i) {
        int valueToInsert = unpairedElements[i];
        std::vector<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
        result.insert(insertPos, valueToInsert);
    }

    return result;
}

// Implémentation de Merge-Insertion Sort pour std::deque
std::deque<int> PmergeMe::mergeInsertionSort(const std::deque<int>& data) {
    int n = data.size();
    if (n <= 1)
        return data;

    // Étape 1 : Groupement en paires
    std::vector<std::pair<int, int> > pairs;
    std::deque<int> unpairedElements;
    for (int i = 0; i + 1 < n; i += 2) {
        pairs.push_back(std::make_pair(data[i], data[i + 1]));
    }
    if (n % 2 != 0) {
        unpairedElements.push_back(data.back());
    }

    // Étape 2 : Comparaison des paires
    std::deque<int> largerElements;
    std::deque<int> smallerElements;
    for (std::size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first > pairs[i].second) {
            largerElements.push_back(pairs[i].first);
            smallerElements.push_back(pairs[i].second);
        } else {
            largerElements.push_back(pairs[i].second);
            smallerElements.push_back(pairs[i].first);
        }
    }

    // Étape 3 : Tri récursif des plus grands éléments
    std::deque<int> S = mergeInsertionSort(largerElements);

    // Étape 4 : Insertion de l'élément apparié avec le premier élément de S
    std::deque<int> result;
    int indexOfFirstInS = -1;
    if (!smallerElements.empty()) {
        // Trouver l'indice de l'élément apparié avec le premier élément de S
        for (std::size_t i = 0; i < largerElements.size(); ++i) {
            if (largerElements[i] == S[0]) {
                indexOfFirstInS = static_cast<int>(i);
                break;
            }
        }
        if (indexOfFirstInS != -1) {
            // Insérer l'élément apparié au début de S
            result.push_back(smallerElements[indexOfFirstInS]);
        }
    }

    // Ajouter le reste de S
    result.insert(result.end(), S.begin(), S.end());

    // Étape 5 : Insertion des éléments restants selon la suite de Jacobsthal
    std::vector<int> pendingIndices;
    for (std::size_t i = 0; i < smallerElements.size(); ++i) {
        if (static_cast<int>(i) != indexOfFirstInS)
            pendingIndices.push_back(static_cast<int>(i));
    }

    // Générer la suite de Jacobsthal
    std::vector<int> jacobsthalSeq = generateJacobsthalSequence(pendingIndices.size());

    // Insertion des éléments selon la suite de Jacobsthal
    std::vector<bool> inserted(pendingIndices.size(), false);
    for (std::size_t seqIndex = 1; seqIndex < jacobsthalSeq.size(); ++seqIndex) {
        int idx = jacobsthalSeq[seqIndex] - 1;
        if (idx < 0 || idx >= static_cast<int>(pendingIndices.size()))
            continue;
        if (inserted[idx])
            continue;
        int valueToInsert = smallerElements[pendingIndices[idx]];
        std::deque<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
        result.insert(insertPos, valueToInsert);
        inserted[idx] = true;
    }
    // Insérer les éléments restants
    for (std::size_t i = 0; i < pendingIndices.size(); ++i) {
        if (!inserted[i]) {
            int valueToInsert = smallerElements[pendingIndices[i]];
            std::deque<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
            result.insert(insertPos, valueToInsert);
        }
    }

    // Insertion des éléments non appariés
    for (std::size_t i = 0; i < unpairedElements.size(); ++i) {
        int valueToInsert = unpairedElements[i];
        std::deque<int>::iterator insertPos = binarySearchInsertPosition(result.begin(), result.end(), valueToInsert);
        result.insert(insertPos, valueToInsert);
    }

    return result;
}
