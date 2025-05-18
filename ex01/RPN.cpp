/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:59 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 17:58:57 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN & toCopy)
{
	(void)toCopy;
}

RPN::~RPN()
{}

RPN & RPN::operator = (const RPN & toAssign)
{
	(void)toAssign;
	return *this;
}

void RPN::compute(std::stack<int> & stack, std::string token)
{
	if (stack.size() < 2)
		throw std::runtime_error("Error: not enough operand");

	int b = stack.top();
	stack.pop();
	int a = stack.top();
	stack.pop();

	if (token == "+")
		stack.push(a + b);
	else if (token == "-")
		stack.push(a - b);
	else if (token == "*")
		stack.push(a * b);
	else if (token == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error: divide by zero");
		stack.push(a / b);
	}
	else
		throw std::runtime_error("Error: unknow operator => " RESET + token);
}

void RPN::process(const std::string & str)
{
	try
	{
		if (str.empty())
			throw std::runtime_error("Error: expression is empty");

		std::stack<int> stack;
		std::istringstream iss(str);

		std::string token;
		while (iss >> token)
		{
			if (token.length() > 1)
				throw std::runtime_error("Error: too many characters => " RESET + token);
			
			if (std::isdigit(token[0]))
				stack.push(token[0] - '0');
			else
				compute(stack, token);
		}

		if (stack.size() != 1)
			throw std::runtime_error("Error: too many operands");
	
		std::cout << stack.top() << std::endl;
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << FG_RED << e.what() << RESET << '\n';
	}
}
