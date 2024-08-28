/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ranki <ranki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:25:45 by ranki             #+#    #+#             */
/*   Updated: 2024/08/27 22:25:46 by ranki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInput(const std::string& filename);
    float getExchangeRate(const std::string& date) const;

private:
    std::map<std::string, float> exchangeRates;
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& value) const;
};

#endif // BITCOINEXCHANGE_HPP
