/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:08:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/27 23:54:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYDEBUG_HPP
# define DISPLAYDEBUG_HPP

#include "PmergeMe.hpp"
#include "utils.hpp"

template <typename T>
void displayByPair(const std::string & intro, const T & data, size_t element_size)
{
	std::cout << intro;
	
	bool is_in_pair = false;
	typename T::const_iterator it = data.begin();
	for (size_t i = 0; i < data.size(); ++i)
	{
		bool start_pair = i % (element_size * 2) == 0;
		if (start_pair)
			is_in_pair = data.size() - i >= (element_size * 2);
		
		if (i % element_size == 0)
		{
			if (!is_in_pair)
				std::cout << " " FG_PURPLE;
			else if (start_pair)
				std::cout << " " FG_GREEN;
			else
				std::cout << FG_YELLOW;
		}
		if ((i + 1) % element_size == 0)
			std::cout << BOLD_ON << *it << BOLD_OFF << ' ';
		else
			std::cout << *it << ' ';
		it++;
	}
	std::cout <<  RESET << std::endl;
}

void displayPendValue(const std::string & intro, const t_vector & data, const t_vector &pend);
void displayVectorByPair(const std::string & intro, const t_vector & vector, size_t element_size);
void displayLevel(size_t element_size);
void displayVector(std::vector<int> & data);

#endif
