/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:42 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/06 19:36:50 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string& expression)
{
	std::istringstream iss(expression);
	std::string token;
	
	while (iss >> token)
	{
		if (token.length() == 1 && isOperator(token[0]))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Invalid expression");
			
			long b = _stack.top();
			_stack.pop();
			long a = _stack.top();
			_stack.pop();
			
			long result = performOperation(a, b, token[0]);
			_stack.push(result);
		}
		else if (isNumber(token))
		{
			long num = std::atol(token.c_str());
			if (num >= 10 || num < 0)
				throw std::runtime_error("Number must be < 10");
			_stack.push(num);
		}
		else
		{
			throw std::runtime_error("Invalid token");
		}
	}
}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

long RPN::calculate()
{
	if (_stack.size() != 1)
		throw std::runtime_error("Invalid expression");
	return _stack.top();
}

bool RPN::isOperator(char c) const
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::isNumber(const std::string& token) const
{
	if (token.empty())
		return false;
	
	for (size_t i = 0; i < token.length(); ++i)
	{
		if (!isdigit(token[i]))
			return false;
	}
	
	return true;
}

long RPN::performOperation(long a, long b, char op)
{
	switch (op)
	{
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("Division by zero");
			return a / b;
		default:
			throw std::runtime_error("Invalid operator");
	}
}