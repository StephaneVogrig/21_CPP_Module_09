/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:08:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 21:41:28 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYDEBUG_HPP
# define DISPLAYDEBUG_HPP

#include "utils.hpp"

const std::string getPairColor(size_t index, size_t element_size, size_t total_size);
bool isFirstInElement(size_t index, size_t element_size);
bool isLastInElement(size_t index, size_t element_size);

template <typename T>
void displayByPair(const std::string & intro, const T & data, size_t element_size)
{
	std::cout << intro;
	
	typename T::const_iterator it = data.begin();
	for (size_t i = 0; i < data.size(); ++i)
	{
		if (isFirstInElement(i, element_size))
			std::cout << getPairColor(i, element_size, data.size());
		
		if (isLastInElement(i, element_size))
			std::cout << ' ' << BOLD_ON << *it << BOLD_OFF;
		else
			std::cout << ' ' << *it;
		++it;
	}	
	std::cout <<  RESET << std::endl;
}

void displayLevel(size_t element_size);
void displayVectorIndex(const std::string & intro, const t_vector & data, const t_vector &pend);
void displayListList(const std::string & intro, const t_list_of_list & list);

#endif
