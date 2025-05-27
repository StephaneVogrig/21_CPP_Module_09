/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 04:51:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/27 22:56:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
		
void argvToVector(int argc, char ** argv, std::vector<int> & input)
{
	std::cout << *argv << " " << std::flush;
	argv++;
	while (--argc)
	{
		std::cout << *argv << " " << std::flush;
		char * endptr = NULL;
		int value = strtol(*argv, &endptr, 10);
		if (*endptr != '\0' || endptr == *argv || value < 1 || value > INT_MAX)
			throw std::runtime_error("Error: Bad value => " + std::string(*argv));
		input.push_back(value);
		argv++;
	}
	std::cout << std::endl;
}

// void displayContainer(const std::string & str, std::vector<int> vector)
// {
// 	std::cout << str;
// 	size_t i;
// 	for (i = 0; i < vector.size() - 1; ++i)
// 		std::cout << vector[i] << " ";
// 	std::cout << vector[i] << '\n';
// }

void displayTime(size_t size, const std::string & str, clock_t clock)
{
	double time_us = (double)clock / CLOCKS_PER_SEC * 1e6;
	std::cout << "Time to process a range of "
				<< size << " elements with "
				<< str << ": "
				<< std::fixed << std::setprecision(3)
				<< time_us << " us"
				<< std::endl;
}

#define WIDTH 80

void displaySubtest(const std::string & title, const std::string & color)
{
	int padding = (WIDTH - 2 - title.length()) / 2;
	std::string left = std::string(padding, '-');
	std::string right = std::string(WIDTH - padding - 2 - title.length(), '-');
	std::cout << color << '\n';
	std::cout<< left << " "  << title << " " << right << '\n';
	std::cout << RESET << std::endl;
}

void displaySection(const std::string & title, const std::string & color)
{
	std::cout << '\n';
	int padding = (WIDTH - 2 - title.length()) / 2;
	std::string star = std::string(WIDTH, '*');
	std::string blankLeft = std::string(padding, ' ');
	std::string blankRight = std::string(WIDTH - padding - 2 - title.length(), ' ');
	std::cout << color << star << '\n';
	std::cout << "*" << blankLeft << title << blankRight << "*" << '\n';
	std::cout << star << RESET "\n" << std::endl;
}
