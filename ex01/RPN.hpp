/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:39:25 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 16:54:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <string>
# include <stdexcept>
# include <cctype>

class RPN
{
	private:

		RPN();
		RPN(const RPN & toCopy);
		~RPN();
		RPN & operator = (const RPN & toAssign);

		static bool isOperator(char c);
		static void compute(std::stack<int> & stack, char operation);

	public:

		static void process(const std::string & str);

};

#endif