/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:27:07 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 16:22:46 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "RPN.hpp"

int main(int argc, char ** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << *argv << " <expression>" << std::endl;
		return (EXIT_FAILURE);
	}
	
	RPN::process(std::string(argv[1]));
	
	return EXIT_SUCCESS;
}
