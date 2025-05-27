/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:09:10 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/26 18:46:27 by svogrig          ###   ########.fr       */
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
void displayVectorByPair(const std::string & intro, const t_vector & vector, size_t elementSize)
{
	std::cout << intro;
	
	size_t i = 0;
	bool is_in_pair = false;
	for (i = 0; i < vector.size(); ++i)
	{
		bool start_pair = i % (elementSize * 2) == 0;
		if (start_pair)
			is_in_pair = vector.size() - i >= (elementSize * 2);
		
		if (i % elementSize == 0)
		{
			if (!is_in_pair)
				std::cout << " " FG_PURPLE;
			else if (start_pair)
				std::cout << " " FG_GREEN;
			else
				std::cout << FG_YELLOW;
		}
		if ((i + 1) % elementSize == 0)
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

void displayVector(std::vector<int> & data)
{
	size_t i;
	for (i = 0; i < data.size() - 1; ++i)
		std::cout << data[i] << " ";
	std::cout << data[i];
}
