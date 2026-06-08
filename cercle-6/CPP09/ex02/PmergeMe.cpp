/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:11:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:46:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <climits>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other)
    : _inputVector(other._inputVector), _inputDeque(other._inputDeque) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        _inputVector = other._inputVector;
        _inputDeque = other._inputDeque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::isDigitsOnly(const std::string& token) {
    if (token.empty())
        return false;
    for (size_t i = 0; i < token.size(); ++i) {
        if (token[i] < '0' || token[i] > '9')
            return false;
    }
    return true;
}

bool PmergeMe::hasDuplicate(const std::vector<int>& values, int value) {
    for (size_t i = 0; i < values.size(); ++i) {
        if (values[i] == value)
            return true;
    }
    return false;
}

double PmergeMe::elapsedMicroseconds(clock_t start, clock_t end) {
    return static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void PmergeMe::printVector(const std::vector<int>& values, const std::string& label) {
    std::cout << label;
    for (size_t i = 0; i < values.size(); ++i) {
        if (i != 0)
            std::cout << " ";
        std::cout << values[i];
    }
    std::cout << std::endl;
}

size_t PmergeMe::lowerBoundIndexVector(const std::vector<int>& values, int target) {
    size_t left = 0;
    size_t right = values.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (values[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

size_t PmergeMe::lowerBoundIndexDeque(const std::deque<int>& values, int target) {
    size_t left = 0;
    size_t right = values.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (values[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

std::vector<size_t> PmergeMe::jacobsthalOrderVector(size_t pendSize) {
    std::vector<size_t> order;
    if (pendSize <= 1)
        return order;

    size_t previousBoundary = 1;
    size_t jPrev = 1;
    size_t jCurr = 1;

    while (true) {
        size_t next = jCurr + 2 * jPrev;
        if (next > pendSize)
            break;
        for (size_t i = next; i > previousBoundary; --i)
            order.push_back(i - 1);
        previousBoundary = next;
        jPrev = jCurr;
        jCurr = next;
    }

    for (size_t i = pendSize; i > previousBoundary; --i)
        order.push_back(i - 1);

    return order;
}

std::deque<size_t> PmergeMe::jacobsthalOrderDeque(size_t pendSize) {
    std::deque<size_t> order;
    if (pendSize <= 1)
        return order;

    size_t previousBoundary = 1;
    size_t jPrev = 1;
    size_t jCurr = 1;

    while (true) {
        size_t next = jCurr + 2 * jPrev;
        if (next > pendSize)
            break;
        for (size_t i = next; i > previousBoundary; --i)
            order.push_back(i - 1);
        previousBoundary = next;
        jPrev = jCurr;
        jCurr = next;
    }

    for (size_t i = pendSize; i > previousBoundary; --i)
        order.push_back(i - 1);

    return order;
}

void PmergeMe::parseArguments(int argc, char** argv) {
    _inputVector.clear();
    _inputDeque.clear();

    if (argc < 2)
        throw std::runtime_error("Error");

    for (int i = 1; i < argc; ++i) {
        std::string token(argv[i]);
        if (!isDigitsOnly(token))
            throw std::runtime_error("Error");

        std::istringstream iss(token);
        long value;
        iss >> value;
        if (iss.fail() || !iss.eof() || value <= 0 || value > INT_MAX)
            throw std::runtime_error("Error");

        if (hasDuplicate(_inputVector, static_cast<int>(value)))
            throw std::runtime_error("Error");

        _inputVector.push_back(static_cast<int>(value));
        _inputDeque.push_back(static_cast<int>(value));
    }
}

std::vector<int> PmergeMe::fordJohnsonVector(const std::vector<int>& input) const {
    if (input.size() <= 1)
        return input;

    std::vector<PairData> pairs;
    std::vector<int> maxima;
    bool hasStraggler = (input.size() % 2 != 0);
    int straggler = 0;

    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        PairData pair;
        if (input[i] < input[i + 1]) {
            pair.small = input[i];
            pair.large = input[i + 1];
        } else {
            pair.small = input[i + 1];
            pair.large = input[i];
        }
        pairs.push_back(pair);
        maxima.push_back(pair.large);
    }

    if (hasStraggler)
        straggler = input[input.size() - 1];

    std::vector<int> mainChain = fordJohnsonVector(maxima);

    std::vector<int> pend;
    std::vector<char> used(pairs.size(), 0);
    pend.reserve(mainChain.size());
    for (size_t i = 0; i < mainChain.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].large == mainChain[i]) {
                pend.push_back(pairs[j].small);
                used[j] = 1;
                found = true;
                break;
            }
        }
        if (!found)
            throw std::runtime_error("Error");
    }

    if (!pend.empty()) {
        size_t insertPos = lowerBoundIndexVector(mainChain, pend[0]);
        mainChain.insert(mainChain.begin() + insertPos, pend[0]);

        std::vector<size_t> order = jacobsthalOrderVector(pend.size());
        for (size_t i = 0; i < order.size(); ++i) {
            size_t idx = order[i];
            insertPos = lowerBoundIndexVector(mainChain, pend[idx]);
            mainChain.insert(mainChain.begin() + insertPos, pend[idx]);
        }
    }

    if (hasStraggler) {
        size_t insertPos = lowerBoundIndexVector(mainChain, straggler);
        mainChain.insert(mainChain.begin() + insertPos, straggler);
    }

    return mainChain;
}

std::deque<int> PmergeMe::fordJohnsonDeque(const std::deque<int>& input) const {
    if (input.size() <= 1)
        return input;

    std::deque<PairData> pairs;
    std::deque<int> maxima;
    bool hasStraggler = (input.size() % 2 != 0);
    int straggler = 0;

    for (size_t i = 0; i + 1 < input.size(); i += 2) {
        PairData pair;
        if (input[i] < input[i + 1]) {
            pair.small = input[i];
            pair.large = input[i + 1];
        } else {
            pair.small = input[i + 1];
            pair.large = input[i];
        }
        pairs.push_back(pair);
        maxima.push_back(pair.large);
    }

    if (hasStraggler)
        straggler = input[input.size() - 1];

    std::deque<int> mainChain = fordJohnsonDeque(maxima);

    std::deque<int> pend;
    std::deque<char> used(pairs.size(), 0);
    for (size_t i = 0; i < mainChain.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].large == mainChain[i]) {
                pend.push_back(pairs[j].small);
                used[j] = 1;
                found = true;
                break;
            }
        }
        if (!found)
            throw std::runtime_error("Error");
    }

    if (!pend.empty()) {
        size_t insertPos = lowerBoundIndexDeque(mainChain, pend[0]);
        mainChain.insert(mainChain.begin() + insertPos, pend[0]);

        std::deque<size_t> order = jacobsthalOrderDeque(pend.size());
        for (size_t i = 0; i < order.size(); ++i) {
            size_t idx = order[i];
            insertPos = lowerBoundIndexDeque(mainChain, pend[idx]);
            mainChain.insert(mainChain.begin() + insertPos, pend[idx]);
        }
    }

    if (hasStraggler) {
        size_t insertPos = lowerBoundIndexDeque(mainChain, straggler);
        mainChain.insert(mainChain.begin() + insertPos, straggler);
    }

    return mainChain;
}

void PmergeMe::run() const {
    printVector(_inputVector, "Before: ");

    clock_t vecStart = clock();
    std::vector<int> sortedVector = fordJohnsonVector(_inputVector);
    clock_t vecEnd = clock();

    clock_t deqStart = clock();
    std::deque<int> sortedDeque = fordJohnsonDeque(_inputDeque);
    clock_t deqEnd = clock();

    if (sortedVector.size() != sortedDeque.size())
        throw std::runtime_error("Error");
    for (size_t i = 0; i < sortedVector.size(); ++i) {
        if (sortedVector[i] != sortedDeque[i])
            throw std::runtime_error("Error");
    }

    printVector(sortedVector, "After: ");

    std::cout << std::fixed << std::setprecision(5)
              << "Time to process a range of " << _inputVector.size()
              << " elements with std::vector : "
              << elapsedMicroseconds(vecStart, vecEnd) << " us" << std::endl;

    std::cout << std::fixed << std::setprecision(5)
              << "Time to process a range of " << _inputDeque.size()
              << " elements with std::deque : "
              << elapsedMicroseconds(deqStart, deqEnd) << " us" << std::endl;
}
