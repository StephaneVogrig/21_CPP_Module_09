/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:08:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 04:32:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYDEBUG_HPP
# define DISPLAYDEBUG_HPP

#include "PmergeMe.hpp"
#include "utils.hpp"

const std::string getPairColor(size_t index, size_t element_size, size_t total_size);
bool is_first_in_element(size_t index, size_t element_size);
bool is_last_in_element(size_t index, size_t element_size);

template <typename T>
void displayByPair(const std::string & intro, const T & data, size_t element_size)
{
	std::cout << intro;
	
	typename T::const_iterator it = data.begin();
	for (size_t i = 0; i < data.size(); ++i)
	{
		if (is_first_in_element(i, element_size))
			std::cout << getPairColor(i, element_size, data.size());
		
		if (is_last_in_element(i, element_size))
			std::cout << BOLD_ON << *it << BOLD_OFF << ' ';
		else
			std::cout << *it << ' ';
		++it;
	}	
	std::cout <<  RESET << std::endl;
}

void displayPendValue(const std::string & intro, const t_vector & data, const t_vector &pend);
void displayLevel(size_t element_size);
void displayVector(std::vector<int> & data);
void displayListList(const std::string & intro, const t_list_of_list & list);

#endif
