/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:50:19 by ranki             #+#    #+#             */
/*   Updated: 2024/11/24 15:23:52 by ranki            ###   ########.fr       */
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

    std::deque<int> mergeInsertionSort(const std::deque<int>& data);
    std::vector<int> mergeInsertionSort(const std::vector<int>& data);

};

#endif


