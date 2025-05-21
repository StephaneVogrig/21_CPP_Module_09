/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/21 21:06:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "utils.hpp"

int main(int argc, char ** argv)
{
	try
	{
		displaySection("PmergeMe");
		if (argc < 2)
			throw std::runtime_error("Error: Not enough arguments.\nUsage: ./PmergeMe <positive_integer_sequence>");

		std::vector<int> input;
		argvToVector(argc, argv, input);
		displayContainer(FG_YELLOW "input: " RESET, input);

		// clock_t clockVector = timeToInsertMerge<std::vector<int> >(input);
		clock_t start = clock();
		std::vector<int> vector(input.begin(), input.end());
		PmergeMe::mergeInsertSort(vector);
		clock_t clockVector = clock() - start;
		
		clock_t clockList = timeToInsertMerge<std::list<int> >(input);
		
		displayContainer("Before: ", input);
		displayContainer("After:  ", vector);
		displayTime(input.size(), "std::vector", clockVector);
		displayTime(input.size(), "std::list  ", clockList);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
