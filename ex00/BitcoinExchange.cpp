/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:36:58 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 14:50:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(const std::string & databaseFilename)
{
	loadDatabase(databaseFilename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & toCopy) : _exchangeRates(toCopy._exchangeRates)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange & toAssign)
{
	if (this == &toAssign)
		return *this;
	_exchangeRates = toAssign._exchangeRates;
	return *this;
}

void BitcoinExchange::loadDatabase(const std::string & filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("can't open " + filename);

	std::string line;
	if (!std::getline(file, line))
		throw std::runtime_error(filename + " is empty");

	while (std::getline(file, line))
		processDataLine(line);

	if (_exchangeRates.size() == 0)
		throw std::runtime_error("no data available");

	file.close();
}

void BitcoinExchange::processDataLine(const std::string & line)
{
	try
	{
		Data data = BitcoinExchange::strToData(line, ',');
		_exchangeRates[data.date] = data.value;
	}
	catch (const StrToDataError & e)
	{
		std::cerr << FG_RED "Error: bad data => " RESET << e.what() <<  '\n';
	}
}

void BitcoinExchange::processInputLine(const std::string & line)
{
	try
	{
		Data data = strToData(line, '|');
		float rate = getExchangeRate(data.date);
		if (data.value < 0)
			throw std::runtime_error ("not a positive number");
		else if (data.value > 1000)
			throw std::runtime_error ("too large number");
		
		float result = data.value * rate;
		std::cout << data.date << " => " << data.value << " = " << result << '\n';
	}
	catch (const StrToDataError & e)
	{
		std::cerr << FG_RED "Error: bad input => " RESET << e.what() <<  '\n';
	}
	catch(const std::runtime_error & e)
	{
		std::cerr << FG_RED "Error: " << e.what() << RESET << '\n';
	}
}

float BitcoinExchange::getExchangeRate(const std::string & date) const
{
	t_container::const_iterator it = _exchangeRates.upper_bound(date);
	if (it != _exchangeRates.begin())
		--it;
	return it->second;
}

bool BitcoinExchange::isValideDate(const std::string & date)
{
	char dash = '-';
	if (date.length() != 10 || date[4] != dash || date[7] != dash)
		return false;

	int year;
	int month;
	int day;
	std::stringstream strstream(date);
	strstream >> year >> dash >> month >> dash >> day;

	if (strstream.fail() || strstream.peek() != EOF)
		return false;

	if (year < 0 || month < 1 || month > 12 || day < 1)
		return false;

	if (month == 2)
	{
		bool leap = year % 100 == 0 ? year % 400 == 0 : year % 4 == 0;
		return leap ? day <= 29 : day <= 28;
	}

	if (month == 4 || month == 6 || month == 9 || month == 11)
		return day <= 30;
	
	return day <= 31;	
}

std::string BitcoinExchange::trim(const std::string & str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == std::string::npos)
		return "";

    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}

Data BitcoinExchange::strToData(const std::string & line, char separator)
{
	std::stringstream strstream(trim(line));
	Data data;
	if (!std::getline(strstream, data.date, separator))
		throw StrToDataError(line);
		
	data.date = trim(data.date);
	if (!isValideDate(data.date))
		throw StrToDataError(line);

	strstream >> data.value;
	if (strstream.fail() || strstream.peek() != EOF)
		throw StrToDataError(line);

	return data;
}

StrToDataError::StrToDataError(const std::string & msg) : std::runtime_error(msg)
{}
