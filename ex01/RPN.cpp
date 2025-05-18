/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:38:59 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/18 17:05:56 by svogrig          ###   ########.fr       */
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

void RPN::compute(std::stack<int> & stack, char operation)
{
	if (stack.size() < 2)
		throw std::runtime_error("Error: not enought number in the stack");

	int b = stack.top();
	stack.pop();
	int a = stack.top();
	stack.pop();

	if (operation == '+')
		stack.push(a + b);
	if (operation == '-')
		stack.push(a - b);
	if (operation == '*')
		stack.push(a * b);
	if (operation == '/')
	{
		if (b == 0)
			throw std::runtime_error("Error: divide by zero");
		stack.push(a / b);
	}
}

bool RPN::isOperator(char c)
{
	return c == '+' || c == '-' || c== '*' || c == '/';
}

void RPN::process(const std::string & str)
{
	try
	{
		if (str.empty())
			throw std::runtime_error("Error: expression is empty");

		std::stack<int> stack;

		for (size_t i = 0; i < str.size(); ++i)
		{
			char c = str[i];

			if (std::isdigit(c))
				stack.push(c - '0');
			else if (isOperator(c))
				compute(stack, c);
			else if (isblank(c))
				;
			else
				throw std::runtime_error("Error");
		}

		if (stack.size() != 1)
			throw std::runtime_error("Error");
	
		std::cout << stack.top() << std::endl;
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << e.what() << '\n';
	}
}
