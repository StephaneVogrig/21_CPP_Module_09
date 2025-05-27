/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:28:39 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/27 21:44:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <climits>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <list>
# include <string>
# include <time.h>
# include <vector>

# include "PmergeMe.hpp"
# include "shellColor.hpp"

template <typename T>
clock_t timeToInsertMerge(std::vector<int> input)
{
	clock_t start = clock();
	T container(input.begin(), input.end());
	PmergeMe::mergeInsertSort(container);
	return clock() - start;
};

template <typename T>
void displayContainer(const std::string & str, T container)
{
	std::cout << str;
	for (typename T::iterator it = container.begin(); it != container.end(); ++it)
		std::cout << *it << " ";
	std::cout << '\n';
	// size_t i;
	// for (i = 0; i < container.size() - 1; ++i)
	// 	std::cout << container[i] << " ";
	// std::cout << container[i] << '\n';
}

void argvToVector(int argc, char ** argv, std::vector<int> & input);

void displayContainer(const std::string & str, std::vector<int> vector);
void displayTime(size_t size, const std::string & str, clock_t clock);

void displaySection(const std::string & title, const std::string & color = FG_GREEN);
void displaySubtest(const std::string & title, const std::string & color = FG_GREEN);

#endif