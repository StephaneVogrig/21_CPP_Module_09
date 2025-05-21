/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/21 23:51:13 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "shellColor.hpp"
#include <cmath>
#include <iostream>
#include "utils.hpp"
#include <sstream>
#include <algorithm>

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe & toCopy)
{
	(void)toCopy;
}

PmergeMe::~PmergeMe()
{}

PmergeMe & PmergeMe::operator = (const PmergeMe & toAssign)
{
	(void)toAssign;
	return *this;
}

/* -------------------------------------------------------------------------- */

void swapVector(std::vector<int> & vector, int pos_a, int pos_b, int elementSize)
{
	for (int i = 0; i < elementSize; ++i)
	{
		int temp = vector[pos_a - i];
		vector[pos_a - i] = vector[pos_b - i];
		vector[pos_b - i] = temp;
	}
}

void displayVectorByPair(std::string intro, std::vector<int> & vector, size_t elementSize)
{
	std::cout << intro;
	
	size_t i = 0;
	bool isInPair = false;
	for (i = 0; i < vector.size(); ++i)
	{
		bool startPair = i % (elementSize * 2) == 0;
		if (startPair)
			isInPair = vector.size() - i >= (elementSize * 2);
		
		if (i % elementSize == 0)
		{
			if (!isInPair)
				std::cout << " " FG_PURPLE;
			else if (startPair)
				std::cout << " " FG_GREEN;
			else
				std::cout << FG_YELLOW;
		}
		if ((i + 1) % elementSize == 0 && isInPair)
			std::cout << BOLD_ON << vector[i] << BOLD_OFF << ' ';
		else
			std::cout << vector[i] << ' ';
	}
	std::cout <<  RESET << std::endl;
}

void displayLevel(int recursLevel, size_t elementSize)
{
	std::ostringstream oss;
	oss << "sort level: " << recursLevel << " - elementSize: " << elementSize;
	displaySection(std::string(oss.str()), FG_PURPLE);
}

void PmergeMe::sort(std::vector<int> & vector, int recursLevel)
{
	size_t elementSize = pow(2, recursLevel);
	size_t nbrElement = vector.size() / elementSize;
	if (nbrElement < 2)
		return ;
	displayLevel(recursLevel, elementSize);
	displayVectorByPair(FG_PURPLE "to sort:", vector, elementSize);

	size_t pairLength = elementSize * 2;
	for (size_t i = pairLength - 1; i < vector.size(); i += pairLength)
	{
		size_t ib = i - elementSize;
		if (vector[i] < vector[ib])
			swapVector(vector, i, ib, elementSize);
	}

	displayVectorByPair(FG_PURPLE "sorted :", vector, elementSize);
	
	sort(vector, recursLevel + 1);
	// size_t nbrPair = nbrElement / 2;
	if (nbrElement < 3)
		return ;
	// t_vector main;
	// // copy b1 in main
	
	// t_vector pend;
	
	
	
}

void PmergeMe::mergeInsertSort(std::vector<int> & vector)
{
	sort(vector, 0);
}

void PmergeMe::mergeInsertSort(std::list<int> & list)
{
	(void)list;
}

void PmergeMe::displayVector(std::vector<int> & vector)
{
	size_t i;
	for (i = 0; i < vector.size() - 1; ++i)
		std::cout << vector[i] << " ";
	std::cout << vector[i];
}