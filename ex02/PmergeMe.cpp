/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:04:00 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/27 20:28:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include "utils.hpp"
#include "shellColor.hpp"
#include "displayDebug.hpp"
#include <iterator>

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

t_vector::iterator binarySearch(t_vector & main, int left, int right, int value, const t_vector & data)
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
			idx_insert =  mid + 1;
		}
	}
	return main.begin() + idx_insert;
}

t_list_iter::iterator binarySearch(t_list_iter::iterator left, t_list_iter::iterator right, int value)
{
	// std::cout << FG_PURPLE "binary search for " FG_BLUE << value << "\n" RESET;
	t_list_iter::difference_type count = std::distance(left, right);
	t_list_iter::iterator result = left;
	while (count > 0)
	{
		std::cout << FG_PURPLE "***\nbinary search for " FG_BLUE << value << "\n" RESET;
		std::cout << FG_PURPLE "left: " FG_BLUE << *(*left) << FG_PURPLE " - right: " FG_BLUE << *(*right)<< RESET << std::endl;
		std::cout << FG_PURPLE "count " FG_BLUE << count << "\n" RESET;
		t_list_iter::difference_type step = count / 2;
		t_list_iter::iterator mid = left;
		std::advance(mid, step);
		std::cout << "mid: " << *(*mid) << std::endl;
		if (*(*mid) > value)
		{
			right = mid;
		}
		else
		{
			++mid;
			left = mid;
		}
		result = mid;
		count = step;
	}
	std::cout << FG_PURPLE "result; " FG_BLUE << *(*result) << RESET << std::endl;
	return result;
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

void insertion(t_vector & data, size_t nbr_element, size_t element_size)
{
	// size_t nbr_element = data.size() / element_size;
	size_t main_nbr_element = 1 + nbr_element / 2;
	size_t pend_nbr_element = nbr_element - main_nbr_element;
	// size_t remain_nbr = data.size() - nbr_element * element_size;

	// displayLevel(element_size);
	// displayVectorByPair(FG_PURPLE "input  :", data, element_size);

	t_vector main; // store index of first lowest and all bigest element from data
	main.push_back(element_size - 1); // add b1
	for (size_t i = 1; i < nbr_element; i += 2) // add a1, a2, ...
		main.push_back((i + 1) * element_size - 1);

	// displayPendValue(FG_PURPLE "main   :", data, main);

	// t_vector pend; // store index of element in data
	// for (size_t i = 2; i < nbr_element; i += 2) // b2, b3, ...
	// 	pend.push_back((i + 1) * element_size - 1);
	// displayPendValue(FG_PURPLE "pend   :", data, pend);
	// t_vector pend2;

	// in main, insert index of lowest element from data
	size_t i_jacob = 3;
	size_t idx_start = element_size - 1;

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
			size_t idx_to_insert = idx_start + i * 2 * element_size;
			// insert(data, idx_to_insert, main, idx_bound - 1);

			main.insert(binarySearch(main, 0, idx_bound - 1, data[idx_to_insert], data), idx_to_insert);
			// pend2.push_back(idx_to_insert);
		}
		idx_start += nbr_to_insert * 2 * element_size;
		pend_nbr_element -= nbr_to_insert;
	}

	// displayPendValue(FG_PURPLE "pend2  :", data, pend2);

	t_vector tmp(data);
	// displayVectorByPair(FG_PURPLE "tmp  :", tmp, element_size);
	// std::cout << std::endl;

	t_vector::iterator result = data.begin();
	for (size_t i = 0; i < main.size(); ++i)
	{
		// std::cout << "i: " << i << " main[i]:" << main[i];
		t_vector::iterator last = tmp.begin() + main[i] + 1;
		t_vector::iterator first = last - (element_size);
		// std::cout << " first:" << *first << " last:" << *last << " result:" << *result << std::endl;
		std::copy(first, last, result);
	// displayVectorByPair(FG_PURPLE "data  :", data, element_size);
		result += element_size;
	}
	// std::cout << std::endl;
	// PmergeMe::displayVector(data);
	// std::cout << std::endl;
}

void swapVector(t_vector::iterator ita, t_vector::iterator itb, int element_size)
{
	for (int i = 0; i < element_size; ++i)
		std::swap(*(ita - i), *(itb - i));
}

void PmergeMe::sort(t_vector & data, size_t element_size)
{
	size_t nbrElement = data.size() / element_size;
	if (nbrElement < 2)
		return ;
	// displayLevel(element_size);
	// displayVectorByPair(FG_PURPLE "to sort:", data, element_size);

	size_t pairLength = element_size * 2;
	for (size_t idx_second = pairLength - 1; idx_second < data.size(); idx_second += pairLength)
	{
		size_t idx_first = idx_second - element_size;
		if (data[idx_second] < data[idx_first])
			swapVector(data.begin() + idx_second, data.begin() + idx_first, element_size);
	}

	// displayVectorByPair(FG_PURPLE "sorted :", data, element_size);

	sort(data, element_size * 2);

	if (nbrElement < 3)
		return ;
	insertion(data, nbrElement, element_size);
}


// t_list::iterator listMoveIterator(t_list::iterator it, int nbr)
// {
// 	if (nbr > 0)
// 		while (nbr--)
// 			it++;
// 	else
// 		while (nbr++)
// 			it--;
// 	return it;
// }
void display(const std::string & intro, const t_list_iter & list)
{
	std::cout << FG_PURPLE << intro << FG_BLUE;
	for (t_list_iter::const_iterator it = list.begin(); it != list.end(); ++it)
		std::cout << " " << *(*it);
	std::cout << std::endl;
}

void insertion(t_list & data, size_t nbr_element, size_t element_size)
{
	(void)data;
	(void)nbr_element;
	(void)element_size;
	size_t main_nbr_element = 1 + nbr_element / 2;
	size_t pend_nbr_element = nbr_element - main_nbr_element;

	displayLevel(element_size);
	displayByPair(FG_PURPLE "sorted :", data, element_size);
	std::cout << FG_PURPLE "nbr_element: " FG_BLUE << nbr_element << FG_PURPLE "\nmain_nbr_element: " FG_BLUE << main_nbr_element << FG_PURPLE "\npend_nbr_element: " FG_BLUE << pend_nbr_element << RESET << std::endl;
	
	std::list<t_list::iterator> main; // store itrator of first lowest and all bigest element from data
	std::list<t_list::iterator> pend; // store itrator of lowest element from data except the first
	t_list::iterator it = data.begin();
	std::advance(it, element_size - 1); // b1
	main.push_back(it);
	for (size_t i = 1; i < nbr_element; ++i)
	{
		std::advance(it, element_size); // a1, a2, a3, ...
		main.push_back(it);
		if (++i >= nbr_element)
			break;
		std::advance(it, element_size); // b2, b3, ...
		pend.push_back(it);
	}
	display(FG_PURPLE "main :", main);
	display(FG_PURPLE "pend :", pend);

	
	
	// main.push_back(listMoveIterator(data.begin(), element_size - 1));
	
	// t_list::iterator first = listMoveIterator(data.begin(), 2 * element_size);
	// for (size_t i = 0; i < pend_nbr_element; ++i)
	// {
	// 	t_list::iterator last = listMoveIterator(first, element_size);
	// 	t_list tmp;
	// 	tmp.splice(tmp.end(), data, first, last);
	// 	pend.push_back(tmp);
	// 	first = listMoveIterator(last, element_size);
	// 	// displayByPair(FG_PURPLE "pend :", pend, element_size);
	// }
	
	// in main, insert index of lowest element from data
	size_t i_jacob = 3;
	size_t search_range = 1;
	while (pend.size() > 0)
	{
		
		std::cout << "==============================================" << std::endl;
		size_t nbr_to_insert = jacobsthal(i_jacob++);
		if (nbr_to_insert > pend.size())
			nbr_to_insert = pend.size();
		std::cout << "nbr_to_insert: " << nbr_to_insert << std::endl;

		search_range = (search_range + 1) * 2 - 1;
		if (search_range > main.size())
			search_range = main.size();
		std::cout << "search_range: " << search_range << std::endl;

		
		for (size_t i = nbr_to_insert; i > 0; --i)
		{
			std::cout << "-----------------------------------------" << std::endl;
			std::cout << "nbr_to_insert: " << nbr_to_insert << std::endl;
			
			t_list_iter::iterator it_pend = pend.begin();
			std::advance(it_pend, nbr_to_insert - 1);
			std::cout << "it_pend: " << *(*it_pend) << std::endl;

			// insert
			t_list_iter::iterator right = main.begin();
			std::advance(right, search_range - 1);

			t_list_iter::iterator main_it_to_insert = binarySearch(main.begin(), right, *(*it_pend));
			main.splice(main_it_to_insert, pend, it_pend);

			display(FG_PURPLE "main :", main);
			display(FG_PURPLE "pend :", pend);
			--nbr_to_insert;
		}
	}
	
}

void PmergeMe::sort(t_list & data, int element_size)
{
	int nbrElement = data.size() / element_size;
	if (nbrElement < 2)
		return ;
		
	displayLevel(element_size);
	displayByPair(FG_PURPLE "to sort:", data, element_size);
	// std::cout << "element_size: " << element_size << std::endl;
	
	std::pair<t_list::iterator, t_list::iterator> it_elem_first;
	std::pair<t_list::iterator, t_list::iterator> it_elem_second;
	it_elem_first.first = data.begin();
	
	int pairLength = element_size * 2;
	for (int i = 0; i < nbrElement; i += 2)
	{
		it_elem_first.second = it_elem_first.first;
		std::advance(it_elem_first.second, element_size - 1);
		it_elem_second.first = it_elem_first.second;
		it_elem_second.first++;
		it_elem_second.second = it_elem_second.first;
		std::advance(it_elem_second.second, element_size - 1);
		
		// std::cout << "elem first first:" << *it_elem_first.first << " second:" << *it_elem_first.second << " elem second first:" << *it_elem_second.first << " second:" << *it_elem_second.second << std::endl;
		
		if (*it_elem_second.second < *it_elem_first.second)
		{
			// ++it_elem_second.second;
			// std::cout << FG_YELLOW "swap " RESET << *it_elem_first.first << FG_YELLOW " to " RESET << *it_elem_first.second << FG_YELLOW " with " RESET << *it_elem_second.first << FG_YELLOW" to " RESET << *it_elem_second.second << std::endl;
			data.splice(it_elem_first.first, data, it_elem_second.first, ++it_elem_second.second);
			std::advance(it_elem_first.first, element_size);
		}
		else
		{
			// std::cout << "it_elem_first.first: " << *it_elem_first.first;
			std::advance(it_elem_first.first, pairLength - 1);
			// std::cout << " after add paeirlenght -1, it_elem_first.first: " << *it_elem_first.first << std::endl;
		}
		
		// displayByPair(FG_PURPLE "sorted :", data, element_size);
	}

	displayByPair(FG_PURPLE "sorted :", data, element_size);

	sort(data, element_size * 2);

	if (nbrElement < 3)
		return ;
	insertion(data, nbrElement, element_size);
}

void PmergeMe::mergeInsertSort(t_vector & data)
{
	sort(data, 1);
}

void PmergeMe::mergeInsertSort(t_list & data)
{
	sort(data, 1);
}
