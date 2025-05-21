/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:28:39 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/21 20:59:14 by svogrig          ###   ########.fr       */
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

void argvToVector(int argc, char ** argv, std::vector<int> & input);

void displayContainer(const std::string & str, std::vector<int> vector);
void displayTime(size_t size, const std::string & str, clock_t clock);

void displaySection(const std::string & title, const std::string & color = FG_GREEN);
void displaySubtest(const std::string & title, const std::string & color = FG_GREEN);

#endif