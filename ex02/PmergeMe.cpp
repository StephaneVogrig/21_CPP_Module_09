/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/22 03:20:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
#include "shellColor.hpp"

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

void displayLevel(size_t elementSize)
{
	std::ostringstream oss;
	oss << "sort - elementSize: " << elementSize;
	displaySubtest(std::string(oss.str()), FG_PURPLE);
}

void insertion(t_vector & vector, size_t elementSize)
{
	displayLevel(elementSize);
	displayVectorByPair(FG_PURPLE "input  :", vector, elementSize);
	size_t nbr_element = vector.size() / elementSize;
	size_t main_nbr_element = 1 + nbr_element / 2;
	size_t pend_nbr_element = nbr_element - main_nbr_element;
	std::cout	<< "nbr_element: " << nbr_element << " main_nbr_element; " << main_nbr_element
				<< " pend_nbr_element: " << pend_nbr_element << std::endl;

	t_vector main(main_nbr_element * elementSize, 0);
	t_vector::iterator it_last = std::copy(vector.begin(), vector.begin() + elementSize, main.begin()); // b1
	(void)it_last;
	for (size_t i = 1; i < nbr_element; i += 2) // a1, a2, ...
	{
		// std::cout << " i:" << i << std::flush;
		t_vector::iterator start = vector.begin() + i * elementSize;
		it_last = std::copy(start, start + elementSize, it_last);
	}
	// std::cout << std::endl;
	displayVectorByPair(FG_PURPLE "main   :", main, elementSize);

	t_vector pend(pend_nbr_element * elementSize, 0);
	it_last = pend.begin();
	for (size_t i = 2; i < nbr_element; i += 2 ) // b2, b3, ...
	{
		// std::cout << "i:" << i << std::flush;

		t_vector::iterator start = vector.begin() + i * elementSize;
		it_last = std::copy(start, start + elementSize, it_last);
	}
	// std::cout << std::endl;
	displayVectorByPair(FG_PURPLE "pend   :", pend, elementSize);
}

void swapVector(t_vector::iterator ita, t_vector::iterator itb, int elementSize)
{
	for (int i = 0; i < elementSize; ++i)
		std::swap(*(ita - i), *(itb - i));
}

void PmergeMe::sort(t_vector & vector, size_t elementSize)
{
	size_t nbrElement = vector.size() / elementSize;
	if (nbrElement < 2)
		return ;
	displayLevel(elementSize);
	displayVectorByPair(FG_PURPLE "to sort:", vector, elementSize);

	size_t pairLength = elementSize * 2;
	for (size_t i = pairLength - 1; i < vector.size(); i += pairLength)
	{
		size_t ib = i - elementSize;
		if (vector[i] < vector[ib])
			swapVector(vector.begin() + i, vector.begin() + ib, elementSize);
	}

	displayVectorByPair(FG_PURPLE "sorted :", vector, elementSize);
	
	sort(vector, elementSize * 2);
	if (nbrElement < 3)
		return ;
	insertion(vector, elementSize);
}

void PmergeMe::mergeInsertSort(t_vector & vector)
{
	sort(vector, 1);
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