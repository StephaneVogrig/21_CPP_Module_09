/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 03:28:39 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 20:34:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <climits>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <list>
# include <string>
# include <time.h>
# include <vector>

# include "PmergeMe.hpp"
# include "shellColor.hpp"

# define PRINT_WIDTH 80

template <typename T>
void displayContainer(const std::string & str, const T container)
{
	std::cout << str;
	for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
		std::cout << " " << *it;
	std::cout << '\n';
}

void argvToVector(int argc, char ** argv, std::vector<int> & input);
void displayTime(size_t size, const std::string & str, clock_t clock);
void displaySection(const std::string & title, const std::string & color = FG_GREEN);
void displaySubtest(const std::string & title, const std::string & color = FG_GREEN);

#endif
