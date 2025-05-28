/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 04:51:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 20:33:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
		
void argvToVector(int argc, char ** argv, std::vector<int> & input)
{
	argv++;
	while (--argc)
	{
		char * endptr = NULL;
		int value = strtol(*argv, &endptr, 10);
		if (*endptr != '\0' || endptr == *argv || value < 1 || value > INT_MAX)
			throw std::runtime_error("Error: Bad value => " + std::string(*argv));
		input.push_back(value);
		argv++;
	}
}

void displayTime(size_t size, const std::string & str, clock_t clock)
{
	std::cout << "Time to process a range of "
				<< size << " elements with "
				<< str << ": "
				<< clock << " us"
				<< std::endl;
}

void displaySubtest(const std::string & title, const std::string & color)
{
	int padding = (PRINT_WIDTH - 2 - title.length()) / 2;
	std::string left = std::string(padding, '-');
	std::string right = std::string(PRINT_WIDTH - padding - 2 - title.length(), '-');
	std::cout << color << '\n';
	std::cout<< left << " "  << title << " " << right << '\n';
	std::cout << RESET << std::endl;
}

void displaySection(const std::string & title, const std::string & color)
{
	std::cout << '\n';
	int padding = (PRINT_WIDTH - 2 - title.length()) / 2;
	std::string star = std::string(PRINT_WIDTH, '*');
	std::string blankLeft = std::string(padding, ' ');
	std::string blankRight = std::string(PRINT_WIDTH - padding - 2 - title.length(), ' ');
	std::cout << color << star << '\n';
	std::cout << "*" << blankLeft << title << blankRight << "*" << '\n';
	std::cout << star << RESET "\n" << std::endl;
}
