/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 21:42:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "utils.hpp"
#include "displayDebug.hpp"

int main(int argc, char ** argv)
{
	try
	{
		displaySection("PmergeMe");
		if (argc < 2)
			throw std::runtime_error("Error: Not enough arguments.\nUsage: ./PmergeMe <positive_integer_sequence>");

		std::vector<int> input;
		argvToVector(argc, argv, input);

		#ifdef DEBUG
		displaySubtest("mergeInsert a vector");
		#endif

		clock_t start = clock();
		std::vector<int> vector(input.begin(), input.end());
		PmergeMe::mergeInsertSort(vector);
		clock_t clockVector = clock() - start;

		#ifdef DEBUG
		displaySubtest("mergeInsert a list");
		#endif

		start = clock();
		std::list<int> list(input.begin(), input.end());
		PmergeMe::mergeInsertSort(list);
		clock_t clockList = clock() - start;

		#ifdef DEBUG
		displaySubtest("result");
		#endif

		displayContainer<std::vector<int> >("Before      : ", input);
		displayContainer<std::vector<int> >("After vector: ", vector);
		displayContainer<std::list<int> >("After list  : ", list);
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
