/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:50:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:44:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>

// ─── Canonical form ───────────────────────────────────────────────────────────

BitcoinExchange::BitcoinExchange() 
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _database(other._database) 
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) 
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() 
{}

// ─── Private helpers ──────────────────────────────────────────────────────────

std::string BitcoinExchange::trim(const std::string& str) 
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) 
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++) 
{
        if (i == 4 || i == 7) continue;
        if (!isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year  = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day   = atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12) return false;
    if (day   < 1)               return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];
}

// ─── Public methods ───────────────────────────────────────────────────────────

void BitcoinExchange::loadDatabase(const std::string& filename) 
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) 
{
        line = trim(line);
        if (line.empty()) continue;

        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) continue;

        std::string date    = trim(line.substr(0, commaPos));
        std::string rateStr = trim(line.substr(commaPos + 1));

        if (!isValidDate(date)) continue;

        std::istringstream iss(rateStr);
        float rate;
        if (!(iss >> rate)) continue;

        _database[date] = rate;
    }
}

void BitcoinExchange::processInput(const std::string& filename) const {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) 
{
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) 
{
        line = trim(line);
        if (line.empty()) continue;

        // split on " | "
        size_t pipePos = line.find(" | ");
        if (pipePos == std::string::npos) 
{
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date     = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 3));

        // validate date
        if (!isValidDate(date)) 
{
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // parse and validate value
        std::istringstream iss(valueStr);
        double value;
        if (!(iss >> value)) 
{
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string leftover;
        if (iss >> leftover) 
{
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0) 
{
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000) 
{
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        // look up closest lower-or-equal date in DB
        if (_database.empty()) 
{
            std::cerr << "Error: database is empty." << std::endl;
            continue;
        }
        std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
        if (it == _database.end() || it->first != date) 
{
            if (it == _database.begin()) 
{
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }
            --it;
        }

        std::cout << date << " => " << value << " = "
                  << value * it->second << std::endl;
    }
}

