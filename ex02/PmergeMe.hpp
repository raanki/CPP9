/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:50:19 by ranki             #+#    #+#             */
/*   Updated: 2024/08/28 11:20:39 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe {
public:
    PmergeMe(const std::vector<int>& data);
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void sortWithVector();
    void sortWithDeque();

    const std::vector<int>& getSortedVector() const;
    const std::deque<int>& getSortedDeque() const;

private:
    std::vector<int> vectorData;
    std::deque<int> dequeData;

    void fordJohnsonSortVector();
    void fordJohnsonSortDeque();

    void mergePairsVector(int left, int right);
    void mergePairsDeque(int left, int right);

    void insertAndMergeVector(int left, int mid, int right);
    void insertAndMergeDeque(int left, int mid, int right);
};

#endif

