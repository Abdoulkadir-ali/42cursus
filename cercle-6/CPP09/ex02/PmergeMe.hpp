/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:46:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <ctime>
#include <deque>
#include <string>
#include <vector>
#include <climits>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    void parseArguments(int argc, char** argv);
    void run() const;

private:
    struct PairData {
        int small;
        int large;
    };

    std::vector<int> _inputVector;
    std::deque<int> _inputDeque;

    static bool isDigitsOnly(const std::string& token);
    static bool hasDuplicate(const std::vector<int>& values, int value);
    static double elapsedMicroseconds(clock_t start, clock_t end);

    static void printVector(const std::vector<int>& values, const std::string& label);

    std::vector<int> fordJohnsonVector(const std::vector<int>& input) const;
    std::deque<int> fordJohnsonDeque(const std::deque<int>& input) const;

    static size_t lowerBoundIndexVector(const std::vector<int>& values, int target);
    static size_t lowerBoundIndexDeque(const std::deque<int>& values, int target);

    static std::vector<size_t> jacobsthalOrderVector(size_t pendSize);
    static std::deque<size_t> jacobsthalOrderDeque(size_t pendSize);
};

#endif
