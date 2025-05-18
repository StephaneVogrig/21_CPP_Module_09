/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:37:33 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 14:41:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include <stdexcept>
# include "shellColor.hpp"

struct Data
{
	std::string date;
	float		value;
};

class StrToDataError : public std::runtime_error
{
	public:
		StrToDataError(const std::string & msg);
};

class BitcoinExchange
{
	private:

		typedef std::map<std::string, float> t_container;
		t_container _exchangeRates;

		void loadDatabase(const std::string & filename);
		void processDataLine(const std::string & line);
		float getExchangeRate(const std::string & date) const;
		Data strToData(const std::string & line, char separator);
		bool isValideDate(const std::string & date);
		std::string trim(const std::string & str);

	public:

		BitcoinExchange(const std::string & databaseFilename = "data.csv");
		BitcoinExchange(const BitcoinExchange & toCopy);
		~BitcoinExchange();
		BitcoinExchange & operator = (const BitcoinExchange & toAssign);
		
		void processInputLine(const std::string & line);

};
#endif