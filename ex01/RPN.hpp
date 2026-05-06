/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 15:29:27 by rnovotny          #+#    #+#             */
/*   Updated: 2026/05/06 19:36:55 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>
# include <sstream>
# include <stdexcept>
# include <cstdlib>

class RPN
{
private:
	std::stack<long> _stack;
	
	RPN();
	
public:
	RPN(const std::string& expression);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();
	
	long calculate();
	
private:
	bool isOperator(char c) const;
	bool isNumber(const std::string& token) const;
	long performOperation(long a, long b, char op);
};

#endif