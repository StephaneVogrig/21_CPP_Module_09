/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/26 03:51:58 by svogrig          ###   ########.fr       */
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

void insert(t_vector data, size_t idx_to_insert, t_vector & main, int right)
{
	// std::cout << "value to insert: " << data[idx_to_insert] << " in ";
	// displayPendValue(FG_PURPLE "main   :", data, main);
	int left = 0;
	int idx_insert = 0;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
	// std::cout << "insert between : " << left << " and " << right << " mid " << mid;
	// std::cout << " data[idx_to_insert]: " << data[idx_to_insert] << " data[main[mid] " << data[main[mid]] << std::endl;
		if (data[idx_to_insert] < data[main[mid]])
		{
			right = mid - 1;
			idx_insert = mid;
		}
		else
		{
			left = mid + 1;
			idx_insert =  mid + 1;
		}
	}

	main.insert(main.begin() + idx_insert, idx_to_insert);
	// std::cout << FG_YELLOW "insert before idx: " << idx_insert << " value: " << data[main[idx_insert]] << RESET << std::endl;

	// displayPendValue(FG_PURPLE "main   :", data, main);
}

size_t jacobsthal(size_t i)
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

	// displayLevel(elementSize);
	// displayVectorByPair(FG_PURPLE "input  :", data, elementSize);

	t_vector main; // store index of first lowest and all bigest element from data
	main.push_back(elementSize - 1); // add b1
	for (size_t i = 1; i < nbr_element; i += 2) // add a1, a2, ...
		main.push_back((i + 1) * elementSize - 1);

	// displayPendValue(FG_PURPLE "main   :", data, main);

	// t_vector pend; // store index of element in data
	// for (size_t i = 2; i < nbr_element; i += 2) // b2, b3, ...
	// 	pend.push_back((i + 1) * elementSize - 1);

	// displayPendValue(FG_PURPLE "pend   :", data, pend);
	// t_vector pend2;

	// in main, insert index of lowest element from data
	size_t i_jacob = 3;
	size_t idx_start = elementSize - 1;

	size_t idx_bound = 1;
	while (pend_nbr_element)
	{
		size_t nbr_to_insert = jacobsthal(i_jacob++);
		if (nbr_to_insert > pend_nbr_element)
			nbr_to_insert = pend_nbr_element;
		idx_bound = (idx_bound + 1)  * 2 - 1;
		if (idx_bound > main.size())
			idx_bound = main.size() - 1;
		for (size_t i = nbr_to_insert; i > 0; --i)
		{
			size_t idx_to_insert = idx_start + i * 2 * elementSize;
			insert(data, idx_to_insert, main, idx_bound - 1);
			// pend2.push_back(idx_to_insert);
		}
		idx_start += nbr_to_insert * 2 * elementSize;
		pend_nbr_element -= nbr_to_insert;
	}

	// displayPendValue(FG_PURPLE "pend2  :", data, pend2);

	t_vector tmp(data);
	// displayVectorByPair(FG_PURPLE "tmp  :", tmp, elementSize);
	// std::cout << std::endl;

	t_vector::iterator result = data.begin();
	for (size_t i = 0; i < main.size(); ++i)
	{
		// std::cout << "i: " << i << " main[i]:" << main[i];
		t_vector::iterator last = tmp.begin() + main[i] + 1;
		t_vector::iterator first = last - (elementSize);
		// std::cout << " first:" << *first << " last:" << *last << " result:" << *result << std::endl;
		std::copy(first, last, result);
	// displayVectorByPair(FG_PURPLE "data  :", data, elementSize);
		result += elementSize;
	}
	// std::cout << std::endl;
	// PmergeMe::displayVector(data);
	// std::cout << std::endl;
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
	// displayLevel(elementSize);
	// displayVectorByPair(FG_PURPLE "to sort:", vector, elementSize);

	size_t pairLength = elementSize * 2;
	for (size_t i1 = pairLength - 1; i1 < vector.size(); i1 += pairLength)
	{
		size_t i2 = i1 - elementSize;
		if (vector[i1] < vector[i2])
			swapVector(vector.begin() + i1, vector.begin() + i2, elementSize);
	}

	// displayVectorByPair(FG_PURPLE "sorted :", vector, elementSize);

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
