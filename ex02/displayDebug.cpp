/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:09:10 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 01:19:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "displayDebug.hpp"

void displayPendValue(const std::string & intro, const t_vector & data, const t_vector &pend)
{
	std::cout << intro << FG_BLUE;
	for (size_t i = 0; i < pend.size(); ++i)
		std::cout  << " " << data[pend[i]];
	std::cout << RESET << std::endl;
}

const std::string getPairColor(size_t index, size_t element_size, size_t total_size)
{
	
	bool is_in_pair = total_size - index >= (element_size * 2);
	if (!is_in_pair)
		return FG_PURPLE;

	bool start_pair = index % (element_size * 2) == 0;
	if (start_pair)
		return FG_GREEN;
	return FG_YELLOW;
}

bool is_first_in_element(size_t index, size_t element_size)
{
	return index % element_size == 0;
}

bool is_last_in_element(size_t index, size_t element_size)
{
	return (index + 1) % element_size == 0;
}

void displayLevel(size_t element_size)
{
	std::ostringstream oss;
	oss << "sort - element_size: " << element_size;
	displaySubtest(std::string(oss.str()), FG_PURPLE);
}

void displayVector(std::vector<int> & data)
{
	size_t i;
	for (i = 0; i < data.size() - 1; ++i)
		std::cout << data[i] << " ";
	std::cout << data[i];
}
