/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:24:37 by lps               #+#    #+#             */
/*   Updated: 2024/09/19 12:24:39 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

class BitcoinExchange
{
	std::map<std::string, float> database;
	bool isLeapYear(int year);
	void createDatabase();
	bool isDateValid(const std::string date);
	void readInputFile(std::string& inputFile);
	void compareValue(const std::string& date, float value);
	bool isFileEmpty(const std::string& filename);
	int countOccurrences(const std::string& str, char ch);
	int isValueValid(std::string value);
	BitcoinExchange();
	public:
		BitcoinExchange(std::string inputFile);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& rhs);
		~BitcoinExchange();
		void printDatabase();
};

#endif // !BITCOINEXCHANGE_HPP