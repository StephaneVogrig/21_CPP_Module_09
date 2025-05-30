/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:39:25 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 17:57:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <string>
# include <stdexcept>
# include <cctype>
# include <sstream>
# include "shellColor.hpp"

class RPN
{
	private:

		RPN();
		RPN(const RPN & toCopy);
		~RPN();
		RPN & operator = (const RPN & toAssign);

		static void compute(std::stack<int> & stack, std::string token);

	public:

		static void process(const std::string & str);

};

#endif