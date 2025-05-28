/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:09:10 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 21:33:36 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "displayDebug.hpp"

void displayVectorIndex(const std::string & intro, const t_vector & data, const t_vector &pend)
{
	std::cout << intro << FG_BLUE;
	for (size_t i = 0; i < pend.size(); ++i)
		std::cout  << " " << data[pend[i]];
	std::cout << RESET << std::endl;
}

const std::string getPairColor(size_t index, size_t element_size, size_t total_size)
{
	bool is_start_of_pair = index % (element_size * 2) == 0;
	if (is_start_of_pair)
	{
		bool is_pair_complete = total_size - index >= (element_size * 2);
		return is_pair_complete? FG_GREEN : FG_PURPLE;
	}
	bool is_element_complete = total_size - index >= (element_size);
	return is_element_complete ? FG_YELLOW : FG_PURPLE;
}

bool isFirstInElement(size_t index, size_t element_size)
{
	return index % element_size == 0;
}

bool isLastInElement(size_t index, size_t element_size)
{
	return (index + 1) % element_size == 0;
}

void displayLevel(size_t element_size)
{
	std::ostringstream oss;
	oss << "sort - element_size: " << element_size;
	displaySubtest(std::string(oss.str()), FG_PURPLE);
}

void displayListList(const std::string & intro, const t_list_of_list & list)
{
	std::cout << FG_PURPLE << intro << FG_BLUE;
	for (t_list_of_list::const_iterator it = list.begin(); it != list.end(); ++it)
		std::cout << " " << it->back();
	std::cout << std::endl;
}
