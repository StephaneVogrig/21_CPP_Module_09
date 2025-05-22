/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/22 18:55:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
#include "shellColor.hpp"
#include "displayDebug.hpp"

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

void insert()
{
	
}

size_t jacob(size_t i)
{
	static size_t jacob_list[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	if (i < 1 )
		return 0;
	else if (i >= sizeof(jacob_list) / sizeof(size_t))
		throw std::runtime_error("Jacobsthal sequence return a number over an int");
	return jacob_list[i] - jacob_list[i - 1];
}

void insertion(t_vector & data, size_t elementSize)
{
	size_t nbr_element = data.size() / elementSize;
	size_t main_nbr_element = 1 + nbr_element / 2;
	size_t pend_nbr_element = nbr_element - main_nbr_element;
	// size_t remain_nbr = data.size() - nbr_element * elementSize;

	displayLevel(elementSize);
	displayVectorByPair(FG_PURPLE "input  :", data, elementSize);

	t_vector main; // store index of element in data
	main.push_back(elementSize - 1); // b1
	for (size_t i = 1; i < nbr_element; i += 2) // a1, a2, ...
		main.push_back((i + 1) * elementSize - 1);

	displayPendValue(FG_PURPLE "main   :", data, main);

	t_vector pend; // store index of element in data
	for (size_t i = 2; i < nbr_element; i += 2) // b2, b3, ...
		pend.push_back((i + 1) * elementSize - 1);

	displayPendValue(FG_PURPLE "pend   :", data, pend);
	t_vector pend2;
	size_t i_jacob = 3;
	size_t i_previous = elementSize - 1;
	while (pend_nbr_element)
	{
		size_t nbr_to_insert = jacob(i_jacob++);
		if (nbr_to_insert > pend_nbr_element)
			nbr_to_insert = pend_nbr_element;
		for (size_t i = nbr_to_insert; i > 0; --i)
		{
			size_t idx_to_insert = i_previous + i * 2 * elementSize;
			pend2.push_back(idx_to_insert);
		}
		i_previous += nbr_to_insert * 2 * elementSize;
		pend_nbr_element -= nbr_to_insert;
	}

	displayPendValue(FG_PURPLE "pend2  :", data, pend2);
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
