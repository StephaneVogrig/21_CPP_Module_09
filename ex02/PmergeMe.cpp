/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 16:34:10 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iterator>

#include "displayDebug.hpp"
#include "PmergeMe.hpp"
#include "utils.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe & to_copy)
{
	(void)to_copy;
}

PmergeMe::~PmergeMe()
{}

PmergeMe & PmergeMe::operator = (const PmergeMe & to_assign)
{
	(void)to_assign;
	return *this;
}

/* -------------------------------------------------------------------------- */

static size_t jacobsthal(size_t i)
{
	static size_t jacob_list[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531};
	if (i < 1 )
		return 0;
	else if (i >= sizeof(jacob_list) / sizeof(size_t))
		throw std::runtime_error("Jacobsthal sequence return a number over an size_t");
	return jacob_list[i] - jacob_list[i - 1];
}

/* -------------------------------------------------------------------------- */

static t_vector::iterator binarySearch(t_vector & main, int left, int right, int value, const t_vector & data)
{
	int idx_insert = 0;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (value < data[main[mid]])
		{
			right = mid - 1;
			idx_insert = mid;
		}
		else
		{
			left = mid + 1;
			idx_insert = mid + 1;
		}
	}
	return main.begin() + idx_insert;
}

static void insertion(t_vector & data, size_t nbr_element, size_t element_size)
{
	size_t main_nbr_element = 1 + nbr_element / 2;
	size_t pend_nbr_element = nbr_element - main_nbr_element;

	t_vector main;
	main.push_back(element_size - 1);
	for (size_t i = 1; i < nbr_element; i += 2)
		main.push_back((i + 1) * element_size - 1);

	size_t i_jacob = 3;
	size_t idx_start = element_size - 1;
	size_t search_range = 1;
	while (pend_nbr_element)
	{
		size_t nbr_to_insert = jacobsthal(i_jacob++);
		if (nbr_to_insert > pend_nbr_element)
			nbr_to_insert = pend_nbr_element;
		search_range = (search_range + 1) * 2 - 1;
		if (search_range > main.size())
			search_range = main.size();
		for (size_t i = nbr_to_insert; i > 0; --i)
		{
			size_t idx_to_insert = idx_start + i * 2 * element_size;
			main.insert(binarySearch(main, 0, search_range - 1, data[idx_to_insert], data), idx_to_insert);
		}
		idx_start += nbr_to_insert * 2 * element_size;
		pend_nbr_element -= nbr_to_insert;
	}

	t_vector tmp(data);
	t_vector::iterator result = data.begin();
	for (size_t i = 0; i < main.size(); ++i)
	{
		t_vector::iterator last = tmp.begin() + main[i] + 1;
		t_vector::iterator first = last - element_size;
		std::copy(first, last, result);
		result += element_size;
	}

	#ifdef DEBUG
	displayByPair(FG_PURPLE "insert :", data, element_size);
	#endif
}

static void swapVector(t_vector::iterator ita, t_vector::iterator itb, int element_size)
{
	for (int i = 0; i < element_size; ++i)
		std::swap(*ita--, *itb--);
}

void PmergeMe::sort(t_vector & data, size_t element_size)
{
	size_t nbrElement = data.size() / element_size;
	if (nbrElement < 2)
		return ;

	size_t pairLength = element_size * 2;
	for (size_t idx_second = pairLength - 1; idx_second < data.size(); idx_second += pairLength)
	{
		size_t idx_first = idx_second - element_size;
		if (data[idx_second] < data[idx_first])
			swapVector(data.begin() + idx_second, data.begin() + idx_first, element_size);
	}

	#ifdef DEBUG
	displayByPair(FG_PURPLE "sorted :", data, element_size);
	#endif

	sort(data, element_size * 2);

	if (nbrElement < 3)
		return ;
	insertion(data, nbrElement, element_size);
}

/* -------------------------------------------------------------------------- */

static t_list_of_list::iterator binarySearch(t_list_of_list::iterator left, t_list_of_list::iterator right, int value)
{
	t_list_of_list::difference_type distance = std::distance(left, right);
	t_list_of_list::iterator mid = left;
	while (distance > 0)
	{
		if (distance == 1)
		{
			if (value < left->back())
				return left;
			if (value < right->back())
				return right;
			return ++right;
		}
		distance /= 2;
		mid = left;
		std::advance(mid, distance);
		if (mid->back() > value)
		{
			right = mid;
		}
		else
		{
			++mid;
			left = mid;
		}
	}
	return mid;
}

static void extractElementFromData(t_list & data, size_t element_size, t_list_of_list & destination)
{
	destination.push_back(t_list());
	t_list & list_dest = destination.back();
	t_list::iterator it = data.begin();
	std::advance(it, element_size);
	list_dest.splice(list_dest.begin(), data, data.begin(), it);
}

static void splitDataToMainPendRemain(t_list & data, size_t element_size, t_list_of_list & main, t_list_of_list & pend, t_list & remain)
{
	size_t nbr_element = data.size() / element_size;
	extractElementFromData(data, element_size, main);
	for (size_t i = 1; i < nbr_element; ++i)
	{
		extractElementFromData(data, element_size, main);
		if (++i >= nbr_element)
			break;
		extractElementFromData(data, element_size, pend);
	}
	remain.swap(data);
}

static void rebuildData(t_list & data, t_list_of_list & main, t_list & remain)
{
	while (main.size())
	{
		data.splice(data.end(), main.front(), main.front().begin(), main.front().end());
		main.erase(main.begin());
	}
	data.splice(data.end(), remain, remain.begin(), remain.end());
}

static void insertion(t_list & data, size_t element_size)
{
	t_list_of_list main;
	t_list_of_list pend;
	t_list remain;
	splitDataToMainPendRemain(data, element_size, main, pend, remain);

	size_t i_jacob = 3;
	size_t search_range = 1;
	while (pend.size() > 0)
	{
		size_t nbr_to_insert = jacobsthal(i_jacob++);
		if (nbr_to_insert > pend.size())
			nbr_to_insert = pend.size();

		search_range = (search_range + 1) * 2 - 1;
		if (search_range > main.size())
			search_range = main.size();

		for (size_t i = nbr_to_insert; i > 0; --i)
		{
			t_list_of_list::iterator it_pend = pend.begin();
			std::advance(it_pend, nbr_to_insert - 1);

			t_list_of_list::iterator right = main.begin();
			std::advance(right, search_range - 1);

			t_list_of_list::iterator main_it_to_insert = binarySearch(main.begin(), right, it_pend->back());
			main.splice(main_it_to_insert, pend, it_pend);
			--nbr_to_insert;
		}
	}

	rebuildData(data, main, remain);

	#ifdef DEBUG
	displayByPair(FG_PURPLE "insert :", data, element_size);
	#endif
}

void PmergeMe::sort(t_list & data, int element_size)
{
	int nbrElement = data.size() / element_size;
	if (nbrElement < 2)
		return ;

	t_list::iterator a_start = data.begin();

	int nbr_pair = nbrElement / 2;
	for (int i = 0; i < nbr_pair; ++i)
	{
		t_list::iterator a_end = a_start;
		std::advance(a_end, element_size - 1);
		
		t_list::iterator b_start = a_end;
		++b_start;
		
		t_list::iterator b_end = b_start;
		std::advance(b_end, element_size - 1);
		
		if (*b_end < *a_end)
		{
			data.splice(a_start, data, b_start, ++b_end);
			a_start = ++a_end;
		}
		else
			a_start = ++b_end;
	}

	#ifdef DEBUG
	displayByPair(FG_PURPLE "sorted :", data, element_size);
	#endif
	sort(data, element_size * 2);

	if (nbrElement < 3)
		return ;
	insertion(data, element_size);
}
