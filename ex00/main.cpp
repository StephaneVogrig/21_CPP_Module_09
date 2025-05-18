/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 14:46:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "BitcoinExchange.hpp"

void run(std::ifstream & inputFile)
{
	try
	{
		BitcoinExchange bitcoinExchange("data.csv");
		std::string line;
		if (!std::getline(inputFile, line))
			throw std::runtime_error("the input file is empty");

		while(std::getline(inputFile, line))
			bitcoinExchange.processInputLine(line);
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << FG_RED "Error: " << e.what() << RESET << '\n';
	}	
}

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cerr << FG_YELLOW "Usage: " << *argv << " <file>" RESET << std::endl;
		return (EXIT_FAILURE);
	}

	std::ifstream inputFile(argv[1]);

	if (inputFile.is_open())
		run(inputFile);
	else
	{
		std::cerr << FG_RED "Error: can't open file " RESET << argv[1] << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
