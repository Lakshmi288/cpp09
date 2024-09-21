/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lps <lps@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:24:30 by lps               #+#    #+#             */
/*   Updated: 2024/09/21 17:06:06 by lps              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { }

void BitcoinExchange::createDatabase()
{
	std::ifstream file("./data.csv");
	if (!file.is_open())
		throw std::runtime_error("Error: unable to open './data.csv' file.\nPlease provide a data.csv file.");
	if (isFileEmpty("./data.csv"))
		throw std::runtime_error("Error: file 'data.csv' is empty.");
	std::string line;
	getline(file, line);
	while (std::getline(file, line))
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());

		std::size_t pos = line.find(",");
		if (pos != std::string::npos)
		{
			std::string date = line.substr(0, pos);
			std::string sValue = line.substr(pos + 1);
			float value = std::atof(sValue.c_str());
			database.insert(std::make_pair(date, value));
		}
	}
	if (database.size() == 0)
		throw std::runtime_error("Error: database is empty!");
}

int BitcoinExchange::countOccurrences(const std::string& str, char ch) {
    size_t count = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ch)
            count++;
    }
    return count;
}

int BitcoinExchange::isValueValid(std::string value)
{
	std::string tmp = value;
	if (countOccurrences(value, '.') > 1 || value[value.length() - 1] == '.') { return (1); }

	if ( value[0] == '-' || value[0] == '+')
		value.erase(0, 1);
	size_t length = value.length();
	if (value[length - 1] == 'f')
	{
		length--;
		if (value[length - 1] == '.') {	return (1); }
	}
	for (size_t i = 0; i < length; i++)
	{
		if (!isdigit(value[i]) && value[i] != '.')
			return (1);
	}
	try
	{
		float number = std::atof(tmp.c_str());
		if (number < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			return (3);
		}
		else if (number > 1000.0)
		{
			std::cout << "Error: too large a number." << std::endl;
			return (3);
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		throw;
	}
	return (2);
}

bool BitcoinExchange::isDateValid(const std::string date)
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < date.size(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return (false);
	}
	int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);
	const int days_in_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isLeapYear(year)) {
        if (day < 1 || day > 29) {
            return false;
        }
    } else {
        if (day < 1 || day > days_in_months[month - 1]) {
            return false;
        }
	}
	return (true);
}

bool BitcoinExchange::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isFileEmpty(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.peek() == std::ifstream::traits_type::eof();
}

void BitcoinExchange::readInputFile(std::string& inputFile)
{
	try
	{
		std::ifstream file(inputFile.c_str());
		if (!file.is_open())
			throw std::runtime_error("Error: unable to open file '" + inputFile + "'");
		std::string line;
		getline(file, line);
		if (isFileEmpty(inputFile))
			throw std::runtime_error("Error: file '" + inputFile + "' is empty.");
		if (line != "date | value")
			file.seekg(0, std::ios::beg);

		while (std::getline(file, line))
		{	
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			std::size_t pos = line.find("|");
			if (pos != std::string::npos)
			{
				std::string date = line.substr(0, pos);
				if (!isDateValid(date))
				{
					std::cout << "Error: bad input => " << line << std::endl;
					continue;
				}
				std::string sValue = line.substr(pos + 1);
				float value = std::atof(sValue.c_str());
				int validValue = isValueValid(sValue);
				if (validValue == 2)
					compareValue(date, value);
				else if (validValue == 1)
					std::cout << "Error: bad input => " << line << std::endl;
			}
			else
				std::cout << "Error: bad input => " << line << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

BitcoinExchange::BitcoinExchange(std::string inputFile)
{
	try
	{
		createDatabase();
		readInputFile(inputFile);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void BitcoinExchange::compareValue(const std::string& date, float value) {
    std::map<std::string, float>::iterator it = database.lower_bound(date);
	if (it == database.end() || it->first != date)
	{
		if (it != database.begin())
			--it;
		else if (it == database.begin())
		{
    		std::cout << date << " => " << value << " = "  <<  it->second * value << std::endl;
			return ;
		}
		else
            throw std::runtime_error("No valid date found in database.");
	}
	std::cout << std::setprecision(7)<<it->first  << " => " << value << " = "  <<  it->second * value << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
		this->database = rhs.database; 
	return (*this);
}

BitcoinExchange::~BitcoinExchange() { }

void BitcoinExchange::printDatabase()
{
	std::map<std::string, float>::iterator it;
	for (it = database.begin(); it != database.end(); it++)
	{
		std::cout << it->first << " => " << it->second << "\n";
	}
}
