/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:42 by rnovotny          #+#    #+#             */
/*   Updated: 2026/03/11 16:35:08 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
	loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	
	std::string line;
	std::getline(file, line); // Skip header
	
	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		
		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 1);
		
		double value = std::atof(valueStr.c_str());
		_database[date] = value;
	}
	file.close();
}

void BitcoinExchange::processInputFile(const std::string& inputFile)
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	
	std::string line;
	std::getline(file, line); // Skip header
	
	while (std::getline(file, line))
	{
		processLine(line);
	}
	file.close();
}

void BitcoinExchange::processLine(const std::string& line)
{
	size_t pos = line.find('|');
	if (pos == std::string::npos)
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return;
	}
	
	std::string date = trim(line.substr(0, pos));
	std::string valueStr = trim(line.substr(pos + 1));
	
	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return;
	}
	
	double value;
	if (!isValidValue(valueStr, value))
		return;
	
	double rate = getExchangeRate(date);
	std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	for (size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return false;
	}
	
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	
	if (year < 2009 || year > 2022)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	
	return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const
{
	if (valueStr.empty())
	{
		std::cerr << "Error: bad input." << std::endl;
		return false;
	}
	
	char* endptr;
	value = std::strtod(valueStr.c_str(), &endptr);
	
	if (*endptr != '\0' && *endptr != '\n')
	{
		std::cerr << "Error: bad input." << std::endl;
		return false;
	}
	
	if (value < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}
	
	if (value > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	
	return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it = _database.find(date);
	if (it != _database.end())
		return it->second;
	
	// Find closest lower date
	it = _database.lower_bound(date);
	if (it == _database.begin())
		return 0;
	
	--it;
	return it->second;
}

std::string BitcoinExchange::trim(const std::string& str) const
{
	size_t start = 0;
	size_t end = str.length();
	
	while (start < end && std::isspace(str[start]))
		start++;
	
	while (end > start && std::isspace(str[end - 1]))
		end--;
	
	return str.substr(start, end - start);
}
