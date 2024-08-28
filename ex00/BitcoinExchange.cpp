/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:25:29 by ranki             #+#    #+#             */
/*   Updated: 2024/08/28 10:03:07 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <sstream>
#include <ctime>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : exchangeRates(other.exchangeRates)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
        exchangeRates = other.exchangeRates;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, value;

        if (std::getline(ss, date, ',') && std::getline(ss, value))
        {
            if (isValidDate(date) && isValidValue(value))
            {
                exchangeRates[date] = std::atof(value.c_str());
            }
            else
            {
                std::cerr << "Error: invalid data => " << line << std::endl;
            }
        }
    }

    file.close();
}

static inline std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : s.substr(start);
}

static inline std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(" \t\n\r");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static inline std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

void BitcoinExchange::processInput(const std::string& filename)
{

    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {

        std::istringstream ss(line);
        std::string date, value;

        if (std::getline(ss, date, '|') && std::getline(ss, value))
        {
            date = trim(date);
            value = trim(value);
            if (isValidDate(date) && isValidValue(value))
            {
                float btcValue = std::atof(value.c_str());

                if (btcValue >= 0 && btcValue <= 1000)
                {
                    float rate = getExchangeRate(date);
                    std::cout << date << " => " << btcValue << " = " << btcValue * rate << std::endl;
                }
                else
                {
                    if (btcValue < 0)
                    {
                        std::cerr << "Error: not a positive number." << std::endl;
                    }
                    else if (btcValue >= static_cast<float>(std::numeric_limits<int>::max()))
                    {
                        std::cerr << "Error: too large a number." << std::endl;
                    }
                    else
                    {
                        std::cerr << "Error: value out of range => " << value << std::endl;
                    }
                }

            }
            else
            {
                std::cerr << "Error: invalid input => " << line << std::endl;
            }
        }
        else
        {
          std::cerr << "Error: invalid input => " << line << std::endl;
        }
    }

    file.close();
}

float BitcoinExchange::getExchangeRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = exchangeRates.lower_bound(date);
    if (it == exchangeRates.end() || it->first != date)
    {
        if (it != exchangeRates.begin())
        {
            --it;
        }
    }
    return (it != exchangeRates.end()) ? it->second : 0.0f;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (std::size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    if (mktime(&tm) == -1)
        return false;

    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;

    return date == oss.str();
}

bool BitcoinExchange::isValidValue(const std::string& value) const
{
    std::istringstream ss(value);
    float f;
    ss >> f;
    return !ss.fail() && ss.eof();
}
